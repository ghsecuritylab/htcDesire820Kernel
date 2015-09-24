// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_IMAGE_CANVAS_IMAGE_SOURCE_H_
#define UI_GFX_IMAGE_CANVAS_IMAGE_SOURCE_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "ui/gfx/gfx_export.h"
#include "ui/gfx/image/image_skia_source.h"
#include "ui/gfx/size.h"

namespace gfx {
class Canvas;
class ImageSkiaRep;

class GFX_EXPORT CanvasImageSource : public gfx::ImageSkiaSource {
 public:
  CanvasImageSource(const gfx::Size& size, bool is_opaque);

  
  virtual void Draw(gfx::Canvas* canvas) = 0;

  
  const gfx::Size& size() const { return size_; };

  
  virtual gfx::ImageSkiaRep GetImageForScale(float scale) OVERRIDE;

 protected:
  virtual ~CanvasImageSource() {}

  const gfx::Size size_;
  const bool is_opaque_;
  DISALLOW_COPY_AND_ASSIGN(CanvasImageSource);
};

}  

#endif  