// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GIN_PUBLIC_CONTEXT_HOLDER_H_
#define GIN_PUBLIC_CONTEXT_HOLDER_H_

#include <list>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "gin/gin_export.h"
#include "v8/include/v8.h"

namespace gin {

enum ContextEmbedderDataFields {
  kDebugIdIndex = 0,
  kPerContextDataStartIndex,
};

class PerContextData;

class GIN_EXPORT ContextHolder {
 public:
  explicit ContextHolder(v8::Isolate* isolate);
  ~ContextHolder();

  v8::Isolate* isolate() const { return isolate_; }

  v8::Handle<v8::Context> context() const {
    return v8::Local<v8::Context>::New(isolate_, context_);
  }

  void SetContext(v8::Handle<v8::Context> context);

 private:
  v8::Isolate* isolate_;
  v8::Persistent<v8::Context> context_;
  scoped_ptr<PerContextData> data_;

  DISALLOW_COPY_AND_ASSIGN(ContextHolder);
};

}  

#endif  
