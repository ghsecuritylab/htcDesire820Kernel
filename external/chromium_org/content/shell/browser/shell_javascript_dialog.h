// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_SHELL_BROWSER_SHELL_JAVASCRIPT_DIALOG_H_
#define CONTENT_SHELL_BROWSER_SHELL_JAVASCRIPT_DIALOG_H_

#include "content/public/browser/javascript_dialog_manager.h"

#if defined(TOOLKIT_GTK)
#include "ui/base/gtk/gtk_signal.h"
#endif

#if defined(OS_MACOSX)
#if __OBJC__
@class ShellJavaScriptDialogHelper;
#else
class ShellJavaScriptDialogHelper;
#endif  
#endif  

namespace content {

class ShellJavaScriptDialogManager;

class ShellJavaScriptDialog {
 public:
  ShellJavaScriptDialog(
      ShellJavaScriptDialogManager* manager,
      gfx::NativeWindow parent_window,
      JavaScriptMessageType message_type,
      const base::string16& message_text,
      const base::string16& default_prompt_text,
      const JavaScriptDialogManager::DialogClosedCallback& callback);
  ~ShellJavaScriptDialog();

  
  void Cancel();

 private:
  ShellJavaScriptDialogManager* manager_;
  JavaScriptDialogManager::DialogClosedCallback callback_;

#if defined(OS_MACOSX)
  ShellJavaScriptDialogHelper* helper_;  
#elif defined(OS_WIN)
  JavaScriptMessageType message_type_;
  HWND dialog_win_;
  base::string16 message_text_;
  base::string16 default_prompt_text_;
  static INT_PTR CALLBACK DialogProc(HWND dialog, UINT message, WPARAM wparam,
                                     LPARAM lparam);
#elif defined(TOOLKIT_GTK)
  GtkWidget* gtk_dialog_;
  gfx::NativeWindow parent_window_;
  CHROMEGTK_CALLBACK_1(ShellJavaScriptDialog, void, OnResponse, int);
#endif

  DISALLOW_COPY_AND_ASSIGN(ShellJavaScriptDialog);
};

}  

#endif  