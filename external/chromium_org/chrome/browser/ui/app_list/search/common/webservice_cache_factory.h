// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_APP_LIST_SEARCH_COMMON_WEBSERVICE_CACHE_FACTORY_H_
#define CHROME_BROWSER_UI_APP_LIST_SEARCH_COMMON_WEBSERVICE_CACHE_FACTORY_H_

#include "components/browser_context_keyed_service/browser_context_keyed_service_factory.h"

template<typename T> struct DefaultSingletonTraits;

namespace content {
class BrowserContext;
}

namespace app_list {

class WebserviceCache;

class WebserviceCacheFactory : public BrowserContextKeyedServiceFactory {
 public:
  
  static WebserviceCacheFactory* GetInstance();

  
  static WebserviceCache* GetForBrowserContext(
      content::BrowserContext* context);

 private:
  friend struct DefaultSingletonTraits<WebserviceCacheFactory>;

  WebserviceCacheFactory();
  virtual ~WebserviceCacheFactory();

  
  virtual BrowserContextKeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(WebserviceCacheFactory);
};

}  

#endif  