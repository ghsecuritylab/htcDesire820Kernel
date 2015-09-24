// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEBKIT_BROWSER_APPCACHE_APPCACHE_QUOTA_CLIENT_H_
#define WEBKIT_BROWSER_APPCACHE_APPCACHE_QUOTA_CLIENT_H_

#include <deque>
#include <map>
#include <string>

#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/completion_callback.h"
#include "webkit/browser/appcache/appcache_storage.h"
#include "webkit/browser/quota/quota_client.h"
#include "webkit/browser/quota/quota_task.h"
#include "webkit/browser/webkit_storage_browser_export.h"
#include "webkit/common/quota/quota_types.h"

namespace appcache {

class AppCacheService;
class AppCacheStorageImpl;
class AppCacheQuotaClientTest;

class AppCacheQuotaClient : public quota::QuotaClient {
 public:
  typedef std::deque<base::Closure> RequestQueue;

  virtual ~AppCacheQuotaClient();

  
  virtual ID id() const OVERRIDE;
  virtual void OnQuotaManagerDestroyed() OVERRIDE;
  virtual void GetOriginUsage(const GURL& origin,
                              quota::StorageType type,
                              const GetUsageCallback& callback) OVERRIDE;
  virtual void GetOriginsForType(quota::StorageType type,
                                 const GetOriginsCallback& callback) OVERRIDE;
  virtual void GetOriginsForHost(quota::StorageType type,
                                 const std::string& host,
                                 const GetOriginsCallback& callback) OVERRIDE;
  virtual void DeleteOriginData(const GURL& origin,
                                quota::StorageType type,
                                const DeletionCallback& callback) OVERRIDE;
  virtual bool DoesSupport(quota::StorageType type) const OVERRIDE;

 private:
  friend class AppCacheService;  
  friend class AppCacheStorageImpl;  
  friend class AppCacheQuotaClientTest;

  WEBKIT_STORAGE_BROWSER_EXPORT
      explicit AppCacheQuotaClient(AppCacheService* service);

  void DidDeleteAppCachesForOrigin(int rv);
  void GetOriginsHelper(quota::StorageType type,
                        const std::string& opt_host,
                        const GetOriginsCallback& callback);
  void ProcessPendingRequests();
  void DeletePendingRequests();
  const AppCacheStorage::UsageMap* GetUsageMap();
  net::CancelableCompletionCallback* GetServiceDeleteCallback();

  
  WEBKIT_STORAGE_BROWSER_EXPORT void NotifyAppCacheReady();
  WEBKIT_STORAGE_BROWSER_EXPORT void NotifyAppCacheDestroyed();

  
  
  RequestQueue pending_batch_requests_;
  RequestQueue pending_serial_requests_;

  
  
  DeletionCallback current_delete_request_callback_;
  scoped_ptr<net::CancelableCompletionCallback> service_delete_callback_;

  AppCacheService* service_;
  bool appcache_is_ready_;
  bool quota_manager_is_destroyed_;

  DISALLOW_COPY_AND_ASSIGN(AppCacheQuotaClient);
};

}  

#endif  
