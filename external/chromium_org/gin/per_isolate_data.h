// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GIN_PER_ISOLATE_DATA_H_
#define GIN_PER_ISOLATE_DATA_H_

#include <map>

#include "base/basictypes.h"
#include "gin/gin_export.h"
#include "gin/public/wrapper_info.h"
#include "v8/include/v8.h"

namespace gin {

class GIN_EXPORT PerIsolateData {
 public:
  explicit PerIsolateData(v8::Isolate* isolate);
  ~PerIsolateData();

  static PerIsolateData* From(v8::Isolate* isolate);

  
  
  
  void SetObjectTemplate(WrapperInfo* info,
                         v8::Local<v8::ObjectTemplate> object_template);
  void SetFunctionTemplate(WrapperInfo* info,
                           v8::Local<v8::FunctionTemplate> function_template);

  
  
  
  
  v8::Local<v8::ObjectTemplate> GetObjectTemplate(WrapperInfo* info);
  v8::Local<v8::FunctionTemplate> GetFunctionTemplate(WrapperInfo* info);

  v8::Isolate* isolate() { return isolate_; }

 private:
  typedef std::map<
      WrapperInfo*, v8::Eternal<v8::ObjectTemplate> > ObjectTemplateMap;
  typedef std::map<
      WrapperInfo*, v8::Eternal<v8::FunctionTemplate> > FunctionTemplateMap;

  
  
  v8::Isolate* isolate_;
  ObjectTemplateMap object_templates_;
  FunctionTemplateMap function_templates_;

  DISALLOW_COPY_AND_ASSIGN(PerIsolateData);
};

}  

#endif  
