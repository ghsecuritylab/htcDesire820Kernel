

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

#include "pub_core_basics.h"
#include "pub_core_demangle.h"
#include "pub_core_libcassert.h"
#include "pub_core_libcbase.h"
#include "pub_core_libcprint.h"
#include "pub_core_mallocfree.h"
#include "pub_core_options.h"

#include "vg_libciface.h"
#include "demangle.h"


/* Note that the C++ demangler is from GNU libiberty and is almost
   completely unmodified.  We use vg_libciface.h as a way to
   impedance-match the libiberty code into our own framework.

   The current code is from libiberty in the gcc tree, gcc svn
   r181975, dated 12 Dec 2011 (when the gcc trunk was in Stage 3
   leading up to a gcc-4.7 release).  As of r141363, libiberty is LGPL
   2.1, which AFAICT is compatible with "GPL 2 or later" and so is OK
   for inclusion in Valgrind.

   To update to a newer libiberty, it might be simplest to svn diff
   the gcc tree libibery against r181975 and then apply those diffs
   here. */


void VG_(demangle) ( Bool do_cxx_demangling, Bool do_z_demangling,
                     Char* orig, Char* result, Int result_size )
{
#  define N_ZBUF 4096
   HChar* demangled = NULL;
   HChar z_demangled[N_ZBUF];

   
   if (do_z_demangling) {
      if (VG_(maybe_Z_demangle)( orig, NULL,0,
                                 z_demangled, N_ZBUF, NULL, NULL, NULL )) {
         orig = z_demangled;
      }
   }

   
   if (do_cxx_demangling && VG_(clo_demangle)) {
      demangled = ML_(cplus_demangle) ( orig, DMGL_ANSI | DMGL_PARAMS );
   } else {
      demangled = NULL;
   }
   if (demangled) {
      VG_(strncpy_safely)(result, demangled, result_size);
      VG_(arena_free) (VG_AR_DEMANGLE, demangled);
   } else {
      VG_(strncpy_safely)(result, orig, result_size);
   }

   
   
   
   
   
#  undef N_ZBUF
}




Bool VG_(maybe_Z_demangle) ( const HChar* sym, 
                             HChar* so, Int soLen,
                             HChar* fn, Int fnLen,
                             Bool* isWrap,
                             Int*  eclassTag,
                             Int*  eclassPrio )
{
#  define EMITSO(ch)                           \
      do {                                     \
         if (so) {                             \
            if (soi >= soLen) {                \
               so[soLen-1] = 0; oflow = True;  \
            } else {                           \
               so[soi++] = ch; so[soi] = 0;    \
            }                                  \
         }                                     \
      } while (0)
#  define EMITFN(ch)                           \
      do {                                     \
         if (fni >= fnLen) {                   \
            fn[fnLen-1] = 0; oflow = True;     \
         } else {                              \
            fn[fni++] = ch; fn[fni] = 0;       \
         }                                     \
      } while (0)

   Bool error, oflow, valid, fn_is_encoded, is_VG_Z_prefixed;
   Int  soi, fni, i;

   vg_assert(soLen > 0 || (soLen == 0 && so == NULL));
   vg_assert(fnLen > 0);
   error = False;
   oflow = False;
   soi = 0;
   fni = 0;

   valid =     sym[0] == '_'
           &&  sym[1] == 'v'
           &&  sym[2] == 'g'
           && (sym[3] == 'r' || sym[3] == 'w')
           &&  VG_(isdigit)(sym[4])
           &&  VG_(isdigit)(sym[5])
           &&  VG_(isdigit)(sym[6])
           &&  VG_(isdigit)(sym[7])
           &&  VG_(isdigit)(sym[8])
           &&  sym[9] == 'Z'
           && (sym[10] == 'Z' || sym[10] == 'U')
           &&  sym[11] == '_';

   if (valid
       && sym[4] == '0' && sym[5] == '0' && sym[6] == '0' && sym[7] == '0'
       && sym[8] != '0') {
      valid = False;
   }

   if (!valid)
      return False;

   fn_is_encoded = sym[10] == 'Z';

   if (isWrap)
      *isWrap = sym[3] == 'w';

   if (eclassTag) {
      *eclassTag =    1000 * ((Int)sym[4] - '0')
                   +  100 * ((Int)sym[5] - '0')
                   +  10 * ((Int)sym[6] - '0')
                   +  1 * ((Int)sym[7] - '0');
      vg_assert(*eclassTag >= 0 && *eclassTag <= 9999);
   }

   if (eclassPrio) {
      *eclassPrio = ((Int)sym[8]) - '0';
      vg_assert(*eclassPrio >= 0 && *eclassPrio <= 9);
   }

   is_VG_Z_prefixed =
      sym[12] == 'V' &&
      sym[13] == 'G' &&
      sym[14] == '_' &&
      sym[15] == 'Z' &&
      sym[16] == '_';
   if (is_VG_Z_prefixed) {
      vg_assert2(0, "symbol with a 'VG_Z_' prefix: %s.\n"
                    "see pub_tool_redir.h for an explanation.", sym);
   }

   
   i = 12;
   while (True) {

      if (sym[i] == '_')
      
         break;

      if (sym[i] == 0) {
         error = True;
         goto out;
      }

      if (sym[i] != 'Z') {
         EMITSO(sym[i]);
         i++;
         continue;
      }

      
      i++;
      switch (sym[i]) {
         case 'a': EMITSO('*'); break;
         case 'c': EMITSO(':'); break;
         case 'd': EMITSO('.'); break;
         case 'h': EMITSO('-'); break;
         case 'p': EMITSO('+'); break;
         case 's': EMITSO(' '); break;
         case 'u': EMITSO('_'); break;
         case 'A': EMITSO('@'); break;
         case 'D': EMITSO('$'); break;
         case 'L': EMITSO('('); break;
         case 'R': EMITSO(')'); break;
         case 'Z': EMITSO('Z'); break;
         default: error = True; goto out;
      }
      i++;
   }

   vg_assert(sym[i] == '_');
   i++;

   
   if (!fn_is_encoded) {

      
      while (True) {
         if (sym[i] == 0)
            break;
         EMITFN(sym[i]);
         i++;
      }
      goto out;

   }

   
   while (True) {

      if (sym[i] == 0)
         break;

      if (sym[i] != 'Z') {
         EMITFN(sym[i]);
         i++;
         continue;
      }

      
      i++;
      switch (sym[i]) {
         case 'a': EMITFN('*'); break;
         case 'c': EMITFN(':'); break;
         case 'd': EMITFN('.'); break;
         case 'h': EMITFN('-'); break;
         case 'p': EMITFN('+'); break;
         case 's': EMITFN(' '); break;
         case 'u': EMITFN('_'); break;
         case 'A': EMITFN('@'); break;
         case 'D': EMITFN('$'); break;
         case 'L': EMITFN('('); break;
         case 'R': EMITFN(')'); break;
         case 'Z': EMITFN('Z'); break;
         default: error = True; goto out;
      }
      i++;
   }

  out:
   EMITSO(0);
   EMITFN(0);

   if (error) {
      
      VG_(message)(Vg_UserMsg,
                   "m_demangle: error Z-demangling: %s\n", sym);
      return False;
   }
   if (oflow) {
      
      VG_(message)(Vg_UserMsg,
                   "m_demangle: oflow Z-demangling: %s\n", sym);
      return False;
   }

   return True;
}


