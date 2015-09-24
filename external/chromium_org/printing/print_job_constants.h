// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PRINTING_PRINT_JOB_CONSTANTS_H_
#define PRINTING_PRINT_JOB_CONSTANTS_H_

#include "build/build_config.h"
#include "printing/printing_export.h"

namespace printing {

PRINTING_EXPORT extern const char kIsFirstRequest[];
PRINTING_EXPORT extern const char kPreviewRequestID[];
PRINTING_EXPORT extern const char kPreviewUIID[];
PRINTING_EXPORT extern const char kSettingCloudPrintId[];
PRINTING_EXPORT extern const char kSettingCloudPrintDialog[];
PRINTING_EXPORT extern const char kSettingCollate[];
PRINTING_EXPORT extern const char kSettingColor[];
PRINTING_EXPORT extern const char kSettingSetColorAsDefault[];
PRINTING_EXPORT extern const char kSettingContentHeight[];
PRINTING_EXPORT extern const char kSettingContentWidth[];
PRINTING_EXPORT extern const char kSettingCopies[];
PRINTING_EXPORT extern const char kSettingDeviceName[];
PRINTING_EXPORT extern const char kSettingDuplexMode[];
PRINTING_EXPORT extern const char kSettingFitToPageEnabled[];
PRINTING_EXPORT extern const char kSettingGenerateDraftData[];
PRINTING_EXPORT extern const char kSettingHeaderFooterEnabled[];
PRINTING_EXPORT extern const float kSettingHeaderFooterInterstice;
PRINTING_EXPORT extern const char kSettingHeaderFooterDate[];
PRINTING_EXPORT extern const char kSettingHeaderFooterTitle[];
PRINTING_EXPORT extern const char kSettingHeaderFooterURL[];
PRINTING_EXPORT extern const char kSettingLandscape[];
PRINTING_EXPORT extern const char kSettingMarginBottom[];
PRINTING_EXPORT extern const char kSettingMarginLeft[];
PRINTING_EXPORT extern const char kSettingMarginRight[];
PRINTING_EXPORT extern const char kSettingMarginTop[];
PRINTING_EXPORT extern const char kSettingMarginsCustom[];
PRINTING_EXPORT extern const char kSettingMarginsType[];
PRINTING_EXPORT extern const char kSettingPreviewPageCount[];
PRINTING_EXPORT extern const char kSettingPageRange[];
PRINTING_EXPORT extern const char kSettingPageRangeFrom[];
PRINTING_EXPORT extern const char kSettingPageRangeTo[];
PRINTING_EXPORT extern const char kSettingPageWidth[];
PRINTING_EXPORT extern const char kSettingPageHeight[];
PRINTING_EXPORT extern const char kSettingPreviewModifiable[];
PRINTING_EXPORT extern const char kSettingPrintableAreaX[];
PRINTING_EXPORT extern const char kSettingPrintableAreaY[];
PRINTING_EXPORT extern const char kSettingPrintableAreaWidth[];
PRINTING_EXPORT extern const char kSettingPrintableAreaHeight[];
PRINTING_EXPORT extern const char kSettingPrinterName[];
PRINTING_EXPORT extern const char kSettingPrintToPDF[];
PRINTING_EXPORT extern const char kSettingPrintWithPrivet[];
PRINTING_EXPORT extern const char kSettingTicket[];
PRINTING_EXPORT extern const char kSettingShouldPrintBackgrounds[];
PRINTING_EXPORT extern const char kSettingShouldPrintSelectionOnly[];

PRINTING_EXPORT extern const int FIRST_PAGE_INDEX;
PRINTING_EXPORT extern const int COMPLETE_PREVIEW_DOCUMENT_INDEX;
PRINTING_EXPORT extern const char kSettingOpenPDFInPreview[];

#if defined (USE_CUPS)
PRINTING_EXPORT extern const char kBlack[];
PRINTING_EXPORT extern const char kCMYK[];
PRINTING_EXPORT extern const char kKCMY[];
PRINTING_EXPORT extern const char kCMY_K[];
PRINTING_EXPORT extern const char kCMY[];
PRINTING_EXPORT extern const char kColor[];
PRINTING_EXPORT extern const char kGray[];
PRINTING_EXPORT extern const char kGrayscale[];
PRINTING_EXPORT extern const char kGreyscale[];
PRINTING_EXPORT extern const char kMonochrome[];
PRINTING_EXPORT extern const char kNormal[];
PRINTING_EXPORT extern const char kNormalGray[];
PRINTING_EXPORT extern const char kRGB[];
PRINTING_EXPORT extern const char kRGBA[];
PRINTING_EXPORT extern const char kRGB16[];
#endif

enum DuplexMode {
  UNKNOWN_DUPLEX_MODE = -1,
  SIMPLEX,
  LONG_EDGE,
  SHORT_EDGE,
};

enum HorizontalHeaderFooterPosition {
  LEFT,
  CENTER,
  RIGHT
};

enum VerticalHeaderFooterPosition {
  TOP,
  BOTTOM
};

enum ColorModel {
  UNKNOWN_COLOR_MODEL,
  GRAY,
  COLOR,
  CMYK,
  CMY,
  KCMY,
  CMY_K,  
  BLACK,
  GRAYSCALE,
  RGB,
  RGB16,
  RGBA,
  COLORMODE_COLOR,  
  COLORMODE_MONOCHROME,  
  HP_COLOR_COLOR,  
  HP_COLOR_BLACK,  
  PRINTOUTMODE_NORMAL,  
  PRINTOUTMODE_NORMAL_GRAY,  
  PROCESSCOLORMODEL_CMYK,  
  PROCESSCOLORMODEL_GREYSCALE,  
  PROCESSCOLORMODEL_RGB,  
};

enum MarginType {
  DEFAULT_MARGINS,  
  NO_MARGINS,
  PRINTABLE_AREA_MARGINS,
  CUSTOM_MARGINS,
};

}  

#endif  
