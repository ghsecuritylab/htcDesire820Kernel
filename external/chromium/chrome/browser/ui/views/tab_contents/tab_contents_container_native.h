// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_TAB_CONTENTS_TAB_CONTENTS_CONTAINER_NATIVE_H_
#define CHROME_BROWSER_UI_VIEWS_TAB_CONTENTS_TAB_CONTENTS_CONTAINER_NATIVE_H_
#pragma once

#include "chrome/browser/ui/views/tab_contents/native_tab_contents_container.h"
#include "content/common/notification_observer.h"
#include "content/common/notification_registrar.h"
#include "views/view.h"

class NativeTabContentsContainer;
class RenderViewHost;
class RenderWidgetHostView;
class TabContents;

class TabContentsContainer : public views::View,
                             public NotificationObserver {
 public:
  TabContentsContainer();
  virtual ~TabContentsContainer();

  
  void ChangeTabContents(TabContents* contents);

  View* GetFocusView() { return native_container_->GetView(); }

  
  TabContents* tab_contents() const { return tab_contents_; }

  
  void TabContentsFocused(TabContents* tab_contents);

  
  
  void SetFastResize(bool fast_resize);

  
  
  void SetReservedContentsRect(const gfx::Rect& reserved_rect);

  
  virtual void Observe(NotificationType type,
                       const NotificationSource& source,
                       const NotificationDetails& details) OVERRIDE;

  
  virtual void Layout() OVERRIDE;
  virtual void GetAccessibleState(ui::AccessibleViewState* state) OVERRIDE;

 protected:
  
  virtual void ViewHierarchyChanged(bool is_add, views::View* parent,
                                    views::View* child) OVERRIDE;

 private:
  
  void AddObservers();
  void RemoveObservers();

  
  
  void RenderViewHostChanged(RenderViewHost* old_host,
                             RenderViewHost* new_host);

  
  
  
  void TabContentsDestroyed(TabContents* contents);

  
  void RenderWidgetHostViewChanged(RenderWidgetHostView* new_view);

  
  
  NativeTabContentsContainer* native_container_;

  
  TabContents* tab_contents_;

  
  NotificationRegistrar registrar_;

  
  
  
  gfx::Rect cached_reserved_rect_;

  DISALLOW_COPY_AND_ASSIGN(TabContentsContainer);
};

#endif  