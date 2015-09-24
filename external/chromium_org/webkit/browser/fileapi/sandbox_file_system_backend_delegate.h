// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef WEBKIT_BROWSER_FILEAPI_SANDBOX_FILE_SYSTEM_BACKEND_DELEGATE_H_
#define WEBKIT_BROWSER_FILEAPI_SANDBOX_FILE_SYSTEM_BACKEND_DELEGATE_H_

#include <map>
#include <set>
#include <string>
#include <utility>

#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "base/time/time.h"
#include "webkit/browser/fileapi/file_system_backend.h"
#include "webkit/browser/fileapi/file_system_options.h"
#include "webkit/browser/fileapi/file_system_quota_util.h"
#include "webkit/browser/webkit_storage_browser_export.h"

namespace base {
class SequencedTaskRunner;
}

namespace quota {
class QuotaManagerProxy;
class SpecialStoragePolicy;
}

namespace webkit_blob {
class FileStreamReader;
}

namespace fileapi {

class AsyncFileUtil;
class FileStreamWriter;
class FileSystemFileUtil;
class FileSystemOperationContext;
class FileSystemURL;
class FileSystemUsageCache;
class ObfuscatedFileUtil;
class QuotaReservationManager;
class SandboxFileSystemBackend;
class SandboxFileSystemTestHelper;
class SandboxQuotaObserver;

class WEBKIT_STORAGE_BROWSER_EXPORT SandboxFileSystemBackendDelegate
    : public FileSystemQuotaUtil {
 public:
  typedef FileSystemBackend::OpenFileSystemCallback OpenFileSystemCallback;

  
  static const base::FilePath::CharType kFileSystemDirectory[];

  
  
  class OriginEnumerator {
   public:
    virtual ~OriginEnumerator() {}

    
    virtual GURL Next() = 0;

    
    virtual bool HasFileSystemType(FileSystemType type) const = 0;
  };

  
  static std::string GetTypeString(FileSystemType type);

  SandboxFileSystemBackendDelegate(
      quota::QuotaManagerProxy* quota_manager_proxy,
      base::SequencedTaskRunner* file_task_runner,
      const base::FilePath& profile_path,
      quota::SpecialStoragePolicy* special_storage_policy,
      const FileSystemOptions& file_system_options);

  virtual ~SandboxFileSystemBackendDelegate();

  
  
  OriginEnumerator* CreateOriginEnumerator();

  
  
  
  
  
  
  base::FilePath GetBaseDirectoryForOriginAndType(
      const GURL& origin_url,
      FileSystemType type,
      bool create);

  
  void OpenFileSystem(
      const GURL& origin_url,
      FileSystemType type,
      OpenFileSystemMode mode,
      const OpenFileSystemCallback& callback,
      const GURL& root_url);
  scoped_ptr<FileSystemOperationContext> CreateFileSystemOperationContext(
      const FileSystemURL& url,
      FileSystemContext* context,
      base::PlatformFileError* error_code) const;
  scoped_ptr<webkit_blob::FileStreamReader> CreateFileStreamReader(
      const FileSystemURL& url,
      int64 offset,
      const base::Time& expected_modification_time,
      FileSystemContext* context) const;
  scoped_ptr<FileStreamWriter> CreateFileStreamWriter(
      const FileSystemURL& url,
      int64 offset,
      FileSystemContext* context,
      FileSystemType type) const;

  
  virtual base::PlatformFileError DeleteOriginDataOnFileThread(
      FileSystemContext* context,
      quota::QuotaManagerProxy* proxy,
      const GURL& origin_url,
      FileSystemType type) OVERRIDE;
  virtual void GetOriginsForTypeOnFileThread(
      FileSystemType type,
      std::set<GURL>* origins) OVERRIDE;
  virtual void GetOriginsForHostOnFileThread(
      FileSystemType type,
      const std::string& host,
      std::set<GURL>* origins) OVERRIDE;
  virtual int64 GetOriginUsageOnFileThread(
      FileSystemContext* context,
      const GURL& origin_url,
      FileSystemType type) OVERRIDE;
  virtual scoped_refptr<QuotaReservation>
      CreateQuotaReservationOnFileTaskRunner(
          const GURL& origin_url,
          FileSystemType type) OVERRIDE;
  virtual void AddFileUpdateObserver(
      FileSystemType type,
      FileUpdateObserver* observer,
      base::SequencedTaskRunner* task_runner) OVERRIDE;
  virtual void AddFileChangeObserver(
      FileSystemType type,
      FileChangeObserver* observer,
      base::SequencedTaskRunner* task_runner) OVERRIDE;
  virtual void AddFileAccessObserver(
      FileSystemType type,
      FileAccessObserver* observer,
      base::SequencedTaskRunner* task_runner) OVERRIDE;
  virtual const UpdateObserverList* GetUpdateObservers(
      FileSystemType type) const OVERRIDE;
  virtual const ChangeObserverList* GetChangeObservers(
      FileSystemType type) const OVERRIDE;
  virtual const AccessObserverList* GetAccessObservers(
      FileSystemType type) const OVERRIDE;

  
  void RegisterQuotaUpdateObserver(FileSystemType type);

  void InvalidateUsageCache(const GURL& origin_url,
                            FileSystemType type);
  void StickyInvalidateUsageCache(const GURL& origin_url,
                                  FileSystemType type);

  void CollectOpenFileSystemMetrics(base::PlatformFileError error_code);

  base::SequencedTaskRunner* file_task_runner() {
    return file_task_runner_.get();
  }

  AsyncFileUtil* file_util() { return sandbox_file_util_.get(); }
  FileSystemUsageCache* usage_cache() { return file_system_usage_cache_.get(); }
  SandboxQuotaObserver* quota_observer() { return quota_observer_.get(); }

  quota::SpecialStoragePolicy* special_storage_policy() {
    return special_storage_policy_.get();
  }

  const FileSystemOptions& file_system_options() const {
    return file_system_options_;
  }

  FileSystemFileUtil* sync_file_util();

 private:
  friend class SandboxQuotaObserver;
  friend class SandboxFileSystemTestHelper;
  friend class QuotaBackendImpl;
  FRIEND_TEST_ALL_PREFIXES(SandboxFileSystemBackendDelegateTest, IsAccessValid);

  
  
  bool IsAccessValid(const FileSystemURL& url) const;

  
  
  bool IsAllowedScheme(const GURL& url) const;

  
  base::FilePath GetUsageCachePathForOriginAndType(
      const GURL& origin_url,
      FileSystemType type);

  
  static base::FilePath GetUsageCachePathForOriginAndType(
      ObfuscatedFileUtil* sandbox_file_util,
      const GURL& origin_url,
      FileSystemType type,
      base::PlatformFileError* error_out);

  int64 RecalculateUsage(FileSystemContext* context,
                         const GURL& origin,
                         FileSystemType type);

  ObfuscatedFileUtil* obfuscated_file_util();

  scoped_refptr<base::SequencedTaskRunner> file_task_runner_;

  scoped_ptr<AsyncFileUtil> sandbox_file_util_;
  scoped_ptr<FileSystemUsageCache> file_system_usage_cache_;
  scoped_ptr<SandboxQuotaObserver> quota_observer_;
  scoped_ptr<QuotaReservationManager> quota_reservation_manager_;

  scoped_refptr<quota::SpecialStoragePolicy> special_storage_policy_;

  FileSystemOptions file_system_options_;

  bool is_filesystem_opened_;
  base::ThreadChecker io_thread_checker_;

  
  std::set<GURL> visited_origins_;

  std::set<std::pair<GURL, FileSystemType> > sticky_dirty_origins_;

  std::map<FileSystemType, UpdateObserverList> update_observers_;
  std::map<FileSystemType, ChangeObserverList> change_observers_;
  std::map<FileSystemType, AccessObserverList> access_observers_;

  base::Time next_release_time_for_open_filesystem_stat_;

  base::WeakPtrFactory<SandboxFileSystemBackendDelegate> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(SandboxFileSystemBackendDelegate);
};

}  

#endif  