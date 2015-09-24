// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_SEARCH_URLS_H_
#define CHROME_COMMON_SEARCH_URLS_H_

class GURL;

namespace search {

bool MatchesOriginAndPath(const GURL& my_url, const GURL& other_url);

}  

#endif  