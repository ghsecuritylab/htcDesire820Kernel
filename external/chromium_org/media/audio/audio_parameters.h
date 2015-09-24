// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_AUDIO_AUDIO_PARAMETERS_H_
#define MEDIA_AUDIO_AUDIO_PARAMETERS_H_

#include "base/basictypes.h"
#include "base/time/time.h"
#include "media/base/channel_layout.h"
#include "media/base/media_export.h"

namespace media {

struct MEDIA_EXPORT AudioInputBufferParameters {
  double volume;
  uint32 size;
  bool key_pressed;
};

struct MEDIA_EXPORT AudioInputBuffer {
  AudioInputBufferParameters params;
  int8 audio[1];
};

class MEDIA_EXPORT AudioParameters {
 public:
  
  
  enum Format {
    AUDIO_PCM_LINEAR = 0,     
    AUDIO_PCM_LOW_LATENCY,    
    AUDIO_FAKE,               
    AUDIO_LAST_FORMAT         
  };

  enum {
    
    kTelephoneSampleRate = 8000,
    
    kAudioCDSampleRate = 44100,
  };

  
  
  enum PlatformEffectsMask {
    NO_EFFECTS = 0x0,
    ECHO_CANCELLER = 0x1
  };

  AudioParameters();
  AudioParameters(Format format, ChannelLayout channel_layout,
                  int sample_rate, int bits_per_sample,
                  int frames_per_buffer);
  AudioParameters(Format format, ChannelLayout channel_layout,
                  int input_channels,
                  int sample_rate, int bits_per_sample,
                  int frames_per_buffer, int effects);
  AudioParameters(Format format, ChannelLayout channel_layout,
                  int channels, int input_channels,
                  int sample_rate, int bits_per_sample,
                  int frames_per_buffer, int effects);

  void Reset(Format format, ChannelLayout channel_layout,
             int channels, int input_channels,
             int sample_rate, int bits_per_sample,
             int frames_per_buffer);

  
  
  bool IsValid() const;

  
  int GetBytesPerBuffer() const;

  
  int GetBytesPerSecond() const;

  
  int GetBytesPerFrame() const;

  
  
  base::TimeDelta GetBufferDuration() const;

  Format format() const { return format_; }
  ChannelLayout channel_layout() const { return channel_layout_; }
  int sample_rate() const { return sample_rate_; }
  int bits_per_sample() const { return bits_per_sample_; }
  int frames_per_buffer() const { return frames_per_buffer_; }
  int channels() const { return channels_; }
  int input_channels() const { return input_channels_; }
  int effects() const { return effects_; }

  
  bool operator==(const AudioParameters& other) const {
    return format_ == other.format() &&
           sample_rate_ == other.sample_rate() &&
           channel_layout_ == other.channel_layout() &&
           channels_ == other.channels() &&
           input_channels_ == other.input_channels() &&
           bits_per_sample_ == other.bits_per_sample() &&
           frames_per_buffer_ == other.frames_per_buffer() &&
           effects_ == other.effects();
  }

 private:
  
  
  Format format_;                 
  ChannelLayout channel_layout_;  
  int sample_rate_;               
  int bits_per_sample_;           
  int frames_per_buffer_;         

  int channels_;                  
                                  
  int input_channels_;            
                                  
                                  
  int effects_;                   
};

inline bool operator<(const AudioParameters& a, const AudioParameters& b) {
  if (a.format() != b.format())
    return a.format() < b.format();
  if (a.channels() != b.channels())
    return a.channels() < b.channels();
  if (a.input_channels() != b.input_channels())
    return a.input_channels() < b.input_channels();
  if (a.sample_rate() != b.sample_rate())
    return a.sample_rate() < b.sample_rate();
  if (a.bits_per_sample() != b.bits_per_sample())
    return a.bits_per_sample() < b.bits_per_sample();
  return a.frames_per_buffer() < b.frames_per_buffer();
}

}  

#endif  
