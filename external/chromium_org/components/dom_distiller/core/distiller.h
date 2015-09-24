// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOM_DISTILLER_CORE_DISTILLER_H_
#define COMPONENTS_DOM_DISTILLER_CORE_DISTILLER_H_

#include <map>
#include <string>

#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/values.h"
#include "components/dom_distiller/core/distiller_page.h"
#include "components/dom_distiller/core/distiller_url_fetcher.h"
#include "components/dom_distiller/core/proto/distilled_page.pb.h"
#include "net/url_request/url_request_context_getter.h"
#include "url/gurl.h"

namespace dom_distiller {

class DistillerImpl;

class Distiller {
 public:
  typedef base::Callback<void(
      scoped_ptr<DistilledPageProto>)> DistillerCallback;
  virtual ~Distiller() {}

  
  
  virtual void DistillPage(const GURL& url,
                           const DistillerCallback& callback) = 0;
};

class DistillerFactory {
 public:
  virtual scoped_ptr<Distiller> CreateDistiller() = 0;
  virtual ~DistillerFactory() {}
};

class DistillerFactoryImpl : public DistillerFactory {
 public:
  DistillerFactoryImpl(
      scoped_ptr<DistillerPageFactory> distiller_page_factory,
      scoped_ptr<DistillerURLFetcherFactory> distiller_url_fetcher_factory);
  virtual ~DistillerFactoryImpl();
  virtual scoped_ptr<Distiller> CreateDistiller() OVERRIDE;

 private:
  scoped_ptr<DistillerPageFactory> distiller_page_factory_;
  scoped_ptr<DistillerURLFetcherFactory> distiller_url_fetcher_factory_;
};

class DistillerImpl : public Distiller,
                      public DistillerPage::Delegate {
 public:
  DistillerImpl(
      const DistillerPageFactory& distiller_page_factory,
      const DistillerURLFetcherFactory& distiller_url_fetcher_factory);
  virtual ~DistillerImpl();

  
  
  virtual void Init();

  virtual void DistillPage(const GURL& url,
                           const DistillerCallback& callback) OVERRIDE;

  
  virtual void OnLoadURLDone() OVERRIDE;
  virtual void OnExecuteJavaScriptDone(const base::Value* value) OVERRIDE;

  void OnFetchImageDone(const std::string& id, const std::string& response);

 private:
  virtual void LoadURL(const GURL& url);
  virtual void FetchImage(const std::string& image_id, const std::string& item);

  
  
  void GetDistilledContent();

  const DistillerPageFactory& distiller_page_factory_;
  const DistillerURLFetcherFactory& distiller_url_fetcher_factory_;
  scoped_ptr<DistillerPage> distiller_page_;
  DistillerCallback distillation_cb_;

  std::map<std::string, DistillerURLFetcher* > image_fetchers_;

  scoped_ptr<DistilledPageProto> proto_;

  DISALLOW_COPY_AND_ASSIGN(DistillerImpl);
};

}  

#endif  