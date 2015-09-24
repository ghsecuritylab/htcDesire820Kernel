// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef BASE_ATOMIC_REF_COUNT_H_
#define BASE_ATOMIC_REF_COUNT_H_
#pragma once

#include "base/atomicops.h"
#include "base/third_party/dynamic_annotations/dynamic_annotations.h"

namespace base {

typedef subtle::Atomic32 AtomicRefCount;

inline void AtomicRefCountIncN(volatile AtomicRefCount *ptr,
                               AtomicRefCount increment) {
  subtle::NoBarrier_AtomicIncrement(ptr, increment);
}

// Insert barriers to ensure that state written before the reference count
inline bool AtomicRefCountDecN(volatile AtomicRefCount *ptr,
                               AtomicRefCount decrement) {
  ANNOTATE_HAPPENS_BEFORE(ptr);
  bool res = (subtle::Barrier_AtomicIncrement(ptr, -decrement) != 0);
  if (!res) {
    ANNOTATE_HAPPENS_AFTER(ptr);
  }
  return res;
}

inline void AtomicRefCountInc(volatile AtomicRefCount *ptr) {
  base::AtomicRefCountIncN(ptr, 1);
}

// Insert barriers to ensure that state written before the reference count
inline bool AtomicRefCountDec(volatile AtomicRefCount *ptr) {
  return base::AtomicRefCountDecN(ptr, 1);
}

inline bool AtomicRefCountIsOne(volatile AtomicRefCount *ptr) {
  bool res = (subtle::Acquire_Load(ptr) == 1);
  if (res) {
    ANNOTATE_HAPPENS_AFTER(ptr);
  }
  return res;
}

inline bool AtomicRefCountIsZero(volatile AtomicRefCount *ptr) {
  bool res = (subtle::Acquire_Load(ptr) == 0);
  if (res) {
    ANNOTATE_HAPPENS_AFTER(ptr);
  }
  return res;
}

}  

#endif  