// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_HISTORY_ARCHIVED_DATABASE_H_
#define CHROME_BROWSER_HISTORY_ARCHIVED_DATABASE_H_
#pragma once

#include "app/sql/connection.h"
#include "app/sql/init_status.h"
#include "app/sql/meta_table.h"
#include "base/basictypes.h"
#include "chrome/browser/history/url_database.h"
#include "chrome/browser/history/visit_database.h"

class FilePath;

namespace history {

class ArchivedDatabase : public URLDatabase,
                         public VisitDatabase {
 public:
  
  ArchivedDatabase();
  virtual ~ArchivedDatabase();

  
  
  bool Init(const FilePath& file_name);

  
  
  
  void BeginTransaction();
  void CommitTransaction();

 private:
  
  virtual sql::Connection& GetDB();

  
  
  
  
  
  
  
  sql::InitStatus EnsureCurrentVersion();

  
  sql::Connection db_;
  sql::MetaTable meta_table_;

  DISALLOW_COPY_AND_ASSIGN(ArchivedDatabase);
};

}  

#endif  
