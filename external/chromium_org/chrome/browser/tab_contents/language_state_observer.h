// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_TAB_CONTENTS_LANGUAGE_STATE_OBSERVER_H_
#define CHROME_BROWSER_TAB_CONTENTS_LANGUAGE_STATE_OBSERVER_H_

namespace content {
class WebContents;
}

class LanguageStateObserver {
 public:
  
  virtual void OnIsPageTranslatedChanged(content::WebContents* source) = 0;

  
  virtual void OnTranslateEnabledChanged(content::WebContents* source) = 0;

 protected:
  virtual ~LanguageStateObserver() {}
};

#endif  
