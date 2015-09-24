// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CORE_BROWSER_TEST_AUTOFILL_EXTERNAL_DELEGATE_H_
#define COMPONENTS_AUTOFILL_CORE_BROWSER_TEST_AUTOFILL_EXTERNAL_DELEGATE_H_

#include "components/autofill/core/browser/autofill_external_delegate.h"

namespace autofill {

class AutofillManager;

void GenerateTestAutofillPopup(
    AutofillExternalDelegate* autofill_external_delegate);

}  

#endif  