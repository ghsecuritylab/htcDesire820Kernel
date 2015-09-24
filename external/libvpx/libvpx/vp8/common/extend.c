/*
 *  Copyright (c) 2010 The WebM project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */


#include "extend.h"
#include "vpx_mem/vpx_mem.h"


static void copy_and_extend_plane
(
    unsigned char *s, 
    int sp,           
    unsigned char *d, 
    int dp,           
    int h,            
    int w,            
    int et,           
    int el,           
    int eb,           
    int er            
)
{
    int i;
    unsigned char *src_ptr1, *src_ptr2;
    unsigned char *dest_ptr1, *dest_ptr2;
    int linesize;

    
    src_ptr1 = s;
    src_ptr2 = s + w - 1;
    dest_ptr1 = d - el;
    dest_ptr2 = d + w;

    for (i = 0; i < h; i++)
    {
        vpx_memset(dest_ptr1, src_ptr1[0], el);
        vpx_memcpy(dest_ptr1 + el, src_ptr1, w);
        vpx_memset(dest_ptr2, src_ptr2[0], er);
        src_ptr1  += sp;
        src_ptr2  += sp;
        dest_ptr1 += dp;
        dest_ptr2 += dp;
    }

    src_ptr1 = d - el;
    src_ptr2 = d + dp * (h - 1) - el;
    dest_ptr1 = d + dp * (-et) - el;
    dest_ptr2 = d + dp * (h) - el;
    linesize = el + er + w;

    for (i = 0; i < et; i++)
    {
        vpx_memcpy(dest_ptr1, src_ptr1, linesize);
        dest_ptr1 += dp;
    }

    for (i = 0; i < eb; i++)
    {
        vpx_memcpy(dest_ptr2, src_ptr2, linesize);
        dest_ptr2 += dp;
    }
}


void vp8_copy_and_extend_frame(YV12_BUFFER_CONFIG *src,
                               YV12_BUFFER_CONFIG *dst)
{
    int et = dst->border;
    int el = dst->border;
    int eb = dst->border + dst->y_height - src->y_height;
    int er = dst->border + dst->y_width - src->y_width;

    copy_and_extend_plane(src->y_buffer, src->y_stride,
                          dst->y_buffer, dst->y_stride,
                          src->y_height, src->y_width,
                          et, el, eb, er);

    et = dst->border >> 1;
    el = dst->border >> 1;
    eb = (dst->border >> 1) + dst->uv_height - src->uv_height;
    er = (dst->border >> 1) + dst->uv_width - src->uv_width;

    copy_and_extend_plane(src->u_buffer, src->uv_stride,
                          dst->u_buffer, dst->uv_stride,
                          src->uv_height, src->uv_width,
                          et, el, eb, er);

    copy_and_extend_plane(src->v_buffer, src->uv_stride,
                          dst->v_buffer, dst->uv_stride,
                          src->uv_height, src->uv_width,
                          et, el, eb, er);
}


void vp8_copy_and_extend_frame_with_rect(YV12_BUFFER_CONFIG *src,
                                         YV12_BUFFER_CONFIG *dst,
                                         int srcy, int srcx,
                                         int srch, int srcw)
{
    int et = dst->border;
    int el = dst->border;
    int eb = dst->border + dst->y_height - src->y_height;
    int er = dst->border + dst->y_width - src->y_width;
    int src_y_offset = srcy * src->y_stride + srcx;
    int dst_y_offset = srcy * dst->y_stride + srcx;
    int src_uv_offset = ((srcy * src->uv_stride) >> 1) + (srcx >> 1);
    int dst_uv_offset = ((srcy * dst->uv_stride) >> 1) + (srcx >> 1);

    
    if (srcy)
      et = 0;
    if (srcx)
      el = 0;
    if (srcy + srch != src->y_height)
      eb = 0;
    if (srcx + srcw != src->y_width)
      er = 0;

    copy_and_extend_plane(src->y_buffer + src_y_offset,
                          src->y_stride,
                          dst->y_buffer + dst_y_offset,
                          dst->y_stride,
                          srch, srcw,
                          et, el, eb, er);

    et = (et + 1) >> 1;
    el = (el + 1) >> 1;
    eb = (eb + 1) >> 1;
    er = (er + 1) >> 1;
    srch = (srch + 1) >> 1;
    srcw = (srcw + 1) >> 1;

    copy_and_extend_plane(src->u_buffer + src_uv_offset,
                          src->uv_stride,
                          dst->u_buffer + dst_uv_offset,
                          dst->uv_stride,
                          srch, srcw,
                          et, el, eb, er);

    copy_and_extend_plane(src->v_buffer + src_uv_offset,
                          src->uv_stride,
                          dst->v_buffer + dst_uv_offset,
                          dst->uv_stride,
                          srch, srcw,
                          et, el, eb, er);
}


void vp8_extend_mb_row(YV12_BUFFER_CONFIG *ybf,
                       unsigned char *YPtr,
                       unsigned char *UPtr,
                       unsigned char *VPtr)
{
    int i;

    YPtr += ybf->y_stride * 14;
    UPtr += ybf->uv_stride * 6;
    VPtr += ybf->uv_stride * 6;

    for (i = 0; i < 4; i++)
    {
        YPtr[i] = YPtr[-1];
        UPtr[i] = UPtr[-1];
        VPtr[i] = VPtr[-1];
    }

    YPtr += ybf->y_stride;
    UPtr += ybf->uv_stride;
    VPtr += ybf->uv_stride;

    for (i = 0; i < 4; i++)
    {
        YPtr[i] = YPtr[-1];
        UPtr[i] = UPtr[-1];
        VPtr[i] = VPtr[-1];
    }
}