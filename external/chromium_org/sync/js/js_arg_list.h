// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_JS_JS_ARG_LIST_H_
#define SYNC_JS_JS_ARG_LIST_H_


#include <string>

#include "base/values.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/util/immutable.h"

namespace syncer {

class SYNC_EXPORT JsArgList {
 public:
  
  JsArgList();

  
  explicit JsArgList(base::ListValue* args);

  ~JsArgList();

  const base::ListValue& Get() const;

  std::string ToString() const;

  

 private:
  typedef Immutable<base::ListValue, HasSwapMemFnByPtr<base::ListValue> >
      ImmutableListValue;
  ImmutableListValue args_;
};

}  

#endif  