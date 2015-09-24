// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_SYNC_FILE_SYSTEM_EXTENSION_SYNC_EVENT_OBSERVER_H_
#define CHROME_BROWSER_EXTENSIONS_API_SYNC_FILE_SYSTEM_EXTENSION_SYNC_EVENT_OBSERVER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/values.h"
#include "chrome/browser/sync_file_system/sync_event_observer.h"
#include "components/browser_context_keyed_service/browser_context_keyed_service.h"

class Profile;

namespace sync_file_system {
class SyncFileSystemService;
}

namespace extensions {

class ExtensionSyncEventObserver
    : public sync_file_system::SyncEventObserver,
      public BrowserContextKeyedService {
 public:
  explicit ExtensionSyncEventObserver(Profile* profile);
  virtual ~ExtensionSyncEventObserver();

  void InitializeForService(
      sync_file_system::SyncFileSystemService* sync_service);

  
  virtual void Shutdown() OVERRIDE;

  
  virtual void OnSyncStateUpdated(
      const GURL& app_origin,
      sync_file_system::SyncServiceState state,
      const std::string& description) OVERRIDE;

  virtual void OnFileSynced(
      const fileapi::FileSystemURL& url,
      sync_file_system::SyncFileStatus status,
      sync_file_system::SyncAction action,
      sync_file_system::SyncDirection direction) OVERRIDE;

 private:
  
  
  std::string GetExtensionId(const GURL& app_origin);

  Profile* profile_;

  
  sync_file_system::SyncFileSystemService* sync_service_;

  void BroadcastOrDispatchEvent(const GURL& app_origin,
                                const std::string& event_name,
                                scoped_ptr<base::ListValue> value);

  DISALLOW_COPY_AND_ASSIGN(ExtensionSyncEventObserver);
};

}  

#endif  
