// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ASH_SESSION_STATE_DELEGATE_CHROMEOS_H_
#define CHROME_BROWSER_UI_ASH_SESSION_STATE_DELEGATE_CHROMEOS_H_

#include "ash/session_state_delegate.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/observer_list.h"
#include "chrome/browser/chromeos/login/user_manager.h"

namespace ash {
class SessionStateObserver;
}  

class SessionStateDelegateChromeos
    : public ash::SessionStateDelegate,
      public chromeos::UserManager::UserSessionStateObserver {
 public:
  SessionStateDelegateChromeos();
  virtual ~SessionStateDelegateChromeos();

  
  virtual int GetMaximumNumberOfLoggedInUsers() const OVERRIDE;
  virtual int NumberOfLoggedInUsers() const OVERRIDE;
  virtual bool IsActiveUserSessionStarted() const OVERRIDE;
  virtual bool CanLockScreen() const OVERRIDE;
  virtual bool IsScreenLocked() const OVERRIDE;
  virtual bool ShouldLockScreenBeforeSuspending() const OVERRIDE;
  virtual void LockScreen() OVERRIDE;
  virtual void UnlockScreen() OVERRIDE;
  virtual bool IsUserSessionBlocked() const OVERRIDE;
  virtual const base::string16 GetUserDisplayName(
      ash::MultiProfileIndex index) const OVERRIDE;
  virtual const std::string GetUserEmail(
      ash::MultiProfileIndex index) const OVERRIDE;
  virtual const std::string GetUserID(
      ash::MultiProfileIndex index) const OVERRIDE;
  virtual const gfx::ImageSkia& GetUserImage(
      ash::MultiProfileIndex index) const OVERRIDE;
  virtual void GetLoggedInUsers(ash::UserIdList* users) OVERRIDE;
  virtual void SwitchActiveUser(const std::string& user_id) OVERRIDE;
  virtual void CycleActiveUser(CycleUser cycle_user) OVERRIDE;
  virtual void AddSessionStateObserver(
      ash::SessionStateObserver* observer) OVERRIDE;
  virtual void RemoveSessionStateObserver(
      ash::SessionStateObserver* observer) OVERRIDE;
  virtual bool TransferWindowToDesktopOfUser(
      aura::Window* window,
      ash::MultiProfileIndex index) OVERRIDE;
  
  virtual void ActiveUserChanged(const chromeos::User* active_user) OVERRIDE;
  virtual void UserAddedToSession(const chromeos::User* added_user) OVERRIDE;

 private:
  
  ObserverList<ash::SessionStateObserver> session_state_observer_list_;

  DISALLOW_COPY_AND_ASSIGN(SessionStateDelegateChromeos);
};

#endif  