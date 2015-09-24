// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_SSL_SSL_POLICY_BACKEND_H_
#define CONTENT_BROWSER_SSL_SSL_POLICY_BACKEND_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "net/cert/cert_status_flags.h"
#include "net/cert/x509_certificate.h"

namespace content {
class NavigationControllerImpl;
class SSLHostState;

class SSLPolicyBackend {
 public:
  explicit SSLPolicyBackend(NavigationControllerImpl* controller);

  
  void HostRanInsecureContent(const std::string& host, int pid);

  
  bool DidHostRunInsecureContent(const std::string& host, int pid) const;

  
  
  void DenyCertForHost(net::X509Certificate* cert,
                       const std::string& host,
                       net::CertStatus error);

  
  
  void AllowCertForHost(net::X509Certificate* cert,
                        const std::string& host,
                        net::CertStatus error);

  
  net::CertPolicy::Judgment QueryPolicy(net::X509Certificate* cert,
                                        const std::string& host,
                                        net::CertStatus error);

 private:
  
  SSLHostState* ssl_host_state_;

  NavigationControllerImpl* controller_;

  DISALLOW_COPY_AND_ASSIGN(SSLPolicyBackend);
};

}  

#endif  
