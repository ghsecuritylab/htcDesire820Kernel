// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_SYNCER_H_
#define SYNC_ENGINE_SYNCER_H_

#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/synchronization/lock.h"
#include "sync/base/sync_export.h"
#include "sync/engine/conflict_resolver.h"
#include "sync/engine/syncer_types.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/sessions/sync_session.h"
#include "sync/util/extensions_activity.h"

namespace syncer {

class CancelationSignal;

class SYNC_EXPORT_PRIVATE Syncer {
 public:
  typedef std::vector<int64> UnsyncedMetaHandles;

  Syncer(CancelationSignal* cancelation_signal);
  virtual ~Syncer();

  bool ExitRequested();

  
  
  
  
  virtual bool NormalSyncShare(ModelTypeSet request_types,
                               const sessions::NudgeTracker& nudge_tracker,
                               sessions::SyncSession* session);

  
  
  
  
  
  virtual bool ConfigureSyncShare(
      ModelTypeSet request_types,
      sync_pb::GetUpdatesCallerInfo::GetUpdatesSource source,
      sessions::SyncSession* session);

  
  
  
  
  virtual bool PollSyncShare(ModelTypeSet request_types,
                             sessions::SyncSession* session);

 private:
  void ApplyUpdates(sessions::SyncSession* session);
  bool DownloadAndApplyUpdates(
      ModelTypeSet request_types,
      sessions::SyncSession* session,
      base::Callback<void(sync_pb::ClientToServerMessage*)> build_fn);

  
  
  
  
  SyncerError BuildAndPostCommits(
      ModelTypeSet request_types,
      sessions::SyncSession* session);

  void HandleCycleBegin(sessions::SyncSession* session);
  bool HandleCycleEnd(
      sessions::SyncSession* session,
      sync_pb::GetUpdatesCallerInfo::GetUpdatesSource source);

  syncer::CancelationSignal* const cancelation_signal_;

  friend class SyncerTest;
  FRIEND_TEST_ALL_PREFIXES(SyncerTest, NameClashWithResolver);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest, IllegalAndLegalUpdates);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest, TestCommitListOrderingAndNewParent);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest,
                           TestCommitListOrderingAndNewParentAndChild);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest, TestCommitListOrderingCounterexample);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest, TestCommitListOrderingWithNesting);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest, TestCommitListOrderingWithNewItems);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest, TestGetUnsyncedAndSimpleCommit);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest, TestPurgeWhileUnsynced);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest, TestPurgeWhileUnapplied);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest, UnappliedUpdateDuringCommit);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest, DeletingEntryInFolder);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest,
                           LongChangelistCreatesFakeOrphanedEntries);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest, QuicklyMergeDualCreatedHierarchy);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest, LongChangelistWithApplicationConflict);
  FRIEND_TEST_ALL_PREFIXES(SyncerTest, DeletingEntryWithLocalEdits);
  FRIEND_TEST_ALL_PREFIXES(EntryCreatedInNewFolderTest,
                           EntryCreatedInNewFolderMidSync);

  DISALLOW_COPY_AND_ASSIGN(Syncer);
};

}  

#endif  
