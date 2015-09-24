/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */


#include "nss.h"

#if defined(DEBUG)
#define _DEBUG_STRING " (debug)"
#else
#define _DEBUG_STRING ""
#endif

const char __nss_ssl_rcsid[] = "$Header: NSS " NSS_VERSION _DEBUG_STRING
        "  " __DATE__ " " __TIME__ " $";
const char __nss_ssl_sccsid[] = "@(#)NSS " NSS_VERSION _DEBUG_STRING
        "  " __DATE__ " " __TIME__;
