// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_AUTOCOMPLETE_AUTOCOMPLETE_POPUP_WIN_H_
#define CHROME_BROWSER_UI_VIEWS_AUTOCOMPLETE_AUTOCOMPLETE_POPUP_WIN_H_
#pragma once

#include "base/memory/weak_ptr.h"
#include "views/widget/widget_win.h"

class AutocompletePopupWin
    : public views::WidgetWin,
      public base::SupportsWeakPtr<AutocompletePopupWin> {
 public:
  
  AutocompletePopupWin();
  virtual ~AutocompletePopupWin();

  
  
  gfx::NativeView GetRelativeWindowForPopup(
      gfx::NativeView edit_native_view) const;

 private:
  DISALLOW_COPY_AND_ASSIGN(AutocompletePopupWin);
};

#endif  
