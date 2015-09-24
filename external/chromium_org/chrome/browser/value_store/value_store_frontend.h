// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_VALUE_STORE_VALUE_STORE_FRONTEND_H_
#define CHROME_BROWSER_VALUE_STORE_VALUE_STORE_FRONTEND_H_

#include <string>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "base/values.h"
#include "chrome/browser/value_store/value_store.h"

namespace base {
class FilePath;
}

class ValueStoreFrontend
    : public base::SupportsWeakPtr<ValueStoreFrontend>,
      public base::NonThreadSafe {
 public:
  typedef base::Callback<void(scoped_ptr<base::Value>)> ReadCallback;

  ValueStoreFrontend();
  explicit ValueStoreFrontend(const base::FilePath& db_path);
  
  explicit ValueStoreFrontend(scoped_ptr<ValueStore> value_store);
  ~ValueStoreFrontend();

  void Init(const base::FilePath& db_path);

  
  
  void Get(const std::string& key, const ReadCallback& callback);

  
  void Set(const std::string& key, scoped_ptr<base::Value> value);

  
  void Remove(const std::string& key);

 private:
  class Backend;

  
  
  scoped_refptr<Backend> backend_;

  DISALLOW_COPY_AND_ASSIGN(ValueStoreFrontend);
};

#endif  
