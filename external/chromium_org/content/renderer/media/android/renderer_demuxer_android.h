// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_ANDROID_RENDERER_DEMUXER_ANDROID_H_
#define CONTENT_RENDERER_MEDIA_ANDROID_RENDERER_DEMUXER_ANDROID_H_

#include "base/atomic_sequence_num.h"
#include "base/id_map.h"
#include "ipc/ipc_channel_proxy.h"
#include "media/base/android/demuxer_stream_player_params.h"

namespace content {

class MediaSourceDelegate;
class ThreadSafeSender;

class RendererDemuxerAndroid : public IPC::ChannelProxy::MessageFilter {
 public:
  RendererDemuxerAndroid();

  
  
  
  int GetNextDemuxerClientID();

  
  
  
  
  void AddDelegate(int demuxer_client_id, MediaSourceDelegate* delegate);

  
  
  
  void RemoveDelegate(int demuxer_client_id);

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  
  
  
  
  void DemuxerReady(int demuxer_client_id,
                    const media::DemuxerConfigs& configs);
  void ReadFromDemuxerAck(int demuxer_client_id,
                          const media::DemuxerData& data);
  void DemuxerSeekDone(int demuxer_client_id,
                       const base::TimeDelta& actual_browser_seek_time);
  void DurationChanged(int demuxer_client_id, const base::TimeDelta& duration);

 protected:
  friend class base::RefCountedThreadSafe<RendererDemuxerAndroid>;
  virtual ~RendererDemuxerAndroid();

 private:
  void DispatchMessage(const IPC::Message& message);
  void OnReadFromDemuxer(int demuxer_client_id,
                         media::DemuxerStream::Type type);
  void OnDemuxerSeekRequest(int demuxer_client_id,
                            const base::TimeDelta& time_to_seek,
                            bool is_browser_seek);
  void OnMediaConfigRequest(int demuxer_client_id);

  base::AtomicSequenceNumber next_demuxer_client_id_;

  IDMap<MediaSourceDelegate> delegates_;
  scoped_refptr<ThreadSafeSender> thread_safe_sender_;
  scoped_refptr<base::MessageLoopProxy> media_message_loop_;

  DISALLOW_COPY_AND_ASSIGN(RendererDemuxerAndroid);
};

}  

#endif  
