// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_TOOLS_FLIP_SERVER_BALSA_HEADERS_TOKEN_UTILS_H_
#define NET_TOOLS_FLIP_SERVER_BALSA_HEADERS_TOKEN_UTILS_H_
#pragma once

#include "net/tools/flip_server/balsa_headers.h"
#include "base/string_piece.h"

namespace net {

class BalsaHeadersTokenUtils {
 public:
  

  
  
  
  
  static bool CheckHeaderForLastToken(const BalsaHeaders& headers,
                                      const base::StringPiece& key,
                                      const base::StringPiece& token);

  
  
  
  static void TokenizeHeaderValue(const BalsaHeaders& headers,
                                  const base::StringPiece& key,
                                  BalsaHeaders::HeaderTokenList* tokens);

  
  
  
  static void RemoveLastTokenFromHeaderValue(const base::StringPiece& key,
                                             BalsaHeaders* headers);

  
  
  
  static void ParseTokenList(const char* start,
                             const char* end,
                             BalsaHeaders::HeaderTokenList* tokens);

 private:
  
  static void TokenizeHeaderLine(
      const BalsaHeaders& headers,
      const BalsaHeaders::HeaderLineDescription& line,
      BalsaHeaders::HeaderTokenList* tokens);

  BalsaHeadersTokenUtils();  
};

}  

#endif  
