// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_DOWNLOAD_DOWNLOAD_REQUEST_INFOBAR_DELEGATE_H_
#define CHROME_BROWSER_DOWNLOAD_DOWNLOAD_REQUEST_INFOBAR_DELEGATE_H_

#include "base/basictypes.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/download/download_request_limiter.h"
#include "chrome/browser/infobars/confirm_infobar_delegate.h"

class InfoBarService;

class DownloadRequestInfoBarDelegate : public ConfirmInfoBarDelegate {
 public:
  typedef base::Callback<void(
      InfoBarService* infobar_service,
      base::WeakPtr<DownloadRequestLimiter::TabDownloadState> host)>
    FakeCreateCallback;

  virtual ~DownloadRequestInfoBarDelegate();

  
  static void Create(
      InfoBarService* infobar_service,
      base::WeakPtr<DownloadRequestLimiter::TabDownloadState> host);

#if defined(UNIT_TEST)
  static scoped_ptr<DownloadRequestInfoBarDelegate> Create(
      base::WeakPtr<DownloadRequestLimiter::TabDownloadState> host) {
    return scoped_ptr<DownloadRequestInfoBarDelegate>(
        new DownloadRequestInfoBarDelegate(host));
  }
#endif

  static void SetCallbackForTesting(FakeCreateCallback* callback);

 private:
  static FakeCreateCallback* callback_;

  explicit DownloadRequestInfoBarDelegate(
      base::WeakPtr<DownloadRequestLimiter::TabDownloadState> host);

  
  virtual int GetIconID() const OVERRIDE;
  virtual base::string16 GetMessageText() const OVERRIDE;
  virtual base::string16 GetButtonLabel(InfoBarButton button) const OVERRIDE;
  virtual bool Accept() OVERRIDE;
  virtual bool Cancel() OVERRIDE;

  bool responded_;
  base::WeakPtr<DownloadRequestLimiter::TabDownloadState> host_;

  DISALLOW_COPY_AND_ASSIGN(DownloadRequestInfoBarDelegate);
};

#endif  
