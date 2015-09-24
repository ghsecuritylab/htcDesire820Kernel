

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

#ifndef __PUB_TOOL_LIBCPROC_H
#define __PUB_TOOL_LIBCPROC_H


extern Char** VG_(client_envp);

extern Char* VG_(getenv) ( Char* name );

extern const Char *VG_(libdir);

extern const Char* VG_(LD_PRELOAD_var_name);


extern Int  VG_(waitpid)( Int pid, Int *status, Int options );
extern Int  VG_(system) ( Char* cmd );
extern Int  VG_(fork)   ( void);
extern void VG_(execv)  ( Char* filename, Char** argv );


extern Int VG_(getrlimit) ( Int resource, struct vki_rlimit *rlim );
extern Int VG_(setrlimit) ( Int resource, const struct vki_rlimit *rlim );
extern Int VG_(prctl) (Int option, 
                       ULong arg2, ULong arg3, ULong arg4, ULong arg5);


extern Int VG_(gettid)  ( void );
extern Int VG_(getpid)  ( void );
extern Int VG_(getppid) ( void );
extern Int VG_(getpgrp) ( void );
extern Int VG_(geteuid) ( void );
extern Int VG_(getegid) ( void );


extern UInt VG_(read_millisecond_timer) ( void );


typedef void (*vg_atfork_t)(ThreadId);
extern void VG_(atfork)(vg_atfork_t pre, vg_atfork_t parent, vg_atfork_t child);


#endif   

