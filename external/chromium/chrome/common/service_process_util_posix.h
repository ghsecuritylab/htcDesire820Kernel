// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_SERVICE_PROCESS_UTIL_POSIX_H_
#define CHROME_COMMON_SERVICE_PROCESS_UTIL_POSIX_H_

#include "service_process_util.h"

#include <signal.h>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/message_loop.h"
#include "base/message_pump_libevent.h"

#if defined(OS_LINUX)
#include "chrome/common/multi_process_lock.h"
MultiProcessLock* TakeServiceRunningLock(bool waiting);
#endif  

#if defined(OS_MACOSX)
#include "base/files/file_path_watcher.h"
#include "base/mac/scoped_cftyperef.h"

class CommandLine;
CFDictionaryRef CreateServiceProcessLaunchdPlist(CommandLine* cmd_line,
                                                 bool for_auto_launch);
#endif  

namespace base {
class WaitableEvent;
}

// Watches for |kShutDownMessage| to be written to the file descriptor it is
class ServiceProcessShutdownMonitor
    : public base::MessagePumpLibevent::Watcher {
 public:

  enum {
    kShutDownMessage = 0xdecea5e
  };

  explicit ServiceProcessShutdownMonitor(Task* shutdown_task);
  virtual ~ServiceProcessShutdownMonitor();

  
  virtual void OnFileCanReadWithoutBlocking(int fd);
  virtual void OnFileCanWriteWithoutBlocking(int fd);

 private:
  scoped_ptr<Task> shutdown_task_;
};

struct ServiceProcessState::StateData
    : public base::RefCountedThreadSafe<ServiceProcessState::StateData> {
  StateData();

  
  
  void SignalReady(base::WaitableEvent* signal, bool* success);


  
  

#if defined(OS_MACOSX)
  bool WatchExecutable();

  base::mac::ScopedCFTypeRef<CFDictionaryRef> launchd_conf_;
  base::files::FilePathWatcher executable_watcher_;
#endif  
#if defined(OS_LINUX)
  scoped_ptr<MultiProcessLock> initializing_lock_;
  scoped_ptr<MultiProcessLock> running_lock_;
#endif  
  scoped_ptr<ServiceProcessShutdownMonitor> shut_down_monitor_;
  base::MessagePumpLibevent::FileDescriptorWatcher watcher_;
  int sockets_[2];
  struct sigaction old_action_;
  bool set_action_;

 protected:
  friend class base::RefCountedThreadSafe<ServiceProcessState::StateData>;
  virtual ~StateData();
};

#endif  