// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_SUGGESTIONS_INTERNALS_SUGGESTIONS_INTERNALS_UI_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_SUGGESTIONS_INTERNALS_SUGGESTIONS_INTERNALS_UI_HANDLER_H_

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/ui/webui/ntp/suggestions_combiner.h"
#include "content/public/browser/web_ui_message_handler.h"

class Profile;

namespace base {
class ListValue;
}

class SuggestionsInternalsUIHandler : public content::WebUIMessageHandler,
                                      public SuggestionsCombiner::Delegate {
 public:
  explicit SuggestionsInternalsUIHandler(Profile* profile);
  virtual ~SuggestionsInternalsUIHandler();

  
  virtual void OnSuggestionsReady() OVERRIDE;

 protected:
  
  
  virtual void RegisterMessages() OVERRIDE;

  void HandleGetSuggestions(const base::ListValue* one_element_input_string);

  
  scoped_ptr<SuggestionsCombiner> suggestions_combiner_;

  Profile* profile_;

  DISALLOW_COPY_AND_ASSIGN(SuggestionsInternalsUIHandler);
};

#endif  
