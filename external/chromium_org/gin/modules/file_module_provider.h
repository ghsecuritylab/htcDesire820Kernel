// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GIN_MODULES_FILE_MODULE_PROVIDER_H_
#define GIN_MODULES_FILE_MODULE_PROVIDER_H_

#include <set>
#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "gin/gin_export.h"
#include "gin/runner.h"

namespace gin {

class GIN_EXPORT FileModuleProvider {
 public:
  explicit FileModuleProvider(
      const std::vector<base::FilePath>& search_paths);
  ~FileModuleProvider();

  
  
  void AttempToLoadModules(Runner* runner, const std::set<std::string>& ids);

 private:
  std::vector<base::FilePath> search_paths_;

  
  
  std::set<std::string> attempted_ids_;

  DISALLOW_COPY_AND_ASSIGN(FileModuleProvider);
};

}  

#endif  
