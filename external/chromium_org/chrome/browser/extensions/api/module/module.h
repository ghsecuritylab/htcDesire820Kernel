// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_MODULE_MODULE_H_
#define CHROME_BROWSER_EXTENSIONS_API_MODULE_MODULE_H_

#include "chrome/browser/extensions/chrome_extension_function.h"

namespace extensions {
class ExtensionPrefs;

namespace extension {
std::string GetUpdateURLData(const ExtensionPrefs* prefs,
                             const std::string& extension_id);
}  

class ExtensionSetUpdateUrlDataFunction : public ChromeSyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("extension.setUpdateUrlData",
                             EXTENSION_SETUPDATEURLDATA)

 protected:
  virtual ~ExtensionSetUpdateUrlDataFunction() {}

  
  virtual bool RunImpl() OVERRIDE;
};

class ExtensionIsAllowedIncognitoAccessFunction
    : public ChromeSyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("extension.isAllowedIncognitoAccess",
                             EXTENSION_ISALLOWEDINCOGNITOACCESS)

 protected:
  virtual ~ExtensionIsAllowedIncognitoAccessFunction() {}

  
  virtual bool RunImpl() OVERRIDE;
};

class ExtensionIsAllowedFileSchemeAccessFunction
    : public ChromeSyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("extension.isAllowedFileSchemeAccess",
                             EXTENSION_ISALLOWEDFILESCHEMEACCESS)

 protected:
  virtual ~ExtensionIsAllowedFileSchemeAccessFunction() {}

  
  virtual bool RunImpl() OVERRIDE;
};

}  

#endif  