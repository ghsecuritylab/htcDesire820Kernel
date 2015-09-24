// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_AUDIO_ALSA_AUDIO_MANAGER_ALSA_H_
#define MEDIA_AUDIO_ALSA_AUDIO_MANAGER_ALSA_H_

#include <string>
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/threading/thread.h"
#include "media/audio/audio_manager_base.h"

namespace media {

class AlsaWrapper;

class MEDIA_EXPORT AudioManagerAlsa : public AudioManagerBase {
 public:
  AudioManagerAlsa(AudioLogFactory* audio_log_factory);

  static void ShowLinuxAudioInputSettings();

  
  virtual bool HasAudioOutputDevices() OVERRIDE;
  virtual bool HasAudioInputDevices() OVERRIDE;
  virtual void ShowAudioInputSettings() OVERRIDE;
  virtual void GetAudioInputDeviceNames(
      AudioDeviceNames* device_names) OVERRIDE;
  virtual void GetAudioOutputDeviceNames(
      AudioDeviceNames* device_names) OVERRIDE;
  virtual AudioParameters GetInputStreamParameters(
      const std::string& device_id) OVERRIDE;

  
  virtual AudioOutputStream* MakeLinearOutputStream(
      const AudioParameters& params) OVERRIDE;
  virtual AudioOutputStream* MakeLowLatencyOutputStream(
      const AudioParameters& params,
      const std::string& device_id,
      const std::string& input_device_id) OVERRIDE;
  virtual AudioInputStream* MakeLinearInputStream(
      const AudioParameters& params, const std::string& device_id) OVERRIDE;
  virtual AudioInputStream* MakeLowLatencyInputStream(
      const AudioParameters& params, const std::string& device_id) OVERRIDE;

 protected:
  virtual ~AudioManagerAlsa();

  virtual AudioParameters GetPreferredOutputStreamParameters(
      const std::string& output_device_id,
      const AudioParameters& input_params) OVERRIDE;

 private:
  enum StreamType {
    kStreamPlayback = 0,
    kStreamCapture,
  };

  
  void GetAlsaAudioDevices(StreamType type,
                           media::AudioDeviceNames* device_names);

  
  
  void GetAlsaDevicesInfo(StreamType type,
                          void** hint,
                          media::AudioDeviceNames* device_names);

  
  static bool IsAlsaDeviceAvailable(StreamType type,
                                    const char* device_name);

  static const char* UnwantedDeviceTypeWhenEnumerating(
      StreamType wanted_type);

  
  bool HasAnyAlsaAudioDevice(StreamType stream);

  
  AudioOutputStream* MakeOutputStream(const AudioParameters& params);

  
  AudioInputStream* MakeInputStream(const AudioParameters& params,
                                    const std::string& device_id);

  scoped_ptr<AlsaWrapper> wrapper_;

  DISALLOW_COPY_AND_ASSIGN(AudioManagerAlsa);
};

}  

#endif  
