// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_QUIC_QUIC_BLOCKED_WRITER_INTERFACE_H_
#define NET_QUIC_QUIC_BLOCKED_WRITER_INTERFACE_H_

#include "net/base/net_export.h"

namespace net {

class NET_EXPORT_PRIVATE QuicBlockedWriterInterface {
 public:
  virtual ~QuicBlockedWriterInterface() {}

  
  
  
  virtual bool OnCanWrite() = 0;
};

}  

#endif  
