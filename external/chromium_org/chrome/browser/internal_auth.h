// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_INTERNAL_AUTH_H_
#define CHROME_BROWSER_INTERNAL_AUTH_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"

namespace chrome {

class InternalAuthVerification {
 public:
  
  static bool VerifyPassport(
      const std::string& passport,
      const std::string& domain,
      const std::map<std::string, std::string>& var_value_map);

 private:
  friend class InternalAuthGeneration;
  friend class InternalAuthVerificationService;
  friend class InternalAuthGenerationService;
  FRIEND_TEST_ALL_PREFIXES(InternalAuthTest, ExpirationAndBruteForce);

  
  
  
  static void ChangeKey(const std::string& key);

#ifdef UNIT_TEST
  static void set_verification_window_seconds(int seconds) {
    verification_window_seconds_ = seconds;
  }
#endif

  static int get_verification_window_ticks();

  static int verification_window_seconds_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(InternalAuthVerification);
};

class InternalAuthGeneration {
 private:
  FRIEND_TEST_ALL_PREFIXES(InternalAuthTest, BasicGeneration);
  FRIEND_TEST_ALL_PREFIXES(InternalAuthTest, DoubleGeneration);
  FRIEND_TEST_ALL_PREFIXES(InternalAuthTest, BadGeneration);
  FRIEND_TEST_ALL_PREFIXES(InternalAuthTest, BasicVerification);
  FRIEND_TEST_ALL_PREFIXES(InternalAuthTest, BruteForce);
  FRIEND_TEST_ALL_PREFIXES(InternalAuthTest, ExpirationAndBruteForce);
  FRIEND_TEST_ALL_PREFIXES(InternalAuthTest, ChangeKey);

  
  static std::string GeneratePassport(
      const std::string& domain,
      const std::map<std::string, std::string>& var_value_map);

  
  static void GenerateNewKey();
};

}  

#endif  