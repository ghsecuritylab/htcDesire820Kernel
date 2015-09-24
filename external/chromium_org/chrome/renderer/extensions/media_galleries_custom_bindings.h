// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_RENDERER_EXTENSIONS_MEDIA_GALLERIES_CUSTOM_BINDINGS_H_
#define CHROME_RENDERER_EXTENSIONS_MEDIA_GALLERIES_CUSTOM_BINDINGS_H_

#include "chrome/renderer/extensions/chrome_v8_extension.h"

namespace extensions {

class MediaGalleriesCustomBindings : public ChromeV8Extension {
 public:
  MediaGalleriesCustomBindings(Dispatcher* dispatcher,
                               ChromeV8Context* context);

 private:
  
  
  void GetMediaFileSystemObject(
      const v8::FunctionCallbackInfo<v8::Value>& args);

  DISALLOW_COPY_AND_ASSIGN(MediaGalleriesCustomBindings);
};

}  

#endif  