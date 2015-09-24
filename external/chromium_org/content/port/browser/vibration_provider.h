// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PORT_BROWSER_VIBRATION_PROVIDER_H_
#define CONTENT_PORT_BROWSER_VIBRATION_PROVIDER_H_

namespace content {

class VibrationProvider {
 public:
  
  virtual void Vibrate(int64 milliseconds) = 0;

  
  virtual void CancelVibration() = 0;

  virtual ~VibrationProvider() {}
};

}  

#endif 