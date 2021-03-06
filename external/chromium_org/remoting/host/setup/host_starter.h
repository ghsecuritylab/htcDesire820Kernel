// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_HOST_STARTER
#define REMOTING_HOST_HOST_STARTER

#include <string>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "google_apis/gaia/gaia_oauth_client.h"
#include "remoting/base/rsa_key_pair.h"
#include "remoting/base/url_request_context.h"
#include "remoting/host/setup/daemon_controller.h"
#include "remoting/host/setup/service_client.h"

namespace remoting {

class HostStarter : public gaia::GaiaOAuthClient::Delegate,
                    public remoting::ServiceClient::Delegate {
 public:
  enum Result {
    START_COMPLETE,
    NETWORK_ERROR,
    OAUTH_ERROR,
    START_ERROR,
  };

  typedef base::Callback<void(Result)> CompletionCallback;

  virtual ~HostStarter();

  
  static scoped_ptr<HostStarter> Create(
      const std::string& chromoting_hosts_url,
      net::URLRequestContextGetter* url_request_context_getter);

  
  
  
  void StartHost(const std::string& host_name,
                 const std::string& host_pin,
                 bool consent_to_data_collection,
                 const std::string& auth_code,
                 const std::string& redirect_url,
                 CompletionCallback on_done);

  
  virtual void OnGetTokensResponse(const std::string& refresh_token,
                                   const std::string& access_token,
                                   int expires_in_seconds) OVERRIDE;
  virtual void OnRefreshTokenResponse(const std::string& access_token,
                                      int expires_in_seconds) OVERRIDE;
  virtual void OnGetUserEmailResponse(const std::string& user_email) OVERRIDE;

  
  virtual void OnHostRegistered(const std::string& authorization_code) OVERRIDE;
  virtual void OnHostUnregistered() OVERRIDE;

  
  
  
  
  virtual void OnOAuthError() OVERRIDE;
  virtual void OnNetworkError(int response_code) OVERRIDE;

 private:
  HostStarter(scoped_ptr<gaia::GaiaOAuthClient> oauth_client,
              scoped_ptr<remoting::ServiceClient> service_client,
              scoped_refptr<remoting::DaemonController> daemon_controller);

  void StartHostProcess();

  void OnHostStarted(DaemonController::AsyncResult result);

  scoped_ptr<gaia::GaiaOAuthClient> oauth_client_;
  scoped_ptr<remoting::ServiceClient> service_client_;
  scoped_refptr<remoting::DaemonController> daemon_controller_;
  gaia::OAuthClientInfo oauth_client_info_;
  std::string host_name_;
  std::string host_pin_;
  bool consent_to_data_collection_;
  CompletionCallback on_done_;
  scoped_refptr<base::SingleThreadTaskRunner> main_task_runner_;
  std::string refresh_token_;
  std::string access_token_;
  std::string host_owner_;
  std::string xmpp_login_;
  scoped_refptr<remoting::RsaKeyPair> key_pair_;
  std::string host_id_;
  bool use_service_account_;

  
  
  
  bool unregistering_host_;

  base::WeakPtr<HostStarter> weak_ptr_;
  base::WeakPtrFactory<HostStarter> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(HostStarter);
};

}  

#endif  
