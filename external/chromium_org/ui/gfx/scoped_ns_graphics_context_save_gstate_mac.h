// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_SCOPED_NS_GRAPHICS_CONTEXT_SAVE_GSTATE_MAC_H_
#define UI_GFX_SCOPED_NS_GRAPHICS_CONTEXT_SAVE_GSTATE_MAC_H_

#include "base/basictypes.h"
#include "ui/gfx/gfx_export.h"

#if defined(__OBJC__)
@class NSGraphicsContext;
#else
class NSGraphicsContext;
#endif

namespace gfx {

class GFX_EXPORT ScopedNSGraphicsContextSaveGState {
 public:
  ScopedNSGraphicsContextSaveGState();
  ~ScopedNSGraphicsContextSaveGState();

 private:
  NSGraphicsContext* context_;  

  DISALLOW_COPY_AND_ASSIGN(ScopedNSGraphicsContextSaveGState);
};

}  

#endif  
