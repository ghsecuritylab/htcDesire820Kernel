// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_GLUE_PROXY_DATA_TYPE_CONTROLLER_H__
#define CHROME_BROWSER_SYNC_GLUE_PROXY_DATA_TYPE_CONTROLLER_H__

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "chrome/browser/sync/glue/data_type_controller.h"

namespace browser_sync {

class ProxyDataTypeController : public DataTypeController {
 public:
  explicit ProxyDataTypeController(syncer::ModelType type);

  
  virtual void LoadModels(
      const ModelLoadCallback& model_load_callback) OVERRIDE;
  virtual void StartAssociating(const StartCallback& start_callback) OVERRIDE;
  virtual void Stop() OVERRIDE;
  virtual syncer::ModelType type() const OVERRIDE;
  virtual syncer::ModelSafeGroup model_safe_group() const OVERRIDE;
  virtual std::string name() const OVERRIDE;
  virtual State state() const OVERRIDE;

  
  virtual void OnSingleDatatypeUnrecoverableError(
      const tracked_objects::Location& from_here,
      const std::string& message) OVERRIDE;

 protected:
  
  virtual ~ProxyDataTypeController();

  
  virtual void OnModelLoaded() OVERRIDE;

 private:
  State state_;

  
  syncer::ModelType type_;

  DISALLOW_COPY_AND_ASSIGN(ProxyDataTypeController);
};

}  

#endif  