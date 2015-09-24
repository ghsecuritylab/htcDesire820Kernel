/*
 * Copyright (c) 2011 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_TEST_CGEN_STRUCTS_H_
#define PPAPI_C_TEST_CGEN_STRUCTS_H_

#include "ppapi/c/pp_macros.h"
#include "ppapi/c/test_cgen/stdint.h"



typedef uint8_t s_array[3];

typedef enum {
  esv1 = 1,
  esv2 = 2
} senum;

struct st1 {
  int32_t i;
  senum j;
};

struct st2 {
  s_array pixels[640][480];
};

typedef float (*func_t)(const s_array data);

typedef func_t (*findfunc_t)(const char* x);

struct sfoo {
  s_array screen[480][640];
  findfunc_t myfunc;
};

#endif  
