// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_CONVERT_USER_SCRIPT_H_
#define CHROME_BROWSER_EXTENSIONS_CONVERT_USER_SCRIPT_H_
#pragma once

#include <string>

#include "base/memory/ref_counted.h"

class Extension;
class FilePath;
class GURL;

scoped_refptr<Extension> ConvertUserScriptToExtension(
    const FilePath& user_script, const GURL& original_url, std::string* error);

#endif  
