// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef MEDIA_CAST_LOGGING_LOGGING_IMPL_H_
#define MEDIA_CAST_LOGGING_LOGGING_IMPL_H_


#include "base/memory/ref_counted.h"
#include "base/task_runner.h"
#include "media/cast/cast_config.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/logging/logging_raw.h"
#include "media/cast/logging/logging_stats.h"

namespace media {
namespace cast {

class LoggingImpl : public base::NonThreadSafe {
 public:
  LoggingImpl(base::TickClock* clock,
              scoped_refptr<base::TaskRunner> main_thread_proxy,
              const CastLoggingConfig& config);

  ~LoggingImpl();

  
  
  void InsertFrameEvent(CastLoggingEvent event,
                        uint32 rtp_timestamp,
                        uint32 frame_id);
  void InsertFrameEventWithSize(CastLoggingEvent event,
                                uint32 rtp_timestamp,
                                uint32 frame_id,
                                int frame_size);
  void InsertFrameEventWithDelay(CastLoggingEvent event,
                                 uint32 rtp_timestamp,
                                 uint32 frame_id,
                                 base::TimeDelta delay);
  void InsertPacketListEvent(CastLoggingEvent event, const PacketList& packets);

  void InsertPacketEvent(CastLoggingEvent event,
                         uint32 rtp_timestamp,
                         uint32 frame_id,
                         uint16 packet_id,
                         uint16 max_packet_id,
                         size_t size);
  void InsertGenericEvent(CastLoggingEvent event, int value);

  
  FrameRawMap GetFrameRawData();
  PacketRawMap GetPacketRawData();
  GenericRawMap GetGenericRawData();
  
  const FrameStatsMap* GetFrameStatsData();
  const PacketStatsMap* GetPacketStatsData();
  const GenericStatsMap* GetGenericStatsData();

  void Reset();

 private:
  scoped_refptr<base::TaskRunner> main_thread_proxy_;
  const CastLoggingConfig config_;
  LoggingRaw raw_;
  LoggingStats stats_;

  DISALLOW_COPY_AND_ASSIGN(LoggingImpl);
};

}  
}  

#endif  
