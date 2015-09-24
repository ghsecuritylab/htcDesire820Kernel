// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_SAVABLE_URL_SCHEMES_H_
#define CONTENT_COMMON_SAVABLE_URL_SCHEMES_H_

namespace content {

const char* const* GetSavableSchemesInternal();

void SetSavableSchemes(const char* const* savable_schemes);

}  

#endif  
