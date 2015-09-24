

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2008-2012 OpenWorks Ltd
      info@open-works.co.uk

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

#ifndef __PUB_TOOL_SPARSEWA_H
#define __PUB_TOOL_SPARSEWA_H




typedef  struct _SparseWA  SparseWA; 

SparseWA* VG_(newSWA) ( void*(*alloc_nofail)(HChar* cc, SizeT), 
                        HChar* cc,
                        void(*dealloc)(void*) );

void VG_(deleteSWA) ( SparseWA* swa );

// overwritten.  Returned Bool is True iff a previous binding existed.
Bool VG_(addToSWA) ( SparseWA* swa, UWord key, UWord val );

Bool VG_(delFromSWA) ( SparseWA* swa,
                       UWord* oldK, UWord* oldV,
                       UWord key );

Bool VG_(lookupSWA) ( SparseWA* swa,
                      UWord* keyP, UWord* valP,
                      UWord key );

void VG_(initIterSWA) ( SparseWA* swa );

Bool VG_(nextIterSWA)( SparseWA* swa,
                       UWord* keyP, UWord* valP );

UWord VG_(sizeSWA) ( SparseWA* swa );

#endif   

