// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_PROXY_FILE_CHOOSER_RESOURCE_H_
#define PPAPI_PROXY_FILE_CHOOSER_RESOURCE_H_

#include <queue>
#include <string>
#include <vector>

#include "ppapi/proxy/plugin_resource.h"
#include "ppapi/proxy/ppapi_proxy_export.h"
#include "ppapi/shared_impl/array_writer.h"
#include "ppapi/shared_impl/tracked_callback.h"
#include "ppapi/thunk/ppb_file_chooser_api.h"

namespace ppapi {

struct FileRefCreateInfo;

namespace proxy {

class PPAPI_PROXY_EXPORT FileChooserResource
    : public PluginResource,
      public NON_EXPORTED_BASE(thunk::PPB_FileChooser_API) {
 public:
  FileChooserResource(Connection connection,
                      PP_Instance instance,
                      PP_FileChooserMode_Dev mode,
                      const std::string& accept_types);
  virtual ~FileChooserResource();

  
  virtual thunk::PPB_FileChooser_API* AsPPB_FileChooser_API() OVERRIDE;

  
  virtual int32_t Show(const PP_ArrayOutput& output,
                       scoped_refptr<TrackedCallback> callback) OVERRIDE;
  virtual int32_t ShowWithoutUserGesture(
      PP_Bool save_as,
      PP_Var suggested_file_name,
      const PP_ArrayOutput& output,
      scoped_refptr<TrackedCallback> callback) OVERRIDE;
  virtual int32_t Show0_5(scoped_refptr<TrackedCallback> callback) OVERRIDE;
  virtual PP_Resource GetNextChosenFile() OVERRIDE;
  virtual int32_t ShowWithoutUserGesture0_5(
      PP_Bool save_as,
      PP_Var suggested_file_name,
      scoped_refptr<TrackedCallback> callback) OVERRIDE;

  
  static void PopulateAcceptTypes(const std::string& input,
                                  std::vector<std::string>* output);

 private:
  void OnPluginMsgShowReply(
      const ResourceMessageReplyParams& params,
      const std::vector<FileRefCreateInfo>& chosen_files);

  int32_t ShowInternal(PP_Bool save_as,
                       const PP_Var& suggested_file_name,
                       scoped_refptr<TrackedCallback> callback);

  PP_FileChooserMode_Dev mode_;
  std::vector<std::string> accept_types_;

  
  ArrayWriter output_;

  
  
  
  
  std::queue<PP_Resource> file_queue_;

  scoped_refptr<TrackedCallback> callback_;

  DISALLOW_COPY_AND_ASSIGN(FileChooserResource);
};

}  
}  

#endif  