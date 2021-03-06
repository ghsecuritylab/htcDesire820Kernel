// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_API_FAKE_SYNCABLE_SERVICE_H_
#define SYNC_API_FAKE_SYNCABLE_SERVICE_H_

#include "sync/api/syncable_service.h"

namespace syncer {

class SyncErrorFactory;

class FakeSyncableService : public SyncableService {
 public:
  FakeSyncableService();
  virtual ~FakeSyncableService();

  
  void set_merge_data_and_start_syncing_error(const SyncError& error);
  void set_process_sync_changes_error(const SyncError& error);

  
  
  bool syncing() const;

  
  virtual SyncMergeResult MergeDataAndStartSyncing(
      ModelType type,
      const SyncDataList& initial_sync_data,
      scoped_ptr<SyncChangeProcessor> sync_processor,
      scoped_ptr<SyncErrorFactory> sync_error_factory) OVERRIDE;
  virtual void StopSyncing(ModelType type) OVERRIDE;
  virtual SyncDataList GetAllSyncData(ModelType type) const OVERRIDE;
  virtual SyncError ProcessSyncChanges(
      const tracked_objects::Location& from_here,
      const SyncChangeList& change_list) OVERRIDE;

 private:
  scoped_ptr<SyncChangeProcessor> sync_processor_;
  SyncError merge_data_and_start_syncing_error_;
  SyncError process_sync_changes_error_;
  bool syncing_;
  ModelType type_;
};

}  

#endif  
