// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_TEST_PIXEL_TEST_SOFTWARE_OUTPUT_DEVICE_H_
#define CC_TEST_PIXEL_TEST_SOFTWARE_OUTPUT_DEVICE_H_

#include "cc/output/software_output_device.h"

namespace cc {

class PixelTestSoftwareOutputDevice : public SoftwareOutputDevice {
 public:
  virtual void Resize(gfx::Size size) OVERRIDE;

  void set_surface_expansion_size(gfx::Size surface_expansion_size) {
    surface_expansion_size_ = surface_expansion_size;
  }

 private:
  gfx::Size surface_expansion_size_;
};

}  

#endif  
