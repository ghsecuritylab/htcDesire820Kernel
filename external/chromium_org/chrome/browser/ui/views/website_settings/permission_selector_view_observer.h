// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_WEBSITE_SETTINGS_PERMISSION_SELECTOR_VIEW_OBSERVER_H_
#define CHROME_BROWSER_UI_VIEWS_WEBSITE_SETTINGS_PERMISSION_SELECTOR_VIEW_OBSERVER_H_

class PermissionSelectorView;

class PermissionSelectorViewObserver {
 public:
  
  virtual void OnPermissionChanged(PermissionSelectorView* selector) = 0;

 protected:
  virtual ~PermissionSelectorViewObserver() {}
};

#endif  
