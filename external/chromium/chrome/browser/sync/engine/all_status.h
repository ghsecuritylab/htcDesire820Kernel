// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_ENGINE_ALL_STATUS_H_
#define CHROME_BROWSER_SYNC_ENGINE_ALL_STATUS_H_
#pragma once

#include <map>

#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "chrome/browser/sync/engine/syncapi.h"
#include "chrome/browser/sync/engine/syncer_types.h"

namespace browser_sync {

class ScopedStatusLock;
class ServerConnectionManager;
class Syncer;
class SyncerThread;
struct AuthWatcherEvent;
struct ServerConnectionEvent;

class AllStatus : public SyncEngineEventListener {
  friend class ScopedStatusLock;
 public:

  AllStatus();
  ~AllStatus();

  void HandleServerConnectionEvent(const ServerConnectionEvent& event);

  void HandleAuthWatcherEvent(const AuthWatcherEvent& event);

  virtual void OnSyncEngineEvent(const SyncEngineEvent& event);

  sync_api::SyncManager::Status status() const;

  void SetNotificationsEnabled(bool notifications_enabled);

  void IncrementNotificationsSent();

  void IncrementNotificationsReceived();

 protected:
  
  
  sync_api::SyncManager::Status CalcSyncing(const SyncEngineEvent& event) const;
  sync_api::SyncManager::Status CreateBlankStatus() const;

  
  void CalcStatusChanges();

  sync_api::SyncManager::Status status_;

  mutable base::Lock mutex_;  
  DISALLOW_COPY_AND_ASSIGN(AllStatus);
};

class ScopedStatusLock {
 public:
  explicit ScopedStatusLock(AllStatus* allstatus);
  ~ScopedStatusLock();
 protected:
  AllStatus* allstatus_;
};

}  

#endif  