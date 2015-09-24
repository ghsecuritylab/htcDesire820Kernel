// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_TEST_SHELL_TEST_API_H_
#define ASH_TEST_SHELL_TEST_API_H_

#include "base/basictypes.h"

namespace views {
namespace corewm {
class InputMethodEventFilter;
}  
}  

namespace ash {
class AshNativeCursorManager;
class ShelfDelegate;
class ShelfModel;
class Shell;

namespace internal {
class AppListController;
class DragDropController;
class RootWindowLayoutManager;
class ScreenPositionController;
class SystemGestureEventFilter;
class WorkspaceController;
}  

namespace test {

class ShellTestApi {
public:
  explicit ShellTestApi(Shell* shell);

  internal::RootWindowLayoutManager* root_window_layout();
  views::corewm::InputMethodEventFilter* input_method_event_filter();
  internal::SystemGestureEventFilter* system_gesture_event_filter();
  internal::WorkspaceController* workspace_controller();
  internal::ScreenPositionController* screen_position_controller();
  AshNativeCursorManager* ash_native_cursor_manager();
  ShelfModel* shelf_model();
  internal::DragDropController* drag_drop_controller();
  internal::AppListController* app_list_controller();

  void DisableOutputConfiguratorAnimation();

  
  void SetShelfDelegate(ShelfDelegate* delegate);

 private:
  Shell* shell_;  

  DISALLOW_COPY_AND_ASSIGN(ShellTestApi);
};

}  
}  

#endif  