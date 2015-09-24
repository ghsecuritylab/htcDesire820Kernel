// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_EXTENSION_INFOBAR_DELEGATE_H_
#define CHROME_BROWSER_EXTENSIONS_EXTENSION_INFOBAR_DELEGATE_H_
#pragma once

#include "chrome/browser/tab_contents/confirm_infobar_delegate.h"

class Browser;
class Extension;
class ExtensionHost;
class TabContents;

class ExtensionInfoBarDelegate : public InfoBarDelegate,
                                 public NotificationObserver {
 public:
  
  class DelegateObserver {
   public:
    virtual void OnDelegateDeleted() = 0;

   protected:
    virtual ~DelegateObserver() {}
  };

  ExtensionInfoBarDelegate(Browser* browser,
                           TabContents* contents,
                           const Extension* extension,
                           const GURL& url);

  const Extension* extension() { return extension_; }
  ExtensionHost* extension_host() { return extension_host_.get(); }

  void set_observer(DelegateObserver* observer) { observer_ = observer; }

  bool closing() const { return closing_; }

 private:
  virtual ~ExtensionInfoBarDelegate();

  
  virtual InfoBar* CreateInfoBar();
  virtual bool EqualsDelegate(InfoBarDelegate* delegate) const;
  virtual void InfoBarDismissed();
  virtual void InfoBarClosed();
  virtual Type GetInfoBarType() const;
  virtual ExtensionInfoBarDelegate* AsExtensionInfoBarDelegate();

  
  virtual void Observe(NotificationType type,
                       const NotificationSource& source,
                       const NotificationDetails& details);

  
  
  
  
  scoped_ptr<ExtensionHost> extension_host_;

  
  DelegateObserver* observer_;

  const Extension* extension_;
  TabContents* tab_contents_;
  NotificationRegistrar registrar_;

  
  
  bool closing_;

  DISALLOW_COPY_AND_ASSIGN(ExtensionInfoBarDelegate);
};

#endif  
