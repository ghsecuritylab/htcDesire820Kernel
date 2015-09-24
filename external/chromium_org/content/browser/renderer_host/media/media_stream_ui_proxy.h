// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_MEDIA_MEDIA_STREAM_UI_PROXY_H_
#define CONTENT_BROWSER_RENDERER_HOST_MEDIA_MEDIA_STREAM_UI_PROXY_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/public/common/media_stream_request.h"

namespace content {

class RenderViewHostDelegate;

class CONTENT_EXPORT MediaStreamUIProxy {
 public:
  typedef base::Callback<
      void (const MediaStreamDevices& devices)> ResponseCallback;

  static scoped_ptr<MediaStreamUIProxy> Create();
  static scoped_ptr<MediaStreamUIProxy> CreateForTests(
      RenderViewHostDelegate* render_delegate);

  virtual ~MediaStreamUIProxy();

  
  
  
  
  virtual void RequestAccess(const MediaStreamRequest& request,
                             const ResponseCallback& response_callback);

  
  
  
  
  virtual void OnStarted(const base::Closure& stop_callback);

  void SetRenderViewHostDelegateForTests(RenderViewHostDelegate* delegate);

 protected:
  MediaStreamUIProxy(RenderViewHostDelegate* test_render_delegate);

 private:
  class Core;
  friend class Core;
  friend class FakeMediaStreamUIProxy;

  void ProcessAccessRequestResponse(const MediaStreamDevices& devices);
  void ProcessStopRequestFromUI();

  scoped_ptr<Core> core_;
  ResponseCallback response_callback_;
  base::Closure stop_callback_;

  base::WeakPtrFactory<MediaStreamUIProxy> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(MediaStreamUIProxy);
};

class CONTENT_EXPORT FakeMediaStreamUIProxy : public MediaStreamUIProxy {
 public:
  explicit FakeMediaStreamUIProxy();
  virtual ~FakeMediaStreamUIProxy();

  void SetAvailableDevices(const MediaStreamDevices& devices);

  
  virtual void RequestAccess(
      const MediaStreamRequest& request,
      const ResponseCallback& response_callback) OVERRIDE;
  virtual void OnStarted(const base::Closure& stop_callback) OVERRIDE;

 private:
  MediaStreamDevices devices_;

  DISALLOW_COPY_AND_ASSIGN(FakeMediaStreamUIProxy);
};

}  

#endif  