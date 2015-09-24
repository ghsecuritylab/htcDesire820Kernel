/* ***** BEGIN LICENSE BLOCK *****
 * Version: MPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Mozilla Public License Version
 * 1.1 (the "License"); you may not use this file except in compliance with
 * the License. You may obtain a copy of the License at
 * http://www.mozilla.org/MPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is
 * mozilla.org.
 * Portions created by the Initial Developer are Copyright (C) 2004
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *   Johnny Stenback <jst@mozilla.org> (Original author)
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the MPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the MPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#ifndef nptypes_h_
#define nptypes_h_


#if defined(WIN32) || defined(OS2)
  typedef short int16_t;
  typedef unsigned short uint16_t;
  typedef int int32_t;
  typedef unsigned int uint32_t;
  typedef long long int64_t;
  typedef unsigned long long uint64_t;
#elif defined(_AIX) || defined(__sun) || defined(__osf__) || defined(IRIX) || defined(HPUX)
  #include <inttypes.h>

  #ifndef __cplusplus
    typedef int bool;
    #define true   1
    #define false  0
  #endif
#elif defined(bsdi) || defined(FREEBSD) || defined(OPENBSD)
  #include <sys/types.h>

  #if defined(bsdi)
  typedef u_int32_t uint32_t;
  typedef u_int64_t uint64_t;

  #if !defined(__cplusplus)
    typedef int bool;
    #define true   1
    #define false  0
  #endif
  #else
    #include <inttypes.h>
    #include <stdbool.h>
  #endif
#elif defined(BEOS)
  #include <inttypes.h>
#else
  #include <stdint.h>

  #ifndef __cplusplus
    #if !defined(__GNUC__) || (__GNUC__ > 2 || __GNUC_MINOR__ > 95)
      #include <stdbool.h>
    #else
      #define bool int
      #define true   1
      #define false  0
    #endif
  #endif
#endif

#endif 
