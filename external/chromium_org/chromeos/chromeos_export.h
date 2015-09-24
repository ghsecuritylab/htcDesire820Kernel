// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_CHROMEOS_EXPORT_H_
#define CHROMEOS_CHROMEOS_EXPORT_H_

#if defined(COMPONENT_BUILD)
#if defined(WIN32)

#if defined(CHROMEOS_IMPLEMENTATION)
#define CHROMEOS_EXPORT __declspec(dllexport)
#else
#define CHROMEOS_EXPORT __declspec(dllimport)
#endif  

#else  
#if defined(CHROMEOS_IMPLEMENTATION)
#define CHROMEOS_EXPORT __attribute__((visibility("default")))
#else
#define CHROMEOS_EXPORT
#endif
#endif

#else  
#define CHROMEOS_EXPORT
#endif

#endif  