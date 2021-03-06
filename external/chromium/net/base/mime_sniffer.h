// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_BASE_MIME_SNIFFER_H__
#define NET_BASE_MIME_SNIFFER_H__
#pragma once

#include <string>
#include "net/base/net_export.h"

class GURL;

namespace net {

const int kMaxBytesToSniff = 1024;

bool ShouldSniffMimeType(const GURL& url, const std::string& mime_type);

NET_EXPORT bool SniffMimeType(const char* content, size_t content_size,
                   const GURL& url, const std::string& type_hint,
                   std::string* result);

}  

#endif  
