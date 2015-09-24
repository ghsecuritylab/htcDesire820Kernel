// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_PROXY_PPP_MESSAGING_PROXY_H_
#define PPAPI_PROXY_PPP_MESSAGING_PROXY_H_

#include "base/compiler_specific.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/ppp_messaging.h"
#include "ppapi/proxy/interface_proxy.h"

namespace ppapi {
namespace proxy {

class SerializedVarReceiveInput;

class PPP_Messaging_Proxy : public InterfaceProxy {
 public:
  PPP_Messaging_Proxy(Dispatcher* dispatcher);
  virtual ~PPP_Messaging_Proxy();

  static const Info* GetInfo();

  
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;

 private:
  
  void OnMsgHandleMessage(PP_Instance instance,
                          SerializedVarReceiveInput data);

  
  
  
  const PPP_Messaging* ppp_messaging_impl_;

  DISALLOW_COPY_AND_ASSIGN(PPP_Messaging_Proxy);
};

}  
}  

#endif  
