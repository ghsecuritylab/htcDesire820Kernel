// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_COCOA_PANELS_PANEL_COCOA_H_
#define CHROME_BROWSER_UI_COCOA_PANELS_PANEL_COCOA_H_

#import <Foundation/Foundation.h>
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/ui/panels/native_panel.h"
#include "ui/gfx/rect.h"

class Panel;
@class PanelWindowControllerCocoa;

class PanelCocoa : public NativePanel {
 public:
  PanelCocoa(Panel* panel, const gfx::Rect& bounds, bool always_on_top);
  virtual ~PanelCocoa();

  
  virtual void ShowPanel() OVERRIDE;
  virtual void ShowPanelInactive() OVERRIDE;
  virtual gfx::Rect GetPanelBounds() const OVERRIDE;
  virtual void SetPanelBounds(const gfx::Rect& bounds) OVERRIDE;
  virtual void SetPanelBoundsInstantly(const gfx::Rect& bounds) OVERRIDE;
  virtual void ClosePanel() OVERRIDE;
  virtual void ActivatePanel() OVERRIDE;
  virtual void DeactivatePanel() OVERRIDE;
  virtual bool IsPanelActive() const OVERRIDE;
  virtual void PreventActivationByOS(bool prevent_activation) OVERRIDE;
  virtual gfx::NativeWindow GetNativePanelWindow() OVERRIDE;
  virtual void UpdatePanelTitleBar() OVERRIDE;
  virtual void UpdatePanelLoadingAnimations(bool should_animate) OVERRIDE;
  virtual void PanelWebContentsFocused(content::WebContents* contents) OVERRIDE;
  virtual void PanelCut() OVERRIDE;
  virtual void PanelCopy() OVERRIDE;
  virtual void PanelPaste() OVERRIDE;
  virtual void DrawAttention(bool draw_attention) OVERRIDE;
  virtual bool IsDrawingAttention() const OVERRIDE;
  virtual void HandlePanelKeyboardEvent(
      const content::NativeWebKeyboardEvent& event) OVERRIDE;
  virtual void FullScreenModeChanged(bool is_full_screen) OVERRIDE;
  virtual bool IsPanelAlwaysOnTop() const OVERRIDE;
  virtual void SetPanelAlwaysOnTop(bool on_top) OVERRIDE;
  virtual void UpdatePanelMinimizeRestoreButtonVisibility() OVERRIDE;
  virtual void SetWindowCornerStyle(panel::CornerStyle corner_style) OVERRIDE;
  virtual void PanelExpansionStateChanging(
      Panel::ExpansionState old_state,
      Panel::ExpansionState new_state) OVERRIDE;
  virtual void AttachWebContents(content::WebContents* contents) OVERRIDE;
  virtual void DetachWebContents(content::WebContents* contents) OVERRIDE;

  
  virtual gfx::Size WindowSizeFromContentSize(
      const gfx::Size& content_size) const OVERRIDE;
  virtual gfx::Size ContentSizeFromWindowSize(
      const gfx::Size& window_size) const OVERRIDE;
  virtual int TitleOnlyHeight() const OVERRIDE;

  virtual void MinimizePanelBySystem() OVERRIDE;
  virtual bool IsPanelMinimizedBySystem() const OVERRIDE;
  virtual bool IsPanelShownOnActiveDesktop() const OVERRIDE;
  virtual void ShowShadow(bool show) OVERRIDE;
  virtual NativePanelTesting* CreateNativePanelTesting() OVERRIDE;

  Panel* panel() const;
  void DidCloseNativeWindow();

  bool IsClosed() const;

  
  
  void set_cached_bounds_directly(const gfx::Rect& bounds) { bounds_ = bounds; }

 private:
  friend class CocoaNativePanelTesting;
  friend class PanelCocoaTest;
  FRIEND_TEST_ALL_PREFIXES(PanelCocoaTest, CreateClose);
  FRIEND_TEST_ALL_PREFIXES(PanelCocoaTest, NativeBounds);
  FRIEND_TEST_ALL_PREFIXES(PanelCocoaTest, TitlebarViewCreate);
  FRIEND_TEST_ALL_PREFIXES(PanelCocoaTest, TitlebarViewSizing);
  FRIEND_TEST_ALL_PREFIXES(PanelCocoaTest, TitlebarViewClose);
  FRIEND_TEST_ALL_PREFIXES(PanelCocoaTest, MenuItems);
  FRIEND_TEST_ALL_PREFIXES(PanelCocoaTest, KeyEvent);
  FRIEND_TEST_ALL_PREFIXES(PanelCocoaTest, ThemeProvider);
  FRIEND_TEST_ALL_PREFIXES(PanelCocoaTest, SetTitle);
  FRIEND_TEST_ALL_PREFIXES(PanelCocoaTest, ActivatePanel);

  void setBoundsInternal(const gfx::Rect& bounds, bool animate);

  scoped_ptr<Panel> panel_;
  PanelWindowControllerCocoa* controller_;  

  
  
  
  gfx::Rect bounds_;

  
  bool always_on_top_;

  bool is_shown_;  
  NSInteger attention_request_id_;  

  
  panel::CornerStyle corner_style_;

  DISALLOW_COPY_AND_ASSIGN(PanelCocoa);
};

#endif  
