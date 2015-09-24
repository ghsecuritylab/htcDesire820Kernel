// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_BASE_NET_ERRORS_H__
#define NET_BASE_NET_ERRORS_H__

#include <vector>

#include "base/basictypes.h"
#include "base/platform_file.h"
#include "net/base/net_export.h"

namespace net {

NET_EXPORT extern const char kErrorDomain[];

enum Error {
  
  OK = 0,

#define NET_ERROR(label, value) ERR_ ## label = value,
#include "net/base/net_error_list.h"
#undef NET_ERROR

  
  ERR_CERT_BEGIN = ERR_CERT_COMMON_NAME_INVALID,
};

NET_EXPORT const char* ErrorToString(int error);

inline bool IsCertificateError(int error) {
  
  
  return (error <= ERR_CERT_BEGIN && error > ERR_CERT_END) ||
         (error == ERR_SSL_WEAK_SERVER_EPHEMERAL_DH_KEY) ||
         (error == ERR_SSL_PINNED_KEY_NOT_IN_CERT_CHAIN);
}

NET_EXPORT Error MapSystemError(int os_error);

NET_EXPORT std::vector<int> GetAllErrorCodesForUma();

NET_EXPORT Error PlatformFileErrorToNetError(
    base::PlatformFileError file_error);

}  

#endif  