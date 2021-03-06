// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_GAMEPAD_XBOX_DATA_FETCHER_MAC_H_
#define CONTENT_BROWSER_GAMEPAD_XBOX_DATA_FETCHER_MAC_H_

#include <CoreFoundation/CoreFoundation.h>
#include <IOKit/IOKitLib.h>

#include <set>

#include "base/basictypes.h"
#include "base/mac/scoped_cftyperef.h"
#include "base/mac/scoped_ioobject.h"
#include "base/mac/scoped_ioplugininterface.h"
#include "base/memory/scoped_ptr.h"

class XboxController {
 public:
  enum LEDPattern {
    LED_OFF = 0,

    
    LED_FLASH = 1,

    
    
    LED_FLASH_TOP_LEFT = 2,
    LED_FLASH_TOP_RIGHT = 3,
    LED_FLASH_BOTTOM_LEFT = 4,
    LED_FLASH_BOTTOM_RIGHT = 5,

    
    LED_HOLD_TOP_LEFT = 6,
    LED_HOLD_TOP_RIGHT = 7,
    LED_HOLD_BOTTOM_LEFT = 8,
    LED_HOLD_BOTTOM_RIGHT = 9,

    LED_ROTATE = 10,

    LED_FLASH_FAST = 11,
    LED_FLASH_SLOW = 12,  

    
    
    LED_ALTERNATE_PATTERN = 13,

    

    
    LED_FLASH_ONCE = 15,

    LED_NUM_PATTERNS
  };

  struct Data {
    bool buttons[15];
    float triggers[2];
    float axes[4];
  };

  class Delegate {
   public:
    virtual void XboxControllerGotData(XboxController* controller,
                                       const Data& data) = 0;
    virtual void XboxControllerError(XboxController* controller) = 0;
  };

  explicit XboxController(Delegate* delegate_);
  virtual ~XboxController();

  bool OpenDevice(io_service_t service);

  void SetLEDPattern(LEDPattern pattern);

  UInt32 location_id() { return location_id_; }
  int GetVendorId() const;
  int GetProductId() const;

 private:
  static void WriteComplete(void* context, IOReturn result, void* arg0);
  static void GotData(void* context, IOReturn result, void* arg0);

  void ProcessPacket(size_t length);
  void QueueRead();

  void IOError();

  
  
  base::mac::ScopedIOPluginInterface<struct IOUSBDeviceStruct320> device_;

  
  
  base::mac::ScopedIOPluginInterface<struct IOUSBInterfaceStruct300> interface_;

  bool device_is_open_;
  bool interface_is_open_;

  base::ScopedCFTypeRef<CFRunLoopSourceRef> source_;

  
  
  
  
  
  
  uint16 read_buffer_size_;
  scoped_ptr<uint8[]> read_buffer_;

  
  
  LEDPattern led_pattern_;

  UInt32 location_id_;

  Delegate* delegate_;

  DISALLOW_COPY_AND_ASSIGN(XboxController);
};

class XboxDataFetcher : public XboxController::Delegate {
 public:
  class Delegate {
   public:
    virtual void XboxDeviceAdd(XboxController* device) = 0;
    virtual void XboxDeviceRemove(XboxController* device) = 0;
    virtual void XboxValueChanged(XboxController* device,
                                  const XboxController::Data& data) = 0;
  };

  explicit XboxDataFetcher(Delegate* delegate);
  virtual ~XboxDataFetcher();

  bool RegisterForNotifications();
  void UnregisterFromNotifications();

  XboxController* ControllerForLocation(UInt32 location_id);

 private:
  static void DeviceAdded(void* context, io_iterator_t iterator);
  static void DeviceRemoved(void* context, io_iterator_t iterator);
  void AddController(XboxController* controller);
  void RemoveController(XboxController* controller);
  void RemoveControllerByLocationID(uint32 id);
  virtual void XboxControllerGotData(XboxController* controller,
                                     const XboxController::Data& data) OVERRIDE;
  virtual void XboxControllerError(XboxController* controller) OVERRIDE;

  Delegate* delegate_;

  std::set<XboxController*> controllers_;

  bool listening_;

  
  
  CFRunLoopSourceRef source_;
  IONotificationPortRef port_;
  base::mac::ScopedIOObject<io_iterator_t> device_added_iter_;
  base::mac::ScopedIOObject<io_iterator_t> device_removed_iter_;

  DISALLOW_COPY_AND_ASSIGN(XboxDataFetcher);
};

#endif  
