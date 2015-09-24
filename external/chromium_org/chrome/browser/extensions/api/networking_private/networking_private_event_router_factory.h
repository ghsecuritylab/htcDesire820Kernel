// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_NETWORKING_PRIVATE_NETWORKING_PRIVATE_EVENT_ROUTER_FACTORY_H_
#define CHROME_BROWSER_EXTENSIONS_API_NETWORKING_PRIVATE_NETWORKING_PRIVATE_EVENT_ROUTER_FACTORY_H_

#include "base/memory/singleton.h"
#include "components/browser_context_keyed_service/browser_context_keyed_service_factory.h"

class Profile;

namespace extensions {

class NetworkingPrivateEventRouter;

class NetworkingPrivateEventRouterFactory
    : public BrowserContextKeyedServiceFactory {
 public:
  
  
  static NetworkingPrivateEventRouter* GetForProfile(Profile* profile);

  
  static NetworkingPrivateEventRouterFactory* GetInstance();

 protected:
  
  virtual content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const OVERRIDE;
  virtual bool ServiceIsCreatedWithBrowserContext() const OVERRIDE;
  virtual bool ServiceIsNULLWhileTesting() const OVERRIDE;

 private:
  friend struct DefaultSingletonTraits<NetworkingPrivateEventRouterFactory>;

  NetworkingPrivateEventRouterFactory();
  virtual ~NetworkingPrivateEventRouterFactory();

  
  virtual BrowserContextKeyedService* BuildServiceInstanceFor(
      content::BrowserContext* profile) const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(NetworkingPrivateEventRouterFactory);
};

}  

#endif  
