// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_EVENT_SOURCE_H_
#define UI_EVENTS_EVENT_SOURCE_H_

#include "ui/events/events_export.h"

namespace ui {

class Event;
class EventProcessor;

class EVENTS_EXPORT EventSource {
 public:
  virtual ~EventSource() {}

  virtual EventProcessor* GetEventProcessor() = 0;

 protected:
  void SendEventToProcessor(Event* event);
};

}  

#endif 
