// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_PASSWORDS_MANAGE_PASSWORDS_BUBBLE_MODEL_H_
#define CHROME_BROWSER_UI_PASSWORDS_MANAGE_PASSWORDS_BUBBLE_MODEL_H_

#include "components/autofill/core/common/password_form.h"
#include "content/public/browser/web_contents_observer.h"

class ManagePasswordsIconController;

namespace content {
class WebContents;
}

class ManagePasswordsBubbleModel : public content::WebContentsObserver {
 public:
  explicit ManagePasswordsBubbleModel(content::WebContents* web_contents);
  virtual ~ManagePasswordsBubbleModel();

  enum ManagePasswordsBubbleState {
    PASSWORD_TO_BE_SAVED,
    MANAGE_PASSWORDS_AFTER_SAVING,
    MANAGE_PASSWORDS
  };

  
  void OnCancelClicked();

  
  void OnSaveClicked();

  
  void OnManageLinkClicked();

  
  
  void OnPasswordAction(autofill::PasswordForm password_form, bool remove);

  
  
  
  
  void DeleteFromBestMatches(autofill::PasswordForm password_form);

  ManagePasswordsBubbleState manage_passwords_bubble_state() {
    return manage_passwords_bubble_state_;
  }

  bool password_submitted() { return password_submitted_; }
  const base::string16& title() { return title_; }
  const autofill::PasswordForm& pending_credentials() {
    return pending_credentials_;
  }
  const autofill::PasswordFormMap& best_matches() { return best_matches_; }
  const base::string16& manage_link() { return manage_link_; }

 private:
  
  virtual void WebContentsDestroyed(
      content::WebContents* web_contents) OVERRIDE;

  content::WebContents* web_contents_;
  ManagePasswordsBubbleState manage_passwords_bubble_state_;
  bool password_submitted_;
  base::string16 title_;
  autofill::PasswordForm pending_credentials_;
  autofill::PasswordFormMap best_matches_;
  base::string16 manage_link_;

  DISALLOW_COPY_AND_ASSIGN(ManagePasswordsBubbleModel);
};

#endif  