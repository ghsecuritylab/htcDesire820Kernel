// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_DIR_READER_FALLBACK_H_
#define BASE_DIR_READER_FALLBACK_H_
#pragma once

namespace base {

class DirReaderFallback {
 public:
  
  
  explicit DirReaderFallback(const char* directory_path) { }
  
  
  bool IsValid() const { return false; }
  
  bool Next() { return false; }
  
  const char* name() { return 0;}
  
  int fd() const { return -1; }
  
  static bool IsFallback() { return true; }
};

}  

#endif  
