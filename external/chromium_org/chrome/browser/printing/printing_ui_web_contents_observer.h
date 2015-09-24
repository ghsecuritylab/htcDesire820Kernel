// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PRINTING_PRINTING_UI_WEB_CONTENTS_OBSERVER_H_
#define CHROME_BROWSER_PRINTING_PRINTING_UI_WEB_CONTENTS_OBSERVER_H_

#include "base/basictypes.h"
#include "content/public/browser/web_contents_observer.h"
#include "ui/gfx/native_widget_types.h"

class PrintingUIWebContentsObserver : public content::WebContentsObserver {
 public:
  explicit PrintingUIWebContentsObserver(content::WebContents* web_contents);

  
  gfx::NativeView GetParentView();

 private:
  DISALLOW_COPY_AND_ASSIGN(PrintingUIWebContentsObserver);
};

#endif  
