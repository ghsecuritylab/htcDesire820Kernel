// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_IME_INPUT_METHOD_IMM32_H_
#define UI_BASE_IME_INPUT_METHOD_IMM32_H_

#include <windows.h>

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "ui/base/ime/input_method_win.h"

namespace ui {

class UI_EXPORT InputMethodIMM32 : public InputMethodWin {
 public:
  InputMethodIMM32(internal::InputMethodDelegate* delegate,
                   HWND toplevel_window_handle);

  
  virtual void OnFocus() OVERRIDE;
  virtual void OnBlur() OVERRIDE;
  virtual bool OnUntranslatedIMEMessage(const base::NativeEvent& event,
                                        NativeEventResult* result) OVERRIDE;
  virtual void OnTextInputTypeChanged(const TextInputClient* client) OVERRIDE;
  virtual void OnCaretBoundsChanged(const TextInputClient* client) OVERRIDE;
  virtual void CancelComposition(const TextInputClient* client) OVERRIDE;
  virtual bool IsCandidatePopupOpen() const OVERRIDE;

 protected:
  
  virtual void OnWillChangeFocusedClient(TextInputClient* focused_before,
                                         TextInputClient* focused) OVERRIDE;
  virtual void OnDidChangeFocusedClient(TextInputClient* focused_before,
                                        TextInputClient* focused) OVERRIDE;

 private:
  LRESULT OnImeSetContext(HWND window_handle,
                          UINT message,
                          WPARAM wparam,
                          LPARAM lparam,
                          BOOL* handled);
  LRESULT OnImeStartComposition(HWND window_handle,
                                UINT message,
                                WPARAM wparam,
                                LPARAM lparam,
                                BOOL* handled);
  LRESULT OnImeComposition(HWND window_handle,
                           UINT message,
                           WPARAM wparam,
                           LPARAM lparam,
                           BOOL* handled);
  LRESULT OnImeEndComposition(HWND window_handle,
                              UINT message,
                              WPARAM wparam,
                              LPARAM lparam,
                              BOOL* handled);
  LRESULT OnImeNotify(UINT message,
                      WPARAM wparam,
                      LPARAM lparam,
                      BOOL* handled);

  
  void ConfirmCompositionText();

  
  void UpdateIMEState();

  bool enabled_;

  
  bool is_candidate_popup_open_;

  
  
  HWND composing_window_handle_;

  DISALLOW_COPY_AND_ASSIGN(InputMethodIMM32);
};

}  

#endif  
