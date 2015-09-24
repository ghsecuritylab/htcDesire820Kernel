// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_GTK_BOOKMARKS_BOOKMARK_BAR_INSTRUCTIONS_GTK_H_
#define CHROME_BROWSER_UI_GTK_BOOKMARKS_BOOKMARK_BAR_INSTRUCTIONS_GTK_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "ui/base/gtk/gtk_signal.h"

typedef struct _GtkWidget GtkWidget;
class BookmarkBarInstructionsDelegate;
class GtkThemeService;
class Profile;

class BookmarkBarInstructionsGtk : public content::NotificationObserver {
 public:
  BookmarkBarInstructionsGtk(BookmarkBarInstructionsDelegate* delegate,
                             Profile* profile);

  
  GtkWidget* widget() const { return instructions_hbox_; }

 private:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  CHROMEGTK_CALLBACK_0(BookmarkBarInstructionsGtk, void, OnButtonClick);

  
  void UpdateColors();

  BookmarkBarInstructionsDelegate* delegate_;

  Profile* profile_;

  GtkThemeService* theme_service_;

  
  GtkWidget* instructions_hbox_;
  GtkWidget* instructions_label_;
  GtkWidget* instructions_link_;

  content::NotificationRegistrar registrar_;

  DISALLOW_COPY_AND_ASSIGN(BookmarkBarInstructionsGtk);
};

#endif  