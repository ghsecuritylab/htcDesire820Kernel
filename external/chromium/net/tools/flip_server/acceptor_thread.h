// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_TOOLS_FLIP_SERVER_ACCEPTOR_THREAD_H_
#define NET_TOOLS_FLIP_SERVER_ACCEPTOR_THREAD_H_

#include <list>
#include <string>
#include <vector>

#include "base/threading/simple_thread.h"
#include "net/tools/flip_server/epoll_server.h"
#include "net/tools/flip_server/sm_interface.h"
#include "openssl/ssl.h"

struct sockaddr_in;

namespace net {

class FlipAcceptor;
class MemoryCache;
class SMConnection;
struct SSLState;

class Notification {
 public:
   explicit Notification(bool value) : value_(value) {}

   void Notify() {
     base::AutoLock al(lock_);
     value_ = true;
   }
   bool HasBeenNotified() {
     base::AutoLock al(lock_);
     return value_;
   }
   bool value_;
   base::Lock lock_;
};

class SMAcceptorThread : public base::SimpleThread,
                         public EpollCallbackInterface,
                         public SMConnectionPoolInterface {
 public:
  SMAcceptorThread(FlipAcceptor *acceptor, MemoryCache* memory_cache);
  ~SMAcceptorThread();

  
  virtual void OnRegistration(EpollServer* eps, int fd, int event_mask) {}
  virtual void OnModification(int fd, int event_mask) {}
  virtual void OnEvent(int fd, EpollEvent* event);
  virtual void OnUnregistration(int fd, bool replaced) {}
  virtual void OnShutdown(EpollServer* eps, int fd) {}

  
  virtual void SMConnectionDone(SMConnection* sc);

  
  SMConnection* NewConnection();
  SMConnection* FindOrMakeNewSMConnection();
  void InitWorker();
  void HandleConnection(int server_fd, struct sockaddr_in *remote_addr);
  void AcceptFromListenFD();

  
  void Quit() { quitting_.Notify(); }

  
  
  void HandleConnectionIdleTimeout();

  virtual void Run();

 private:
  EpollServer epoll_server_;
  FlipAcceptor* acceptor_;
  SSLState* ssl_state_;
  bool use_ssl_;
  int idle_socket_timeout_s_;

  std::vector<SMConnection*> unused_server_connections_;
  std::vector<SMConnection*> tmp_unused_server_connections_;
  std::vector<SMConnection*> allocated_server_connections_;
  std::list<SMConnection*> active_server_connections_;
  Notification quitting_;
  MemoryCache* memory_cache_;
};

}  

#endif  
