// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_WEBRTC_BROWSERTEST_BASE_H_
#define CHROME_BROWSER_MEDIA_WEBRTC_BROWSERTEST_BASE_H_

#include <string>

#include "chrome/test/base/in_process_browser_test.h"

class InfoBar;

namespace content {
class WebContents;
}

class WebRtcTestBase : public InProcessBrowserTest {
 protected:
  
  static const char kAudioVideoCallConstraints[];
  static const char kAudioOnlyCallConstraints[];
  static const char kVideoOnlyCallConstraints[];

  static const char kFailedWithPermissionDeniedError[];

  WebRtcTestBase();
  virtual ~WebRtcTestBase();

  
  
  void GetUserMediaAndAccept(content::WebContents* tab_contents) const;
  void GetUserMediaWithSpecificConstraintsAndAccept(
      content::WebContents* tab_contents,
      const std::string& constraints) const;
  void GetUserMediaAndDeny(content::WebContents* tab_contents);
  void GetUserMediaWithSpecificConstraintsAndDeny(
      content::WebContents* tab_contents,
      const std::string& constraints) const;
  void GetUserMediaAndDismiss(content::WebContents* tab_contents) const;
  void GetUserMedia(content::WebContents* tab_contents,
                    const std::string& constraints) const;

  
  
  content::WebContents* OpenPageAndGetUserMediaInNewTab(const GURL& url) const;

  
  
  content::WebContents* OpenPageAndAcceptUserMedia(const GURL& url) const;

  void ConnectToPeerConnectionServer(const std::string& peer_name,
                                     content::WebContents* tab_contents) const;
  std::string ExecuteJavascript(const std::string& javascript,
                                content::WebContents* tab_contents) const;

  
  
  
  void DetectErrorsInJavaScript();

 private:
  void CloseInfoBarInTab(content::WebContents* tab_contents,
                         InfoBar* infobar) const;
  InfoBar* GetUserMediaAndWaitForInfoBar(content::WebContents* tab_contents,
                                         const std::string& constraints) const;

  bool detect_errors_in_javascript_;

  DISALLOW_COPY_AND_ASSIGN(WebRtcTestBase);
};

#endif  
