// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_LOCAL_DISCOVERY_PRIVET_TRAFFIC_DETECTOR_H_
#define CHROME_BROWSER_LOCAL_DISCOVERY_PRIVET_TRAFFIC_DETECTOR_H_

#include "base/callback.h"
#include "base/cancelable_callback.h"
#include "content/public/browser/browser_thread.h"
#include "net/base/address_family.h"
#include "net/base/ip_endpoint.h"
#include "net/base/network_change_notifier.h"

namespace net {
class DatagramServerSocket;
class IOBufferWithSize;
}

namespace local_discovery {

class PrivetTrafficDetector
    : public base::RefCountedThreadSafe<
          PrivetTrafficDetector, content::BrowserThread::DeleteOnIOThread>,
      private net::NetworkChangeNotifier::NetworkChangeObserver {
 public:
  PrivetTrafficDetector(net::AddressFamily address_family,
                        const base::Closure& on_traffic_detected);

  void Start();

 private:
  friend struct content::BrowserThread::DeleteOnThread<
      content::BrowserThread::IO>;
  friend class base::DeleteHelper<PrivetTrafficDetector>;
  virtual ~PrivetTrafficDetector();

    
  virtual void OnNetworkChanged(
      net::NetworkChangeNotifier::ConnectionType type) OVERRIDE;

  void StartOnIOThread();
  void ScheduleRestart();
  void Restart(const net::NetworkInterfaceList& networks);
  int Bind();
  bool IsSourceAcceptable() const;
  bool IsPrivetPacket(int rv) const;
  int DoLoop(int rv);

  base::Closure on_traffic_detected_;
  scoped_refptr<base::TaskRunner> callback_runner_;
  net::NetworkInterfaceList networks_;
  net::AddressFamily address_family_;
  net::IPEndPoint recv_addr_;
  scoped_ptr<net::DatagramServerSocket> socket_;
  scoped_refptr<net::IOBufferWithSize> io_buffer_;
  base::Time start_time_;
  int restart_attempts_;

  base::WeakPtrFactory<PrivetTrafficDetector> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(PrivetTrafficDetector);
};

}  

#endif  