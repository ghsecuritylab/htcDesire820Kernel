// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef LIBRARIES_SDK_UTIL_THREAD_POOL_H_
#define LIBRARIES_SDK_UTIL_THREAD_POOL_H_

#include <pthread.h>
#include <semaphore.h>

#include "sdk_util/atomicops.h"

namespace sdk_util {

typedef void (*WorkFunction)(int task_index, void* data);


class ThreadPool {
 public:
  void Dispatch(int num_tasks, WorkFunction work, void* data);
  explicit ThreadPool(int num_threads);
  ~ThreadPool();
 private:
  int DecCounter();
  void Setup(int counter, WorkFunction work, void* data);
  void DispatchMany(int num_tasks, WorkFunction work, void* data);
  void DispatchHere(int num_tasks, WorkFunction work, void* data);
  void WorkLoop();
  static void* WorkerThreadEntry(void* data);
  void PostExitAndJoinAll();
  pthread_t* threads_;
  Atomic32 counter_;
  const int num_threads_;
  bool exiting_;
  void* user_data_;
  WorkFunction user_work_function_;
  sem_t work_sem_;
  sem_t done_sem_;
};

}  

#endif  

