// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_DOWNLOAD_DRAG_DOWNLOAD_FILE_H_
#define CONTENT_BROWSER_DOWNLOAD_DRAG_DOWNLOAD_FILE_H_

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/run_loop.h"
#include "content/browser/download/download_file.h"
#include "content/common/content_export.h"
#include "content/public/browser/download_item.h"
#include "content/public/browser/download_manager.h"
#include "content/public/common/referrer.h"
#include "net/base/file_stream.h"
#include "ui/base/dragdrop/download_file_interface.h"
#include "url/gurl.h"

namespace net {
class FileStream;
}

namespace content {

class DownloadManager;
class WebContents;

class CONTENT_EXPORT DragDownloadFile : public ui::DownloadFileProvider {
 public:
  
  
  
  
  DragDownloadFile(const base::FilePath& file_path,
                   scoped_ptr<net::FileStream> file_stream,
                   const GURL& url,
                   const Referrer& referrer,
                   const std::string& referrer_encoding,
                   WebContents* web_contents);

  
  virtual void Start(ui::DownloadFileObserver* observer) OVERRIDE;
  virtual bool Wait() OVERRIDE;
  virtual void Stop() OVERRIDE;

 private:
  class DragDownloadFileUI;
  enum State {INITIALIZED, STARTED, SUCCESS, FAILURE};

  virtual ~DragDownloadFile();

  void DownloadCompleted(bool is_successful);
  void CheckThread();

  base::FilePath file_path_;
  scoped_ptr<net::FileStream> file_stream_;
  base::MessageLoop* drag_message_loop_;
  State state_;
  scoped_refptr<ui::DownloadFileObserver> observer_;
  base::RunLoop nested_loop_;
  DragDownloadFileUI* drag_ui_;
  base::WeakPtrFactory<DragDownloadFile> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(DragDownloadFile);
};

}  

#endif  
