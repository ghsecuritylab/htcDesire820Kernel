// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_BROWSER_LANGUAGE_STATE_OBSERVER_H_
#define CHROME_BROWSER_UI_BROWSER_LANGUAGE_STATE_OBSERVER_H_

#include "chrome/browser/tab_contents/language_state_observer.h"

#include "base/basictypes.h"
#include "base/compiler_specific.h"

class Browser;

class BrowserLanguageStateObserver : public LanguageStateObserver {
 public:
  explicit BrowserLanguageStateObserver(Browser* browser);

  virtual ~BrowserLanguageStateObserver();

  
  virtual void OnIsPageTranslatedChanged(content::WebContents* source) OVERRIDE;
  virtual void OnTranslateEnabledChanged(content::WebContents* source) OVERRIDE;

 private:
  Browser* browser_;

  DISALLOW_COPY_AND_ASSIGN(BrowserLanguageStateObserver);
};

#endif  