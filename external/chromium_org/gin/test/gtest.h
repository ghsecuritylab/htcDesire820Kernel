// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GIN_TEST_GTEST_H_
#define GIN_TEST_GTEST_H_

#include "v8/include/v8.h"

namespace gin {

class GTest {
 public:
  static const char kModuleName[];
  static v8::Local<v8::ObjectTemplate> GetTemplate(v8::Isolate* isolate);
};

}  

#endif  
