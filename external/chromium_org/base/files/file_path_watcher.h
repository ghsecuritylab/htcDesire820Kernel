// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef BASE_FILES_FILE_PATH_WATCHER_H_
#define BASE_FILES_FILE_PATH_WATCHER_H_

#include "base/base_export.h"
#include "base/basictypes.h"
#include "base/callback.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/message_loop/message_loop_proxy.h"

namespace base {

class BASE_EXPORT FilePathWatcher {
 public:
  
  
  
  typedef base::Callback<void(const FilePath& path, bool error)> Callback;

  
  class PlatformDelegate : public base::RefCountedThreadSafe<PlatformDelegate> {
   public:
    PlatformDelegate();

    
    virtual bool Watch(const FilePath& path,
                       bool recursive,
                       const Callback& callback) WARN_UNUSED_RESULT = 0;

    
    
    
    virtual void Cancel() = 0;

   protected:
    friend class base::RefCountedThreadSafe<PlatformDelegate>;
    friend class FilePathWatcher;

    virtual ~PlatformDelegate();

    
    
    
    virtual void CancelOnMessageLoopThread() = 0;

    scoped_refptr<base::MessageLoopProxy> message_loop() const {
      return message_loop_;
    }

    void set_message_loop(base::MessageLoopProxy* loop) {
      message_loop_ = loop;
    }

    
    void set_cancelled() {
      cancelled_ = true;
    }

    bool is_cancelled() const {
      return cancelled_;
    }

   private:
    scoped_refptr<base::MessageLoopProxy> message_loop_;
    bool cancelled_;
  };

  FilePathWatcher();
  virtual ~FilePathWatcher();

  
  
  
  static void CancelWatch(const scoped_refptr<PlatformDelegate>& delegate);

  
  
  
  
  
  
  
  bool Watch(const FilePath& path, bool recursive, const Callback& callback);

 private:
  scoped_refptr<PlatformDelegate> impl_;

  DISALLOW_COPY_AND_ASSIGN(FilePathWatcher);
};

}  

#endif  