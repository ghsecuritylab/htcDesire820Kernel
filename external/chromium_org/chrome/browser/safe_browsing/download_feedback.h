// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SAFE_BROWSING_DOWNLOAD_FEEDBACK_H_
#define CHROME_BROWSER_SAFE_BROWSING_DOWNLOAD_FEEDBACK_H_

#include <string>

#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "chrome/browser/safe_browsing/two_phase_uploader.h"

namespace content {
class DownloadItem;
}

namespace safe_browsing {

class DownloadFeedbackFactory;

class DownloadFeedback : public base::NonThreadSafe {
 public:
  
  
  static DownloadFeedback* Create(
      net::URLRequestContextGetter* request_context_getter,
      base::TaskRunner* file_task_runner,
      const base::FilePath& file_path,
      const std::string& ping_request,
      const std::string& ping_response);

  
  
  
  static const int64 kMaxUploadSize;

  virtual ~DownloadFeedback() {}

  
  
  static void RegisterFactory(DownloadFeedbackFactory* factory) {
    factory_ = factory;
  }

  
  
  
  
  virtual void Start(const base::Closure& finish_callback) = 0;

  virtual const std::string& GetPingRequestForTesting() const = 0;
  virtual const std::string& GetPingResponseForTesting() const = 0;

 private:
  
  
  static DownloadFeedbackFactory* factory_;
};

class DownloadFeedbackFactory {
 public:
  virtual ~DownloadFeedbackFactory() {}

  virtual DownloadFeedback* CreateDownloadFeedback(
      net::URLRequestContextGetter* request_context_getter,
      base::TaskRunner* file_task_runner,
      const base::FilePath& file_path,
      const std::string& ping_request,
      const std::string& ping_response) = 0;
};

}  

#endif  
