// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_DISPLAY_VIRTUAL_KEYBOARD_WINDOW_CONTROLLER_H_
#define ASH_DISPLAY_VIRTUAL_KEYBOARD_WINDOW_CONTROLLER_H_

#include "ash/ash_export.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "ui/gfx/display.h"

namespace keyboard {
class KeyboardController;
}

namespace ash {

namespace test {
class VirtualKeyboardWindowControllerTest;
}  

namespace internal {
class DisplayInfo;
class RootWindowController;

class ASH_EXPORT VirtualKeyboardWindowController {
 public:
  VirtualKeyboardWindowController();
  virtual ~VirtualKeyboardWindowController();

  void ActivateKeyboard(keyboard::KeyboardController* keyboard_controller);

  
  
  void UpdateWindow(const DisplayInfo& display_info);

  
  void Close();

 private:
  friend class test::VirtualKeyboardWindowControllerTest;

  
  void FlipDisplay();

  RootWindowController* root_window_controller_for_test() {
    return root_window_controller_.get();
  }

  scoped_ptr<RootWindowController> root_window_controller_;

  DISALLOW_COPY_AND_ASSIGN(VirtualKeyboardWindowController);
};

}  
}  

#endif  
