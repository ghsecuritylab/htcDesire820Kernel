/* Copyright (c) 2012 The Chromium Authors. All rights reserved.
 * Use of this source code is governed by a BSD-style license that can be
 * found in the LICENSE file.
 */


#ifndef PPAPI_C_PRIVATE_PPB_FLASH_CLIPBOARD_H_
#define PPAPI_C_PRIVATE_PPB_FLASH_CLIPBOARD_H_

#include "ppapi/c/pp_bool.h"
#include "ppapi/c/pp_instance.h"
#include "ppapi/c/pp_macros.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_var.h"

#define PPB_FLASH_CLIPBOARD_INTERFACE_4_0 "PPB_Flash_Clipboard;4.0"
#define PPB_FLASH_CLIPBOARD_INTERFACE_5_0 "PPB_Flash_Clipboard;5.0"
#define PPB_FLASH_CLIPBOARD_INTERFACE PPB_FLASH_CLIPBOARD_INTERFACE_5_0



typedef enum {
  
  PP_FLASH_CLIPBOARD_TYPE_STANDARD = 0,
  
  PP_FLASH_CLIPBOARD_TYPE_SELECTION = 1
} PP_Flash_Clipboard_Type;
PP_COMPILE_ASSERT_SIZE_IN_BYTES(PP_Flash_Clipboard_Type, 4);

typedef enum {
  
  PP_FLASH_CLIPBOARD_FORMAT_INVALID = 0,
  PP_FLASH_CLIPBOARD_FORMAT_PLAINTEXT = 1,
  PP_FLASH_CLIPBOARD_FORMAT_HTML = 2,
  PP_FLASH_CLIPBOARD_FORMAT_RTF = 3
} PP_Flash_Clipboard_Format;
PP_COMPILE_ASSERT_SIZE_IN_BYTES(PP_Flash_Clipboard_Format, 4);

struct PPB_Flash_Clipboard_5_0 {
  /**
   * Registers a custom clipboard format. The format is identified by a
   * string. An id identifying the format will be returned if the format is
   * successfully registered, which can be used to read/write data of that
   * format. If the format has already been registered, the id associated with
   * that format will be returned. If the format fails to be registered
   * <code>PP_FLASH_CLIPBOARD_FORMAT_INVALID</code> will be returned.
   *
   * All custom data should be read/written as <code>PP_Var</code> array
   * buffers. The clipboard format is pepper-specific meaning that although the
   * data will be stored on the system clipboard, it can only be accessed in a
   * sensible way by using the pepper API. Data stored in custom formats can
   * be safely shared between different applications that use pepper.
   */
  uint32_t (*RegisterCustomFormat)(PP_Instance instance_id,
                                   const char* format_name);
  PP_Bool (*IsFormatAvailable)(PP_Instance instance_id,
                               PP_Flash_Clipboard_Type clipboard_type,
                               uint32_t format);
  struct PP_Var (*ReadData)(PP_Instance instance_id,
                            PP_Flash_Clipboard_Type clipboard_type,
                            uint32_t format);
  /**
   * Writes the given array of data items to the clipboard. All existing
   * clipboard data in any format is erased before writing this data. Thus,
   * passing an array of size 0 has the effect of clearing the clipboard without
   * writing any data. Each data item in the array should have a different
   * <code>PP_Flash_Clipboard_Format</code>. If multiple data items have the
   * same format, only the last item with that format will be written.
   * If there is an error writing any of the items in the array to the
   * clipboard, none will be written and an error code is returned.
   * The error code will be <code>PP_ERROR_NOSPACE</code> if the value is
   * too large to be written, <code>PP_ERROR_BADARGUMENT</code> if a PP_Var
   * cannot be converted into the format supplied or <code>PP_FAILED</code>
   * if the format is not supported.
   */
  int32_t (*WriteData)(PP_Instance instance_id,
                       PP_Flash_Clipboard_Type clipboard_type,
                       uint32_t data_item_count,
                       const uint32_t formats[],
                       const struct PP_Var data_items[]);
};

typedef struct PPB_Flash_Clipboard_5_0 PPB_Flash_Clipboard;

struct PPB_Flash_Clipboard_4_0 {
  PP_Bool (*IsFormatAvailable)(PP_Instance instance_id,
                               PP_Flash_Clipboard_Type clipboard_type,
                               PP_Flash_Clipboard_Format format);
  struct PP_Var (*ReadData)(PP_Instance instance_id,
                            PP_Flash_Clipboard_Type clipboard_type,
                            PP_Flash_Clipboard_Format format);
  int32_t (*WriteData)(PP_Instance instance_id,
                       PP_Flash_Clipboard_Type clipboard_type,
                       uint32_t data_item_count,
                       const PP_Flash_Clipboard_Format formats[],
                       const struct PP_Var data_items[]);
};

#endif  
