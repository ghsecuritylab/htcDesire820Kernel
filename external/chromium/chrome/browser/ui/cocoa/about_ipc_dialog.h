// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_ABOUT_IPC_DIALOG_H_
#define CHROME_BROWSER_UI_COCOA_ABOUT_IPC_DIALOG_H_
#pragma once

#include "ipc/ipc_logging.h"
#include "ipc/ipc_message_utils.h"

#if defined(IPC_MESSAGE_LOG_ENABLED)

#ifdef __OBJC__
@class AboutIPCController;
#else
class AboutIPCController;
#endif


class AboutIPCBridge : public IPC::Logging::Consumer {
 public:
  AboutIPCBridge(AboutIPCController* controller) : controller_(controller) { }
  virtual ~AboutIPCBridge() { }

  
  virtual void Log(const IPC::LogData& data);

 private:
  AboutIPCController* controller_;  
  DISALLOW_COPY_AND_ASSIGN(AboutIPCBridge);
};

#endif  

#endif  