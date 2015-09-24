// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BROWSING_DATA_MOCK_BROWSING_DATA_DATABASE_HELPER_H_
#define CHROME_BROWSER_BROWSING_DATA_MOCK_BROWSING_DATA_DATABASE_HELPER_H_

#include <list>
#include <map>

#include "base/callback.h"
#include "chrome/browser/browsing_data/browsing_data_database_helper.h"

class MockBrowsingDataDatabaseHelper : public BrowsingDataDatabaseHelper {
 public:
  explicit MockBrowsingDataDatabaseHelper(Profile* profile);

  virtual void StartFetching(
      const base::Callback<void(const std::list<DatabaseInfo>&)>& callback)
          OVERRIDE;

  virtual void DeleteDatabase(const std::string& origin,
      const std::string& name) OVERRIDE;

  
  void AddDatabaseSamples();

  
  void Notify();

  
  void Reset();

  
  
  bool AllDeleted();

  std::string last_deleted_origin_;

  std::string last_deleted_db_;

 private:
  virtual ~MockBrowsingDataDatabaseHelper();

  base::Callback<void(const std::list<DatabaseInfo>&)> callback_;

  
  std::map<const std::string, bool> databases_;

  std::list<DatabaseInfo> response_;
};

#endif  