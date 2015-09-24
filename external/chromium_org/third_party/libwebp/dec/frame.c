// Copyright 2010 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#include <stdlib.h>
#include "./vp8i.h"
#include "../utils/utils.h"

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

#define ALIGN_MASK (32 - 1)


// Simple filter:  up to 2 luma samples are read and 1 is written.
// Complex filter: up to 4 luma samples are read and 3 are written. Same for
static const uint8_t kFilterExtraRows[3] = { 0, 2, 8 };

static WEBP_INLINE int hev_thresh_from_level(int level, int keyframe) {
  if (keyframe) {
    return (level >= 40) ? 2 : (level >= 15) ? 1 : 0;
  } else {
    return (level >= 40) ? 3 : (level >= 20) ? 2 : (level >= 15) ? 1 : 0;
  }
}

static void DoFilter(const VP8Decoder* const dec, int mb_x, int mb_y) {
  const VP8ThreadContext* const ctx = &dec->thread_ctx_;
  const int y_bps = dec->cache_y_stride_;
  VP8FInfo* const f_info = ctx->f_info_ + mb_x;
  uint8_t* const y_dst = dec->cache_y_ + ctx->id_ * 16 * y_bps + mb_x * 16;
  const int level = f_info->f_level_;
  const int ilevel = f_info->f_ilevel_;
  const int limit = 2 * level + ilevel;
  if (level == 0) {
    return;
  }
  if (dec->filter_type_ == 1) {   
    if (mb_x > 0) {
      VP8SimpleHFilter16(y_dst, y_bps, limit + 4);
    }
    if (f_info->f_inner_) {
      VP8SimpleHFilter16i(y_dst, y_bps, limit);
    }
    if (mb_y > 0) {
      VP8SimpleVFilter16(y_dst, y_bps, limit + 4);
    }
    if (f_info->f_inner_) {
      VP8SimpleVFilter16i(y_dst, y_bps, limit);
    }
  } else {    
    const int uv_bps = dec->cache_uv_stride_;
    uint8_t* const u_dst = dec->cache_u_ + ctx->id_ * 8 * uv_bps + mb_x * 8;
    uint8_t* const v_dst = dec->cache_v_ + ctx->id_ * 8 * uv_bps + mb_x * 8;
    const int hev_thresh =
        hev_thresh_from_level(level, dec->frm_hdr_.key_frame_);
    if (mb_x > 0) {
      VP8HFilter16(y_dst, y_bps, limit + 4, ilevel, hev_thresh);
      VP8HFilter8(u_dst, v_dst, uv_bps, limit + 4, ilevel, hev_thresh);
    }
    if (f_info->f_inner_) {
      VP8HFilter16i(y_dst, y_bps, limit, ilevel, hev_thresh);
      VP8HFilter8i(u_dst, v_dst, uv_bps, limit, ilevel, hev_thresh);
    }
    if (mb_y > 0) {
      VP8VFilter16(y_dst, y_bps, limit + 4, ilevel, hev_thresh);
      VP8VFilter8(u_dst, v_dst, uv_bps, limit + 4, ilevel, hev_thresh);
    }
    if (f_info->f_inner_) {
      VP8VFilter16i(y_dst, y_bps, limit, ilevel, hev_thresh);
      VP8VFilter8i(u_dst, v_dst, uv_bps, limit, ilevel, hev_thresh);
    }
  }
}

static void FilterRow(const VP8Decoder* const dec) {
  int mb_x;
  const int mb_y = dec->thread_ctx_.mb_y_;
  assert(dec->thread_ctx_.filter_row_);
  for (mb_x = dec->tl_mb_x_; mb_x < dec->br_mb_x_; ++mb_x) {
    DoFilter(dec, mb_x, mb_y);
  }
}


static void PrecomputeFilterStrengths(VP8Decoder* const dec) {
  if (dec->filter_type_ > 0) {
    int s;
    const VP8FilterHeader* const hdr = &dec->filter_hdr_;
    for (s = 0; s < NUM_MB_SEGMENTS; ++s) {
      int i4x4;
      
      int base_level;
      if (dec->segment_hdr_.use_segment_) {
        base_level = dec->segment_hdr_.filter_strength_[s];
        if (!dec->segment_hdr_.absolute_delta_) {
          base_level += hdr->level_;
        }
      } else {
        base_level = hdr->level_;
      }
      for (i4x4 = 0; i4x4 <= 1; ++i4x4) {
        VP8FInfo* const info = &dec->fstrengths_[s][i4x4];
        int level = base_level;
        if (hdr->use_lf_delta_) {
          
          level += hdr->ref_lf_delta_[0];
          if (i4x4) {
            level += hdr->mode_lf_delta_[0];
          }
        }
        level = (level < 0) ? 0 : (level > 63) ? 63 : level;
        info->f_level_ = level;

        if (hdr->sharpness_ > 0) {
          if (hdr->sharpness_ > 4) {
            level >>= 2;
          } else {
            level >>= 1;
          }
          if (level > 9 - hdr->sharpness_) {
            level = 9 - hdr->sharpness_;
          }
        }
        info->f_ilevel_ = (level < 1) ? 1 : level;
        info->f_inner_ = 0;
      }
    }
  }
}


#define MACROBLOCK_VPOS(mb_y)  ((mb_y) * 16)    

static int FinishRow(VP8Decoder* const dec, VP8Io* const io) {
  int ok = 1;
  const VP8ThreadContext* const ctx = &dec->thread_ctx_;
  const int extra_y_rows = kFilterExtraRows[dec->filter_type_];
  const int ysize = extra_y_rows * dec->cache_y_stride_;
  const int uvsize = (extra_y_rows / 2) * dec->cache_uv_stride_;
  const int y_offset = ctx->id_ * 16 * dec->cache_y_stride_;
  const int uv_offset = ctx->id_ * 8 * dec->cache_uv_stride_;
  uint8_t* const ydst = dec->cache_y_ - ysize + y_offset;
  uint8_t* const udst = dec->cache_u_ - uvsize + uv_offset;
  uint8_t* const vdst = dec->cache_v_ - uvsize + uv_offset;
  const int first_row = (ctx->mb_y_ == 0);
  const int last_row = (ctx->mb_y_ >= dec->br_mb_y_ - 1);
  int y_start = MACROBLOCK_VPOS(ctx->mb_y_);
  int y_end = MACROBLOCK_VPOS(ctx->mb_y_ + 1);

  if (ctx->filter_row_) {
    FilterRow(dec);
  }

  if (io->put) {
    if (!first_row) {
      y_start -= extra_y_rows;
      io->y = ydst;
      io->u = udst;
      io->v = vdst;
    } else {
      io->y = dec->cache_y_ + y_offset;
      io->u = dec->cache_u_ + uv_offset;
      io->v = dec->cache_v_ + uv_offset;
    }

    if (!last_row) {
      y_end -= extra_y_rows;
    }
    if (y_end > io->crop_bottom) {
      y_end = io->crop_bottom;    
    }
    io->a = NULL;
    if (dec->alpha_data_ != NULL && y_start < y_end) {
      
      
      
      
      
      io->a = VP8DecompressAlphaRows(dec, y_start, y_end - y_start);
      if (io->a == NULL) {
        return VP8SetError(dec, VP8_STATUS_BITSTREAM_ERROR,
                           "Could not decode alpha data.");
      }
    }
    if (y_start < io->crop_top) {
      const int delta_y = io->crop_top - y_start;
      y_start = io->crop_top;
      assert(!(delta_y & 1));
      io->y += dec->cache_y_stride_ * delta_y;
      io->u += dec->cache_uv_stride_ * (delta_y >> 1);
      io->v += dec->cache_uv_stride_ * (delta_y >> 1);
      if (io->a != NULL) {
        io->a += io->width * delta_y;
      }
    }
    if (y_start < y_end) {
      io->y += io->crop_left;
      io->u += io->crop_left >> 1;
      io->v += io->crop_left >> 1;
      if (io->a != NULL) {
        io->a += io->crop_left;
      }
      io->mb_y = y_start - io->crop_top;
      io->mb_w = io->crop_right - io->crop_left;
      io->mb_h = y_end - y_start;
      ok = io->put(io);
    }
  }
  
  if (ctx->id_ + 1 == dec->num_caches_) {
    if (!last_row) {
      memcpy(dec->cache_y_ - ysize, ydst + 16 * dec->cache_y_stride_, ysize);
      memcpy(dec->cache_u_ - uvsize, udst + 8 * dec->cache_uv_stride_, uvsize);
      memcpy(dec->cache_v_ - uvsize, vdst + 8 * dec->cache_uv_stride_, uvsize);
    }
  }

  return ok;
}

#undef MACROBLOCK_VPOS


int VP8ProcessRow(VP8Decoder* const dec, VP8Io* const io) {
  int ok = 1;
  VP8ThreadContext* const ctx = &dec->thread_ctx_;
  if (!dec->use_threads_) {
    
    ctx->mb_y_ = dec->mb_y_;
    ctx->filter_row_ = dec->filter_row_;
    ok = FinishRow(dec, io);
  } else {
    WebPWorker* const worker = &dec->worker_;
    
    ok &= WebPWorkerSync(worker);
    assert(worker->status_ == OK);
    if (ok) {   
      ctx->io_ = *io;
      ctx->id_ = dec->cache_id_;
      ctx->mb_y_ = dec->mb_y_;
      ctx->filter_row_ = dec->filter_row_;
      if (ctx->filter_row_) {    
        VP8FInfo* const tmp = ctx->f_info_;
        ctx->f_info_ = dec->f_info_;
        dec->f_info_ = tmp;
      }
      WebPWorkerLaunch(worker);
      if (++dec->cache_id_ == dec->num_caches_) {
        dec->cache_id_ = 0;
      }
    }
  }
  return ok;
}


VP8StatusCode VP8EnterCritical(VP8Decoder* const dec, VP8Io* const io) {
  
  
  if (io->setup && !io->setup(io)) {
    VP8SetError(dec, VP8_STATUS_USER_ABORT, "Frame setup failed");
    return dec->status_;
  }

  
  if (io->bypass_filtering) {
    dec->filter_type_ = 0;
  }
  

  
  
  
  
  
  
  
  
  
  
  
  {
    const int extra_pixels = kFilterExtraRows[dec->filter_type_];
    if (dec->filter_type_ == 2) {
      
      dec->tl_mb_x_ = 0;
      dec->tl_mb_y_ = 0;
    } else {
      
      
      
      
      dec->tl_mb_x_ = (io->crop_left - extra_pixels) >> 4;
      dec->tl_mb_y_ = (io->crop_top - extra_pixels) >> 4;
      if (dec->tl_mb_x_ < 0) dec->tl_mb_x_ = 0;
      if (dec->tl_mb_y_ < 0) dec->tl_mb_y_ = 0;
    }
    
    dec->br_mb_y_ = (io->crop_bottom + 15 + extra_pixels) >> 4;
    dec->br_mb_x_ = (io->crop_right + 15 + extra_pixels) >> 4;
    if (dec->br_mb_x_ > dec->mb_w_) {
      dec->br_mb_x_ = dec->mb_w_;
    }
    if (dec->br_mb_y_ > dec->mb_h_) {
      dec->br_mb_y_ = dec->mb_h_;
    }
  }
  PrecomputeFilterStrengths(dec);
  return VP8_STATUS_OK;
}

int VP8ExitCritical(VP8Decoder* const dec, VP8Io* const io) {
  int ok = 1;
  if (dec->use_threads_) {
    ok = WebPWorkerSync(&dec->worker_);
  }

  if (io->teardown) {
    io->teardown(io);
  }
  return ok;
}


#define MT_CACHE_LINES 3
#define ST_CACHE_LINES 1   

static int InitThreadContext(VP8Decoder* const dec) {
  dec->cache_id_ = 0;
  if (dec->use_threads_) {
    WebPWorker* const worker = &dec->worker_;
    if (!WebPWorkerReset(worker)) {
      return VP8SetError(dec, VP8_STATUS_OUT_OF_MEMORY,
                         "thread initialization failed.");
    }
    worker->data1 = dec;
    worker->data2 = (void*)&dec->thread_ctx_.io_;
    worker->hook = (WebPWorkerHook)FinishRow;
    dec->num_caches_ =
      (dec->filter_type_ > 0) ? MT_CACHE_LINES : MT_CACHE_LINES - 1;
  } else {
    dec->num_caches_ = ST_CACHE_LINES;
  }
  return 1;
}

#undef MT_CACHE_LINES
#undef ST_CACHE_LINES


static int AllocateMemory(VP8Decoder* const dec) {
  const int num_caches = dec->num_caches_;
  const int mb_w = dec->mb_w_;
  
  const size_t intra_pred_mode_size = 4 * mb_w * sizeof(uint8_t);
  const size_t top_size = (16 + 8 + 8) * mb_w;
  const size_t mb_info_size = (mb_w + 1) * sizeof(VP8MB);
  const size_t f_info_size =
      (dec->filter_type_ > 0) ?
          mb_w * (dec->use_threads_ ? 2 : 1) * sizeof(VP8FInfo)
        : 0;
  const size_t yuv_size = YUV_SIZE * sizeof(*dec->yuv_b_);
  const size_t coeffs_size = 384 * sizeof(*dec->coeffs_);
  const size_t cache_height = (16 * num_caches
                            + kFilterExtraRows[dec->filter_type_]) * 3 / 2;
  const size_t cache_size = top_size * cache_height;
  
  const uint64_t alpha_size = (dec->alpha_data_ != NULL) ?
      (uint64_t)dec->pic_hdr_.width_ * dec->pic_hdr_.height_ : 0ULL;
  const uint64_t needed = (uint64_t)intra_pred_mode_size
                        + top_size + mb_info_size + f_info_size
                        + yuv_size + coeffs_size
                        + cache_size + alpha_size + ALIGN_MASK;
  uint8_t* mem;

  if (needed != (size_t)needed) return 0;  
  if (needed > dec->mem_size_) {
    free(dec->mem_);
    dec->mem_size_ = 0;
    dec->mem_ = WebPSafeMalloc(needed, sizeof(uint8_t));
    if (dec->mem_ == NULL) {
      return VP8SetError(dec, VP8_STATUS_OUT_OF_MEMORY,
                         "no memory during frame initialization.");
    }
    
    dec->mem_size_ = (size_t)needed;
  }

  mem = (uint8_t*)dec->mem_;
  dec->intra_t_ = (uint8_t*)mem;
  mem += intra_pred_mode_size;

  dec->y_t_ = (uint8_t*)mem;
  mem += 16 * mb_w;
  dec->u_t_ = (uint8_t*)mem;
  mem += 8 * mb_w;
  dec->v_t_ = (uint8_t*)mem;
  mem += 8 * mb_w;

  dec->mb_info_ = ((VP8MB*)mem) + 1;
  mem += mb_info_size;

  dec->f_info_ = f_info_size ? (VP8FInfo*)mem : NULL;
  mem += f_info_size;
  dec->thread_ctx_.id_ = 0;
  dec->thread_ctx_.f_info_ = dec->f_info_;
  if (dec->use_threads_) {
    
    
    
    dec->thread_ctx_.f_info_ += mb_w;
  }

  mem = (uint8_t*)((uintptr_t)(mem + ALIGN_MASK) & ~ALIGN_MASK);
  assert((yuv_size & ALIGN_MASK) == 0);
  dec->yuv_b_ = (uint8_t*)mem;
  mem += yuv_size;

  dec->coeffs_ = (int16_t*)mem;
  mem += coeffs_size;

  dec->cache_y_stride_ = 16 * mb_w;
  dec->cache_uv_stride_ = 8 * mb_w;
  {
    const int extra_rows = kFilterExtraRows[dec->filter_type_];
    const int extra_y = extra_rows * dec->cache_y_stride_;
    const int extra_uv = (extra_rows / 2) * dec->cache_uv_stride_;
    dec->cache_y_ = ((uint8_t*)mem) + extra_y;
    dec->cache_u_ = dec->cache_y_
                  + 16 * num_caches * dec->cache_y_stride_ + extra_uv;
    dec->cache_v_ = dec->cache_u_
                  + 8 * num_caches * dec->cache_uv_stride_ + extra_uv;
    dec->cache_id_ = 0;
  }
  mem += cache_size;

  
  dec->alpha_plane_ = alpha_size ? (uint8_t*)mem : NULL;
  mem += alpha_size;
  assert(mem <= (uint8_t*)dec->mem_ + dec->mem_size_);

  
  memset(dec->mb_info_ - 1, 0, mb_info_size);

  
  memset(dec->intra_t_, B_DC_PRED, intra_pred_mode_size);

  return 1;
}

static void InitIo(VP8Decoder* const dec, VP8Io* io) {
  
  io->mb_y = 0;
  io->y = dec->cache_y_;
  io->u = dec->cache_u_;
  io->v = dec->cache_v_;
  io->y_stride = dec->cache_y_stride_;
  io->uv_stride = dec->cache_uv_stride_;
  io->a = NULL;
}

int VP8InitFrame(VP8Decoder* const dec, VP8Io* io) {
  if (!InitThreadContext(dec)) return 0;  
  if (!AllocateMemory(dec)) return 0;
  InitIo(dec, io);
  VP8DspInit();  
  return 1;
}


static const int kScan[16] = {
  0 +  0 * BPS,  4 +  0 * BPS, 8 +  0 * BPS, 12 +  0 * BPS,
  0 +  4 * BPS,  4 +  4 * BPS, 8 +  4 * BPS, 12 +  4 * BPS,
  0 +  8 * BPS,  4 +  8 * BPS, 8 +  8 * BPS, 12 +  8 * BPS,
  0 + 12 * BPS,  4 + 12 * BPS, 8 + 12 * BPS, 12 + 12 * BPS
};

static WEBP_INLINE int CheckMode(VP8Decoder* const dec, int mode) {
  if (mode == B_DC_PRED) {
    if (dec->mb_x_ == 0) {
      return (dec->mb_y_ == 0) ? B_DC_PRED_NOTOPLEFT : B_DC_PRED_NOLEFT;
    } else {
      return (dec->mb_y_ == 0) ? B_DC_PRED_NOTOP : B_DC_PRED;
    }
  }
  return mode;
}

static WEBP_INLINE void Copy32b(uint8_t* dst, uint8_t* src) {
  *(uint32_t*)dst = *(uint32_t*)src;
}

void VP8ReconstructBlock(VP8Decoder* const dec) {
  int j;
  uint8_t* const y_dst = dec->yuv_b_ + Y_OFF;
  uint8_t* const u_dst = dec->yuv_b_ + U_OFF;
  uint8_t* const v_dst = dec->yuv_b_ + V_OFF;

  
  
  if (dec->mb_x_ > 0) {
    for (j = -1; j < 16; ++j) {
      Copy32b(&y_dst[j * BPS - 4], &y_dst[j * BPS + 12]);
    }
    for (j = -1; j < 8; ++j) {
      Copy32b(&u_dst[j * BPS - 4], &u_dst[j * BPS + 4]);
      Copy32b(&v_dst[j * BPS - 4], &v_dst[j * BPS + 4]);
    }
  } else {
    for (j = 0; j < 16; ++j) {
      y_dst[j * BPS - 1] = 129;
    }
    for (j = 0; j < 8; ++j) {
      u_dst[j * BPS - 1] = 129;
      v_dst[j * BPS - 1] = 129;
    }
    
    if (dec->mb_y_ > 0) {
      y_dst[-1 - BPS] = u_dst[-1 - BPS] = v_dst[-1 - BPS] = 129;
    }
  }
  {
    
    uint8_t* const top_y = dec->y_t_ + dec->mb_x_ * 16;
    uint8_t* const top_u = dec->u_t_ + dec->mb_x_ * 8;
    uint8_t* const top_v = dec->v_t_ + dec->mb_x_ * 8;
    const int16_t* coeffs = dec->coeffs_;
    int n;

    if (dec->mb_y_ > 0) {
      memcpy(y_dst - BPS, top_y, 16);
      memcpy(u_dst - BPS, top_u, 8);
      memcpy(v_dst - BPS, top_v, 8);
    } else if (dec->mb_x_ == 0) {
      
      
      memset(y_dst - BPS - 1, 127, 16 + 4 + 1);
      memset(u_dst - BPS - 1, 127, 8 + 1);
      memset(v_dst - BPS - 1, 127, 8 + 1);
    }

    

    if (dec->is_i4x4_) {   
      uint32_t* const top_right = (uint32_t*)(y_dst - BPS + 16);

      if (dec->mb_y_ > 0) {
        if (dec->mb_x_ >= dec->mb_w_ - 1) {    
          top_right[0] = top_y[15] * 0x01010101u;
        } else {
          memcpy(top_right, top_y + 16, sizeof(*top_right));
        }
      }
      
      top_right[BPS] = top_right[2 * BPS] = top_right[3 * BPS] = top_right[0];

      
      for (n = 0; n < 16; n++) {
        uint8_t* const dst = y_dst + kScan[n];
        VP8PredLuma4[dec->imodes_[n]](dst);
        if (dec->non_zero_ac_ & (1 << n)) {
          VP8Transform(coeffs + n * 16, dst, 0);
        } else if (dec->non_zero_ & (1 << n)) {  
          VP8TransformDC(coeffs + n * 16, dst);
        }
      }
    } else {    
      const int pred_func = CheckMode(dec, dec->imodes_[0]);
      VP8PredLuma16[pred_func](y_dst);
      if (dec->non_zero_) {
        for (n = 0; n < 16; n++) {
          uint8_t* const dst = y_dst + kScan[n];
          if (dec->non_zero_ac_ & (1 << n)) {
            VP8Transform(coeffs + n * 16, dst, 0);
          } else if (dec->non_zero_ & (1 << n)) {  
            VP8TransformDC(coeffs + n * 16, dst);
          }
        }
      }
    }
    {
      
      const int pred_func = CheckMode(dec, dec->uvmode_);
      VP8PredChroma8[pred_func](u_dst);
      VP8PredChroma8[pred_func](v_dst);

      if (dec->non_zero_ & 0x0f0000) {   
        const int16_t* const u_coeffs = dec->coeffs_ + 16 * 16;
        if (dec->non_zero_ac_ & 0x0f0000) {
          VP8TransformUV(u_coeffs, u_dst);
        } else {
          VP8TransformDCUV(u_coeffs, u_dst);
        }
      }
      if (dec->non_zero_ & 0xf00000) {   
        const int16_t* const v_coeffs = dec->coeffs_ + 20 * 16;
        if (dec->non_zero_ac_ & 0xf00000) {
          VP8TransformUV(v_coeffs, v_dst);
        } else {
          VP8TransformDCUV(v_coeffs, v_dst);
        }
      }

      
      if (dec->mb_y_ < dec->mb_h_ - 1) {
        memcpy(top_y, y_dst + 15 * BPS, 16);
        memcpy(top_u, u_dst +  7 * BPS,  8);
        memcpy(top_v, v_dst +  7 * BPS,  8);
      }
    }
  }
  
  {
    const int y_offset = dec->cache_id_ * 16 * dec->cache_y_stride_;
    const int uv_offset = dec->cache_id_ * 8 * dec->cache_uv_stride_;
    uint8_t* const y_out = dec->cache_y_ + dec->mb_x_ * 16 + y_offset;
    uint8_t* const u_out = dec->cache_u_ + dec->mb_x_ * 8 + uv_offset;
    uint8_t* const v_out = dec->cache_v_ + dec->mb_x_ * 8 + uv_offset;
    for (j = 0; j < 16; ++j) {
      memcpy(y_out + j * dec->cache_y_stride_, y_dst + j * BPS, 16);
    }
    for (j = 0; j < 8; ++j) {
      memcpy(u_out + j * dec->cache_uv_stride_, u_dst + j * BPS, 8);
      memcpy(v_out + j * dec->cache_uv_stride_, v_dst + j * BPS, 8);
    }
  }
}


#if defined(__cplusplus) || defined(c_plusplus)
}    
#endif
