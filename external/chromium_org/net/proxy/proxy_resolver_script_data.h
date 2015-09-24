// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_PROXY_PROXY_RESOLVER_SCRIPT_DATA_H_
#define NET_PROXY_PROXY_RESOLVER_SCRIPT_DATA_H_

#include "base/memory/ref_counted.h"
#include "base/strings/string16.h"
#include "net/base/net_export.h"
#include "url/gurl.h"

namespace net {

class NET_EXPORT_PRIVATE ProxyResolverScriptData
    : public base::RefCountedThreadSafe<ProxyResolverScriptData> {
 public:
  enum Type {
    TYPE_SCRIPT_CONTENTS,
    TYPE_SCRIPT_URL,
    TYPE_AUTO_DETECT,
  };

  
  static scoped_refptr<ProxyResolverScriptData> FromUTF8(
      const std::string& utf8);

  
  static scoped_refptr<ProxyResolverScriptData> FromUTF16(
      const base::string16& utf16);

  
  static scoped_refptr<ProxyResolverScriptData> FromURL(const GURL& url);

  
  static scoped_refptr<ProxyResolverScriptData> ForAutoDetect();

  Type type() const {
    return type_;
  }

  
  
  const base::string16& utf16() const;

  
  
  const GURL& url() const;

  
  bool Equals(const ProxyResolverScriptData* other) const;

 private:
  friend class base::RefCountedThreadSafe<ProxyResolverScriptData>;
  ProxyResolverScriptData(Type type,
                          const GURL& url,
                          const base::string16& utf16);
  virtual ~ProxyResolverScriptData();


  const Type type_;
  const GURL url_;
  const base::string16 utf16_;
};

}  

#endif  