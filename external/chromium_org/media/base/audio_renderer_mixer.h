// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_AUDIO_RENDERER_MIXER_H_
#define MEDIA_BASE_AUDIO_RENDERER_MIXER_H_

#include <map>

#include "base/synchronization/lock.h"
#include "base/time/time.h"
#include "media/base/audio_converter.h"
#include "media/base/audio_renderer_sink.h"

namespace media {

class MEDIA_EXPORT AudioRendererMixer
    : NON_EXPORTED_BASE(public AudioRendererSink::RenderCallback) {
 public:
  AudioRendererMixer(const AudioParameters& input_params,
                     const AudioParameters& output_params,
                     const scoped_refptr<AudioRendererSink>& sink);
  virtual ~AudioRendererMixer();

  
  void AddMixerInput(AudioConverter::InputCallback* input,
                     const base::Closure& error_cb);
  void RemoveMixerInput(AudioConverter::InputCallback* input);

  void set_pause_delay_for_testing(base::TimeDelta delay) {
    pause_delay_ = delay;
  }

 private:
  
  virtual int Render(AudioBus* audio_bus,
                     int audio_delay_milliseconds) OVERRIDE;
  virtual void OnRenderError() OVERRIDE;

  
  scoped_refptr<AudioRendererSink> audio_sink_;

  
  
  typedef std::map<AudioConverter::InputCallback*, base::Closure>
      AudioRendererMixerInputSet;
  AudioRendererMixerInputSet mixer_inputs_;
  base::Lock mixer_inputs_lock_;

  
  AudioConverter audio_converter_;

  
  
  base::TimeDelta pause_delay_;
  base::TimeTicks last_play_time_;
  bool playing_;

  DISALLOW_COPY_AND_ASSIGN(AudioRendererMixer);
};

}  

#endif  
