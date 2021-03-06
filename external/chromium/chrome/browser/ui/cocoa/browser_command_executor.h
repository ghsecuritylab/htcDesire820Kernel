// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_BROWSER_COMMAND_EXECUTOR_H_
#define CHROME_BROWSER_BROWSER_COMMAND_EXECUTOR_H_
#pragma once

@protocol BrowserCommandExecutor
- (void)executeCommand:(int)command;
@end

#endif  

