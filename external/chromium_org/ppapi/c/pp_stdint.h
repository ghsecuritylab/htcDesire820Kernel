/* Copyright (c) 2011 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PP_STDINT_H_
#define PPAPI_C_PP_STDINT_H_

#include "ppapi/c/pp_macros.h"




#if defined(_MSC_VER)

typedef unsigned char uint8_t;

typedef signed char int8_t;

typedef unsigned short uint16_t;

typedef short int16_t;

typedef unsigned int uint32_t;

typedef int int32_t;

typedef __int64 int64_t;

typedef unsigned __int64 uint64_t;

#else
#include <stdint.h>
#endif

#endif  

