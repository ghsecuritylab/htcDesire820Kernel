// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_VIDEO_CAPTURE_ANDROID_VIDEO_CAPTURE_DEVICE_ANDROID_H_
#define MEDIA_VIDEO_CAPTURE_ANDROID_VIDEO_CAPTURE_DEVICE_ANDROID_H_

#include <jni.h>
#include <string>

#include "base/android/scoped_java_ref.h"
#include "base/synchronization/lock.h"
#include "base/threading/thread.h"
#include "base/time/time.h"
#include "media/base/media_export.h"
#include "media/video/capture/video_capture_device.h"

namespace media {

class MEDIA_EXPORT VideoCaptureDeviceAndroid : public VideoCaptureDevice {
 public:
  virtual ~VideoCaptureDeviceAndroid();

  static VideoCaptureDevice* Create(const Name& device_name);
  static bool RegisterVideoCaptureDevice(JNIEnv* env);

  
  virtual void AllocateAndStart(const VideoCaptureParams& params,
                                scoped_ptr<Client> client) OVERRIDE;
  virtual void StopAndDeAllocate() OVERRIDE;

  
  void OnFrameAvailable(
      JNIEnv* env,
      jobject obj,
      jbyteArray data,
      jint length,
      jint rotation);

 private:
  enum InternalState {
    kIdle,  
    kCapturing,  
    kError  
  };

  
  enum AndroidImageFormat {
#define DEFINE_ANDROID_IMAGEFORMAT(name, value) name = value,
#include "media/video/capture/android/imageformat_list.h"
#undef DEFINE_ANDROID_IMAGEFORMAT
  };

  explicit VideoCaptureDeviceAndroid(const Name& device_name);
  bool Init();
  VideoPixelFormat GetColorspace();
  void SetErrorState(const std::string& reason);

  
  
  base::Lock lock_;
  InternalState state_;
  bool got_first_frame_;
  base::TimeTicks expected_next_frame_time_;
  base::TimeDelta frame_interval_;
  scoped_ptr<VideoCaptureDevice::Client> client_;

  Name device_name_;
  VideoCaptureFormat capture_format_;

  
  base::android::ScopedJavaGlobalRef<jobject> j_capture_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(VideoCaptureDeviceAndroid);
};

}  

#endif  
