// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_CHROMEOS_LOGIN_WRONG_HWID_SCREEN_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_CHROMEOS_LOGIN_WRONG_HWID_SCREEN_HANDLER_H_

#include "base/compiler_specific.h"
#include "chrome/browser/chromeos/login/screens/wrong_hwid_screen_actor.h"
#include "chrome/browser/ui/webui/chromeos/login/base_screen_handler.h"
#include "content/public/browser/web_ui.h"

namespace base {
class DictionaryValue;
}

namespace chromeos {

class WrongHWIDScreenHandler : public WrongHWIDScreenActor,
                               public BaseScreenHandler {
 public:
  WrongHWIDScreenHandler();
  virtual ~WrongHWIDScreenHandler();

  
  virtual void PrepareToShow() OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual void SetDelegate(Delegate* delegate) OVERRIDE;

  
  virtual void DeclareLocalizedValues(LocalizedValuesBuilder* builder) OVERRIDE;
  virtual void Initialize() OVERRIDE;

  
  virtual void RegisterMessages() OVERRIDE;

 private:
  
  void HandleOnSkip();

  Delegate* delegate_;

  
  bool show_on_init_;

  DISALLOW_COPY_AND_ASSIGN(WrongHWIDScreenHandler);
};

}  

#endif  

