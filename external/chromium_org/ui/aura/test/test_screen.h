// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_AURA_TEST_TEST_SCREEN_H_
#define UI_AURA_TEST_TEST_SCREEN_H_

#include "base/compiler_specific.h"
#include "ui/aura/window_observer.h"
#include "ui/gfx/display.h"
#include "ui/gfx/screen.h"

namespace gfx {
class Rect;
class Transform;
}

namespace aura {
class RootWindow;
class Window;

class TestScreen : public gfx::Screen,
                   public WindowObserver {
 public:
  static TestScreen* Create();
  
  static TestScreen* CreateFullscreen();
  virtual ~TestScreen();

  RootWindow* CreateRootWindowForPrimaryDisplay();

  void SetDeviceScaleFactor(float device_scale_fator);
  void SetDisplayRotation(gfx::Display::Rotation rotation);
  void SetUIScale(float ui_scale);

 protected:
  gfx::Transform GetRotationTransform() const;
  gfx::Transform GetUIScaleTransform() const;

  
  virtual void OnWindowBoundsChanged(Window* window,
                                     const gfx::Rect& old_bounds,
                                     const gfx::Rect& new_bounds) OVERRIDE;
  virtual void OnWindowDestroying(Window* window) OVERRIDE;

  
  virtual bool IsDIPEnabled() OVERRIDE;
  virtual gfx::Point GetCursorScreenPoint() OVERRIDE;
  virtual gfx::NativeWindow GetWindowUnderCursor() OVERRIDE;
  virtual gfx::NativeWindow GetWindowAtScreenPoint(const gfx::Point& point)
      OVERRIDE;
  virtual int GetNumDisplays() const OVERRIDE;
  virtual std::vector<gfx::Display> GetAllDisplays() const OVERRIDE;
  virtual gfx::Display GetDisplayNearestWindow(
      gfx::NativeView view) const OVERRIDE;
  virtual gfx::Display GetDisplayNearestPoint(
      const gfx::Point& point) const OVERRIDE;
  virtual gfx::Display GetDisplayMatching(
      const gfx::Rect& match_rect) const OVERRIDE;
  virtual gfx::Display GetPrimaryDisplay() const OVERRIDE;
  virtual void AddObserver(gfx::DisplayObserver* observer) OVERRIDE;
  virtual void RemoveObserver(gfx::DisplayObserver* observer) OVERRIDE;

 private:
  explicit TestScreen(const gfx::Rect& screen_bounds);

  aura::RootWindow* root_window_;

  gfx::Display display_;

  float ui_scale_;

  DISALLOW_COPY_AND_ASSIGN(TestScreen);
};

}  

#endif  
