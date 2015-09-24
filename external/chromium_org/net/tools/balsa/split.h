// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_TOOLS_BALSA_SPLIT_H_
#define NET_TOOLS_BALSA_SPLIT_H_

#include <vector>
#include "base/strings/string_piece.h"

namespace net {

void SplitStringPieceToVector(const base::StringPiece& full,
                              const char* delim,
                              std::vector<base::StringPiece>* vec,
                              bool omit_empty_strings);

}  

#endif  
