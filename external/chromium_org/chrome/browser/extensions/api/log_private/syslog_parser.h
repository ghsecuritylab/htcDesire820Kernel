// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_LOG_PRIVATE_SYSLOG_PARSER_H_
#define CHROME_BROWSER_EXTENSIONS_API_LOG_PRIVATE_SYSLOG_PARSER_H_

#include <string>
#include <vector>

#include "base/memory/linked_ptr.h"
#include "chrome/browser/extensions/api/log_private/log_parser.h"
#include "chrome/common/extensions/api/log_private.h"

namespace extensions {

class SyslogParser : public LogParser {
 public:
  SyslogParser();
  virtual ~SyslogParser();

 protected:
  
  virtual Error ParseEntry(
      const std::string& input,
      std::vector<linked_ptr<api::log_private::LogEntry> >* output,
      FilterHandler* filter_handler) const
      OVERRIDE;

 private:
  
  Error ParseTime(const std::string& input, double* output) const;
  
  Error ParseProcess(const std::string& input,
                     api::log_private::LogEntry* entry) const;
  
  void ParseLevel(const std::string& input,
                  api::log_private::LogEntry* entry) const;

  DISALLOW_COPY_AND_ASSIGN(SyslogParser);
};

}  

#endif  