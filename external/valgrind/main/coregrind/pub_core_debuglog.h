

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2000-2012 Julian Seward
      jseward@acm.org

   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
   02111-1307, USA.

   The GNU General Public License is contained in the file COPYING.
*/

#ifndef __PUB_CORE_DEBUGLOG_H
#define __PUB_CORE_DEBUGLOG_H


#include <stdarg.h>

#include "pub_tool_basics.h"  



extern 
void VG_(debugLog_startup) ( Int level, HChar* who );


extern void VG_(debugLog_setXml)(Bool xml);


extern
Int VG_(debugLog_getLevel) ( void );


extern
void VG_(debugLog) ( Int level, const HChar* modulename,
                                const HChar* format, ... )
     __attribute__((format(__printf__, 3, 4)));


extern
UInt VG_(debugLog_vprintf) ( 
        void (*send_fn)(HChar,void*),
        void* send_arg2,             
        const HChar *format, 
        va_list vargs
     );


#endif   

