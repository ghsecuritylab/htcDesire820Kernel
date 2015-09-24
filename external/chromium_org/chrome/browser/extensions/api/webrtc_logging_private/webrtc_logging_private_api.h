// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_WEBRTC_LOGGING_PRIVATE_WEBRTC_LOGGING_PRIVATE_API_H_
#define CHROME_BROWSER_EXTENSIONS_API_WEBRTC_LOGGING_PRIVATE_WEBRTC_LOGGING_PRIVATE_API_H_

#include "chrome/browser/extensions/chrome_extension_function.h"
#include "chrome/common/extensions/api/webrtc_logging_private.h"

namespace content {

class RenderProcessHost;

}

namespace extensions {

class WebrtcLoggingPrivateTabIdFunction : public ChromeAsyncExtensionFunction {
 protected:
  virtual ~WebrtcLoggingPrivateTabIdFunction() {}

  content::RenderProcessHost* RphFromTabIdAndSecurityOrigin(
      int tab_id, const std::string& security_origin);
};

class WebrtcLoggingPrivateSetMetaDataFunction
    : public WebrtcLoggingPrivateTabIdFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webrtcLoggingPrivate.setMetaData",
                             WEBRTCLOGGINGPRIVATE_SETMETADATA)
  WebrtcLoggingPrivateSetMetaDataFunction();

 private:
  virtual ~WebrtcLoggingPrivateSetMetaDataFunction();

  
  virtual bool RunImpl() OVERRIDE;

  
  void SetMetaDataCallback(bool success, const std::string& error_message);
};

class WebrtcLoggingPrivateStartFunction
    : public WebrtcLoggingPrivateTabIdFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webrtcLoggingPrivate.start",
                             WEBRTCLOGGINGPRIVATE_START)
  WebrtcLoggingPrivateStartFunction();

 private:
  virtual ~WebrtcLoggingPrivateStartFunction();

  
  virtual bool RunImpl() OVERRIDE;

  
  void StartCallback(bool success, const std::string& error_message);
};

class WebrtcLoggingPrivateSetUploadOnRenderCloseFunction
    : public WebrtcLoggingPrivateTabIdFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webrtcLoggingPrivate.setUploadOnRenderClose",
                             WEBRTCLOGGINGPRIVATE_SETUPLOADONRENDERCLOSE)
  WebrtcLoggingPrivateSetUploadOnRenderCloseFunction();

 private:
  virtual ~WebrtcLoggingPrivateSetUploadOnRenderCloseFunction();

  
  virtual bool RunImpl() OVERRIDE;
};

class WebrtcLoggingPrivateStopFunction
    : public WebrtcLoggingPrivateTabIdFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webrtcLoggingPrivate.stop",
                             WEBRTCLOGGINGPRIVATE_STOP)
  WebrtcLoggingPrivateStopFunction();

 private:
  virtual ~WebrtcLoggingPrivateStopFunction();

  
  virtual bool RunImpl() OVERRIDE;

  
  void StopCallback(bool success, const std::string& error_message);
};

class WebrtcLoggingPrivateUploadFunction
    : public WebrtcLoggingPrivateTabIdFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webrtcLoggingPrivate.upload",
                             WEBRTCLOGGINGPRIVATE_UPLOAD)
  WebrtcLoggingPrivateUploadFunction();

 private:
  virtual ~WebrtcLoggingPrivateUploadFunction();

  
  virtual bool RunImpl() OVERRIDE;

  
  void UploadCallback(bool success, const std::string& report_id,
                      const std::string& error_message);
};

class WebrtcLoggingPrivateDiscardFunction
    : public WebrtcLoggingPrivateTabIdFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("webrtcLoggingPrivate.discard",
                             WEBRTCLOGGINGPRIVATE_DISCARD)
  WebrtcLoggingPrivateDiscardFunction();

 private:
  virtual ~WebrtcLoggingPrivateDiscardFunction();

  
  virtual bool RunImpl() OVERRIDE;

  
  void DiscardCallback(bool success, const std::string& error_message);
};

}  

#endif  