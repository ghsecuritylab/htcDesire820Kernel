// Copyright 2013 The Chromium Authors. All rights reserved.
// // Use of this source code is governed by a BSD-style license that can be
// // found in the LICENSE file.
#ifndef NET_CERT_SCOPED_NSS_TYPES_H_
#define NET_CERT_SCOPED_NSS_TYPES_H_

#include <cert.h>

#include "base/memory/scoped_ptr.h"

namespace net {

struct FreeCERTCertificate {
 public:
  void operator()(CERTCertificate* x) const {
    CERT_DestroyCertificate(x);
  }
};

typedef scoped_ptr_malloc<CERTCertificate, FreeCERTCertificate>
    ScopedCERTCertificate;

}  

#endif  