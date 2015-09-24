// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_GTK_AUTOFILL_AUTOFILL_POPUP_VIEW_GTK_H_
#define CHROME_BROWSER_UI_GTK_AUTOFILL_AUTOFILL_POPUP_VIEW_GTK_H_

#include <pango/pango.h>
#include <vector>

#include "base/compiler_specific.h"
#include "base/strings/string16.h"
#include "chrome/browser/ui/autofill/autofill_popup_view.h"
#include "ui/base/glib/glib_integers.h"
#include "ui/base/gtk/gtk_signal.h"
#include "ui/base/gtk/gtk_signal_registrar.h"
#include "ui/gfx/font.h"

class Profile;

namespace content {
class RenderViewHost;
}

namespace gfx {
class Rect;
}

typedef struct _GdkEventButton GdkEventButton;
typedef struct _GdkEventConfigure GdkEventConfigure;
typedef struct _GdkEventCrossing GdkEventCrossing;
typedef struct _GdkEventExpose GdkEventExpose;
typedef struct _GdkEventKey GdkEventKey;
typedef struct _GdkEventMotion GdkEventMotion;
typedef struct _GdkColor GdkColor;
typedef struct _GtkWidget GtkWidget;

namespace autofill {

class AutofillPopupController;

class AutofillPopupViewGtk : public AutofillPopupView {
 public:
  explicit AutofillPopupViewGtk(AutofillPopupController* controller);

 private:
  virtual ~AutofillPopupViewGtk();

  
  virtual void Hide() OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual void InvalidateRow(size_t row) OVERRIDE;
  virtual void UpdateBoundsAndRedrawPopup() OVERRIDE;

  CHROMEGTK_CALLBACK_1(AutofillPopupViewGtk, gboolean, HandleConfigure,
                       GdkEventConfigure*);
  CHROMEGTK_CALLBACK_1(AutofillPopupViewGtk, gboolean, HandleButtonRelease,
                       GdkEventButton*);
  CHROMEGTK_CALLBACK_1(AutofillPopupViewGtk, gboolean, HandleExpose,
                       GdkEventExpose*);
  CHROMEGTK_CALLBACK_1(AutofillPopupViewGtk, gboolean, HandleLeave,
                       GdkEventCrossing*)
  CHROMEGTK_CALLBACK_1(AutofillPopupViewGtk, gboolean, HandleMotion,
                       GdkEventMotion*);

  
  void SetUpLayout();

  
  
  void SetLayoutText(const base::string16& text,
                     const gfx::Font& font,
                     const GdkColor text_color);

  
  void DrawSeparator(cairo_t* cairo_context, const gfx::Rect& separator_rect);

  
  void DrawAutofillEntry(cairo_t* cairo_context,
                         size_t index,
                         const gfx::Rect& entry_rect);

  
  
  void SetInitialBounds();

  AutofillPopupController* controller_;  

  ui::GtkSignalRegistrar signals_;

  GtkWidget* window_;  
  PangoLayout* layout_;  

  DISALLOW_COPY_AND_ASSIGN(AutofillPopupViewGtk);
};

}  

#endif  