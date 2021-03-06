// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_CODEC_SCOPED_VPX_CODEC_H_
#define REMOTING_CODEC_SCOPED_VPX_CODEC_H_

#include "base/memory/scoped_ptr.h"

extern "C" {
typedef struct vpx_codec_ctx vpx_codec_ctx_t;
}

namespace remoting {

struct VpxCodecDeleter {
  void operator()(vpx_codec_ctx_t* codec);
};

typedef scoped_ptr<vpx_codec_ctx_t, VpxCodecDeleter> ScopedVpxCodec;

} 

#endif  
