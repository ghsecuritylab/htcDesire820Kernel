// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_BLUETOOTH_BLUETOOTH_API_UTILS_H_
#define CHROME_BROWSER_EXTENSIONS_API_BLUETOOTH_BLUETOOTH_API_UTILS_H_

#include "base/values.h"
#include "chrome/common/extensions/api/bluetooth.h"
#include "device/bluetooth/bluetooth_adapter.h"
#include "device/bluetooth/bluetooth_device.h"

namespace extensions {
namespace api {
namespace bluetooth {

void BluetoothDeviceToApiDevice(
    const device::BluetoothDevice& device,
    Device* out);

void PopulateAdapterState(const device::BluetoothAdapter& adapter,
                          AdapterState* out);

}  
}  
}  

#endif  