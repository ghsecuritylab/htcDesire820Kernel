// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SSL_SSL_CLIENT_CERTIFICATE_SELECTOR_H_
#define CHROME_BROWSER_SSL_SSL_CLIENT_CERTIFICATE_SELECTOR_H_

#include "base/callback_forward.h"

namespace content {
class WebContents;
}

namespace net {
class HttpNetworkSession;
class SSLCertRequestInfo;
class X509Certificate;
}

namespace chrome {

typedef base::Callback<void(net::X509Certificate*)> SelectCertificateCallback;

void ShowSSLClientCertificateSelector(
    content::WebContents* contents,
    const net::HttpNetworkSession* network_session,
    net::SSLCertRequestInfo* cert_request_info,
    const SelectCertificateCallback& callback);

}  

#endif  