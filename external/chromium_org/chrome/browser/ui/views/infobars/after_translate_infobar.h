// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_VIEWS_INFOBARS_AFTER_TRANSLATE_INFOBAR_H_
#define CHROME_BROWSER_UI_VIEWS_INFOBARS_AFTER_TRANSLATE_INFOBAR_H_

#include "chrome/browser/ui/views/infobars/translate_infobar_base.h"
#include "ui/views/controls/button/menu_button_listener.h"

class OptionsMenuModel;
class TranslateInfoBarDelegate;
class TranslateLanguageMenuModel;

namespace views {
class MenuButton;
}

class AfterTranslateInfoBar : public TranslateInfoBarBase,
                              public views::MenuButtonListener {
 public:
  explicit AfterTranslateInfoBar(scoped_ptr<TranslateInfoBarDelegate> delegate);

 private:
  virtual ~AfterTranslateInfoBar();

  
  virtual void Layout() OVERRIDE;
  virtual void ViewHierarchyChanged(
      const ViewHierarchyChangedDetails& details) OVERRIDE;
  virtual void ButtonPressed(views::Button* sender,
                             const ui::Event& event) OVERRIDE;
  virtual int ContentMinimumWidth() const OVERRIDE;

  
  virtual void OnMenuButtonClicked(views::View* source,
                                   const gfx::Point& point) OVERRIDE;

  
  
  
  void GetButtons(views::MenuButton** first_button,
                  views::MenuButton** second_button) const;

  
  
  
  
  views::Label* label_1_;
  views::Label* label_2_;
  views::Label* label_3_;

  views::MenuButton* original_language_menu_button_;
  views::MenuButton* target_language_menu_button_;
  views::LabelButton* revert_button_;
  views::MenuButton* options_menu_button_;

  scoped_ptr<TranslateLanguageMenuModel> original_language_menu_model_;
  scoped_ptr<TranslateLanguageMenuModel> target_language_menu_model_;
  scoped_ptr<OptionsMenuModel> options_menu_model_;

  
  bool swapped_language_buttons_;

  
  bool autodetermined_source_language_;

  DISALLOW_COPY_AND_ASSIGN(AfterTranslateInfoBar);
};

#endif  
