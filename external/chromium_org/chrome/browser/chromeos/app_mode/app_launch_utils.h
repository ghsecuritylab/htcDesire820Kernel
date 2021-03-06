// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_APP_MODE_APP_LAUNCH_UTILS_H_
#define CHROME_BROWSER_CHROMEOS_APP_MODE_APP_LAUNCH_UTILS_H_

#include <string>

class Profile;

namespace chromeos {

void LaunchAppOrDie(Profile *profile, const std::string& app_id);

}  

#endif 
