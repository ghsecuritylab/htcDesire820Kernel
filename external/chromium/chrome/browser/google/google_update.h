// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_GOOGLE_GOOGLE_UPDATE_H_
#define CHROME_BROWSER_GOOGLE_GOOGLE_UPDATE_H_
#pragma once

#include <string>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#if defined(OS_WIN)
#include "google_update_idl.h"
#endif

class MessageLoop;
namespace views {
class Window;
}

enum GoogleUpdateUpgradeResult {
  
  UPGRADE_STARTED = 0,
  
  UPGRADE_CHECK_STARTED,
  
  UPGRADE_IS_AVAILABLE,
  
  UPGRADE_SUCCESSFUL,
  
  UPGRADE_ALREADY_UP_TO_DATE,
  
  UPGRADE_ERROR,
};

enum GoogleUpdateErrorCode {
  
  GOOGLE_UPDATE_NO_ERROR = 0,
  
  
  
  CANNOT_UPGRADE_CHROME_IN_THIS_DIRECTORY,
  
  GOOGLE_UPDATE_JOB_SERVER_CREATION_FAILED,
  
  GOOGLE_UPDATE_ONDEMAND_CLASS_NOT_FOUND,
  
  
  GOOGLE_UPDATE_ONDEMAND_CLASS_REPORTED_ERROR,
  
  GOOGLE_UPDATE_GET_RESULT_CALL_FAILED,
  
  GOOGLE_UPDATE_GET_VERSION_INFO_FAILED,
  
  
  GOOGLE_UPDATE_ERROR_UPDATING,
  
  GOOGLE_UPDATE_DISABLED_BY_POLICY,
};

class GoogleUpdateStatusListener {
 public:
  
  
  
  
  
  
  virtual void OnReportResults(GoogleUpdateUpgradeResult results,
                               GoogleUpdateErrorCode error_code,
                               const std::wstring& version) = 0;
};

class GoogleUpdate : public base::RefCountedThreadSafe<GoogleUpdate> {
 public:
  GoogleUpdate();

  
  
  
  
  
  
  void CheckForUpdate(bool install_if_newer, views::Window* window);

  
  void set_status_listener(GoogleUpdateStatusListener* listener) {
    listener_ = listener;
  }

 private:
  friend class base::RefCountedThreadSafe<GoogleUpdate>;

  virtual ~GoogleUpdate();


#if defined(OS_WIN)

  
  
  
  bool ReportFailure(HRESULT hr, GoogleUpdateErrorCode error_code,
                     MessageLoop* main_loop);

#endif

  
  
  
  
  
  bool InitiateGoogleUpdateCheck(bool install_if_newer, views::Window* window,
                                 MessageLoop* main_loop);

  
  
  
  
  void ReportResults(GoogleUpdateUpgradeResult results,
                     GoogleUpdateErrorCode error_code);

  
  
  std::wstring version_available_;

  
  GoogleUpdateStatusListener* listener_;

  DISALLOW_COPY_AND_ASSIGN(GoogleUpdate);
};

#endif  