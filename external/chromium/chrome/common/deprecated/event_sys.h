// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_DEPRECATED_EVENT_SYS_H_
#define CHROME_COMMON_DEPRECATED_EVENT_SYS_H_
#pragma once


namespace base {
class AutoLock;
class Lock;
}

template <typename EventType>
class EventListener {
 public:
  virtual void HandleEvent(const EventType& event) = 0;

 protected:
  virtual ~EventListener() {}
};


template <typename EventTraits, typename NotifyLock = base::Lock,
          typename ScopedNotifyLocker = base::AutoLock>
class EventChannel;

class EventListenerHookup;

template <typename EventChannel, typename CallbackObject,
          typename CallbackMethod>
EventListenerHookup* NewEventListenerHookup(EventChannel* channel,
                                            CallbackObject* cbobject,
                                            CallbackMethod cbmethod);

template <typename EventChannel, typename CallbackObject,
          typename CallbackMethod, typename CallbackArg0>
EventListenerHookup* NewEventListenerHookup(EventChannel* channel,
                                            CallbackObject* cbobject,
                                            CallbackMethod cbmethod,
                                            CallbackArg0 arg0);

#endif  