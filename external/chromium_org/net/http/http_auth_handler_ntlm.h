// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_HTTP_HTTP_AUTH_HANDLER_NTLM_H_
#define NET_HTTP_HTTP_AUTH_HANDLER_NTLM_H_

#include "build/build_config.h"

#if defined(OS_WIN)
#define NTLM_SSPI
#else
#define NTLM_PORTABLE
#endif

#if defined(NTLM_SSPI)
#define SECURITY_WIN32 1
#include <windows.h>
#include <security.h>
#include "net/http/http_auth_sspi_win.h"
#endif

#include <string>

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "net/http/http_auth_handler.h"
#include "net/http/http_auth_handler_factory.h"

namespace net {

class URLSecurityManager;

class NET_EXPORT_PRIVATE HttpAuthHandlerNTLM : public HttpAuthHandler {
 public:
  class Factory : public HttpAuthHandlerFactory {
   public:
    Factory();
    virtual ~Factory();

    virtual int CreateAuthHandler(
        HttpAuth::ChallengeTokenizer* challenge,
        HttpAuth::Target target,
        const GURL& origin,
        CreateReason reason,
        int digest_nonce_count,
        const BoundNetLog& net_log,
        scoped_ptr<HttpAuthHandler>* handler) OVERRIDE;
#if defined(NTLM_SSPI)
    
    
    
    
    void set_sspi_library(SSPILibrary* sspi_library) {
      sspi_library_.reset(sspi_library);
    }
#endif  
   private:
#if defined(NTLM_SSPI)
    ULONG max_token_length_;
    bool first_creation_;
    bool is_unsupported_;
    scoped_ptr<SSPILibrary> sspi_library_;
#endif  
  };

#if defined(NTLM_PORTABLE)
  
  typedef void (*GenerateRandomProc)(uint8* output, size_t n);

  
  
  typedef std::string (*HostNameProc)();

  
  
  class ScopedProcSetter {
   public:
    ScopedProcSetter(GenerateRandomProc random_proc,
                     HostNameProc host_name_proc) {
      old_random_proc_ = SetGenerateRandomProc(random_proc);
      old_host_name_proc_ = SetHostNameProc(host_name_proc);
    }

    ~ScopedProcSetter() {
      SetGenerateRandomProc(old_random_proc_);
      SetHostNameProc(old_host_name_proc_);
    }

   private:
    GenerateRandomProc old_random_proc_;
    HostNameProc old_host_name_proc_;
  };
#endif

#if defined(NTLM_PORTABLE)
  HttpAuthHandlerNTLM();
#endif
#if defined(NTLM_SSPI)
  HttpAuthHandlerNTLM(SSPILibrary* sspi_library, ULONG max_token_length,
                      URLSecurityManager* url_security_manager);
#endif

  virtual bool NeedsIdentity() OVERRIDE;

  virtual bool AllowsDefaultCredentials() OVERRIDE;

  virtual HttpAuth::AuthorizationResult HandleAnotherChallenge(
      HttpAuth::ChallengeTokenizer* challenge) OVERRIDE;

 protected:
  
  
  int InitializeBeforeFirstChallenge();

  virtual bool Init(HttpAuth::ChallengeTokenizer* tok) OVERRIDE;

  virtual int GenerateAuthTokenImpl(const AuthCredentials* credentials,
                                    const HttpRequestInfo* request,
                                    const CompletionCallback& callback,
                                    std::string* auth_token) OVERRIDE;

 private:
  virtual ~HttpAuthHandlerNTLM();

#if defined(NTLM_PORTABLE)
  
  
  static GenerateRandomProc SetGenerateRandomProc(GenerateRandomProc proc);
  static HostNameProc SetHostNameProc(HostNameProc proc);
#endif

  
  HttpAuth::AuthorizationResult ParseChallenge(
      HttpAuth::ChallengeTokenizer* tok, bool initial_challenge);

  
  
  int GetNextToken(const void* in_token,
                   uint32 in_token_len,
                   void** out_token,
                   uint32* out_token_len);

  
  static std::string CreateSPN(const GURL& origin);

#if defined(NTLM_SSPI)
  HttpAuthSSPI auth_sspi_;
#endif

#if defined(NTLM_PORTABLE)
  static GenerateRandomProc generate_random_proc_;
  static HostNameProc get_host_name_proc_;
#endif

  base::string16 domain_;
  AuthCredentials credentials_;

  
  
  std::string auth_data_;

#if defined(NTLM_SSPI)
  URLSecurityManager* url_security_manager_;
#endif
};

}  

#endif  