// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_JS_JS_BACKEND_H_
#define SYNC_JS_JS_BACKEND_H_


#include <string>

#include "sync/base/sync_export.h"

namespace syncer {

class JsArgList;
class JsEventHandler;
class JsReplyHandler;
template <typename T> class WeakHandle;

class SYNC_EXPORT_PRIVATE JsBackend {
 public:
  
  virtual void SetJsEventHandler(
      const WeakHandle<JsEventHandler>& event_handler) = 0;

  
  
  virtual void ProcessJsMessage(
      const std::string& name, const JsArgList& args,
      const WeakHandle<JsReplyHandler>& reply_handler) = 0;

 protected:
  virtual ~JsBackend() {}
};

}  

#endif  
