// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_TAB_CONTENTS_POPUP_MENU_HELPER_MAC_H_
#define CHROME_BROWSER_TAB_CONTENTS_POPUP_MENU_HELPER_MAC_H_

#include <vector>

#include "content/common/notification_observer.h"
#include "content/common/notification_registrar.h"
#include "ui/gfx/rect.h"

class RenderViewHost;
struct WebMenuItem;

class PopupMenuHelper : public NotificationObserver {
 public:
  
  
  explicit PopupMenuHelper(RenderViewHost* render_view_host);

  
  
  
  void ShowPopupMenu(const gfx::Rect& bounds,
                     int item_height,
                     double item_font_size,
                     int selected_item,
                     const std::vector<WebMenuItem>& items,
                     bool right_aligned);

 private:
  
  virtual void Observe(NotificationType type,
                       const NotificationSource& source,
                       const NotificationDetails& details);

  NotificationRegistrar notification_registrar_;

  RenderViewHost* render_view_host_;

  DISALLOW_COPY_AND_ASSIGN(PopupMenuHelper);
};

#endif  