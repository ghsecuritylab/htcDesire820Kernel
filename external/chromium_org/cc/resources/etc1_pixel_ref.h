// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_RESOURCES_ETC1_PIXEL_REF_H_
#define CC_RESOURCES_ETC1_PIXEL_REF_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "cc/base/cc_export.h"
#include "third_party/skia/include/core/SkPixelRef.h"

namespace cc {

class CC_EXPORT ETC1PixelRef : public SkPixelRef {
 public:
#ifdef SK_SUPPORT_LEGACY_PIXELREF_CONSTRUCTOR
  
  
  explicit ETC1PixelRef(scoped_ptr<uint8_t[]> pixels);
#endif

  
  ETC1PixelRef(const SkImageInfo& info, scoped_ptr<uint8_t[]> pixels);
  virtual ~ETC1PixelRef();

  
  virtual Factory getFactory() const OVERRIDE;

 protected:
  
  virtual void* onLockPixels(SkColorTable** color_table) OVERRIDE;
  virtual void onUnlockPixels() OVERRIDE;

 private:
  scoped_ptr<uint8_t[]> pixels_;

  DISALLOW_COPY_AND_ASSIGN(ETC1PixelRef);
};

}  

#endif  