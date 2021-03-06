// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_EXTENSIONS_API_FILE_HANDLERS_FILE_HANDLERS_PARSER_H_
#define CHROME_COMMON_EXTENSIONS_API_FILE_HANDLERS_FILE_HANDLERS_PARSER_H_

#include <set>
#include <string>
#include <vector>

#include "extensions/common/extension.h"
#include "extensions/common/manifest_handler.h"

namespace extensions {

struct FileHandlerInfo {
  FileHandlerInfo();
  ~FileHandlerInfo();

  std::string id;
  std::string title;

  
  std::set<std::string> extensions;

  
  std::set<std::string> types;
};

struct FileHandlers : public Extension::ManifestData {
  FileHandlers();
  virtual ~FileHandlers();

  std::vector<FileHandlerInfo> file_handlers;

  static const std::vector<FileHandlerInfo>* GetFileHandlers(
      const Extension* extension);
};

class FileHandlersParser : public ManifestHandler {
 public:
  FileHandlersParser();
  virtual ~FileHandlersParser();

  virtual bool Parse(Extension* extension, base::string16* error) OVERRIDE;

 private:
  virtual const std::vector<std::string> Keys() const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(FileHandlersParser);
};

}  

#endif  
