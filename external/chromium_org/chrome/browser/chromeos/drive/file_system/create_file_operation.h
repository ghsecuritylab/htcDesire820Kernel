// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_FILE_SYSTEM_CREATE_FILE_OPERATION_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_FILE_SYSTEM_CREATE_FILE_OPERATION_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/drive/file_errors.h"
#include "google_apis/drive/gdata_errorcode.h"

namespace base {
class FilePath;
class SequencedTaskRunner;
}  

namespace google_apis {
class ResourceEntry;
}  

namespace drive {

namespace internal {
class FileCache;
class ResourceMetadata;
}  

struct EntryInfoPairResult;
class JobScheduler;
class ResourceEntry;

namespace file_system {

class OperationObserver;

class CreateFileOperation {
 public:
  CreateFileOperation(base::SequencedTaskRunner* blocking_task_runner,
                      OperationObserver* observer,
                      JobScheduler* scheduler,
                      internal::ResourceMetadata* metadata,
                      internal::FileCache* cache);
  ~CreateFileOperation();

  
  
  
  
  
  
  
  void CreateFile(const base::FilePath& file_path,
                  bool is_exclusive,
                  const std::string& mime_type,
                  const FileOperationCallback& callback);

 private:
  
  void CreateFileAfterCheckPreCondition(const base::FilePath& file_path,
                                        const FileOperationCallback& callback,
                                        std::string* parent_resource_id,
                                        std::string* mime_type,
                                        FileError error);

  
  
  void CreateFileAfterUpload(
      const FileOperationCallback& callback,
      google_apis::GDataErrorCode error,
      scoped_ptr<google_apis::ResourceEntry> resource_entry);

  
  void CreateFileAfterUpdateLocalState(const FileOperationCallback& callback,
                                       base::FilePath* file_path,
                                       FileError error);

  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;
  OperationObserver* observer_;
  JobScheduler* scheduler_;
  internal::ResourceMetadata* metadata_;
  internal::FileCache* cache_;

  
  
  base::WeakPtrFactory<CreateFileOperation> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(CreateFileOperation);
};

}  
}  

#endif  
