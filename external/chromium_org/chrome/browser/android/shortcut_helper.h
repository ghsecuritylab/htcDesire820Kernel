// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_ANDROID_SHORTCUT_HELPER_H_
#define CHROME_BROWSER_ANDROID_SHORTCUT_HELPER_H_

#include "base/android/jni_helper.h"
#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "chrome/browser/android/tab_android.h"
#include "chrome/common/cancelable_task_tracker.h"
#include "content/public/browser/web_contents_observer.h"

namespace chrome {
struct FaviconBitmapResult;
}  

namespace content {
class WebContents;
}  

namespace IPC {
class Message;
}

class GURL;

class ShortcutBuilder : public content::WebContentsObserver {
 public:
  enum ShortcutType {
    APP_SHORTCUT,
    APP_SHORTCUT_APPLE,
    BOOKMARK
  };

  explicit ShortcutBuilder(content::WebContents* web_contents,
                           const base::string16& title,
                           int launcher_large_icon_size);
  virtual ~ShortcutBuilder() {}

  void OnDidRetrieveWebappInformation(bool success,
                                      bool is_mobile_webapp_capable,
                                      bool is_apple_mobile_webapp_capable,
                                      const GURL& expected_url);

  void FinishAddingShortcut(const chrome::FaviconBitmapResult& bitmap_result);

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void WebContentsDestroyed(content::WebContents* web_contents)
      OVERRIDE;

 private:
  void Destroy();

  GURL url_;
  base::string16 title_;
  int launcher_large_icon_size_;
  ShortcutType shortcut_type_;
  CancelableTaskTracker cancelable_task_tracker_;

  DISALLOW_COPY_AND_ASSIGN(ShortcutBuilder);
};

class ShortcutHelper {
 public:
  
  
  static void AddShortcut(content::WebContents* web_contents,
                          const base::string16& title,
                          int launcher_larger_icon_size);

  
  static void AddShortcutInBackground(
      const GURL& url,
      const base::string16& title,
      ShortcutBuilder::ShortcutType shortcut_type,
      const chrome::FaviconBitmapResult& bitmap_result);

  
  static bool RegisterShortcutHelper(JNIEnv* env);

 private:
  DISALLOW_COPY_AND_ASSIGN(ShortcutHelper);
};

#endif  