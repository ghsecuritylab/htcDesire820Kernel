// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_PRINTING_PRINTING_MESSAGE_FILTER_H_
#define CHROME_BROWSER_PRINTING_PRINTING_MESSAGE_FILTER_H_

#include <string>

#include "base/compiler_specific.h"
#include "content/public/browser/browser_message_filter.h"

#if defined(OS_WIN)
#include "base/memory/shared_memory.h"
#endif

struct PrintHostMsg_ScriptedPrint_Params;
class Profile;
class ProfileIOData;

namespace base {
class DictionaryValue;
class FilePath;
}

namespace content {
class WebContents;
}

namespace printing {
class PrinterQuery;
class PrintJobManager;
class PrintQueriesQueue;
}

class PrintingMessageFilter : public content::BrowserMessageFilter {
 public:
  PrintingMessageFilter(int render_process_id, Profile* profile);

  
  virtual void OverrideThreadForMessage(
      const IPC::Message& message,
      content::BrowserThread::ID* thread) OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message,
                                 bool* message_was_ok) OVERRIDE;

 private:
  virtual ~PrintingMessageFilter();

#if defined(OS_WIN)
  
  void OnDuplicateSection(base::SharedMemoryHandle renderer_handle,
                          base::SharedMemoryHandle* browser_handle);
#endif

#if defined(OS_CHROMEOS) || defined(OS_ANDROID)
  
  
  void OnAllocateTempFileForPrinting(int render_view_id,
                                     base::FileDescriptor* temp_file_fd,
                                     int* sequence_number);
  void OnTempFileForPrintingWritten(int render_view_id, int sequence_number);
#endif

#if defined(OS_CHROMEOS)
  void CreatePrintDialogForFile(int render_view_id, const base::FilePath& path);
#endif

#if defined(OS_ANDROID)
  
  
  void UpdateFileDescriptor(int render_view_id, int fd);
#endif

  
  
  content::WebContents* GetWebContentsForRenderView(int render_view_id);

  
  
  
  
  struct GetPrintSettingsForRenderViewParams;

  
  
  void GetPrintSettingsForRenderView(
      int render_view_id,
      GetPrintSettingsForRenderViewParams params,
      const base::Closure& callback,
      scoped_refptr<printing::PrinterQuery> printer_query);

  void OnGetPrintSettingsFailed(
      const base::Closure& callback,
      scoped_refptr<printing::PrinterQuery> printer_query);

  
  void OnIsPrintingEnabled(bool* is_enabled);

  
  void OnGetDefaultPrintSettings(IPC::Message* reply_msg);
  void OnGetDefaultPrintSettingsReply(
      scoped_refptr<printing::PrinterQuery> printer_query,
      IPC::Message* reply_msg);

  
  
  
  void OnScriptedPrint(const PrintHostMsg_ScriptedPrint_Params& params,
                       IPC::Message* reply_msg);
  void OnScriptedPrintReply(
      scoped_refptr<printing::PrinterQuery> printer_query,
      IPC::Message* reply_msg);

  
  
  
  void OnUpdatePrintSettings(int document_cookie,
                             const base::DictionaryValue& job_settings,
                             IPC::Message* reply_msg);
  void OnUpdatePrintSettingsReply(
      scoped_refptr<printing::PrinterQuery> printer_query,
      IPC::Message* reply_msg);

#if defined(ENABLE_FULL_PRINTING)
  
  void OnCheckForCancel(int32 preview_ui_id,
                        int preview_request_id,
                        bool* cancel);
#endif

  ProfileIOData* profile_io_data_;

  const int render_process_id_;

  scoped_refptr<printing::PrintQueriesQueue> queue_;

  DISALLOW_COPY_AND_ASSIGN(PrintingMessageFilter);
};

#endif  