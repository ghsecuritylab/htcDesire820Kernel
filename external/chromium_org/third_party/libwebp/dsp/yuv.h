// Copyright 2010 Google Inc. All Rights Reserved.
// Use of this source code is governed by a BSD-style license

#ifndef WEBP_DSP_YUV_H_
#define WEBP_DSP_YUV_H_

#include "../dec/decode_vp8.h"

#define WEBP_YUV_USE_TABLE

#if defined(WEBP_EXPERIMENTAL_FEATURES)
#endif


#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

enum { YUV_FIX = 16,                
       YUV_HALF = 1 << (YUV_FIX - 1),
       YUV_MASK = (256 << YUV_FIX) - 1,
       YUV_RANGE_MIN = -227,        
       YUV_RANGE_MAX = 256 + 226    
};

#ifdef WEBP_YUV_USE_TABLE

extern int16_t VP8kVToR[256], VP8kUToB[256];
extern int32_t VP8kVToG[256], VP8kUToG[256];
extern uint8_t VP8kClip[YUV_RANGE_MAX - YUV_RANGE_MIN];
extern uint8_t VP8kClip4Bits[YUV_RANGE_MAX - YUV_RANGE_MIN];

static WEBP_INLINE void VP8YuvToRgb(uint8_t y, uint8_t u, uint8_t v,
                                    uint8_t* const rgb) {
  const int r_off = VP8kVToR[v];
  const int g_off = (VP8kVToG[v] + VP8kUToG[u]) >> YUV_FIX;
  const int b_off = VP8kUToB[u];
  rgb[0] = VP8kClip[y + r_off - YUV_RANGE_MIN];
  rgb[1] = VP8kClip[y + g_off - YUV_RANGE_MIN];
  rgb[2] = VP8kClip[y + b_off - YUV_RANGE_MIN];
}

static WEBP_INLINE void VP8YuvToBgr(uint8_t y, uint8_t u, uint8_t v,
                                    uint8_t* const bgr) {
  const int r_off = VP8kVToR[v];
  const int g_off = (VP8kVToG[v] + VP8kUToG[u]) >> YUV_FIX;
  const int b_off = VP8kUToB[u];
  bgr[0] = VP8kClip[y + b_off - YUV_RANGE_MIN];
  bgr[1] = VP8kClip[y + g_off - YUV_RANGE_MIN];
  bgr[2] = VP8kClip[y + r_off - YUV_RANGE_MIN];
}

static WEBP_INLINE void VP8YuvToRgb565(uint8_t y, uint8_t u, uint8_t v,
                                       uint8_t* const rgb) {
  const int r_off = VP8kVToR[v];
  const int g_off = (VP8kVToG[v] + VP8kUToG[u]) >> YUV_FIX;
  const int b_off = VP8kUToB[u];
  const uint8_t rg = ((VP8kClip[y + r_off - YUV_RANGE_MIN] & 0xf8) |
                      (VP8kClip[y + g_off - YUV_RANGE_MIN] >> 5));
  const uint8_t gb = (((VP8kClip[y + g_off - YUV_RANGE_MIN] << 3) & 0xe0) |
                      (VP8kClip[y + b_off - YUV_RANGE_MIN] >> 3));
#ifdef WEBP_SWAP_16BIT_CSP
  rgb[0] = gb;
  rgb[1] = rg;
#else
  rgb[0] = rg;
  rgb[1] = gb;
#endif
}

static WEBP_INLINE void VP8YuvToRgba4444(uint8_t y, uint8_t u, uint8_t v,
                                         uint8_t* const argb) {
  const int r_off = VP8kVToR[v];
  const int g_off = (VP8kVToG[v] + VP8kUToG[u]) >> YUV_FIX;
  const int b_off = VP8kUToB[u];
  const uint8_t rg = ((VP8kClip4Bits[y + r_off - YUV_RANGE_MIN] << 4) |
                      VP8kClip4Bits[y + g_off - YUV_RANGE_MIN]);
  const uint8_t ba = (VP8kClip4Bits[y + b_off - YUV_RANGE_MIN] << 4) | 0x0f;
#ifdef WEBP_SWAP_16BIT_CSP
  argb[0] = ba;
  argb[1] = rg;
#else
  argb[0] = rg;
  argb[1] = ba;
#endif
}

#else   

#define kYScale 76309      
#define kVToR   104597     
#define kUToG   25674      
#define kVToG   53278      
#define kUToB   132201     
#define kRCst (-kYScale * 16 - kVToR * 128 + YUV_HALF)
#define kGCst (-kYScale * 16 + kUToG * 128 + kVToG * 128 + YUV_HALF)
#define kBCst (-kYScale * 16 - kUToB * 128 + YUV_HALF)

static WEBP_INLINE uint8_t VP8Clip8(int v) {
  return ((v & ~YUV_MASK) == 0) ? (uint8_t)(v >> YUV_FIX)
                                : (v < 0) ? 0u : 255u;
}

static WEBP_INLINE uint8_t VP8ClipN(int v, int N) {  
  return ((v & ~YUV_MASK) == 0) ? (uint8_t)(v >> (YUV_FIX + (8 - N)))
                                : (v < 0) ? 0u : (255u >> (8 - N));
}

static WEBP_INLINE int VP8YUVToR(int y, int v) {
  return kYScale * y + kVToR * v + kRCst;
}

static WEBP_INLINE int VP8YUVToG(int y, int u, int v) {
  return kYScale * y - kUToG * u - kVToG * v + kGCst;
}

static WEBP_INLINE int VP8YUVToB(int y, int u) {
  return kYScale * y  + kUToB * u + kBCst;
}

static WEBP_INLINE void VP8YuvToRgb(uint8_t y, uint8_t u, uint8_t v,
                                    uint8_t* const rgb) {
  rgb[0] = VP8Clip8(VP8YUVToR(y, v));
  rgb[1] = VP8Clip8(VP8YUVToG(y, u, v));
  rgb[2] = VP8Clip8(VP8YUVToB(y, u));
}

static WEBP_INLINE void VP8YuvToBgr(uint8_t y, uint8_t u, uint8_t v,
                                    uint8_t* const bgr) {
  bgr[0] = VP8Clip8(VP8YUVToB(y, u));
  bgr[1] = VP8Clip8(VP8YUVToG(y, u, v));
  bgr[2] = VP8Clip8(VP8YUVToR(y, v));
}

static WEBP_INLINE void VP8YuvToRgb565(uint8_t y, uint8_t u, uint8_t v,
                                       uint8_t* const rgb) {
  const int r = VP8Clip8(VP8YUVToR(y, u));
  const int g = VP8ClipN(VP8YUVToG(y, u, v), 6);
  const int b = VP8ClipN(VP8YUVToB(y, v), 5);
  const uint8_t rg = (r & 0xf8) | (g >> 3);
  const uint8_t gb = (g << 5) | b;
#ifdef WEBP_SWAP_16BIT_CSP
  rgb[0] = gb;
  rgb[1] = rg;
#else
  rgb[0] = rg;
  rgb[1] = gb;
#endif
}

static WEBP_INLINE void VP8YuvToRgba4444(uint8_t y, uint8_t u, uint8_t v,
                                         uint8_t* const argb) {
  const int r = VP8Clip8(VP8YUVToR(y, u));
  const int g = VP8ClipN(VP8YUVToG(y, u, v), 4);
  const int b = VP8Clip8(VP8YUVToB(y, v));
  const uint8_t rg = (r & 0xf0) | g;
  const uint8_t ba = b | 0x0f;   
#ifdef WEBP_SWAP_16BIT_CSP
  argb[0] = ba;
  argb[1] = rg;
#else
  argb[0] = rg;
  argb[1] = ba;
#endif
}

#endif  

static WEBP_INLINE void VP8YuvToArgb(uint8_t y, uint8_t u, uint8_t v,
                                     uint8_t* const argb) {
  argb[0] = 0xff;
  VP8YuvToRgb(y, u, v, argb + 1);
}

static WEBP_INLINE void VP8YuvToBgra(uint8_t y, uint8_t u, uint8_t v,
                                     uint8_t* const bgra) {
  VP8YuvToBgr(y, u, v, bgra);
  bgra[3] = 0xff;
}

static WEBP_INLINE void VP8YuvToRgba(uint8_t y, uint8_t u, uint8_t v,
                                     uint8_t* const rgba) {
  VP8YuvToRgb(y, u, v, rgba);
  rgba[3] = 0xff;
}

void VP8YUVInit(void);


static WEBP_INLINE int VP8ClipUV(int v) {
  v = (v + (257 << (YUV_FIX + 2 - 1))) >> (YUV_FIX + 2);
  return ((v & ~0xff) == 0) ? v : (v < 0) ? 0 : 255;
}

#ifndef USE_YUVj

static WEBP_INLINE int VP8RGBToY(int r, int g, int b) {
  const int kRound = (1 << (YUV_FIX - 1)) + (16 << YUV_FIX);
  const int luma = 16839 * r + 33059 * g + 6420 * b;
  return (luma + kRound) >> YUV_FIX;  
}

static WEBP_INLINE int VP8RGBToU(int r, int g, int b) {
  const int u = -9719 * r - 19081 * g + 28800 * b;
  return VP8ClipUV(u);
}

static WEBP_INLINE int VP8RGBToV(int r, int g, int b) {
  const int v = +28800 * r - 24116 * g - 4684 * b;
  return VP8ClipUV(v);
}

#else

static WEBP_INLINE int VP8RGBToY(int r, int g, int b) {
  const int kRound = (1 << (YUV_FIX - 1));
  const int luma = 19595 * r + 38470 * g + 7471 * b;
  return (luma + kRound) >> YUV_FIX;  
}

static WEBP_INLINE int VP8RGBToU(int r, int g, int b) {
  const int u = -11058 * r - 21710 * g + 32768 * b;
  return VP8ClipUV(u);
}

static WEBP_INLINE int VP8RGBToV(int r, int g, int b) {
  const int v = 32768 * r - 27439 * g - 5329 * b;
  return VP8ClipUV(v);
}

#endif    

#if defined(__cplusplus) || defined(c_plusplus)
}    
#endif

#endif  