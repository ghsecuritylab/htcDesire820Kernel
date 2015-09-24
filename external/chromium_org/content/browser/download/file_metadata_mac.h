// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_DOWNLOAD_FILE_METADATA_MAC_H_
#define CONTENT_BROWSER_DOWNLOAD_FILE_METADATA_MAC_H_

class GURL;

namespace base {
class FilePath;
}

namespace content {

void AddOriginMetadataToFile(const base::FilePath& file, const GURL& source,
                             const GURL& referrer);

void AddQuarantineMetadataToFile(const base::FilePath& file, const GURL& source,
                                 const GURL& referrer);

}  

#endif  