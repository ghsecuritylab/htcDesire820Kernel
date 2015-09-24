// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PROFILES_PROFILE_INFO_UTIL_H_
#define CHROME_BROWSER_PROFILES_PROFILE_INFO_UTIL_H_

#include "ui/gfx/image/image.h"

namespace profiles {

extern const int kAvatarIconWidth;
extern const int kAvatarIconHeight;
extern const int kAvatarIconPadding;

gfx::Image GetSizedAvatarIconWithBorder(const gfx::Image& image,
                                        bool is_rectangle,
                                        int width, int height);

gfx::Image GetAvatarIconForMenu(const gfx::Image& image,
                                bool is_rectangle);

gfx::Image GetAvatarIconForWebUI(const gfx::Image& image,
                                 bool is_rectangle);

gfx::Image GetAvatarIconForTitleBar(const gfx::Image& image,
                                    bool is_rectangle,
                                    int dst_width,
                                    int dst_height);

}  

#endif  
