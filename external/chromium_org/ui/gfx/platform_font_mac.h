// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_PLATFORM_FONT_MAC_H_
#define UI_GFX_PLATFORM_FONT_MAC_H_

#include "base/compiler_specific.h"
#include "base/mac/scoped_nsobject.h"
#include "ui/gfx/platform_font.h"

namespace gfx {

class PlatformFontMac : public PlatformFont {
 public:
  PlatformFontMac();
  explicit PlatformFontMac(NativeFont native_font);
  PlatformFontMac(const std::string& font_name,
                  int font_size);

  
  virtual Font DeriveFont(int size_delta, int style) const OVERRIDE;
  virtual int GetHeight() const OVERRIDE;
  virtual int GetBaseline() const OVERRIDE;
  virtual int GetCapHeight() const OVERRIDE;
  virtual int GetAverageCharacterWidth() const OVERRIDE;
  virtual int GetStringWidth(const base::string16& text) const OVERRIDE;
  virtual int GetExpectedTextWidth(int length) const OVERRIDE;
  virtual int GetStyle() const OVERRIDE;
  virtual std::string GetFontName() const OVERRIDE;
  virtual std::string GetActualFontNameForTesting() const OVERRIDE;
  virtual int GetFontSize() const OVERRIDE;
  virtual NativeFont GetNativeFont() const OVERRIDE;

 private:
  PlatformFontMac(const std::string& font_name, int font_size, int font_style);
  virtual ~PlatformFontMac();

  
  void CalculateMetrics();

  
  
  
  
  base::scoped_nsobject<NSFont> native_font_;

  
  
  std::string font_name_;  
  int font_size_;
  int font_style_;

  
  int height_;
  int ascent_;
  int cap_height_;
  int average_width_;

  DISALLOW_COPY_AND_ASSIGN(PlatformFontMac);
};

}  

#endif  
