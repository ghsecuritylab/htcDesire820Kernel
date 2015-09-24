// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_GTK_CREATE_APPLICATION_SHORTCUTS_DIALOG_GTK_H_
#define CHROME_BROWSER_UI_GTK_CREATE_APPLICATION_SHORTCUTS_DIALOG_GTK_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/sequenced_task_runner_helpers.h"
#include "chrome/browser/shell_integration.h"
#include "content/public/browser/browser_thread.h"
#include "ui/base/gtk/gtk_signal.h"
#include "url/gurl.h"

using content::BrowserThread;

typedef struct _GdkPixbuf GdkPixbuf;
typedef struct _GtkWidget GtkWidget;
typedef struct _GtkWindow GtkWindow;

class Profile;

namespace content {
class WebContents;
}

namespace extensions {
class Extension;
}

namespace gfx {
class ImageFamily;
}

class CreateApplicationShortcutsDialogGtk
    : public base::RefCountedThreadSafe<CreateApplicationShortcutsDialogGtk,
                                        BrowserThread::DeleteOnUIThread> {
 protected:
  explicit CreateApplicationShortcutsDialogGtk(GtkWindow* parent);
  virtual ~CreateApplicationShortcutsDialogGtk();

  CHROMEGTK_CALLBACK_1(CreateApplicationShortcutsDialogGtk, void,
                       OnCreateDialogResponse, int);

  CHROMEGTK_CALLBACK_1(CreateApplicationShortcutsDialogGtk, void,
                       OnErrorDialogResponse, int);

  CHROMEGTK_CALLBACK_0(CreateApplicationShortcutsDialogGtk, void,
                       OnToggleCheckbox);

  virtual void CreateDialogBox(GtkWindow* parent);
  virtual void CreateIconPixBuf(const gfx::ImageFamily& image);

  
  
  virtual void OnCreatedShortcut(void) {}

  virtual void CreateDesktopShortcut(
      const ShellIntegration::ShortcutInfo& shortcut_info,
      const ShellIntegration::ShortcutLocations& creation_locations);
  virtual void ShowErrorDialog();

  GtkWindow* parent_;

  
  GtkWidget* desktop_checkbox_;
  GtkWidget* menu_checkbox_;

  
  ShellIntegration::ShortcutInfo shortcut_info_;
  
  bool create_in_chrome_apps_subdir_;

  
  
  GdkPixbuf* favicon_pixbuf_;

  
  GtkWidget* create_dialog_;

  
  GtkWidget* error_dialog_;

 private:
  friend struct BrowserThread::DeleteOnThread<BrowserThread::UI>;
  friend class base::DeleteHelper<CreateApplicationShortcutsDialogGtk>;
  DISALLOW_COPY_AND_ASSIGN(CreateApplicationShortcutsDialogGtk);
};

class CreateWebApplicationShortcutsDialogGtk
    : public CreateApplicationShortcutsDialogGtk {
 public:
  
  static void Show(GtkWindow* parent, content::WebContents* web_contents);

  CreateWebApplicationShortcutsDialogGtk(GtkWindow* parent,
                                         content::WebContents* web_contents);

  virtual void OnCreatedShortcut(void) OVERRIDE;

 protected:
  virtual ~CreateWebApplicationShortcutsDialogGtk() {}

 private:
  
  content::WebContents* web_contents_;

  DISALLOW_COPY_AND_ASSIGN(CreateWebApplicationShortcutsDialogGtk);
};

class CreateChromeApplicationShortcutsDialogGtk
  : public CreateApplicationShortcutsDialogGtk {
 public:
  CreateChromeApplicationShortcutsDialogGtk(
      GtkWindow* parent,
      Profile* profile,
      const extensions::Extension* app,
      const base::Closure& close_callback);

 protected:
  virtual ~CreateChromeApplicationShortcutsDialogGtk();

  virtual void CreateDesktopShortcut(
      const ShellIntegration::ShortcutInfo& shortcut_info,
      const ShellIntegration::ShortcutLocations& creation_locations) OVERRIDE;

 private:
  void OnShortcutInfoLoaded(
      const ShellIntegration::ShortcutInfo& shortcut_info);

  const extensions::Extension* app_;
  base::FilePath profile_path_;
  base::Closure close_callback_;
  DISALLOW_COPY_AND_ASSIGN(CreateChromeApplicationShortcutsDialogGtk);
};

#endif  