// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_WIN_SESSION_DESKTOP_ENVIRONMENT_H_
#define REMOTING_HOST_WIN_SESSION_DESKTOP_ENVIRONMENT_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "remoting/host/me2me_desktop_environment.h"

namespace remoting {

class SessionDesktopEnvironment : public Me2MeDesktopEnvironment {
 public:
  virtual ~SessionDesktopEnvironment();

  
  virtual scoped_ptr<InputInjector> CreateInputInjector() OVERRIDE;

 private:
  friend class SessionDesktopEnvironmentFactory;
  SessionDesktopEnvironment(
      scoped_refptr<base::SingleThreadTaskRunner> caller_task_runner,
      scoped_refptr<base::SingleThreadTaskRunner> input_task_runner,
      scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner,
      const base::Closure& inject_sas);

  
  base::Closure inject_sas_;

  DISALLOW_COPY_AND_ASSIGN(SessionDesktopEnvironment);
};

class SessionDesktopEnvironmentFactory : public Me2MeDesktopEnvironmentFactory {
 public:
  SessionDesktopEnvironmentFactory(
      scoped_refptr<base::SingleThreadTaskRunner> caller_task_runner,
      scoped_refptr<base::SingleThreadTaskRunner> input_task_runner,
      scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner,
      const base::Closure& inject_sas);
  virtual ~SessionDesktopEnvironmentFactory();

  
  virtual scoped_ptr<DesktopEnvironment> Create(
      base::WeakPtr<ClientSessionControl> client_session_control) OVERRIDE;

 private:
  
  base::Closure inject_sas_;

  DISALLOW_COPY_AND_ASSIGN(SessionDesktopEnvironmentFactory);
};

}  

#endif  
