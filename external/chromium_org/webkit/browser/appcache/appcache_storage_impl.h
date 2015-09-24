// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEBKIT_BROWSER_APPCACHE_APPCACHE_STORAGE_IMPL_H_
#define WEBKIT_BROWSER_APPCACHE_APPCACHE_STORAGE_IMPL_H_

#include <deque>
#include <map>
#include <set>
#include <utility>
#include <vector>

#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/memory/weak_ptr.h"
#include "base/message_loop/message_loop_proxy.h"
#include "webkit/browser/appcache/appcache_database.h"
#include "webkit/browser/appcache/appcache_disk_cache.h"
#include "webkit/browser/appcache/appcache_storage.h"
#include "webkit/browser/webkit_storage_browser_export.h"

namespace content {
class ChromeAppCacheServiceTest;
}

namespace appcache {

class AppCacheStorageImpl : public AppCacheStorage {
 public:
  explicit AppCacheStorageImpl(AppCacheService* service);
  virtual ~AppCacheStorageImpl();

  void Initialize(const base::FilePath& cache_directory,
                  base::MessageLoopProxy* db_thread,
                  base::MessageLoopProxy* cache_thread);
  void Disable();
  bool is_disabled() const { return is_disabled_; }

  
  virtual void GetAllInfo(Delegate* delegate) OVERRIDE;
  virtual void LoadCache(int64 id, Delegate* delegate) OVERRIDE;
  virtual void LoadOrCreateGroup(const GURL& manifest_url,
                                 Delegate* delegate) OVERRIDE;
  virtual void StoreGroupAndNewestCache(AppCacheGroup* group,
                                        AppCache* newest_cache,
                                        Delegate* delegate) OVERRIDE;
  virtual void FindResponseForMainRequest(const GURL& url,
                                          const GURL& preferred_manifest_url,
                                          Delegate* delegate) OVERRIDE;
  virtual void FindResponseForSubRequest(
      AppCache* cache, const GURL& url,
      AppCacheEntry* found_entry, AppCacheEntry* found_fallback_entry,
      bool* found_network_namespace) OVERRIDE;
  virtual void MarkEntryAsForeign(const GURL& entry_url,
                                  int64 cache_id) OVERRIDE;
  virtual void MakeGroupObsolete(AppCacheGroup* group,
                                 Delegate* delegate) OVERRIDE;
  virtual AppCacheResponseReader* CreateResponseReader(
      const GURL& manifest_url, int64 group_id, int64 response_id) OVERRIDE;
  virtual AppCacheResponseWriter* CreateResponseWriter(
      const GURL& manifest_url, int64 group_id) OVERRIDE;
  virtual void DoomResponses(const GURL& manifest_url,
                             const std::vector<int64>& response_ids) OVERRIDE;
  virtual void DeleteResponses(const GURL& manifest_url,
                               const std::vector<int64>& response_ids) OVERRIDE;
  virtual void PurgeMemory() OVERRIDE;

 private:
  friend class AppCacheStorageImplTest;

  
  
  
  class DatabaseTask;
  class InitTask;
  class CloseConnectionTask;
  class DisableDatabaseTask;
  class GetAllInfoTask;
  class StoreOrLoadTask;
  class CacheLoadTask;
  class GroupLoadTask;
  class StoreGroupAndCacheTask;
  class FindMainResponseTask;
  class MarkEntryAsForeignTask;
  class MakeGroupObsoleteTask;
  class GetDeletableResponseIdsTask;
  class InsertDeletableResponseIdsTask;
  class DeleteDeletableResponseIdsTask;
  class UpdateGroupLastAccessTimeTask;

  typedef std::deque<DatabaseTask*> DatabaseTaskQueue;
  typedef std::map<int64, CacheLoadTask*> PendingCacheLoads;
  typedef std::map<GURL, GroupLoadTask*> PendingGroupLoads;
  typedef std::deque<std::pair<GURL, int64> > PendingForeignMarkings;
  typedef std::set<StoreGroupAndCacheTask*> PendingQuotaQueries;

  bool IsInitTaskComplete() {
    return last_cache_id_ != AppCacheStorage::kUnitializedId;
  }

  CacheLoadTask* GetPendingCacheLoadTask(int64 cache_id);
  GroupLoadTask* GetPendingGroupLoadTask(const GURL& manifest_url);
  void GetPendingForeignMarkingsForCache(
      int64 cache_id, std::vector<GURL>* urls);

  void ScheduleSimpleTask(const base::Closure& task);
  void RunOnePendingSimpleTask();

  void DelayedStartDeletingUnusedResponses();
  void StartDeletingResponses(const std::vector<int64>& response_ids);
  void ScheduleDeleteOneResponse();
  void DeleteOneResponse();

  void OnDeletedOneResponse(int rv);
  void OnDiskCacheInitialized(int rv);
  void CallReinitialize();

  
  bool FindResponseForMainRequestInGroup(
      AppCacheGroup* group,  const GURL& url, Delegate* delegate);
  void DeliverShortCircuitedFindMainResponse(
      const GURL& url,
      const AppCacheEntry& found_entry,
      scoped_refptr<AppCacheGroup> group,
      scoped_refptr<AppCache> newest_cache,
      scoped_refptr<DelegateReference> delegate_ref);

  void CallOnMainResponseFound(
      DelegateReferenceVector* delegates,
      const GURL& url, const AppCacheEntry& entry,
      const GURL& namespace_entry_url, const AppCacheEntry& fallback_entry,
      int64 cache_id, int64 group_id, const GURL& manifest_url);

  WEBKIT_STORAGE_BROWSER_EXPORT AppCacheDiskCache* disk_cache();

  
  base::FilePath cache_directory_;
  bool is_incognito_;

  
  
  
  scoped_refptr<base::MessageLoopProxy> db_thread_;
  scoped_refptr<base::MessageLoopProxy> cache_thread_;

  
  DatabaseTaskQueue scheduled_database_tasks_;
  PendingCacheLoads pending_cache_loads_;
  PendingGroupLoads pending_group_loads_;
  PendingForeignMarkings pending_foreign_markings_;
  PendingQuotaQueries pending_quota_queries_;

  
  std::deque<int64> deletable_response_ids_;
  std::vector<int64> deleted_response_ids_;
  bool is_response_deletion_scheduled_;
  bool did_start_deleting_responses_;
  int64 last_deletable_response_rowid_;

  
  AppCacheDatabase* database_;

  
  
  bool is_disabled_;

  scoped_ptr<AppCacheDiskCache> disk_cache_;

  
  
  std::deque<base::Closure> pending_simple_tasks_;
  base::WeakPtrFactory<AppCacheStorageImpl> weak_factory_;

  friend class content::ChromeAppCacheServiceTest;
};

}  

#endif  