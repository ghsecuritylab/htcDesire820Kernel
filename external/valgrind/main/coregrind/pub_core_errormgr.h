

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

#ifndef __PUB_CORE_ERRORMGR_H
#define __PUB_CORE_ERRORMGR_H


#include "pub_tool_errormgr.h"

typedef
   enum { 
      
      
      
      ThreadErr = -1,
   }
   CoreErrorKind;

extern void VG_(load_suppressions)        ( void );

extern void VG_(show_all_errors)          ( Int verbosity, Bool xml );

extern void VG_(show_last_error)          ( void );

extern void VG_(show_error_counts_as_XML) ( void );

extern Bool VG_(is_action_requested)      ( Char* action, Bool* clo );

extern Bool VG_(showing_core_errors)      ( void );

extern UInt VG_(get_n_errs_found)         ( void );
extern UInt VG_(get_n_errs_shown)         ( void );

extern void VG_(print_errormgr_stats)     ( void );

#endif   

