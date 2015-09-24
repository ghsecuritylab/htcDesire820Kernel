// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_WEB_UI_UTIL_H_
#define CHROME_BROWSER_UI_WEBUI_WEB_UI_UTIL_H_
#pragma once

#include <string>

class SkBitmap;

namespace web_ui_util {

std::string GetImageDataUrl(const SkBitmap& bitmap);

std::string GetImageDataUrlFromResource(int resource_id);

}  

#endif  
