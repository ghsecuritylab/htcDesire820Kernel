// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_CHROMEDRIVER_CHROME_CONSOLE_LOGGER_H_
#define CHROME_TEST_CHROMEDRIVER_CHROME_CONSOLE_LOGGER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "chrome/test/chromedriver/chrome/devtools_event_listener.h"

class Log;

class ConsoleLogger : public DevToolsEventListener {
 public:
  
  
  explicit ConsoleLogger(Log* log);

  
  virtual Status OnConnected(DevToolsClient* client) OVERRIDE;
  
  virtual Status OnEvent(DevToolsClient* client,
                         const std::string& method,
                         const base::DictionaryValue& params) OVERRIDE;

 private:
  Log* log_;  

  DISALLOW_COPY_AND_ASSIGN(ConsoleLogger);
};

#endif  
