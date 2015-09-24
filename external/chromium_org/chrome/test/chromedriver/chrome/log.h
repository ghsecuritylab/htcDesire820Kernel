// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_TEST_CHROMEDRIVER_CHROME_LOG_H_
#define CHROME_TEST_CHROMEDRIVER_CHROME_LOG_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/time/time.h"

namespace base {
class Value;
}

class Log {
 public:
  
  enum Level {
    kAll,
    kDebug,
    kInfo,
    kWarning,
    kError,
    kOff
  };

  virtual ~Log() {}

  
  virtual void AddEntryTimestamped(const base::Time& timestamp,
                                   Level level,
                                   const std::string& source,
                                   const std::string& message) = 0;

  
  void AddEntry(Level level,
                const std::string& source,
                const std::string& message);

  
  void AddEntry(Level level, const std::string& message);
};

typedef bool (*IsVLogOnFunc)(int vlog_level);
void InitLogging(IsVLogOnFunc is_vlog_on_func);

bool IsVLogOn(int vlog_level);

std::string PrettyPrintValue(const base::Value& value);

std::string FormatValueForDisplay(const base::Value& value);

std::string FormatJsonForDisplay(const std::string& json);

#endif  
