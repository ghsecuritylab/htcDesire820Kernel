// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_PROTOCOL_CONNECTION_TO_CLIENT_H_
#define REMOTING_PROTOCOL_CONNECTION_TO_CLIENT_H_

#include <deque>
#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "base/threading/non_thread_safe.h"
#include "remoting/protocol/audio_writer.h"
#include "remoting/protocol/session.h"
#include "remoting/protocol/video_writer.h"

namespace net {
class IPEndPoint;
}  

namespace remoting {
namespace protocol {

class ClientStub;
class ClipboardStub;
class HostStub;
class InputStub;
class HostControlDispatcher;
class HostEventDispatcher;

class ConnectionToClient : public base::NonThreadSafe,
                           public Session::EventHandler {
 public:
  class EventHandler {
   public:
    
    virtual void OnConnectionAuthenticated(ConnectionToClient* connection) = 0;

    
    
    virtual void OnConnectionChannelsConnected(
        ConnectionToClient* connection) = 0;

    
    virtual void OnConnectionClosed(ConnectionToClient* connection,
                                    ErrorCode error) = 0;

    
    virtual void OnSequenceNumberUpdated(ConnectionToClient* connection,
                                         int64 sequence_number) = 0;

    
    
    virtual void OnRouteChange(ConnectionToClient* connection,
                               const std::string& channel_name,
                               const TransportRoute& route) = 0;

   protected:
    virtual ~EventHandler() {}
  };

  
  
  explicit ConnectionToClient(Session* session);
  virtual ~ConnectionToClient();

  
  
  void SetEventHandler(EventHandler* event_handler);

  
  virtual Session* session();

  
  virtual void Disconnect();

  
  
  virtual void UpdateSequenceNumber(int64 sequence_number);

  
  
  
  
  virtual VideoStub* video_stub();
  virtual AudioStub* audio_stub();
  virtual ClientStub* client_stub();

  
  
  virtual void set_clipboard_stub(ClipboardStub* clipboard_stub);
  virtual ClipboardStub* clipboard_stub();
  virtual void set_host_stub(HostStub* host_stub);
  virtual HostStub* host_stub();
  virtual void set_input_stub(InputStub* input_stub);
  virtual InputStub* input_stub();

  
  virtual void OnSessionStateChange(Session::State state) OVERRIDE;
  virtual void OnSessionRouteChange(const std::string& channel_name,
                                    const TransportRoute& route) OVERRIDE;

 private:
  
  void OnChannelInitialized(bool successful);

  void NotifyIfChannelsReady();

  void Close(ErrorCode error);

  
  void CloseChannels();

  
  EventHandler* handler_;

  
  ClipboardStub* clipboard_stub_;
  HostStub* host_stub_;
  InputStub* input_stub_;

  
  scoped_ptr<Session> session_;

  scoped_ptr<HostControlDispatcher> control_dispatcher_;
  scoped_ptr<HostEventDispatcher> event_dispatcher_;
  scoped_ptr<VideoWriter> video_writer_;
  scoped_ptr<AudioWriter> audio_writer_;

  DISALLOW_COPY_AND_ASSIGN(ConnectionToClient);
};

}  
}  

#endif  
