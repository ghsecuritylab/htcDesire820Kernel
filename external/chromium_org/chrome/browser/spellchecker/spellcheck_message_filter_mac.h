// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SPELLCHECKER_SPELLCHECK_MESSAGE_FILTER_MAC_H_
#define CHROME_BROWSER_SPELLCHECKER_SPELLCHECK_MESSAGE_FILTER_MAC_H_

#include <map>

#include "chrome/browser/spellchecker/spellcheck_message_filter.h"
#include "chrome/common/spellcheck_result.h"
#include "content/public/browser/browser_message_filter.h"

class SpellCheckMessageFilterMac : public content::BrowserMessageFilter {
 public:
  explicit SpellCheckMessageFilterMac(int render_process_id);

  
  virtual void OverrideThreadForMessage(
      const IPC::Message& message,
      content::BrowserThread::ID* thread) OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message,
                                 bool* message_was_ok) OVERRIDE;

  
  
  
  static void CombineResults(
      std::vector<SpellCheckResult>* remote_results,
      const std::vector<SpellCheckResult>& local_results);

 private:
  friend class TestingSpellCheckMessageFilter;
  friend class SpellcheckMessageFilterMacTest;

  virtual ~SpellCheckMessageFilterMac();

  void OnCheckSpelling(const base::string16& word, int route_id, bool* correct);
  void OnFillSuggestionList(const base::string16& word,
                            std::vector<base::string16>* suggestions);
  void OnShowSpellingPanel(bool show);
  void OnUpdateSpellingPanelWithMisspelledWord(const base::string16& word);
  void OnRequestTextCheck(int route_id,
                          int identifier,
                          const base::string16& text,
                          std::vector<SpellCheckMarker> markers);

  int ToDocumentTag(int route_id);
  void RetireDocumentTag(int route_id);
  std::map<int,int> tag_map_;

  int render_process_id_;

  
  scoped_ptr<SpellingServiceClient> client_;

  DISALLOW_COPY_AND_ASSIGN(SpellCheckMessageFilterMac);
};

#endif  