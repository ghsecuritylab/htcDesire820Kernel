// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_UPDATER_REQUEST_QUEUE_IMPL_H_
#define CHROME_BROWSER_EXTENSIONS_UPDATER_REQUEST_QUEUE_IMPL_H_

#include <algorithm>

#include "base/bind.h"
#include "base/compiler_specific.h"
#include "base/message_loop/message_loop.h"
#include "base/stl_util.h"
#include "chrome/browser/extensions/updater/request_queue.h"

namespace extensions {

template<typename T>
RequestQueue<T>::RequestQueue(
    const net::BackoffEntry::Policy* const backoff_policy,
    const base::Closure& start_request_callback)
    : backoff_policy_(backoff_policy),
      start_request_callback_(start_request_callback),
      timer_(false, false) {
}

template<typename T>
RequestQueue<T>::~RequestQueue() {}

template<typename T>
T* RequestQueue<T>::active_request() {
  return active_request_.get();
}

template<typename T>
int RequestQueue<T>::active_request_failure_count() {
  return active_backoff_entry_->failure_count();
}

template<typename T>
scoped_ptr<T> RequestQueue<T>::reset_active_request() {
  active_backoff_entry_.reset();
  return active_request_.Pass();
}

template<typename T>
void RequestQueue<T>::ScheduleRequest(scoped_ptr<T> request) {
  PushImpl(request.Pass(), scoped_ptr<net::BackoffEntry>(
      new net::BackoffEntry(backoff_policy_)));
  StartNextRequest();
}

template<typename T>
void RequestQueue<T>::PushImpl(scoped_ptr<T> request,
                               scoped_ptr<net::BackoffEntry> backoff_entry) {
  pending_requests_.push_back(Request(
      backoff_entry.release(), request.release()));
  std::push_heap(pending_requests_.begin(), pending_requests_.end(),
                 CompareRequests);
}

template<typename T>
bool RequestQueue<T>::empty() const {
  return pending_requests_.empty();
}

template<typename T>
size_t RequestQueue<T>::size() const {
  return pending_requests_.size();
}

template<typename T>
base::TimeTicks RequestQueue<T>::NextReleaseTime() const {
  return pending_requests_.front().backoff_entry->GetReleaseTime();
}

template<typename T>
void RequestQueue<T>::StartNextRequest() {
  if (active_request_)
    
    
    return;

  if (empty())
    
    return;

  base::TimeTicks next_release = NextReleaseTime();
  base::TimeTicks now = base::TimeTicks::Now();
  if (next_release > now) {
    
    
    timer_.Start(FROM_HERE, next_release - now,
          base::Bind(&RequestQueue<T>::StartNextRequest,
                     base::Unretained(this)));
    return;
  }

  
  
  
  
  
  
  
  std::pop_heap(pending_requests_.begin(), pending_requests_.end(),
                CompareRequests);

  active_backoff_entry_.reset(pending_requests_.back().backoff_entry.release());
  active_request_.reset(pending_requests_.back().request.release());

  pending_requests_.pop_back();

  start_request_callback_.Run();
}

template<typename T>
void RequestQueue<T>::RetryRequest(const base::TimeDelta& min_backoff_delay) {
  active_backoff_entry_->InformOfRequest(false);
  if (active_backoff_entry_->GetTimeUntilRelease() < min_backoff_delay) {
    active_backoff_entry_->SetCustomReleaseTime(
        base::TimeTicks::Now() + min_backoff_delay);
  }
  PushImpl(active_request_.Pass(), active_backoff_entry_.Pass());
}

template<typename T>
typename RequestQueue<T>::iterator RequestQueue<T>::begin() {
  return iterator(pending_requests_.begin());
}

template<typename T>
typename RequestQueue<T>::iterator RequestQueue<T>::end() {
  return iterator(pending_requests_.end());
}

template<typename T>
void RequestQueue<T>::set_backoff_policy(
    const net::BackoffEntry::Policy* backoff_policy) {
  backoff_policy_ = backoff_policy;
}

template<typename T>
bool RequestQueue<T>::CompareRequests(
    const Request& a,
    const Request& b) {
  return a.backoff_entry->GetReleaseTime() >
         b.backoff_entry->GetReleaseTime();
}

}  

#endif  
