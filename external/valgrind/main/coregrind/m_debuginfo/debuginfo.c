

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
#include "pub_core_vki.h"
#include "pub_core_libcsetjmp.h" 
#include "pub_core_threadstate.h"
#include "pub_core_debuginfo.h"  
#include "pub_core_demangle.h"
#include "pub_core_libcbase.h"
#include "pub_core_libcassert.h"
#include "pub_core_libcprint.h"
#include "pub_core_libcfile.h"
#include "pub_core_libcproc.h"   
#include "pub_core_seqmatch.h"
#include "pub_core_options.h"
#include "pub_core_redir.h"      
#include "pub_core_aspacemgr.h"
#include "pub_core_machine.h"    
#include "pub_core_xarray.h"
#include "pub_core_oset.h"
#include "pub_core_stacktrace.h" 
#include "pub_core_ume.h"

#include "priv_misc.h"           
#include "priv_d3basics.h"       
#include "priv_tytypes.h"
#include "priv_storage.h"
#include "priv_readdwarf.h"
#include "priv_readstabs.h"
#if defined(VGO_linux)
# include "priv_readelf.h"
# include "priv_readdwarf3.h"
# include "priv_readpdb.h"
#elif defined(VGO_darwin)
# include "priv_readmacho.h"
# include "priv_readpdb.h"
#endif






static void cfsi_cache__invalidate ( void );



static DebugInfo* debugInfo_list = NULL;


static void move_DebugInfo_one_step_forward ( DebugInfo* di )
{
   DebugInfo *di0, *di1, *di2;
   if (di == debugInfo_list)
      return; 
   vg_assert(di != NULL);
   di0 = debugInfo_list;
   di1 = NULL;
   di2 = NULL;
   while (True) {
      if (di0 == NULL || di0 == di) break;
      di2 = di1;
      di1 = di0;
      di0 = di0->next;
   }
   vg_assert(di0 == di);
   if (di0 != NULL && di1 != NULL && di2 != NULL) {
      DebugInfo* tmp;
      vg_assert(di2->next == di1);
      vg_assert(di1->next == di0);
      tmp = di0->next;
      di2->next = di0;
      di0->next = di1;
      di1->next = tmp;
   }
   else
   if (di0 != NULL && di1 != NULL && di2 == NULL) {
      
      vg_assert(debugInfo_list == di1);
      vg_assert(di1->next == di0);
      di1->next = di0->next;
      di0->next = di1;
      debugInfo_list = di0;
   }
}



static ULong handle_counter = 1;

static 
DebugInfo* alloc_DebugInfo( const UChar* filename )
{
   Bool       traceme;
   DebugInfo* di;

   vg_assert(filename);

   di = ML_(dinfo_zalloc)("di.debuginfo.aDI.1", sizeof(DebugInfo));
   di->handle       = handle_counter++;
   di->fsm.filename = ML_(dinfo_strdup)("di.debuginfo.aDI.2", filename);
   di->fsm.maps     = VG_(newXA)(
                         ML_(dinfo_zalloc), "di.debuginfo.aDI.3",
                         ML_(dinfo_free), sizeof(struct _DebugInfoMapping));

   traceme 
      = VG_(string_match)( VG_(clo_trace_symtab_patt), filename );
   if (traceme) {
      di->trace_symtab = VG_(clo_trace_symtab);
      di->trace_cfi    = VG_(clo_trace_cfi);
      di->ddump_syms   = VG_(clo_debug_dump_syms);
      di->ddump_line   = VG_(clo_debug_dump_line);
      di->ddump_frames = VG_(clo_debug_dump_frames);
   }

   return di;
}


static void free_DebugInfo ( DebugInfo* di )
{
   Word i, j, n;
   struct strchunk *chunk, *next;
   TyEnt* ent;
   GExpr* gexpr;

   vg_assert(di != NULL);
   if (di->fsm.maps)     VG_(deleteXA)(di->fsm.maps);
   if (di->fsm.filename) ML_(dinfo_free)(di->fsm.filename);
   if (di->soname)       ML_(dinfo_free)(di->soname);
   if (di->loctab)       ML_(dinfo_free)(di->loctab);
   if (di->cfsi)         ML_(dinfo_free)(di->cfsi);
   if (di->cfsi_exprs)   VG_(deleteXA)(di->cfsi_exprs);
   if (di->fpo)          ML_(dinfo_free)(di->fpo);

   if (di->symtab) {
      n = di->symtab_used;
      for (i = 0; i < n; i++) {
         DiSym* sym = &di->symtab[i];
         if (sym->sec_names)
            ML_(dinfo_free)(sym->sec_names);
      }
      
      ML_(dinfo_free)(di->symtab);
   }

   for (chunk = di->strchunks; chunk != NULL; chunk = next) {
      next = chunk->next;
      ML_(dinfo_free)(chunk);
   }

   if (di->admin_tyents) {
      n = VG_(sizeXA)(di->admin_tyents);
      for (i = 0; i < n; i++) {
         ent = (TyEnt*)VG_(indexXA)(di->admin_tyents, i);
         
         ML_(TyEnt__make_EMPTY)(ent);
      }
      VG_(deleteXA)(di->admin_tyents);
      di->admin_tyents = NULL;
   }

   if (di->admin_gexprs) {
      n = VG_(sizeXA)(di->admin_gexprs);
      for (i = 0; i < n; i++) {
         gexpr = *(GExpr**)VG_(indexXA)(di->admin_gexprs, i);
         ML_(dinfo_free)(gexpr);
      }
      VG_(deleteXA)(di->admin_gexprs);
      di->admin_gexprs = NULL;
   }

   if (di->varinfo) {
      for (i = 0; i < VG_(sizeXA)(di->varinfo); i++) {
         OSet* scope = *(OSet**)VG_(indexXA)(di->varinfo, i);
         if (!scope) continue;
         
         VG_(OSetGen_ResetIter)(scope);
         while (True) {
            DiAddrRange* arange = VG_(OSetGen_Next)(scope);
            if (!arange) break;
            
            vg_assert(arange->vars);
            for (j = 0; j < VG_(sizeXA)( arange->vars ); j++) {
               DiVariable* var = (DiVariable*)VG_(indexXA)(arange->vars,j);
               vg_assert(var);
            }
            VG_(deleteXA)(arange->vars);
         }
         VG_(OSetGen_Destroy)(scope);
      }
      VG_(deleteXA)(di->varinfo);
   }

   ML_(dinfo_free)(di);
}


static void discard_DebugInfo ( DebugInfo* di )
{
   HChar* reason = "munmap";

   DebugInfo** prev_next_ptr = &debugInfo_list;
   DebugInfo*  curr          =  debugInfo_list;

   while (curr) {
      if (curr == di) {
         
         if (curr->have_dinfo
             && (VG_(clo_verbosity) > 1 || VG_(clo_trace_redir)))
            VG_(message)(Vg_DebugMsg, 
                         "Discarding syms at %#lx-%#lx in %s due to %s()\n",
                         di->text_avma, 
                         di->text_avma + di->text_size,
                         curr->fsm.filename ? curr->fsm.filename
                                            : (UChar*)"???",
                         reason);
         vg_assert(*prev_next_ptr == curr);
         *prev_next_ptr = curr->next;
         if (curr->have_dinfo)
            VG_(redir_notify_delete_DebugInfo)( curr );
         free_DebugInfo(curr);
         return;
      }
      prev_next_ptr = &curr->next;
      curr          =  curr->next;
   }

   
}


static Bool discard_syms_in_range ( Addr start, SizeT length )
{
   Bool       anyFound = False;
   Bool       found;
   DebugInfo* curr;

   while (True) {
      found = False;

      curr = debugInfo_list;
      while (True) {
         if (curr == NULL)
            break;
         if (curr->text_present
             && curr->text_size > 0
             && (start+length - 1 < curr->text_avma 
                 || curr->text_avma + curr->text_size - 1 < start)) {
            
	 } else {
	    found = True;
	    break;
	 }
	 curr = curr->next;
      }

      if (!found) break;
      anyFound = True;
      discard_DebugInfo( curr );
   }

   return anyFound;
}


static Bool ranges_overlap (Addr s1, SizeT len1, Addr s2, SizeT len2 )
{
   Addr e1, e2;
   if (len1 == 0 || len2 == 0) 
      return False;
   e1 = s1 + len1 - 1;
   e2 = s2 + len2 - 1;
   vg_assert(s1 <= e1);
   vg_assert(s2 <= e2);
   if (e1 < s2 || e2 < s1) return False;
   return True;
}


static Bool do_DebugInfos_overlap ( DebugInfo* di1, DebugInfo* di2 )
{
   Word i, j;
   vg_assert(di1);
   vg_assert(di2);
   for (i = 0; i < VG_(sizeXA)(di1->fsm.maps); i++) {
      struct _DebugInfoMapping* map1 = VG_(indexXA)(di1->fsm.maps, i);
      for (j = 0; j < VG_(sizeXA)(di2->fsm.maps); j++) {
         struct _DebugInfoMapping* map2 = VG_(indexXA)(di2->fsm.maps, j);
         if (ranges_overlap(map1->avma, map1->size, map2->avma, map2->size))
            return True;
      }
   }

   return False;
}


static void discard_marked_DebugInfos ( void )
{
   DebugInfo* curr;

   while (True) {

      curr = debugInfo_list;
      while (True) {
         if (!curr)
            break;
         if (curr->mark)
            break;
	 curr = curr->next;
      }

      if (!curr) break;
      discard_DebugInfo( curr );

   }
}


static void discard_DebugInfos_which_overlap_with ( DebugInfo* diRef )
{
   DebugInfo* di;
   for (di = debugInfo_list; di; di = di->next) {
      di->mark = do_DebugInfos_overlap( di, diRef );
      if (di == diRef) {
         vg_assert(di->mark);
         di->mark = False;
      }
   }
   discard_marked_DebugInfos();
}


static DebugInfo* find_or_create_DebugInfo_for ( UChar* filename )
{
   DebugInfo* di;
   vg_assert(filename);
   for (di = debugInfo_list; di; di = di->next) {
      vg_assert(di->fsm.filename);
      if (0==VG_(strcmp)(di->fsm.filename, filename))
         break;
   }
   if (!di) {
      di = alloc_DebugInfo(filename);
      vg_assert(di);
      di->next = debugInfo_list;
      debugInfo_list = di;
   }
   return di;
}


static void check_CFSI_related_invariants ( DebugInfo* di )
{
   DebugInfo* di2 = NULL;
   Bool has_nonempty_rx = False;
   Bool cfsi_fits = False;
   Word i, j;
   vg_assert(di);
   vg_assert(di->fsm.have_rx_map);
   vg_assert(di->fsm.have_rw_map);
   for (i = 0; i < VG_(sizeXA)(di->fsm.maps); i++) {
      struct _DebugInfoMapping* map = VG_(indexXA)(di->fsm.maps, i);
      
      if (!map->rx)
         continue;

      
      if (map->size == 0)
         continue;
      has_nonempty_rx = True;
        
      
      
      vg_assert(map->size > 0);

      
      for (di2 = debugInfo_list; di2; di2 = di2->next) {
         if (di2 == di)
            continue;
         for (j = 0; j < VG_(sizeXA)(di2->fsm.maps); j++) {
            struct _DebugInfoMapping* map2 = VG_(indexXA)(di2->fsm.maps, j);
            if (!map2->rx || map2->size == 0)
               continue;
            vg_assert(!ranges_overlap(map->avma,  map->size,
                                      map2->avma, map2->size));
         }
      }
      di2 = NULL;

      
      if (di->cfsi) {
         vg_assert(di->cfsi_minavma <= di->cfsi_maxavma); 
         if (di->cfsi_minavma >= map->avma &&
             di->cfsi_maxavma <  map->avma + map->size)
            cfsi_fits = True;
      }
   }

   
   if (!has_nonempty_rx) {
      vg_assert(di->cfsi == NULL);
      return;
   }

   
   if (di->cfsi)
      vg_assert(cfsi_fits);

   
   if (di->cfsi) {
      vg_assert(di->cfsi_used > 0);
      vg_assert(di->cfsi_size > 0);
      for (i = 0; i < di->cfsi_used; i++) {
         DiCfSI* cfsi = &di->cfsi[i];
         vg_assert(cfsi->len > 0);
         vg_assert(cfsi->base >= di->cfsi_minavma);
         vg_assert(cfsi->base + cfsi->len - 1 <= di->cfsi_maxavma);
         if (i > 0) {
            DiCfSI* cfsip = &di->cfsi[i-1];
            vg_assert(cfsip->base + cfsip->len <= cfsi->base);
         }
      }
   } else {
      vg_assert(di->cfsi_used == 0);
      vg_assert(di->cfsi_size == 0);
   }
}



void VG_(di_initialise) ( void )
{
   vg_assert(debugInfo_list == NULL);

   
   cfsi_cache__invalidate();
}



#if defined(VGO_linux)  ||  defined(VGO_darwin)


static ULong di_notify_ACHIEVE_ACCEPT_STATE ( struct _DebugInfo* di )
{
   ULong di_handle;
   Bool  ok;

   vg_assert(di->fsm.filename);
   TRACE_SYMTAB("\n");
   TRACE_SYMTAB("------ start ELF OBJECT "
                "------------------------------\n");
   TRACE_SYMTAB("------ name = %s\n", di->fsm.filename);
   TRACE_SYMTAB("\n");

   discard_DebugInfos_which_overlap_with( di );

   
#  if defined(VGO_linux)
   ok = ML_(read_elf_debug_info)( di );
#  elif defined(VGO_darwin)
   ok = ML_(read_macho_debug_info)( di );
#  else
#    error "unknown OS"
#  endif

   if (ok) {

      TRACE_SYMTAB("\n------ Canonicalising the "
                   "acquired info ------\n");
      
      cfsi_cache__invalidate();
      
      ML_(canonicaliseTables)( di );
      
      TRACE_SYMTAB("\n------ Notifying m_redir ------\n");
      VG_(redir_notify_new_DebugInfo)( di );
      
      di->have_dinfo = True;
      tl_assert(di->handle > 0);
      di_handle = di->handle;
      check_CFSI_related_invariants(di);

   } else {
      TRACE_SYMTAB("\n------ ELF reading failed ------\n");
      di_handle = 0;
      vg_assert(di->have_dinfo == False);
   }

   TRACE_SYMTAB("\n");
   TRACE_SYMTAB("------ name = %s\n", di->fsm.filename);
   TRACE_SYMTAB("------ end ELF OBJECT "
                "------------------------------\n");
   TRACE_SYMTAB("\n");

   return di_handle;
}



ULong VG_(di_notify_mmap)( Addr a, Bool allow_SkFileV, Int use_fd )
{
   NSegment const * seg;
   HChar*     filename;
   Bool       is_rx_map, is_rw_map, is_ro_map;
   DebugInfo* di;
   Int        actual_fd, oflags;
   SysRes     preadres;
   HChar      buf1k[1024];
   Bool       debug = False;
   SysRes     statres;
   struct vg_stat statbuf;

   vg_assert(use_fd >= -1);

   seg = VG_(am_find_nsegment)(a);
   vg_assert(seg);

   if (debug)
      VG_(printf)("di_notify_mmap-1: %#lx-%#lx %c%c%c\n",
                  seg->start, seg->end, 
                  seg->hasR ? 'r' : '-',
                  seg->hasW ? 'w' : '-',seg->hasX ? 'x' : '-' );

   
   vg_assert(seg->end > seg->start);

   
   if ( ! (seg->kind == SkFileC
           || (seg->kind == SkFileV && allow_SkFileV)) )
      return 0;

   
   filename = VG_(am_get_filename)( (NSegment*)seg );
   if (!filename)
      return 0;

   if (debug)
      VG_(printf)("di_notify_mmap-2: %s\n", filename);

   
   statres = VG_(stat)(filename, &statbuf);

   vg_assert(sr_isError(statres) || ! VKI_S_ISLNK(statbuf.mode));

   if (sr_isError(statres)) {
      DebugInfo fake_di;
      Bool quiet = VG_(strstr)(filename, "/var/run/nscd/") != NULL;
      if (!quiet && VG_(clo_verbosity) > 1) {
         VG_(memset)(&fake_di, 0, sizeof(fake_di));
         fake_di.fsm.filename = filename;
         ML_(symerr)(&fake_di, True, "failed to stat64/stat this file");
      }
      return 0;
   }

   if (! VKI_S_ISREG(statbuf.mode))
      return 0;

   

   is_rx_map = False;
   is_rw_map = False;
   is_ro_map = False;

#  if defined(VGA_x86) || defined(VGA_ppc32) || defined(VGA_mips32)
   is_rx_map = seg->hasR && seg->hasX;
   is_rw_map = seg->hasR && seg->hasW;
#  elif defined(VGA_amd64) || defined(VGA_ppc64) || defined(VGA_arm)
   is_rx_map = seg->hasR && seg->hasX && !seg->hasW;
   is_rw_map = seg->hasR && seg->hasW && !seg->hasX;
#  elif defined(VGP_s390x_linux)
   is_rx_map = seg->hasR && seg->hasX && !seg->hasW;
   is_rw_map = seg->hasR && seg->hasW;
#  else
#    error "Unknown platform"
#  endif

#  if defined(VGP_x86_darwin) && DARWIN_VERS == DARWIN_10_7
   is_ro_map = seg->hasR && !seg->hasW && !seg->hasX;
#  endif

   if (debug)
      VG_(printf)("di_notify_mmap-3: is_rx_map %d, is_rw_map %d\n",
                  (Int)is_rx_map, (Int)is_rw_map);

   
   if (!(is_rx_map || is_rw_map || is_ro_map))
      return 0;

   
   
   VG_(memset)(buf1k, 0, sizeof(buf1k));
   oflags = VKI_O_RDONLY;
#  if defined(VKI_O_LARGEFILE)
   oflags |= VKI_O_LARGEFILE;
#  endif

   if (use_fd == -1) {
      SysRes fd = VG_(open)( filename, oflags, 0 );
      if (sr_isError(fd)) {
         if (sr_Err(fd) != VKI_EACCES) {
            DebugInfo fake_di;
            VG_(memset)(&fake_di, 0, sizeof(fake_di));
            fake_di.fsm.filename = filename;
            ML_(symerr)(&fake_di, True,
                        "can't open file to inspect ELF header");
         }
         return 0;
      }
      actual_fd = sr_Res(fd);
   } else {
      actual_fd = use_fd;
   }

   preadres = VG_(pread)( actual_fd, buf1k, sizeof(buf1k), 0 );
   if (use_fd == -1) {
      VG_(close)( actual_fd );
   }

   if (sr_isError(preadres)) {
      DebugInfo fake_di;
      VG_(memset)(&fake_di, 0, sizeof(fake_di));
      fake_di.fsm.filename = filename;
      ML_(symerr)(&fake_di, True, "can't read file to inspect ELF header");
      return 0;
   }
   if (sr_Res(preadres) == 0)
      return 0;
   vg_assert(sr_Res(preadres) > 0 && sr_Res(preadres) <= sizeof(buf1k) );

   
#  if defined(VGO_linux)
   if (!ML_(is_elf_object_file)( buf1k, (SizeT)sr_Res(preadres), False ))
      return 0;
#  elif defined(VGO_darwin)
   if (!ML_(is_macho_object_file)( buf1k, (SizeT)sr_Res(preadres) ))
      return 0;
#  else
#    error "unknown OS"
#  endif

   di = find_or_create_DebugInfo_for( filename );
   vg_assert(di);

   
   struct _DebugInfoMapping map;
   map.avma = a;
   map.size = seg->end + 1 - seg->start;
   map.foff = seg->offset;
   map.rx   = is_rx_map;
   map.rw   = is_rw_map;
   map.ro   = is_ro_map;
   VG_(addToXA)(di->fsm.maps, &map);

   
   di->fsm.have_rx_map |= is_rx_map;
   di->fsm.have_rw_map |= is_rw_map;
   di->fsm.have_ro_map |= is_ro_map;

   
   if (di->fsm.have_rx_map && di->fsm.have_rw_map && !di->have_dinfo) {
      return di_notify_ACHIEVE_ACCEPT_STATE ( di );
   } else {
      return 0;
   }
}


void VG_(di_notify_munmap)( Addr a, SizeT len )
{
   Bool anyFound;
   if (0) VG_(printf)("DISCARD %#lx %#lx\n", a, a+len);
   anyFound = discard_syms_in_range(a, len);
   if (anyFound)
      cfsi_cache__invalidate();
}


void VG_(di_notify_mprotect)( Addr a, SizeT len, UInt prot )
{
   Bool exe_ok = toBool(prot & VKI_PROT_EXEC);
#  if defined(VGA_x86)
   exe_ok = exe_ok || toBool(prot & VKI_PROT_READ);
#  endif
   if (0 && !exe_ok) {
      Bool anyFound = discard_syms_in_range(a, len);
      if (anyFound)
         cfsi_cache__invalidate();
   }
}


void VG_(di_notify_vm_protect)( Addr a, SizeT len, UInt prot )
{
   Bool do_nothing = True;
#  if defined(VGP_x86_darwin) && (DARWIN_VERS == DARWIN_10_7 || DARWIN_VERS == DARWIN_10_8)
   do_nothing = False;
#  endif
   if (do_nothing )
      return;

   Bool r_ok = toBool(prot & VKI_PROT_READ);
   Bool w_ok = toBool(prot & VKI_PROT_WRITE);
   Bool x_ok = toBool(prot & VKI_PROT_EXEC);
   if (! (r_ok && !w_ok && x_ok))
      return; 

   DebugInfo* di;
   struct _DebugInfoMapping *map = NULL;
   Word i;
   for (di = debugInfo_list; di; di = di->next) {
      vg_assert(di->fsm.filename);
      if (di->have_dinfo)
         continue; 
      if (!di->fsm.have_ro_map)
         continue; 
      if (di->fsm.have_rx_map)
         continue; 
      if (!di->fsm.have_rw_map)
         continue; 
      
      for (i = 0; i < VG_(sizeXA)(di->fsm.maps); i++) {
         map = (struct _DebugInfoMapping*)VG_(indexXA)(di->fsm.maps, i);
         if (map->ro && map->avma == a && map->size == len)
            break;
         map = NULL;
      }
      if (!map)
         continue; 
      
      break;
   }
   if (di == NULL)
      return; 

   vg_assert(di->fsm.have_ro_map);
   map->rx = True;
   map->ro = False;
   di->fsm.have_rx_map = True;
   di->fsm.have_ro_map = False;
   
   for (i = 0; i < VG_(sizeXA)(di->fsm.maps); i++) {
      map = (struct _DebugInfoMapping*)VG_(indexXA)(di->fsm.maps, i);
      if (map->ro) {
         di->fsm.have_ro_map = True;
         break;
      }
   }

   
   if (di->fsm.have_rx_map && di->fsm.have_rw_map && !di->have_dinfo) {
      ULong di_handle __attribute__((unused))
         = di_notify_ACHIEVE_ACCEPT_STATE( di );
   }
}



void VG_(di_notify_pdb_debuginfo)( Int fd_obj, Addr avma_obj,
                                   SizeT total_size, PtrdiffT bias_obj )
{
   Int    i, r, sz_exename;
   ULong  obj_mtime, pdb_mtime;
   Char   exename[VKI_PATH_MAX];
   Char*  pdbname = NULL;
   Char*  dot;
   SysRes sres;
   Int    fd_pdbimage;
   SizeT  n_pdbimage;
   struct vg_stat stat_buf;

   if (VG_(clo_verbosity) > 0) {
      VG_(message)(Vg_UserMsg, "\n");
      VG_(message)(Vg_UserMsg,
         "LOAD_PDB_DEBUGINFO: clreq:   fd=%d, avma=%#lx, total_size=%lu, "
         "bias=%#lx\n", 
         fd_obj, avma_obj, total_size, bias_obj
      );
   }

   r = VG_(fstat)(fd_obj, &stat_buf);
   if (r == -1)
      goto out; 
   vg_assert(r == 0);
   obj_mtime = stat_buf.mtime;

   
   vg_assert(VKI_PATH_MAX > 100); 
   VG_(memset)(exename, 0, sizeof(exename));
   VG_(sprintf)(exename, "/proc/self/fd/%d", fd_obj);
   sz_exename = VG_(readlink)(exename, exename, sizeof(exename)-2 );
   if (sz_exename == -1)
      goto out; 
   vg_assert(sz_exename >= 0 && sz_exename < sizeof(exename));
   vg_assert(exename[sizeof(exename)-1] == 0);

   if (VG_(clo_verbosity) > 0) {
      VG_(message)(Vg_UserMsg, "LOAD_PDB_DEBUGINFO: objname: %s\n", exename);
   }

   
   pdbname = ML_(find_name_of_pdb_file)(exename);
   if (pdbname) {
      vg_assert(VG_(strlen)(pdbname) >= 5); 
      
      for (i = 0; pdbname[i]; i++) {
         if (pdbname[i] == '\\')
            pdbname[i] = '/';
      }
      Bool is_quald
         = ('a' <= VG_(tolower)(pdbname[0]) && VG_(tolower)(pdbname[0]) <= 'z')
           && pdbname[1] == ':'
           && pdbname[2] == '/';
      HChar* home = VG_(getenv)("HOME");
      HChar* wpfx = VG_(getenv)("WINEPREFIX");
      if (is_quald && wpfx) {
         Int mashedSzB = VG_(strlen)(pdbname) + VG_(strlen)(wpfx) + 50;
         HChar* mashed = ML_(dinfo_zalloc)("di.debuginfo.dnpdi.1", mashedSzB);
         VG_(snprintf)(mashed, mashedSzB, "%s/drive_%c%s",
                       wpfx, pdbname[0], &pdbname[2]);
         vg_assert(mashed[mashedSzB-1] == 0);
         ML_(dinfo_free)(pdbname);
         pdbname = mashed;
      }
      else if (is_quald && home && !wpfx) {
         Int mashedSzB = VG_(strlen)(pdbname) + VG_(strlen)(home) + 50;
         HChar* mashed = ML_(dinfo_zalloc)("di.debuginfo.dnpdi.2", mashedSzB);
         VG_(snprintf)(mashed, mashedSzB, "%s/.wine/drive_%c%s",
		       home, pdbname[0], &pdbname[2]);
         vg_assert(mashed[mashedSzB-1] == 0);
         ML_(dinfo_free)(pdbname);
         pdbname = mashed;
      } else {
         ML_(dinfo_free)(pdbname);
         pdbname = NULL;
      }
   }

   
   if (!pdbname) {
      pdbname = ML_(dinfo_zalloc)("di.debuginfo.lpd1", sz_exename+5);
      VG_(strcpy)(pdbname, exename);
      vg_assert(pdbname[sz_exename+5-1] == 0);
      dot = VG_(strrchr)(pdbname, '.');
      if (!dot)
         goto out; 
      if (dot[1] == 0)
         goto out; 

      if ('A' <= dot[1] && dot[1] <= 'Z')
         VG_(strcpy)(dot, ".PDB");
      else
         VG_(strcpy)(dot, ".pdb");

      vg_assert(pdbname[sz_exename+5-1] == 0);
   }

   
   sres = VG_(stat)(pdbname, &stat_buf);
   if (sr_isError(sres)) {
      VG_(message)(Vg_UserMsg, "Warning: Missing or un-stat-able %s\n",
                               pdbname);
   if (VG_(clo_verbosity) > 0)
      VG_(message)(Vg_UserMsg, "LOAD_PDB_DEBUGINFO: missing: %s\n", pdbname);
      goto out;
   }
   pdb_mtime = stat_buf.mtime;

   if (obj_mtime > pdb_mtime + 60ULL) {
      VG_(message)(Vg_UserMsg,
                   "Warning:       %s (mtime = %llu)\n"
                   " is older than %s (mtime = %llu)\n",
                   pdbname, pdb_mtime, exename, obj_mtime);
   }

   sres = VG_(open)(pdbname, VKI_O_RDONLY, 0);
   if (sr_isError(sres)) {
      VG_(message)(Vg_UserMsg, "Warning: Can't open %s\n", pdbname);
      goto out;
   }

   fd_pdbimage = sr_Res(sres);
   n_pdbimage  = stat_buf.size;
   if (n_pdbimage == 0 || n_pdbimage > 0x7FFFFFFF) {
      
      
      
      
      
      VG_(close)(fd_pdbimage);
      goto out;
   }
   sres = VG_(am_mmap_anon_float_valgrind)( n_pdbimage );
   if (sr_isError(sres)) {
      VG_(close)(fd_pdbimage);
      goto out;
   }

   void* pdbimage = (void*)sr_Res(sres);
   r = VG_(read)( fd_pdbimage, pdbimage, (Int)n_pdbimage );
   if (r < 0 || r != (Int)n_pdbimage) {
      VG_(am_munmap_valgrind)( (Addr)pdbimage, n_pdbimage );
      VG_(close)(fd_pdbimage);
      goto out;
   }

   if (VG_(clo_verbosity) > 0)
      VG_(message)(Vg_UserMsg, "LOAD_PDB_DEBUGINFO: pdbname: %s\n", pdbname);

   cfsi_cache__invalidate();
   
   discard_syms_in_range( avma_obj, total_size );

   { DebugInfo* di = find_or_create_DebugInfo_for(exename);

     
     vg_assert(di && !di->fsm.have_rx_map && !di->fsm.have_rw_map);
     vg_assert(!di->have_dinfo);

     ML_(read_pdb_debug_info)( di, avma_obj, bias_obj,
                               pdbimage, n_pdbimage, pdbname, pdb_mtime );
     
     
     vg_assert(di->have_dinfo); 
     VG_(am_munmap_valgrind)( (Addr)pdbimage, n_pdbimage );
     VG_(close)(fd_pdbimage);

     if (VG_(clo_verbosity) > 0) {
        VG_(message)(Vg_UserMsg, "LOAD_PDB_DEBUGINFO: done:    "
                                 "%lu syms, %lu src locs, %lu fpo recs\n",
                     di->symtab_used, di->loctab_used, di->fpo_size);
     }
   }

  out:
   if (pdbname) ML_(dinfo_free)(pdbname);
}

#endif 



void VG_(di_discard_ALL_debuginfo)( void )
{
   DebugInfo *di, *di2;
   di = debugInfo_list;
   while (di) {
      di2 = di->next;
      VG_(printf)("XXX rm %p\n", di);
      free_DebugInfo( di );
      di = di2;
   }
}


struct _DebugInfoMapping* ML_(find_rx_mapping) ( struct _DebugInfo* di,
                                                 Addr lo, Addr hi )
{
   Word i;
   vg_assert(lo <= hi); 

   
   if (   di->last_rx_map
       && lo >= di->last_rx_map->avma
       && hi <  di->last_rx_map->avma + di->last_rx_map->size)
      return di->last_rx_map;

   for (i = 0; i < VG_(sizeXA)(di->fsm.maps); i++) {
      struct _DebugInfoMapping* map = VG_(indexXA)(di->fsm.maps, i);
      if (   map->rx && map->size > 0
          && lo >= map->avma && hi < map->avma + map->size) {
         di->last_rx_map = map;
         return map;
      }
   }

   return NULL;
}



static void search_all_symtabs ( Addr ptr, DebugInfo** pdi,
                                           Word* symno,
                                 Bool match_anywhere_in_sym,
                                 Bool findText )
{
   Word       sno;
   DebugInfo* di;
   Bool       inRange;

   for (di = debugInfo_list; di != NULL; di = di->next) {

      if (findText) {
         inRange = di->fsm.have_rx_map
                   && (ML_(find_rx_mapping)(di, ptr, ptr) != NULL);
      } else {
         inRange = (di->data_present
                    && di->data_size > 0
                    && di->data_avma <= ptr 
                    && ptr < di->data_avma + di->data_size)
                   ||
                   (di->sdata_present
                    && di->sdata_size > 0
                    && di->sdata_avma <= ptr 
                    && ptr < di->sdata_avma + di->sdata_size)
                   ||
                   (di->bss_present
                    && di->bss_size > 0
                    && di->bss_avma <= ptr 
                    && ptr < di->bss_avma + di->bss_size)
                   ||
                   (di->sbss_present
                    && di->sbss_size > 0
                    && di->sbss_avma <= ptr 
                    && ptr < di->sbss_avma + di->sbss_size)
                   ||
                   (di->rodata_present
                    && di->rodata_size > 0
                    && di->rodata_avma <= ptr 
                    && ptr < di->rodata_avma + di->rodata_size);
      }

      if (!inRange) continue;

      sno = ML_(search_one_symtab) ( 
               di, ptr, match_anywhere_in_sym, findText );
      if (sno == -1) goto not_found;
      *symno = sno;
      *pdi = di;
      return;

   }
  not_found:
   *pdi = NULL;
}


static void search_all_loctabs ( Addr ptr, DebugInfo** pdi,
                                           Word* locno )
{
   Word       lno;
   DebugInfo* di;
   for (di = debugInfo_list; di != NULL; di = di->next) {
      if (di->text_present
          && di->text_size > 0
          && di->text_avma <= ptr 
          && ptr < di->text_avma + di->text_size) {
         lno = ML_(search_one_loctab) ( di, ptr );
         if (lno == -1) goto not_found;
         *locno = lno;
         *pdi = di;
         return;
      }
   }
  not_found:
   *pdi = NULL;
}


static
Bool get_sym_name ( Bool do_cxx_demangling, Bool do_z_demangling,
                    Bool do_below_main_renaming,
                    Addr a, Char* buf, Int nbuf,
                    Bool match_anywhere_in_sym, Bool show_offset,
                    Bool findText, PtrdiffT* offsetP )
{
   DebugInfo* di;
   Word       sno;
   PtrdiffT   offset;

   search_all_symtabs ( a, &di, &sno, match_anywhere_in_sym, findText );
   if (di == NULL) 
      return False;

   vg_assert(di->symtab[sno].pri_name);
   VG_(demangle) ( do_cxx_demangling, do_z_demangling,
                   di->symtab[sno].pri_name, buf, nbuf );

   
   
   
   
   
   if ( do_below_main_renaming && ! VG_(clo_show_below_main) &&
        Vg_FnNameBelowMain == VG_(get_fnname_kind)(buf) )
   {
      VG_(strncpy_safely)(buf, "(below main)", nbuf);
   }
   offset = a - di->symtab[sno].addr;
   if (offsetP) *offsetP = offset;

   if (show_offset && offset != 0) {
      Char     buf2[12];
      Char*    symend = buf + VG_(strlen)(buf);
      Char*    end = buf + nbuf;
      Int      len;

      len = VG_(sprintf)(buf2, "%c%ld",
			 offset < 0 ? '-' : '+',
			 offset < 0 ? -offset : offset);
      vg_assert(len < (Int)sizeof(buf2));

      if (len < (end - symend)) {
	 Char *cp = buf2;
	 VG_(memcpy)(symend, cp, len+1);
      }
   }

   buf[nbuf-1] = 0; 

   return True;
}

Addr VG_(get_tocptr) ( Addr guest_code_addr )
{
   DebugInfo* si;
   Word       sno;
   search_all_symtabs ( guest_code_addr, 
                        &si, &sno,
                        True,
                        True );
   if (si == NULL) 
      return 0;
   else
      return si->symtab[sno].tocptr;
}

Bool VG_(get_fnname) ( Addr a, Char* buf, Int nbuf )
{
   return get_sym_name ( True, True,
                         True,
                         a, buf, nbuf,
                         True, 
                         False,
                         True,
                         NULL );
}

Bool VG_(get_fnname_w_offset) ( Addr a, Char* buf, Int nbuf )
{
   return get_sym_name ( True, True,
                         True,
                         a, buf, nbuf,
                         True, 
                         True,
                         True,
                         NULL );
}

Bool VG_(get_fnname_if_entry) ( Addr a, Char* buf, Int nbuf )
{
   return get_sym_name ( True, True,
                         True,
                         a, buf, nbuf,
                         False, 
                         False,
                         True,
                         NULL );
}

Bool VG_(get_fnname_raw) ( Addr a, Char* buf, Int nbuf )
{
   return get_sym_name ( False, False,
                         False,
                         a, buf, nbuf,
                         True, 
                         False,
                         True,
                         NULL );
}

Bool VG_(get_fnname_no_cxx_demangle) ( Addr a, Char* buf, Int nbuf )
{
   return get_sym_name ( False, True,
                         True,
                         a, buf, nbuf,
                         True, 
                         False,
                         True,
                         NULL );
}

Bool VG_(get_inst_offset_in_function)( Addr a,
                                       PtrdiffT* offset )
{
   Char fnname[64];
   return get_sym_name ( False, False,
                         False,
                         a, fnname, 64,
                         True, 
                         True,
                         True,
                         offset );
}

Vg_FnNameKind VG_(get_fnname_kind) ( Char* name )
{
   if (VG_STREQ("main", name)) {
      return Vg_FnNameMain;

   } else if (
#      if defined(VGO_linux)
       VG_STREQ("__libc_start_main",  name) ||  
       VG_STREQ("generic_start_main", name) ||  
#      elif defined(VGO_darwin)
       
       VG_STREQ("start_according_to_valgrind", name) ||  
#      else
#        error "Unknown OS"
#      endif
       0) {
      return Vg_FnNameBelowMain;

   } else {
      return Vg_FnNameNormal;
   }
}

Vg_FnNameKind VG_(get_fnname_kind_from_IP) ( Addr ip )
{
   
   #define BUFLEN 50
   Char buf[50];

   
   
   if (VG_(get_fnname_raw) ( ip, buf, BUFLEN )) {
      buf[BUFLEN-1] = '\0';      
      return VG_(get_fnname_kind)(buf);
   } else {
      return Vg_FnNameNormal;    
   }
}

Bool VG_(get_datasym_and_offset)( Addr data_addr,
                                  Char* dname, Int n_dname,
                                  PtrdiffT* offset )
{
   Bool ok;
   vg_assert(n_dname > 1);
   ok = get_sym_name ( False, False,
                       False,
                       data_addr, dname, n_dname,
                       True, 
                       False,
                       False,
                       offset );
   if (!ok)
      return False;
   dname[n_dname-1] = 0;
   return True;
}

Bool VG_(get_objname) ( Addr a, Char* buf, Int nbuf )
{
   DebugInfo* di;
   const NSegment *seg;
   HChar* filename;
   vg_assert(nbuf > 0);
   for (di = debugInfo_list; di != NULL; di = di->next) {
      if (di->text_present
          && di->text_size > 0
          && di->text_avma <= a 
          && a < di->text_avma + di->text_size) {
         VG_(strncpy_safely)(buf, di->fsm.filename, nbuf);
         buf[nbuf-1] = 0;
         return True;
      }
   }
   if ( (seg = VG_(am_find_nsegment(a))) != NULL 
        && (filename = VG_(am_get_filename)(seg)) != NULL ) {
      VG_(strncpy_safely)(buf, filename, nbuf);
      return True;
   }
   return False;
}

DebugInfo* VG_(find_DebugInfo) ( Addr a )
{
   static UWord n_search = 0;
   DebugInfo* di;
   n_search++;
   for (di = debugInfo_list; di != NULL; di = di->next) {
      if (di->text_present
          && di->text_size > 0
          && di->text_avma <= a 
          && a < di->text_avma + di->text_size) {
         if (0 == (n_search & 0xF))
            move_DebugInfo_one_step_forward( di );
         return di;
      }
   }
   return NULL;
}

Bool VG_(get_filename)( Addr a, Char* filename, Int n_filename )
{
   DebugInfo* si;
   Word       locno;
   search_all_loctabs ( a, &si, &locno );
   if (si == NULL) 
      return False;
   VG_(strncpy_safely)(filename, si->loctab[locno].filename, n_filename);
   return True;
}

Bool VG_(get_linenum)( Addr a, UInt* lineno )
{
   DebugInfo* si;
   Word       locno;
   search_all_loctabs ( a, &si, &locno );
   if (si == NULL) 
      return False;
   *lineno = si->loctab[locno].lineno;

   return True;
}

Bool VG_(get_filename_linenum) ( Addr a, 
                                 Char* filename, Int n_filename,
                                 Char* dirname,  Int n_dirname,
                                 Bool* dirname_available,
                                 UInt* lineno )
{
   DebugInfo* si;
   Word       locno;

   vg_assert( (dirname == NULL && dirname_available == NULL)
              ||
              (dirname != NULL && dirname_available != NULL) );

   search_all_loctabs ( a, &si, &locno );
   if (si == NULL) {
      if (dirname_available) {
         *dirname_available = False;
         *dirname = 0;
      }
      return False;
   }

   VG_(strncpy_safely)(filename, si->loctab[locno].filename, n_filename);
   *lineno = si->loctab[locno].lineno;

   if (dirname) {
      
      vg_assert(n_dirname > 0);
      if (si->loctab[locno].dirname) {
         
         *dirname_available = True;
         VG_(strncpy_safely)(dirname, si->loctab[locno].dirname,
                                      n_dirname);
      } else {
         
         *dirname_available = False;
         *dirname = 0;
      }
   }

   return True;
}


Bool VG_(lookup_symbol_SLOW)(UChar* sopatt, UChar* name, 
                             Addr* pEnt, Addr* pToc)
{
   Bool     require_pToc = False;
   Int      i;
   DebugInfo* si;
   Bool     debug = False;
#  if defined(VG_PLAT_USES_PPCTOC)
   require_pToc = True;
#  endif
   for (si = debugInfo_list; si; si = si->next) {
      if (debug)
         VG_(printf)("lookup_symbol_SLOW: considering %s\n", si->soname);
      if (!VG_(string_match)(sopatt, si->soname)) {
         if (debug)
            VG_(printf)(" ... skip\n");
         continue;
      }
      for (i = 0; i < si->symtab_used; i++) {
         UChar* pri_name = si->symtab[i].pri_name;
         tl_assert(pri_name);
         if (0==VG_(strcmp)(name, pri_name)
             && (require_pToc ? si->symtab[i].tocptr : True)) {
            *pEnt = si->symtab[i].addr;
            *pToc = si->symtab[i].tocptr;
            return True;
         }
         UChar** sec_names = si->symtab[i].sec_names;
         if (sec_names) {
            tl_assert(sec_names[0]);
            while (*sec_names) {
               if (0==VG_(strcmp)(name, *sec_names)
                   && (require_pToc ? si->symtab[i].tocptr : True)) {
                  *pEnt = si->symtab[i].addr;
                  *pToc = si->symtab[i].tocptr;
                  return True;
               }
               sec_names++;
            }
         }
      }
   }
   return False;
}




static Int putStr ( Int n, Int n_buf, Char* buf, Char* str ) 
{
   vg_assert(n_buf > 0);
   vg_assert(n >= 0 && n < n_buf);
   for (; n < n_buf-1 && *str != 0; n++,str++)
      buf[n] = *str;
   vg_assert(n >= 0 && n < n_buf);
   buf[n] = '\0';
   return n;
}


static Int putStrEsc ( Int n, Int n_buf, Int count, Char* buf, Char* str ) 
{
   Char alt[2];
   vg_assert(n_buf > 0);
   vg_assert(count >= 0 && count < n_buf);
   vg_assert(n >= 0 && n < n_buf);
   for (; *str != 0; str++) {
      vg_assert(count >= 0);
      if (count <= 0)
         goto done;
      switch (*str) {
         case '&': 
            if (count < 5) goto done;
            n = putStr( n, n_buf, buf, "&amp;"); 
            count -= 5;
            break;
         case '<': 
            if (count < 4) goto done;
            n = putStr( n, n_buf, buf, "&lt;"); 
            count -= 4;
            break;
         case '>': 
            if (count < 4) goto done;
            n = putStr( n, n_buf, buf, "&gt;"); 
            count -= 4;
            break;
         default:
            if (count < 1) goto done;
            alt[0] = *str;
            alt[1] = 0;
            n = putStr( n, n_buf, buf, alt );
            count -= 1;
            break;
      }
   }
  done:
   vg_assert(count >= 0); 
   vg_assert(n >= 0 && n < n_buf);
   return n;
}

Char* VG_(describe_IP)(Addr eip, Char* buf, Int n_buf)
{
#  define APPEND(_str) \
      n = putStr(n, n_buf, buf, _str)
#  define APPEND_ESC(_count,_str) \
      n = putStrEsc(n, n_buf, (_count), buf, (_str))
#  define BUF_LEN    4096

   UInt  lineno; 
   UChar ibuf[50];
   Int   n = 0;

   static UChar buf_fn[BUF_LEN];
   static UChar buf_obj[BUF_LEN];
   static UChar buf_srcloc[BUF_LEN];
   static UChar buf_dirname[BUF_LEN];
   buf_fn[0] = buf_obj[0] = buf_srcloc[0] = buf_dirname[0] = 0;

   Bool  know_dirinfo = False;
   Bool  know_fnname  = VG_(clo_sym_offsets)
                        ? VG_(get_fnname_w_offset) (eip, buf_fn, BUF_LEN)
                        : VG_(get_fnname) (eip, buf_fn, BUF_LEN);
   Bool  know_objname = VG_(get_objname)(eip, buf_obj, BUF_LEN);
   Bool  know_srcloc  = VG_(get_filename_linenum)(
                           eip, 
                           buf_srcloc,  BUF_LEN, 
                           buf_dirname, BUF_LEN, &know_dirinfo,
                           &lineno 
                        );
   buf_fn     [ sizeof(buf_fn)-1      ]  = 0;
   buf_obj    [ sizeof(buf_obj)-1     ]  = 0;
   buf_srcloc [ sizeof(buf_srcloc)-1  ]  = 0;
   buf_dirname[ sizeof(buf_dirname)-1 ]  = 0;

   if (VG_(clo_xml)) {

      Bool   human_readable = True;
      HChar* maybe_newline  = human_readable ? "\n      " : "";
      HChar* maybe_newline2 = human_readable ? "\n    "   : "";

      APPEND("<frame>");
      VG_(sprintf)(ibuf,"<ip>0x%llX</ip>", (ULong)eip);
      APPEND(maybe_newline);
      APPEND(ibuf);
      if (know_objname) {
         APPEND(maybe_newline);
         APPEND("<obj>");
         APPEND_ESC(1*BUF_LEN/10, buf_obj);
         APPEND("</obj>");
      }
      if (know_fnname) {
         APPEND(maybe_newline);
         APPEND("<fn>");
         APPEND_ESC(6*BUF_LEN/10, buf_fn);
         APPEND("</fn>");
      }
      if (know_srcloc) {
         if (know_dirinfo) {
            APPEND(maybe_newline);
            APPEND("<dir>");
            APPEND_ESC(1*BUF_LEN/10, buf_dirname);
            APPEND("</dir>");
         }
         APPEND(maybe_newline);
         APPEND("<file>");
         APPEND_ESC(1*BUF_LEN/10, buf_srcloc);
         APPEND("</file>");
         APPEND(maybe_newline);
         APPEND("<line>");
         VG_(sprintf)(ibuf,"%d",lineno);
         APPEND(ibuf);
         APPEND("</line>");
      }
      APPEND(maybe_newline2);
      APPEND("</frame>");

   } else {

      
      
      
      
      
      
      
      
      
      
      
      VG_(sprintf)(ibuf,"0x%llX: ", (ULong)eip);
      APPEND(ibuf);
      if (know_fnname) {
         APPEND(buf_fn);
      } else {
         APPEND("???");
      }
      if (know_srcloc) {
         APPEND(" (");
         
         UChar* dirname = NULL;
         if (VG_(clo_n_fullpath_after) > 0) {
            Int i;
            dirname = buf_dirname;
            
            
            
            for (i = 0; i < VG_(clo_n_fullpath_after); i++) {
               UChar* prefix = VG_(clo_fullpath_after)[i];
               UChar* str    = VG_(strstr)(dirname, prefix);
               if (str) {
                  dirname = str + VG_(strlen)(prefix);
                  break;
               }
            }
            
            if (dirname[0] == '.' && dirname[1] == '/')
               dirname += 2;
         }
         
         
         if (dirname && dirname[0] != 0) {
            APPEND(dirname);
            APPEND("/");
         }
         APPEND(buf_srcloc);
         APPEND(":");
         VG_(sprintf)(ibuf,"%d",lineno);
         APPEND(ibuf);
         APPEND(")");
      } else if (know_objname) {
         APPEND(" (in ");
         APPEND(buf_obj);
         APPEND(")");
      } else if (know_fnname) {
         
         APPEND(" (in ???");
         APPEND(")");
      }

   }
   return buf;

#  undef APPEND
#  undef APPEND_ESC
#  undef BUF_LEN
}



typedef
   struct {
      D3UnwindRegs* uregs;
      Addr          min_accessible;
      Addr          max_accessible;
   }
   CfiExprEvalContext;

__attribute__((noinline))
static
UWord evalCfiExpr ( XArray* exprs, Int ix, 
                    CfiExprEvalContext* eec, Bool* ok )
{
   UWord wL, wR;
   Addr  a;
   CfiExpr* e;
   vg_assert(sizeof(Addr) == sizeof(UWord));
   e = VG_(indexXA)( exprs, ix );
   switch (e->tag) {
      case Cex_Binop:
         wL = evalCfiExpr( exprs, e->Cex.Binop.ixL, eec, ok );
         if (!(*ok)) return 0;
         wR = evalCfiExpr( exprs, e->Cex.Binop.ixR, eec, ok );
         if (!(*ok)) return 0;
         switch (e->Cex.Binop.op) {
            case Cop_Add: return wL + wR;
            case Cop_Sub: return wL - wR;
            case Cop_And: return wL & wR;
            case Cop_Mul: return wL * wR;
            case Cop_Shl: return wL << wR;
            case Cop_Shr: return wL >> wR;
            case Cop_Eq: return wL == wR ? 1 : 0;
            case Cop_Ge: return (Word) wL >= (Word) wR ? 1 : 0;
            case Cop_Gt: return (Word) wL > (Word) wR ? 1 : 0;
            case Cop_Le: return (Word) wL <= (Word) wR ? 1 : 0;
            case Cop_Lt: return (Word) wL < (Word) wR ? 1 : 0;
            case Cop_Ne: return wL != wR ? 1 : 0;
            default: goto unhandled;
         }
         
      case Cex_CfiReg:
         switch (e->Cex.CfiReg.reg) {
#           if defined(VGA_x86) || defined(VGA_amd64)
            case Creg_IA_IP: return eec->uregs->xip;
            case Creg_IA_SP: return eec->uregs->xsp;
            case Creg_IA_BP: return eec->uregs->xbp;
#           elif defined(VGA_arm)
            case Creg_ARM_R15: return eec->uregs->r15;
            case Creg_ARM_R14: return eec->uregs->r14;
            case Creg_ARM_R13: return eec->uregs->r13;
            case Creg_ARM_R12: return eec->uregs->r12;
#           elif defined(VGA_s390x)
            case Creg_IA_IP: return eec->uregs->ia;
            case Creg_IA_SP: return eec->uregs->sp;
            case Creg_IA_BP: return eec->uregs->fp;
            case Creg_S390_R14: return eec->uregs->lr;
#           elif defined(VGA_mips32)
            case Creg_IA_IP: return eec->uregs->pc;
            case Creg_IA_SP: return eec->uregs->sp;
            case Creg_IA_BP: return eec->uregs->fp;
            case Creg_MIPS_RA: return eec->uregs->ra;
#           elif defined(VGA_ppc32) || defined(VGA_ppc64)
#           else
#             error "Unsupported arch"
#           endif
            default: goto unhandled;
         }
         
      case Cex_Const:
         return e->Cex.Const.con;
      case Cex_Deref:
         a = evalCfiExpr( exprs, e->Cex.Deref.ixAddr, eec, ok );
         if (!(*ok)) return 0;
         if (a < eec->min_accessible
             || a > eec->max_accessible - sizeof(UWord) + 1) {
            *ok = False;
            return 0;
         }
         
         return ML_(read_UWord)((void *)a);
      default: 
         goto unhandled;
   }
   
  unhandled:
   VG_(printf)("\n\nevalCfiExpr: unhandled\n");
   ML_(ppCfiExpr)( exprs, ix );
   VG_(printf)("\n");
   vg_assert(0);
   
   return 0;
}


__attribute__((noinline))
static void find_DiCfSI ( DebugInfo** diP, 
                          Word* ixP,
                          Addr ip )
{
   DebugInfo* di;
   Word       i = -1;

   static UWord n_search = 0;
   static UWord n_steps = 0;
   n_search++;

   if (0) VG_(printf)("search for %#lx\n", ip);

   for (di = debugInfo_list; di != NULL; di = di->next) {
      Word j;
      n_steps++;

      if (di->cfsi_used == 0)
         continue;
      if (ip < di->cfsi_minavma || ip > di->cfsi_maxavma)
         continue;

      
      j = ML_(search_one_cfitab)( di, ip );
      vg_assert(j >= -1 && j < (Word)di->cfsi_used);

      if (j != -1) {
         i = j;
         break; 
      }
   }

   if (i == -1) {

      
      *diP = (DebugInfo*)1;
      *ixP = 0;

   } else {

      
      vg_assert(di && VG_IS_4_ALIGNED(di));
      vg_assert(i >= 0 && i < di->cfsi_used);
      *diP = di;
      *ixP = i;

      if ((n_search & 0xF) == 0) {
         
         move_DebugInfo_one_step_forward( di );
      }
      

      if (0 && ((n_search & 0x7FFFF) == 0))
         VG_(printf)("find_DiCfSI: %lu searches, "
                     "%lu DebugInfos looked at\n", 
                     n_search, n_steps);

   }

}



#define N_CFSI_CACHE 511

typedef
   struct { Addr ip; DebugInfo* di; Word ix; }
   CFSICacheEnt;

static CFSICacheEnt cfsi_cache[N_CFSI_CACHE];

static void cfsi_cache__invalidate ( void ) {
   VG_(memset)(&cfsi_cache, 0, sizeof(cfsi_cache));
}


static inline CFSICacheEnt* cfsi_cache__find ( Addr ip )
{
   UWord         hash = ip % N_CFSI_CACHE;
   CFSICacheEnt* ce = &cfsi_cache[hash];
   static UWord  n_q = 0, n_m = 0;

   n_q++;
   if (0 && 0 == (n_q & 0x1FFFFF))
      VG_(printf)("QQQ %lu %lu\n", n_q, n_m);

   if (LIKELY(ce->ip == ip) && LIKELY(ce->di != NULL)) {
      
   } else {
      
      n_m++;
      ce->ip = ip;
      find_DiCfSI( &ce->di, &ce->ix, ip );
   }

   if (UNLIKELY(ce->di == (DebugInfo*)1)) {
      
      return NULL;
   } else {
      
      return ce;
   }
}


inline
static Addr compute_cfa ( D3UnwindRegs* uregs,
                          Addr min_accessible, Addr max_accessible,
                          DebugInfo* di, DiCfSI* cfsi )
{
   CfiExprEvalContext eec;
   Addr               cfa;
   Bool               ok;

   
   cfa = 0;
   switch (cfsi->cfa_how) {
#     if defined(VGA_x86) || defined(VGA_amd64)
      case CFIC_IA_SPREL: 
         cfa = cfsi->cfa_off + uregs->xsp;
         break;
      case CFIC_IA_BPREL: 
         cfa = cfsi->cfa_off + uregs->xbp;
         break;
#     elif defined(VGA_arm)
      case CFIC_ARM_R13REL: 
         cfa = cfsi->cfa_off + uregs->r13;
         break;
      case CFIC_ARM_R12REL: 
         cfa = cfsi->cfa_off + uregs->r12;
         break;
      case CFIC_ARM_R11REL: 
         cfa = cfsi->cfa_off + uregs->r11;
         break;
      case CFIC_ARM_R7REL: 
         cfa = cfsi->cfa_off + uregs->r7;
         break;
#     elif defined(VGA_s390x)
      case CFIC_IA_SPREL:
         cfa = cfsi->cfa_off + uregs->sp;
         break;
      case CFIR_MEMCFAREL:
      {
         Addr a = uregs->sp + cfsi->cfa_off;
         if (a < min_accessible || a > max_accessible-sizeof(Addr))
            break;
         cfa = ML_(read_Addr)((void *)a);
         break;
      }
      case CFIR_SAME:
         cfa = uregs->fp;
         break;
      case CFIC_IA_BPREL:
         cfa = cfsi->cfa_off + uregs->fp;
         break;
#     elif defined(VGA_mips32)
      case CFIC_IA_SPREL:
         cfa = cfsi->cfa_off + uregs->sp;
         break;
      case CFIR_SAME:
         cfa = uregs->fp;
         break;
      case CFIC_IA_BPREL:
         cfa = cfsi->cfa_off + uregs->fp;
         break;
#     elif defined(VGA_ppc32) || defined(VGA_ppc64)
#     else
#       error "Unsupported arch"
#     endif
      case CFIC_EXPR: 
         if (0) {
            VG_(printf)("CFIC_EXPR: ");
            ML_(ppCfiExpr)(di->cfsi_exprs, cfsi->cfa_off);
            VG_(printf)("\n");
         }
         eec.uregs          = uregs;
         eec.min_accessible = min_accessible;
         eec.max_accessible = max_accessible;
         ok = True;
         cfa = evalCfiExpr(di->cfsi_exprs, cfsi->cfa_off, &eec, &ok );
         if (!ok) return 0;
         break;
      default: 
         vg_assert(0);
   }
   return cfa;
}


Addr ML_(get_CFA) ( Addr ip, Addr sp, Addr fp,
                    Addr min_accessible, Addr max_accessible )
{
   CFSICacheEnt* ce;
   DebugInfo*    di;
   DiCfSI*       cfsi __attribute__((unused));

   ce = cfsi_cache__find(ip);

   if (UNLIKELY(ce == NULL))
      return 0; 

   di = ce->di;
   cfsi = &di->cfsi[ ce->ix ];

#  if defined(VGA_x86) || defined(VGA_amd64)
   { D3UnwindRegs uregs;
     uregs.xip = ip;
     uregs.xsp = sp;
     uregs.xbp = fp;
     return compute_cfa(&uregs,
                        min_accessible,  max_accessible, di, cfsi);
   }
#elif defined(VGA_s390x)
   { D3UnwindRegs uregs;
     uregs.ia = ip;
     uregs.sp = sp;
     uregs.fp = fp;
     return compute_cfa(&uregs,
                        min_accessible,  max_accessible, di, cfsi);
   }

#  else
   return 0; 
#  endif
}


Bool VG_(use_CF_info) ( D3UnwindRegs* uregsHere,
                        Addr min_accessible,
                        Addr max_accessible )
{
   DebugInfo*         di;
   DiCfSI*            cfsi = NULL;
   Addr               cfa, ipHere = 0;
   CFSICacheEnt*      ce;
   CfiExprEvalContext eec __attribute__((unused));
   D3UnwindRegs       uregsPrev;

#  if defined(VGA_x86) || defined(VGA_amd64)
   ipHere = uregsHere->xip;
#  elif defined(VGA_arm)
   ipHere = uregsHere->r15;
#  elif defined(VGA_s390x)
   ipHere = uregsHere->ia;
#  elif defined(VGA_mips32)
   ipHere = uregsHere->pc;
#  elif defined(VGA_ppc32) || defined(VGA_ppc64)
#  else
#    error "Unknown arch"
#  endif
   ce = cfsi_cache__find(ipHere);

   if (UNLIKELY(ce == NULL))
      return False; 

   di = ce->di;
   cfsi = &di->cfsi[ ce->ix ];

   if (0) {
      VG_(printf)("found cfisi: "); 
      ML_(ppDiCfSI)(di->cfsi_exprs, cfsi);
   }

   VG_(bzero_inline)(&uregsPrev, sizeof(uregsPrev));

   
   cfa = compute_cfa(uregsHere,
                     min_accessible, max_accessible, di, cfsi);
   if (UNLIKELY(cfa == 0))
      return False;


#  define COMPUTE(_prev, _here, _how, _off)             \
      do {                                              \
         switch (_how) {                                \
            case CFIR_UNKNOWN:                          \
               return False;                            \
            case CFIR_SAME:                             \
               _prev = _here; break;                    \
            case CFIR_MEMCFAREL: {                      \
               Addr a = cfa + (Word)_off;               \
               if (a < min_accessible                   \
                   || a > max_accessible-sizeof(Addr))  \
                  return False;                         \
               _prev = ML_(read_Addr)((void *)a);       \
               break;                                   \
            }                                           \
            case CFIR_CFAREL:                           \
               _prev = cfa + (Word)_off;                \
               break;                                   \
            case CFIR_EXPR:                             \
               if (0)                                   \
                  ML_(ppCfiExpr)(di->cfsi_exprs,_off);  \
               eec.uregs = uregsHere;                   \
               eec.min_accessible = min_accessible;     \
               eec.max_accessible = max_accessible;     \
               Bool ok = True;                          \
               _prev = evalCfiExpr(di->cfsi_exprs, _off, &eec, &ok ); \
               if (!ok) return False;                   \
               break;                                   \
            default:                                    \
               vg_assert(0);                            \
         }                                              \
      } while (0)

#  if defined(VGA_x86) || defined(VGA_amd64)
   COMPUTE(uregsPrev.xip, uregsHere->xip, cfsi->ra_how, cfsi->ra_off);
   COMPUTE(uregsPrev.xsp, uregsHere->xsp, cfsi->sp_how, cfsi->sp_off);
   COMPUTE(uregsPrev.xbp, uregsHere->xbp, cfsi->bp_how, cfsi->bp_off);
#  elif defined(VGA_arm)
   COMPUTE(uregsPrev.r15, uregsHere->r15, cfsi->ra_how,  cfsi->ra_off);
   COMPUTE(uregsPrev.r14, uregsHere->r14, cfsi->r14_how, cfsi->r14_off);
   COMPUTE(uregsPrev.r13, uregsHere->r13, cfsi->r13_how, cfsi->r13_off);
   COMPUTE(uregsPrev.r12, uregsHere->r12, cfsi->r12_how, cfsi->r12_off);
   COMPUTE(uregsPrev.r11, uregsHere->r11, cfsi->r11_how, cfsi->r11_off);
   COMPUTE(uregsPrev.r7,  uregsHere->r7,  cfsi->r7_how,  cfsi->r7_off);
#  elif defined(VGA_s390x)
   COMPUTE(uregsPrev.ia, uregsHere->ia, cfsi->ra_how, cfsi->ra_off);
   COMPUTE(uregsPrev.sp, uregsHere->sp, cfsi->sp_how, cfsi->sp_off);
   COMPUTE(uregsPrev.fp, uregsHere->fp, cfsi->fp_how, cfsi->fp_off);
#  elif defined(VGA_mips32)
   COMPUTE(uregsPrev.pc, uregsHere->pc, cfsi->ra_how, cfsi->ra_off);
   COMPUTE(uregsPrev.sp, uregsHere->sp, cfsi->sp_how, cfsi->sp_off);
   COMPUTE(uregsPrev.fp, uregsHere->fp, cfsi->fp_how, cfsi->fp_off);
#  elif defined(VGA_ppc32) || defined(VGA_ppc64)
#  else
#    error "Unknown arch"
#  endif

#  undef COMPUTE

   *uregsHere = uregsPrev;
   return True;
}



Bool VG_(use_FPO_info) ( Addr* ipP,
                         Addr* spP,
                         Addr* fpP,
                         Addr min_accessible,
                         Addr max_accessible )
{
   Word       i;
   DebugInfo* di;
   FPO_DATA*  fpo = NULL;
   Addr       spHere;

   static UWord n_search = 0;
   static UWord n_steps = 0;
   n_search++;

   if (0) VG_(printf)("search FPO for %#lx\n", *ipP);

   for (di = debugInfo_list; di != NULL; di = di->next) {
      n_steps++;

      if (di->fpo == NULL)
         continue;
      if (*ipP < di->fpo_minavma || *ipP > di->fpo_maxavma)
         continue;

      i = ML_(search_one_fpotab)( di, *ipP );
      if (i != -1) {
         Word j;
         if (0) {
            
            VG_(printf)("look for %#lx  size %ld i %ld\n",
                        *ipP, di->fpo_size, i);
            for (j = 0; j < di->fpo_size; j++)
               VG_(printf)("[%02ld] %#x %d\n", 
                            j, di->fpo[j].ulOffStart, di->fpo[j].cbProcSize);
         }
         vg_assert(i >= 0 && i < di->fpo_size);
         fpo = &di->fpo[i];
         break;
      }
   }

   if (fpo == NULL)
      return False;

   if (0 && ((n_search & 0x7FFFF) == 0))
      VG_(printf)("VG_(use_FPO_info): %lu searches, "
                  "%lu DebugInfos looked at\n",
                  n_search, n_steps);


   if ((n_search & 0x3F) == 0) {
      
      
   }
   

   if (0) {
      VG_(printf)("found fpo: ");
      
   }

 
   spHere = *spP;

   *ipP = ML_(read_Addr)((void *)(spHere + 4*(fpo->cbRegs + fpo->cdwLocals)));
   *spP =                         spHere + 4*(fpo->cbRegs + fpo->cdwLocals + 1 
                                                          + fpo->cdwParams);
   *fpP = ML_(read_Addr)((void *)(spHere + 4*2));
   return True;
}



#define  p2XA  VG_(xaprintf)

static void zterm_XA ( XArray* dst )
{
   HChar zero = 0;
   (void) VG_(addBytesToXA)( dst, &zero, 1 );
}


static Bool data_address_is_in_var ( PtrdiffT* offset,
                                     XArray*  tyents,
                                     DiVariable*   var,
                                     RegSummary*   regs,
                                     Addr          data_addr,
                                     const DebugInfo* di )
{
   MaybeULong mul;
   SizeT      var_szB;
   GXResult   res;
   Bool       show = False;

   vg_assert(var->name);
   vg_assert(var->gexpr);

   
   mul = ML_(sizeOfType)(tyents, var->typeR);
   vg_assert(mul.b == True);
   vg_assert(mul.ul > 0);
   if (sizeof(void*) == 4) vg_assert(mul.ul < (1ULL << 32));

   var_szB = (SizeT)mul.ul; 

   if (show) {
      VG_(printf)("VVVV: data_address_%#lx_is_in_var: %s :: ",
                  data_addr, var->name );
      ML_(pp_TyEnt_C_ishly)( tyents, var->typeR );
      VG_(printf)("\n");
   }

   
   if (var_szB == 0) {
      if (show)
         VG_(printf)("VVVV: -> Fail (variable is zero sized)\n");
      return False;
   }

   res = ML_(evaluate_GX)( var->gexpr, var->fbGX, regs, di );

   if (show) {
      VG_(printf)("VVVV: -> ");
      ML_(pp_GXResult)( res );
      VG_(printf)("\n");
   }

   if (res.kind == GXR_Addr 
       && res.word <= data_addr
       && data_addr < res.word + var_szB) {
      *offset = data_addr - res.word;
      return True;
   } else {
      return False;
   }
}


static void format_message ( XArray*  dn1,
                             XArray*  dn2,
                             Addr     data_addr,
                             DiVariable* var,
                             PtrdiffT var_offset,
                             PtrdiffT residual_offset,
                             XArray*  described,
                             Int      frameNo, 
                             ThreadId tid )
{
   Bool   have_descr, have_srcloc;
   Bool   xml       = VG_(clo_xml);
   UChar* vo_plural = var_offset == 1 ? "" : "s";
   UChar* ro_plural = residual_offset == 1 ? "" : "s";
   UChar* basetag   = "auxwhat"; 
   UChar tagL[32], tagR[32], xagL[32], xagR[32];

   if (frameNo < -1) {
      vg_assert(0); 
   }
   else if (frameNo == -1) {
      vg_assert(tid == VG_INVALID_THREADID);
   }
   else  {
      vg_assert(tid != VG_INVALID_THREADID);
   }

   vg_assert(dn1 && dn2);
   vg_assert(described);
   vg_assert(var && var->name);
   have_descr = VG_(sizeXA)(described) > 0
                && *(UChar*)VG_(indexXA)(described,0) != '\0';
   have_srcloc = var->fileName && var->lineNo > 0;

   tagL[0] = tagR[0] = xagL[0] = xagR[0] = 0;
   if (xml) {
      VG_(sprintf)(tagL, "<%s>",   basetag); 
      VG_(sprintf)(tagR, "</%s>",  basetag); 
      VG_(sprintf)(xagL, "<x%s>",  basetag); 
      VG_(sprintf)(xagR, "</x%s>", basetag); 
   }

#  define TAGL(_xa) p2XA(_xa, "%s", tagL)
#  define TAGR(_xa) p2XA(_xa, "%s", tagR)
#  define XAGL(_xa) p2XA(_xa, "%s", xagL)
#  define XAGR(_xa) p2XA(_xa, "%s", xagR)
#  define TXTL(_xa) p2XA(_xa, "%s", "<text>")
#  define TXTR(_xa) p2XA(_xa, "%s", "</text>")

   

   if ( frameNo >= 0 && (!have_srcloc) && (!have_descr) ) {
      if (xml) {
         TAGL( dn1 );
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside local var \"%pS\",",
               data_addr, var_offset, vo_plural, var->name );
         TAGR( dn1 );
         TAGL( dn2 );
         p2XA( dn2,
               "in frame #%d of thread %d", frameNo, (Int)tid );
         TAGR( dn2 );
      } else {
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside local var \"%s\",",
               data_addr, var_offset, vo_plural, var->name );
         p2XA( dn2,
               "in frame #%d of thread %d", frameNo, (Int)tid );
      }
   } 
   else
   if ( frameNo >= 0 && have_srcloc && (!have_descr) ) {
      if (xml) {
         TAGL( dn1 );
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside local var \"%pS\"",
               data_addr, var_offset, vo_plural, var->name );
         TAGR( dn1 );
         XAGL( dn2 );
         TXTL( dn2 );
         p2XA( dn2,
               "declared at %pS:%d, in frame #%d of thread %d",
               var->fileName, var->lineNo, frameNo, (Int)tid );
         TXTR( dn2 );
         
         p2XA( dn2,
               " <file>%pS</file> <line>%d</line> ", 
               var->fileName, var->lineNo );
         XAGR( dn2 );
      } else {
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside local var \"%s\"",
               data_addr, var_offset, vo_plural, var->name );
         p2XA( dn2,
               "declared at %s:%d, in frame #%d of thread %d",
               var->fileName, var->lineNo, frameNo, (Int)tid );
      }
   }
   else
   if ( frameNo >= 0 && (!have_srcloc) && have_descr ) {
      if (xml) {
         TAGL( dn1 );
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside %pS%pS",
               data_addr, residual_offset, ro_plural, var->name,
               (HChar*)(VG_(indexXA)(described,0)) );
         TAGR( dn1 );
         TAGL( dn2 );
         p2XA( dn2,
               "in frame #%d of thread %d", frameNo, (Int)tid );
         TAGR( dn2 );
      } else {
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside %s%s",
               data_addr, residual_offset, ro_plural, var->name,
               (HChar*)(VG_(indexXA)(described,0)) );
         p2XA( dn2,
               "in frame #%d of thread %d", frameNo, (Int)tid );
      }
   } 
   else
   if ( frameNo >= 0 && have_srcloc && have_descr ) {
      if (xml) {
         TAGL( dn1 );
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside %pS%pS,",
               data_addr, residual_offset, ro_plural, var->name,
               (HChar*)(VG_(indexXA)(described,0)) );
         TAGR( dn1 );
         XAGL( dn2 );
         TXTL( dn2 );
         p2XA( dn2,
               "declared at %pS:%d, in frame #%d of thread %d",
               var->fileName, var->lineNo, frameNo, (Int)tid );
         TXTR( dn2 );
         
         p2XA( dn2,
               " <file>%pS</file> <line>%d</line> ",
               var->fileName, var->lineNo );
         XAGR( dn2 );
      } else {
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside %s%s,",
               data_addr, residual_offset, ro_plural, var->name,
               (HChar*)(VG_(indexXA)(described,0)) );
         p2XA( dn2,
               "declared at %s:%d, in frame #%d of thread %d",
               var->fileName, var->lineNo, frameNo, (Int)tid );
      }
   }
   else
   
   if ( frameNo >= -1 && (!have_srcloc) && (!have_descr) ) {
      if (xml) {
         TAGL( dn1 );
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside global var \"%pS\"",
               data_addr, var_offset, vo_plural, var->name );
         TAGR( dn1 );
      } else {
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside global var \"%s\"",
               data_addr, var_offset, vo_plural, var->name );
      }
   } 
   else
   if ( frameNo >= -1 && have_srcloc && (!have_descr) ) {
      if (xml) {
         TAGL( dn1 );
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside global var \"%pS\"",
               data_addr, var_offset, vo_plural, var->name );
         TAGR( dn1 );
         XAGL( dn2 );
         TXTL( dn2 );
         p2XA( dn2,
               "declared at %pS:%d",
               var->fileName, var->lineNo);
         TXTR( dn2 );
         
         p2XA( dn2,
               " <file>%pS</file> <line>%d</line> ",
               var->fileName, var->lineNo );
         XAGR( dn2 );
      } else {
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside global var \"%s\"",
               data_addr, var_offset, vo_plural, var->name );
         p2XA( dn2,
               "declared at %s:%d",
               var->fileName, var->lineNo);
      }
   }
   else
   if ( frameNo >= -1 && (!have_srcloc) && have_descr ) {
      if (xml) {
         TAGL( dn1 );
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside %pS%pS,",
               data_addr, residual_offset, ro_plural, var->name,
               (HChar*)(VG_(indexXA)(described,0)) );
         TAGR( dn1 );
         TAGL( dn2 );
         p2XA( dn2,
               "a global variable");
         TAGR( dn2 );
      } else {
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside %s%s,",
               data_addr, residual_offset, ro_plural, var->name,
               (char*)(VG_(indexXA)(described,0)) );
         p2XA( dn2,
               "a global variable");
      }
   } 
   else
   if ( frameNo >= -1 && have_srcloc && have_descr ) {
      if (xml) {
         TAGL( dn1 );
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside %pS%pS,",
               data_addr, residual_offset, ro_plural, var->name,
               (HChar*)(VG_(indexXA)(described,0)) );
         TAGR( dn1 );
         XAGL( dn2 );
         TXTL( dn2 );
         p2XA( dn2,
               "a global variable declared at %pS:%d",
               var->fileName, var->lineNo);
         TXTR( dn2 );
         
         p2XA( dn2,
               " <file>%pS</file> <line>%d</line> ",
               var->fileName, var->lineNo );
         XAGR( dn2 );
      } else {
         p2XA( dn1,
               "Location 0x%lx is %lu byte%s inside %s%s,",
               data_addr, residual_offset, ro_plural, var->name,
               (HChar*)(VG_(indexXA)(described,0)) );
         p2XA( dn2,
               "a global variable declared at %s:%d",
               var->fileName, var->lineNo);
      }
   }
   else 
      vg_assert(0);

   
   zterm_XA( dn1 );
   zterm_XA( dn2 );

#  undef TAGL
#  undef TAGR
#  undef XAGL
#  undef XAGR
#  undef TXTL
#  undef TXTR
}


static 
Bool consider_vars_in_frame ( XArray*  dname1,
                              XArray*  dname2,
                              Addr data_addr,
                              Addr ip, Addr sp, Addr fp,
                              
                              ThreadId tid, Int frameNo )
{
   Word       i;
   DebugInfo* di;
   RegSummary regs;
   Bool debug = False;

   static UInt n_search = 0;
   static UInt n_steps = 0;
   n_search++;
   if (debug)
      VG_(printf)("QQQQ: cvif: ip,sp,fp %#lx,%#lx,%#lx\n", ip,sp,fp);
   
   for (di = debugInfo_list; di; di = di->next) {
      n_steps++;
      
      if (!di->text_present || di->text_size == 0)
         continue;
      
      if (di->text_avma <= ip && ip < di->text_avma + di->text_size)
         break;
   }
 
   if (!di)
      return False;

   if (0 && ((n_search & 0x1) == 0))
      VG_(printf)("consider_vars_in_frame: %u searches, "
                  "%u DebugInfos looked at\n", 
                  n_search, n_steps);
   if ((n_search & 0xFFFF) == 0) {
      
      move_DebugInfo_one_step_forward( di );
   }
   

   
   if (!di->varinfo)
      return False;

   regs.ip = ip;
   regs.sp = sp;
   regs.fp = fp;

   
   for (i = VG_(sizeXA)(di->varinfo) - 1; i >= 1; i--) {
      XArray*      vars;
      Word         j;
      DiAddrRange* arange;
      OSet*        this_scope 
         = *(OSet**)VG_(indexXA)( di->varinfo, i );
      if (debug)
         VG_(printf)("QQQQ:   considering scope %ld\n", (Word)i);
      if (!this_scope)
         continue;
      arange = VG_(OSetGen_LookupWithCmp)(
                  this_scope, &ip, 
                  ML_(cmp_for_DiAddrRange_range)
               );
      if (!arange)
         continue;
      
      vg_assert(arange->aMin <= arange->aMax);
      vg_assert(arange->aMin <= ip && ip <= arange->aMax);
      
      vars = arange->vars;
      vg_assert(vars);
      vg_assert(! (arange->aMin == (Addr)0
                   && arange->aMax == ~(Addr)0
                   && VG_(sizeXA)(vars) > 0) );
      for (j = 0; j < VG_(sizeXA)( vars ); j++) {
         DiVariable* var = (DiVariable*)VG_(indexXA)( vars, j );
         PtrdiffT    offset;
         if (debug)
            VG_(printf)("QQQQ:    var:name=%s %#lx-%#lx %#lx\n",
                        var->name,arange->aMin,arange->aMax,ip);
         if (data_address_is_in_var( &offset, di->admin_tyents,
                                     var, &regs,
                                     data_addr, di )) {
            PtrdiffT residual_offset = 0;
            XArray* described = ML_(describe_type)( &residual_offset,
                                                    di->admin_tyents, 
                                                    var->typeR, offset );
            format_message( dname1, dname2,
                            data_addr, var, offset, residual_offset,
                            described, frameNo, tid );
            VG_(deleteXA)( described );
            return True;
         }
      }
   }

   return False;
}

/* Try to form some description of DATA_ADDR by looking at the DWARF3
   debug info we have.  This considers all global variables, and all
   frames in the stacks of all threads.  Result is written at the ends
   of DNAME{1,2}V, which are XArray*s of HChar, that have been
   initialised by the caller, and True is returned.  If no description
   is created, False is returned.  Regardless of the return value,
   DNAME{1,2}V are guaranteed to be zero terminated after the call.

   Note that after the call, DNAME{1,2} may have more than one
   trailing zero, so callers should establish the useful text length
   using VG_(strlen) on the contents, rather than VG_(sizeXA) on the
   XArray itself.
*/
Bool VG_(get_data_description)( 
         void*  dname1v,
         void*  dname2v,
        Addr data_addr
     )
{
#  define N_FRAMES 8
   Addr ips[N_FRAMES], sps[N_FRAMES], fps[N_FRAMES];
   UInt n_frames;

   Addr       stack_min, stack_max;
   ThreadId   tid;
   Bool       found;
   DebugInfo* di;
   Word       j;

   XArray*    dname1 = (XArray*)dname1v;
   XArray*    dname2 = (XArray*)dname2v;

   if (0) VG_(printf)("get_data_description: dataaddr %#lx\n", data_addr);
   for (di = debugInfo_list; di != NULL; di = di->next) {
      OSet*        global_scope;
      Word         gs_size;
      Addr         zero;
      DiAddrRange* global_arange;
      Word         i;
      XArray*      vars;

      
      if (!di->text_present || di->text_size == 0)
         continue;
      
      if (!di->varinfo)
         continue;
      
      if (VG_(sizeXA)( di->varinfo ) == 0)
         continue;
      global_scope = *(OSet**)VG_(indexXA)( di->varinfo, 0 );
      vg_assert(global_scope);
      gs_size = VG_(OSetGen_Size)( global_scope );
      if (gs_size == 0)
          continue;
      vg_assert(gs_size == 1);
      
      zero = 0;
      global_arange 
         = VG_(OSetGen_Lookup)( global_scope, &zero );
      
      vg_assert(global_arange);
      vg_assert(global_arange->aMin == (Addr)0
                && global_arange->aMax == ~(Addr)0);
      
      if (!global_arange->vars)
         continue;
      vars = global_arange->vars;
      for (i = 0; i < VG_(sizeXA)( vars ); i++) {
         PtrdiffT offset;
         DiVariable* var = (DiVariable*)VG_(indexXA)( vars, i );
         vg_assert(var->name);
         if (data_address_is_in_var( &offset, di->admin_tyents, var, 
                                     NULL, 
                                     data_addr, di )) {
            PtrdiffT residual_offset = 0;
            XArray* described = ML_(describe_type)( &residual_offset,
                                                    di->admin_tyents,
                                                    var->typeR, offset );
            format_message( dname1, dname2,
                            data_addr, var, offset, residual_offset,
                            described, -1,
                            VG_INVALID_THREADID );
            VG_(deleteXA)( described );
            zterm_XA( dname1 );
            zterm_XA( dname2 );
            return True;
         }
      }
   }


   VG_(thread_stack_reset_iter)(&tid);
   while ( VG_(thread_stack_next)(&tid, &stack_min, &stack_max) ) {
      if (stack_min >= stack_max)
         continue; 
      if (consider_vars_in_frame( dname1, dname2,
                                  data_addr,
                                  VG_(get_IP)(tid),
                                  VG_(get_SP)(tid), 
                                  VG_(get_FP)(tid), tid, 0 )) {
         zterm_XA( dname1 );
         zterm_XA( dname2 );
         return True;
      }
   }
   

   
   found = False;
   VG_(thread_stack_reset_iter)(&tid);
   while ( VG_(thread_stack_next)(&tid, &stack_min, &stack_max) ) {
      if (stack_min >= stack_max)
         continue; 
      if (stack_min - VG_STACK_REDZONE_SZB <= data_addr
          && data_addr <= stack_max) {
         found = True;
         break;
      }
   }
   if (!found) {
      zterm_XA( dname1 );
      zterm_XA( dname2 );
      return False;
   }

   n_frames = VG_(get_StackTrace)( tid, ips, N_FRAMES,
                                   sps, fps, 0 );

   vg_assert(n_frames >= 0 && n_frames <= N_FRAMES);
   for (j = 0; j < n_frames; j++) {
      if (consider_vars_in_frame( dname1, dname2,
                                  data_addr,
                                  ips[j], 
                                  sps[j], fps[j], tid, j )) {
         zterm_XA( dname1 );
         zterm_XA( dname2 );
         return True;
      }
      if (j > 0 
          && consider_vars_in_frame( dname1, dname2,
                                     data_addr,
                                     ips[j] + 1, 
                                     sps[j], fps[j], tid, j )) {
         zterm_XA( dname1 );
         zterm_XA( dname2 );
         return True;
      }
   }

   
   zterm_XA( dname1 );
   zterm_XA( dname2 );
   return False;
#  undef N_FRAMES
}




static 
void analyse_deps ( XArray*  blocks,
                    XArray*  tyents,
                    Addr ip, const DebugInfo* di, DiVariable* var,
                    Bool arrays_only )
{
   GXResult   res_sp_6k, res_sp_7k, res_fp_6k, res_fp_7k;
   RegSummary regs;
   MaybeULong mul;
   Bool       isVec;
   TyEnt*     ty;

   Bool debug = False;
   if (0&&debug)
      VG_(printf)("adeps: var %s\n", var->name );

   
   mul = ML_(sizeOfType)(tyents, var->typeR);
   vg_assert(mul.b == True);
   vg_assert(mul.ul > 0);
   if (sizeof(void*) == 4) vg_assert(mul.ul < (1ULL << 32));

   
   ty = ML_(TyEnts__index_by_cuOff)( tyents, NULL, var->typeR );
   vg_assert(ty);
   vg_assert(ty->tag == Te_UNKNOWN || ML_(TyEnt__is_type)(ty));
   if (ty->tag == Te_UNKNOWN)
      return; 
   isVec = ty->tag == Te_TyArray;
   if (arrays_only && !isVec)
      return;

   if (0) {ML_(pp_TyEnt_C_ishly)(tyents, var->typeR);
           VG_(printf)("  %s\n", var->name);}

   regs.fp   = 0;
   regs.ip   = ip;
   regs.sp   = 6 * 1024;
   res_sp_6k = ML_(evaluate_GX)( var->gexpr, var->fbGX, &regs, di );

   regs.fp   = 0;
   regs.ip   = ip;
   regs.sp   = 7 * 1024;
   res_sp_7k = ML_(evaluate_GX)( var->gexpr, var->fbGX, &regs, di );

   regs.fp   = 6 * 1024;
   regs.ip   = ip;
   regs.sp   = 0;
   res_fp_6k = ML_(evaluate_GX)( var->gexpr, var->fbGX, &regs, di );

   regs.fp   = 7 * 1024;
   regs.ip   = ip;
   regs.sp   = 0;
   res_fp_7k = ML_(evaluate_GX)( var->gexpr, var->fbGX, &regs, di );

   vg_assert(res_sp_6k.kind == res_sp_7k.kind);
   vg_assert(res_sp_6k.kind == res_fp_6k.kind);
   vg_assert(res_sp_6k.kind == res_fp_7k.kind);

   if (res_sp_6k.kind == GXR_Addr) {
      StackBlock block;
      GXResult res;
      UWord sp_delta = res_sp_7k.word - res_sp_6k.word;
      UWord fp_delta = res_fp_7k.word - res_fp_6k.word;
      tl_assert(sp_delta == 0 || sp_delta == 1024);
      tl_assert(fp_delta == 0 || fp_delta == 1024);

      if (sp_delta == 0 && fp_delta == 0) {
      }
      else
      if (sp_delta == 1024 && fp_delta == 0) {
         regs.sp = regs.fp = 0;
         regs.ip = ip;
         res = ML_(evaluate_GX)( var->gexpr, var->fbGX, &regs, di );
         tl_assert(res.kind == GXR_Addr);
         if (debug)
         VG_(printf)("   %5ld .. %5ld (sp) %s\n",
                     res.word, res.word + ((UWord)mul.ul) - 1, var->name);
         block.base  = res.word;
         block.szB   = (SizeT)mul.ul;
         block.spRel = True;
         block.isVec = isVec;
         VG_(memset)( &block.name[0], 0, sizeof(block.name) );
         if (var->name)
            VG_(strncpy)( &block.name[0], var->name, sizeof(block.name)-1 );
         block.name[ sizeof(block.name)-1 ] = 0;
         VG_(addToXA)( blocks, &block );
      }
      else
      if (sp_delta == 0 && fp_delta == 1024) {
         regs.sp = regs.fp = 0;
         regs.ip = ip;
         res = ML_(evaluate_GX)( var->gexpr, var->fbGX, &regs, di );
         tl_assert(res.kind == GXR_Addr);
         if (debug)
         VG_(printf)("   %5ld .. %5ld (FP) %s\n",
                     res.word, res.word + ((UWord)mul.ul) - 1, var->name);
         block.base  = res.word;
         block.szB   = (SizeT)mul.ul;
         block.spRel = False;
         block.isVec = isVec;
         VG_(memset)( &block.name[0], 0, sizeof(block.name) );
         if (var->name)
            VG_(strncpy)( &block.name[0], var->name, sizeof(block.name)-1 );
         block.name[ sizeof(block.name)-1 ] = 0;
         VG_(addToXA)( blocks, &block );
      }
      else {
         vg_assert(0);
      }
   }
}



void* 
      VG_(di_get_stack_blocks_at_ip)( Addr ip, Bool arrays_only )
{
   
   Word       i;
   DebugInfo* di;
   Bool debug = False;

   XArray* res = VG_(newXA)( ML_(dinfo_zalloc), "di.debuginfo.dgsbai.1",
                             ML_(dinfo_free),
                             sizeof(StackBlock) );

   static UInt n_search = 0;
   static UInt n_steps = 0;
   n_search++;
   if (debug)
      VG_(printf)("QQQQ: dgsbai: ip %#lx\n", ip);
   
   for (di = debugInfo_list; di; di = di->next) {
      n_steps++;
      
      if (!di->text_present || di->text_size == 0)
         continue;
      
      if (di->text_avma <= ip && ip < di->text_avma + di->text_size)
         break;
   }
 
   if (!di)
      return res; 

   if (0 && ((n_search & 0x1) == 0))
      VG_(printf)("VG_(di_get_stack_blocks_at_ip): %u searches, "
                  "%u DebugInfos looked at\n", 
                  n_search, n_steps);
   if ((n_search & 0xFFFF) == 0) {
      
      move_DebugInfo_one_step_forward( di );
   }
   

   
   if (!di->varinfo)
      return res; 


   
   for (i = VG_(sizeXA)(di->varinfo) - 1; i >= 1; i--) {
      XArray*      vars;
      Word         j;
      DiAddrRange* arange;
      OSet*        this_scope 
         = *(OSet**)VG_(indexXA)( di->varinfo, i );
      if (debug)
         VG_(printf)("QQQQ:   considering scope %ld\n", (Word)i);
      if (!this_scope)
         continue;
      arange = VG_(OSetGen_LookupWithCmp)(
                  this_scope, &ip, 
                  ML_(cmp_for_DiAddrRange_range)
               );
      if (!arange)
         continue;
      
      vg_assert(arange->aMin <= arange->aMax);
      vg_assert(arange->aMin <= ip && ip <= arange->aMax);
      
      vars = arange->vars;
      vg_assert(vars);
      vg_assert(! (arange->aMin == (Addr)0
                   && arange->aMax == ~(Addr)0
                   && VG_(sizeXA)(vars) > 0) );
      for (j = 0; j < VG_(sizeXA)( vars ); j++) {
         DiVariable* var = (DiVariable*)VG_(indexXA)( vars, j );
         if (debug)
            VG_(printf)("QQQQ:    var:name=%s %#lx-%#lx %#lx\n", 
                        var->name,arange->aMin,arange->aMax,ip);
         analyse_deps( res, di->admin_tyents, ip,
                       di, var, arrays_only );
      }
   }

   return res;
}



void* 
      VG_(di_get_global_blocks_from_dihandle) ( ULong di_handle,
                                                Bool  arrays_only )
{
   

   DebugInfo* di;
   XArray* gvars; 
   Word nScopes, scopeIx;

   tl_assert(di_handle > 0);
   for (di = debugInfo_list; di; di = di->next) {
      if (di->handle == di_handle)
         break;
   }

   tl_assert(di != NULL);

   
   gvars = VG_(newXA)( ML_(dinfo_zalloc), "di.debuginfo.dggbfd.1",
                       ML_(dinfo_free), sizeof(GlobalBlock) );
   tl_assert(gvars);

   
   if (!di->varinfo)
      return gvars;

   
   nScopes = VG_(sizeXA)( di->varinfo );
   for (scopeIx = 0; scopeIx < nScopes; scopeIx++) {

      
      DiAddrRange* range;
      OSet*  scope
         = *(OSet**)VG_(indexXA)( di->varinfo, scopeIx );
      tl_assert(scope);
      VG_(OSetGen_ResetIter)(scope);
      while ( (range = VG_(OSetGen_Next)(scope)) ) {

         
         Word nVars, varIx;
         tl_assert(range->vars);
         nVars = VG_(sizeXA)( range->vars );
         for (varIx = 0; varIx < nVars; varIx++) {

            Bool        isVec;
            GXResult    res;
            MaybeULong  mul;
            GlobalBlock gb;
            TyEnt*      ty;
            DiVariable* var = VG_(indexXA)( range->vars, varIx );
            tl_assert(var->name);
            if (0) VG_(printf)("at depth %ld var %s ", scopeIx, var->name );

            if (0) { VG_(printf)("EVAL: "); ML_(pp_GX)(var->gexpr);
                     VG_(printf)("\n"); }
            res = ML_(evaluate_trivial_GX)( var->gexpr, di );

            
            if (res.kind != GXR_Addr) {
               if (0) VG_(printf)("FAIL\n");
               continue;
            }

            if (0) VG_(printf)("%#lx\n", res.word);

            
            mul = ML_(sizeOfType)(di->admin_tyents, var->typeR);

            vg_assert(mul.b == True);
            vg_assert(mul.ul > 0);
            if (sizeof(void*) == 4) vg_assert(mul.ul < (1ULL << 32));

            ty = ML_(TyEnts__index_by_cuOff)( di->admin_tyents, NULL,
                                              var->typeR );
            vg_assert(ty);
            vg_assert(ty->tag == Te_UNKNOWN || ML_(TyEnt__is_type)(ty));
            if (ty->tag == Te_UNKNOWN)
               continue; 

            isVec = ty->tag == Te_TyArray;
            if (arrays_only && !isVec) continue;

            
            tl_assert(var->name);
            tl_assert(di->soname);
            if (0) VG_(printf)("XXXX %s %s %d\n", var->name,
                                var->fileName?(HChar*)var->fileName
                                             :"??",var->lineNo);
            VG_(memset)(&gb, 0, sizeof(gb));
            gb.addr  = res.word;
            gb.szB   = (SizeT)mul.ul;
            gb.isVec = isVec;
            VG_(strncpy)(&gb.name[0], var->name, sizeof(gb.name)-1);
            VG_(strncpy)(&gb.soname[0], di->soname, sizeof(gb.soname)-1);
            tl_assert(gb.name[ sizeof(gb.name)-1 ] == 0);
            tl_assert(gb.soname[ sizeof(gb.soname)-1 ] == 0);

            VG_(addToXA)( gvars, &gb );

         } 

      } 

   } 

   return gvars;
}



const DebugInfo* VG_(next_DebugInfo)(const DebugInfo* di)
{
   if (di == NULL)
      return debugInfo_list;
   return di->next;
}

Addr VG_(DebugInfo_get_text_avma)(const DebugInfo* di)
{
   return di->text_present ? di->text_avma : 0; 
}

SizeT VG_(DebugInfo_get_text_size)(const DebugInfo* di)
{
   return di->text_present ? di->text_size : 0; 
}

Addr VG_(DebugInfo_get_plt_avma)(const DebugInfo* di)
{
   return di->plt_present ? di->plt_avma : 0; 
}

SizeT VG_(DebugInfo_get_plt_size)(const DebugInfo* di)
{
   return di->plt_present ? di->plt_size : 0; 
}

Addr VG_(DebugInfo_get_gotplt_avma)(const DebugInfo* di)
{
   return di->gotplt_present ? di->gotplt_avma : 0; 
}

SizeT VG_(DebugInfo_get_gotplt_size)(const DebugInfo* di)
{
   return di->gotplt_present ? di->gotplt_size : 0; 
}

const UChar* VG_(DebugInfo_get_soname)(const DebugInfo* di)
{
   return di->soname;
}

const UChar* VG_(DebugInfo_get_filename)(const DebugInfo* di)
{
   return di->fsm.filename;
}

PtrdiffT VG_(DebugInfo_get_text_bias)(const DebugInfo* di)
{
   return di->text_present ? di->text_bias : 0;
}

Int VG_(DebugInfo_syms_howmany) ( const DebugInfo *si )
{
   return si->symtab_used;
}

void VG_(DebugInfo_syms_getidx) ( const DebugInfo *si, 
                                        Int idx,
                                  Addr*    avma,
                                  Addr*    tocptr,
                                  UInt*    size,
                                  UChar**  pri_name,
                                  UChar*** sec_names,
                                  Bool*    isText,
                                  Bool*    isIFunc )
{
   vg_assert(idx >= 0 && idx < si->symtab_used);
   if (avma)      *avma      = si->symtab[idx].addr;
   if (tocptr)    *tocptr    = si->symtab[idx].tocptr;
   if (size)      *size      = si->symtab[idx].size;
   if (pri_name)  *pri_name  = si->symtab[idx].pri_name;
   if (sec_names) *sec_names = si->symtab[idx].sec_names;
   if (isText)    *isText    = si->symtab[idx].isText;
   if (isIFunc)   *isIFunc   = si->symtab[idx].isIFunc;
}



const HChar* VG_(pp_SectKind)( VgSectKind kind )
{
   switch (kind) {
      case Vg_SectUnknown: return "Unknown";
      case Vg_SectText:    return "Text";
      case Vg_SectData:    return "Data";
      case Vg_SectBSS:     return "BSS";
      case Vg_SectGOT:     return "GOT";
      case Vg_SectPLT:     return "PLT";
      case Vg_SectOPD:     return "OPD";
      case Vg_SectGOTPLT:  return "GOTPLT";
      default:             vg_assert(0);
   }
}


VgSectKind VG_(DebugInfo_sect_kind)( UChar* name, SizeT n_name, 
                                     Addr a)
{
   DebugInfo* di;
   VgSectKind res = Vg_SectUnknown;

   for (di = debugInfo_list; di != NULL; di = di->next) {

      if (0)
         VG_(printf)(
            "addr=%#lx di=%p %s got=%#lx,%ld plt=%#lx,%ld "
            "data=%#lx,%ld bss=%#lx,%ld\n",
            a, di, di->fsm.filename,
            di->got_avma,  di->got_size,
            di->plt_avma,  di->plt_size,
            di->data_avma, di->data_size,
            di->bss_avma,  di->bss_size);

      if (di->text_present
          && di->text_size > 0
          && a >= di->text_avma && a < di->text_avma + di->text_size) {
         res = Vg_SectText;
         break;
      }
      if (di->data_present
          && di->data_size > 0
          && a >= di->data_avma && a < di->data_avma + di->data_size) {
         res = Vg_SectData;
         break;
      }
      if (di->sdata_present
          && di->sdata_size > 0
          && a >= di->sdata_avma && a < di->sdata_avma + di->sdata_size) {
         res = Vg_SectData;
         break;
      }
      if (di->bss_present
          && di->bss_size > 0
          && a >= di->bss_avma && a < di->bss_avma + di->bss_size) {
         res = Vg_SectBSS;
         break;
      }
      if (di->sbss_present
          && di->sbss_size > 0
          && a >= di->sbss_avma && a < di->sbss_avma + di->sbss_size) {
         res = Vg_SectBSS;
         break;
      }
      if (di->plt_present
          && di->plt_size > 0
          && a >= di->plt_avma && a < di->plt_avma + di->plt_size) {
         res = Vg_SectPLT;
         break;
      }
      if (di->got_present
          && di->got_size > 0
          && a >= di->got_avma && a < di->got_avma + di->got_size) {
         res = Vg_SectGOT;
         break;
      }
      if (di->gotplt_present
          && di->gotplt_size > 0
          && a >= di->gotplt_avma && a < di->gotplt_avma + di->gotplt_size) {
         res = Vg_SectGOTPLT;
         break;
      }
      if (di->opd_present
          && di->opd_size > 0
          && a >= di->opd_avma && a < di->opd_avma + di->opd_size) {
         res = Vg_SectOPD;
         break;
      }
      
   }

   vg_assert( (di == NULL && res == Vg_SectUnknown)
              || (di != NULL && res != Vg_SectUnknown) );

   if (name) {

      vg_assert(n_name >= 8);

      if (di && di->fsm.filename) {
         Int i, j;
         Int fnlen = VG_(strlen)(di->fsm.filename);
         Int start_at = 1 + fnlen - n_name;
         if (start_at < 0) start_at = 0;
         vg_assert(start_at < fnlen);
         i = start_at; j = 0;
         while (True) {
            vg_assert(j >= 0 && j < n_name);
            vg_assert(i >= 0 && i <= fnlen);
            name[j] = di->fsm.filename[i];
            if (di->fsm.filename[i] == 0) break;
            i++; j++;
         }
         vg_assert(i == fnlen);
      } else {
         VG_(snprintf)(name, n_name, "%s", "???");
      }

      name[n_name-1] = 0;
   }

   return res;

}

