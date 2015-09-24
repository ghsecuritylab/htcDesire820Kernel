// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_GESTURES_LONG_PRESS_AFFORDANCE_HANDLER_H_
#define ASH_WM_GESTURES_LONG_PRESS_AFFORDANCE_HANDLER_H_

#include "base/timer/timer.h"
#include "ui/aura/window_observer.h"
#include "ui/gfx/animation/linear_animation.h"
#include "ui/gfx/point.h"

namespace ui {
class GestureEvent;
}

namespace ash {

namespace test {
class SystemGestureEventFilterTest;
}

namespace internal {

class LongPressAffordanceHandler : public gfx::LinearAnimation,
                                   public aura::WindowObserver {
 public:
  LongPressAffordanceHandler();
  virtual ~LongPressAffordanceHandler();

  
  void ProcessEvent(aura::Window* target, ui::GestureEvent* event);

 private:
  friend class ash::test::SystemGestureEventFilterTest;

  class LongPressAffordanceView;

  enum LongPressAnimationType {
    NONE,
    GROW_ANIMATION,
    SHRINK_ANIMATION,
  };

  void StartAnimation();
  void StopAffordance();
  void SetTapDownTarget(aura::Window* target);

  
  virtual void AnimateToState(double state) OVERRIDE;
  virtual void AnimationStopped() OVERRIDE;

  
  virtual void OnWindowDestroying(aura::Window* window) OVERRIDE;

  scoped_ptr<LongPressAffordanceView> view_;
  gfx::Point tap_down_location_;
  base::OneShotTimer<LongPressAffordanceHandler> timer_;
  aura::Window* tap_down_target_;
  LongPressAnimationType current_animation_type_;

  DISALLOW_COPY_AND_ASSIGN(LongPressAffordanceHandler);
};

}  
}  

#endif  