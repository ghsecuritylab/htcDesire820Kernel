// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_IME_COMPOSITION_TEXT_UTIL_PANGO_H_
#define UI_BASE_IME_COMPOSITION_TEXT_UTIL_PANGO_H_

#include "ui/base/glib/glib_integers.h"
#include "ui/base/ui_export.h"

typedef struct _PangoAttrList PangoAttrList;

namespace ui {

struct CompositionText;

UI_EXPORT void ExtractCompositionTextFromGtkPreedit(
    const gchar* utf8_text,
    PangoAttrList* attrs,
    int cursor_position,
    CompositionText* composition);

}  

#endif  