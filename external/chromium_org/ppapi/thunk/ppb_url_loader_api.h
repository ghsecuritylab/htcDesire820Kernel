// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_THUNK_URL_LOADER_API_H_
#define PPAPI_THUNK_URL_LOADER_API_H_

#include "base/memory/ref_counted.h"
#include "ppapi/c/ppb_url_loader.h"
#include "ppapi/c/trusted/ppb_url_loader_trusted.h"

namespace ppapi {

class TrackedCallback;
struct URLRequestInfoData;
struct URLResponseInfoData;

namespace thunk {

class PPB_URLLoader_API {
 public:
  virtual ~PPB_URLLoader_API() {}

  
  virtual int32_t Open(PP_Resource request_id,
                       scoped_refptr<TrackedCallback> callback) = 0;

  
  
  
  virtual int32_t Open(const URLRequestInfoData& data,
                       int requestor_pid,
                       scoped_refptr<TrackedCallback> callback) = 0;

  virtual int32_t FollowRedirect(scoped_refptr<TrackedCallback> callback) = 0;
  virtual PP_Bool GetUploadProgress(int64_t* bytes_sent,
                                    int64_t* total_bytes_to_be_sent) = 0;
  virtual PP_Bool GetDownloadProgress(int64_t* bytes_received,
                                      int64_t* total_bytes_to_be_received) = 0;
  virtual PP_Resource GetResponseInfo() = 0;
  virtual int32_t ReadResponseBody(void* buffer,
                                   int32_t bytes_to_read,
                                   scoped_refptr<TrackedCallback> callback) = 0;
  virtual int32_t FinishStreamingToFile(
      scoped_refptr<TrackedCallback> callback) = 0;
  virtual void Close() = 0;

  
  virtual void GrantUniversalAccess() = 0;
  virtual void RegisterStatusCallback(
      PP_URLLoaderTrusted_StatusCallback cb) = 0;
};

}  
}  

#endif  