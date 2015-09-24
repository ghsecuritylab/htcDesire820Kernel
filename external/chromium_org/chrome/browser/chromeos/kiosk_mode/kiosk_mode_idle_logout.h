// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_KIOSK_MODE_KIOSK_MODE_IDLE_LOGOUT_H_
#define CHROME_BROWSER_CHROMEOS_KIOSK_MODE_KIOSK_MODE_IDLE_LOGOUT_H_

#include "ash/wm/user_activity_observer.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/timer/timer.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

namespace chromeos {

class KioskModeIdleLogout : public ash::UserActivityObserver,
                            public content::NotificationObserver {
 public:
  static void Initialize();

  KioskModeIdleLogout();
  virtual ~KioskModeIdleLogout();

 private:
  friend class KioskModeIdleLogoutTest;

  
  void Setup();

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnUserActivity(const ui::Event* event) OVERRIDE;

  
  void Start();

  
  void ResetTimer();

  
  void OnTimeout();

  content::NotificationRegistrar registrar_;

  base::OneShotTimer<KioskModeIdleLogout> timer_;

  DISALLOW_COPY_AND_ASSIGN(KioskModeIdleLogout);
};

}  

#endif  
