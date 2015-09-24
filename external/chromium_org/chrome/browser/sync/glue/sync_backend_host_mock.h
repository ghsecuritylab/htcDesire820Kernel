// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_GLUE_SYNC_BACKEND_HOST_MOCK_H_
#define CHROME_BROWSER_SYNC_GLUE_SYNC_BACKEND_HOST_MOCK_H_

#include <string>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "chrome/browser/sync/glue/sync_backend_host.h"
#include "sync/internal_api/public/util/weak_handle.h"

namespace browser_sync {

class SyncBackendHostMock : public SyncBackendHost {
 public:
  SyncBackendHostMock();
  virtual ~SyncBackendHostMock();

  virtual void Initialize(
      SyncFrontend* frontend,
      scoped_ptr<base::Thread> sync_thread,
      const syncer::WeakHandle<syncer::JsEventHandler>& event_handler,
      const GURL& service_url,
      const syncer::SyncCredentials& credentials,
      bool delete_sync_data_folder,
      scoped_ptr<syncer::SyncManagerFactory> sync_manager_factory,
      scoped_ptr<syncer::UnrecoverableErrorHandler> unrecoverable_error_handler,
      syncer::ReportUnrecoverableErrorFunction
          report_unrecoverable_error_function,
      syncer::NetworkResources* network_resources) OVERRIDE;

  virtual void UpdateCredentials(
      const syncer::SyncCredentials& credentials) OVERRIDE;

  virtual void StartSyncingWithServer() OVERRIDE;

  virtual void SetEncryptionPassphrase(
      const std::string& passphrase,
      bool is_explicit) OVERRIDE;

  virtual bool SetDecryptionPassphrase(
      const std::string& passphrase) OVERRIDE;

  virtual void StopSyncingForShutdown() OVERRIDE;

  virtual scoped_ptr<base::Thread> Shutdown(ShutdownOption option) OVERRIDE;

  virtual void UnregisterInvalidationIds() OVERRIDE;

  virtual void ConfigureDataTypes(
      syncer::ConfigureReason reason,
      const DataTypeConfigStateMap& config_state_map,
      const base::Callback<void(syncer::ModelTypeSet,
                                syncer::ModelTypeSet)>& ready_task,
      const base::Callback<void()>& retry_callback) OVERRIDE;

  virtual void EnableEncryptEverything() OVERRIDE;

  virtual void ActivateDataType(
      syncer::ModelType type, syncer::ModelSafeGroup group,
      ChangeProcessor* change_processor) OVERRIDE;
  virtual void DeactivateDataType(syncer::ModelType type) OVERRIDE;

  virtual syncer::UserShare* GetUserShare() const OVERRIDE;

  virtual Status GetDetailedStatus() OVERRIDE;

  virtual syncer::sessions::SyncSessionSnapshot
      GetLastSessionSnapshot() const OVERRIDE;

  virtual bool HasUnsyncedItems() const OVERRIDE;

  virtual bool IsNigoriEnabled() const OVERRIDE;

  virtual syncer::PassphraseType GetPassphraseType() const OVERRIDE;

  virtual base::Time GetExplicitPassphraseTime() const OVERRIDE;

  virtual bool IsCryptographerReady(
      const syncer::BaseTransaction* trans) const OVERRIDE;

  virtual void GetModelSafeRoutingInfo(
      syncer::ModelSafeRoutingInfo* out) const OVERRIDE;

  virtual SyncedDeviceTracker* GetSyncedDeviceTracker() const OVERRIDE;

  virtual base::MessageLoop* GetSyncLoopForTesting() OVERRIDE;

  void set_fail_initial_download(bool should_fail);

 private:
  bool fail_initial_download_;
};

}  

#endif  