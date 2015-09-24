// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NACL_HOST_NACL_BROKER_SERVICE_WIN_H_
#define CHROME_BROWSER_NACL_HOST_NACL_BROKER_SERVICE_WIN_H_
#pragma once

#include <map>

#include "base/basictypes.h"
#include "base/memory/singleton.h"
#include "chrome/browser/nacl_host/nacl_broker_host_win.h"

class NaClProcessHost;

class NaClBrokerService {
 public:
  
  static NaClBrokerService* GetInstance();

  
  bool StartBroker();

  
  
  bool LaunchLoader(NaClProcessHost* client,
                    const std::wstring& loader_channel_id);

  
  void OnLoaderLaunched(const std::wstring& channel_id,
                        base::ProcessHandle handle);

  
  void OnLoaderDied();

 private:
  typedef std::map<std::wstring, NaClProcessHost*>
      PendingLaunchesMap;

  friend struct DefaultSingletonTraits<NaClBrokerService>;

  NaClBrokerService();
  ~NaClBrokerService() {}

  NaClBrokerHost* GetBrokerHost();

  int loaders_running_;
  PendingLaunchesMap pending_launches_;

  DISALLOW_COPY_AND_ASSIGN(NaClBrokerService);
};

#endif  