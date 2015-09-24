

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

#include "pub_core_basics.h"
#include "pub_core_libcassert.h"
#include "pub_core_libcbase.h"
#include "pub_core_sparsewa.h"      



#define Level0_MAGIC 0x458ec222

#define LevelN_MAGIC 0x0a280a1a


typedef
   struct {
      UWord magic;
      UWord words[256];
      Int   nInUse;
      UChar inUse[256/8];
   }
   Level0;

typedef
   struct {
      UWord magic;
      void* child[256]; 
      Int   nInUse;
      Int   level; 
   }
   LevelN;

typedef
   struct {
      UWord partial_key;
      Int   curr_ix;
      void* curr_nd; 
      Int   resume_point; 
   }
   SWAStackElem;

struct _SparseWA {
   void*        (*alloc_nofail)(HChar*,SizeT);
   HChar*       cc;
   void         (*dealloc)(void*);
   LevelN*      root;
   SWAStackElem iterStack[8];
   Int          isUsed;
};


static inline UWord swa_bitarray_read ( UChar* arr, UWord ix ) {
   UWord bix = ix >> 3;
   UWord off = ix & 7;
   return (arr[bix] >> off) & 1;
}

static inline UWord swa_bitarray_read_then_set ( UChar* arr, UWord ix ) {
   UWord bix = ix >> 3;
   UWord off = ix & 7;
   UChar old = arr[bix];
   UChar nyu = old | (1 << off);
   arr[bix] = nyu;
   return (old >> off) & 1;
}

static inline UWord swa_bitarray_read_then_clear ( UChar* arr, UWord ix ) {
   UWord bix = ix >> 3;
   UWord off = ix & 7;
   UChar old = arr[bix];
   UChar nyu = old & ~(1 << off);
   arr[bix] = nyu;
   return (old >> off) & 1;
}


static void swa_PUSH ( SparseWA* swa, UWord partial_key, Int curr_ix,
                                      void* curr_nd, Int resume_point )
{
   Int sp = swa->isUsed;
   const Int _3_or_7 = sizeof(void*) - 1;
   
   vg_assert(sp >= 0 && sp <= _3_or_7);
   swa->iterStack[sp].partial_key  = partial_key;
   swa->iterStack[sp].curr_ix      = curr_ix;
   swa->iterStack[sp].curr_nd      = curr_nd;
   swa->iterStack[sp].resume_point = resume_point;
   swa->isUsed = sp+1;
}

static void swa_POP ( SparseWA* swa,
                      UWord* partial_key, Int* curr_ix,
                      void** curr_nd, Int* resume_point )
{
   Int sp = swa->isUsed - 1;
   const Int _3_or_7 = sizeof(void*) - 1;
   
   vg_assert(sp >= 0 && sp <= _3_or_7);
   *partial_key  = swa->iterStack[sp].partial_key;
   *curr_ix      = swa->iterStack[sp].curr_ix;
   *curr_nd      = swa->iterStack[sp].curr_nd;
   *resume_point = swa->iterStack[sp].resume_point;
   swa->isUsed = sp;
}


static LevelN* swa_new_LevelN ( SparseWA* swa, Int level )
{
   LevelN* levelN = swa->alloc_nofail( swa->cc, sizeof(LevelN) );
   VG_(memset)(levelN, 0, sizeof(*levelN));
   levelN->magic = LevelN_MAGIC;
   levelN->level = level;
   return levelN;
}

static Level0* swa_new_Level0 ( SparseWA* swa )
{
   Level0* level0 = swa->alloc_nofail( swa->cc, sizeof(Level0) );
   VG_(memset)(level0, 0, sizeof(*level0));
   level0->magic = Level0_MAGIC;
   return level0;
}



void VG_(initIterSWA) ( SparseWA* swa )
{
   swa->isUsed = 0;
   if (swa->root) swa_PUSH(swa, 0, 0, swa->root, 1);
}


Bool VG_(nextIterSWA)( SparseWA* swa,
                       UWord* keyP, UWord* valP )
{
   UWord p_key;
   Int   curr_ix;
   void* curr_nd;
   Int   resume_point;

   dispatch:

   if (swa->isUsed == 0) 
      return False;

   swa_POP(swa, &p_key, &curr_ix, &curr_nd, &resume_point);
   switch (resume_point) {
      case 1:  goto start_new_node;
      case 2:  goto resume_leaf_node;
      case 3:  goto resume_nonleaf_node;
      default: vg_assert(0);
   }

   start_new_node:
   if (*(UWord*)curr_nd == Level0_MAGIC) {
      
      Level0* level0 = (Level0*)curr_nd;
      for (curr_ix = 0; curr_ix < 256; curr_ix++) {
         if (swa_bitarray_read(level0->inUse, curr_ix) == 1) {
            swa_PUSH(swa, p_key, curr_ix, curr_nd, 2);
            *keyP = (p_key << 8) + (UWord)curr_ix;
            *valP = level0->words[curr_ix];
            return True;
            resume_leaf_node:
            level0 = (Level0*)curr_nd;
         }
      }
   } else {
      
      LevelN* levelN;
      vg_assert(*(UWord*)curr_nd == LevelN_MAGIC);
      levelN = (LevelN*)curr_nd;
      for (curr_ix = 0; curr_ix < 256; curr_ix++) {
         if (levelN->child[curr_ix]) {
            swa_PUSH(swa, p_key, curr_ix, curr_nd, 3);
            p_key = (p_key << 8) + (UWord)curr_ix;
            curr_nd = levelN->child[curr_ix];
            goto start_new_node;
            resume_nonleaf_node:
            levelN = (LevelN*)curr_nd;
         }
      }
   }

   goto dispatch;
}


SparseWA* VG_(newSWA) ( void*(*alloc_nofail)(HChar* cc, SizeT), 
                        HChar* cc,
                        void(*dealloc)(void*) )
{
   SparseWA* swa;
   vg_assert(alloc_nofail);
   vg_assert(cc);
   vg_assert(dealloc);
   swa = alloc_nofail( cc, sizeof(SparseWA) );
   VG_(memset)(swa, 0, sizeof(*swa));
   swa->alloc_nofail = alloc_nofail;
   swa->cc = cc;
   swa->dealloc = dealloc;
   swa->root = NULL;
   return swa;
}


static void swa_deleteSWA_wrk ( void(*dealloc)(void*), void* nd )
{
   Int i;
   vg_assert(nd);
   if (*(UWord*)nd == LevelN_MAGIC) {
      LevelN* levelN = (LevelN*)nd;
      for (i = 0; i < 256; i++) {
         if (levelN->child[i]) {
            swa_deleteSWA_wrk( dealloc, levelN->child[i] );
         }
      }     
   } else {
      vg_assert(*(UWord*)nd == Level0_MAGIC);
   }
   dealloc(nd);
}
void VG_(deleteSWA) ( SparseWA* swa )
{
   if (swa->root)
      swa_deleteSWA_wrk( swa->dealloc, swa->root );
   swa->dealloc(swa);
}


Bool VG_(lookupSWA) ( SparseWA* swa,
                      UWord* keyP, UWord* valP,
                      UWord key )
{
   Int     i;
   UWord   ix;
   Level0* level0;
   LevelN* levelN;
   const Int _3_or_7 = sizeof(void*) - 1;

   vg_assert(swa);
   levelN = swa->root;

   
   for (i = _3_or_7; i >= 1; i--) {
      if (!levelN) return False;
      vg_assert(levelN->level == i);
      vg_assert(levelN->nInUse > 0);
      ix = (key >> (i*8)) & 0xFF;
      levelN = levelN->child[ix];
   }

   
   level0 = (Level0*)levelN;
   if (!level0) return False;
   vg_assert(level0->magic == Level0_MAGIC);
   vg_assert(level0->nInUse > 0);
   ix = key & 0xFF;
   if (swa_bitarray_read(level0->inUse, ix) == 0) return False;
   *keyP = key; 
   *valP = level0->words[ix];
   return True;
}


Bool VG_(addToSWA) ( SparseWA* swa, UWord key, UWord val )
{
   Int     i;
   UWord   ix;
   Level0* level0;
   LevelN* levelN;
   Bool    already_present;
   const Int _3_or_7 = sizeof(void*) - 1;

   vg_assert(swa);

   if (!swa->root)
      swa->root = swa_new_LevelN(swa, _3_or_7);
   levelN = swa->root;

   
   for (i = _3_or_7; i >= 2; i--) {
      
      vg_assert(levelN);
      vg_assert(levelN->level == i);
      ix = (key >> (i*8)) & 0xFF;
      if (levelN->child[ix] == NULL) {
         levelN->child[ix] = swa_new_LevelN(swa, i-1);
         levelN->nInUse++;
      }
      vg_assert(levelN->nInUse >= 1 && levelN->nInUse <= 256);
      levelN = levelN->child[ix];
   }

   
   vg_assert(levelN);
   vg_assert(levelN->level == 1);
   ix = (key >> (1*8)) & 0xFF;
   if (levelN->child[ix] == NULL) {
      levelN->child[ix] = swa_new_Level0(swa);
      levelN->nInUse++;
   }
   vg_assert(levelN->nInUse >= 1 && levelN->nInUse <= 256);
   level0 = levelN->child[ix];

   
   vg_assert(level0);
   vg_assert(level0->magic == Level0_MAGIC);
   ix = key & 0xFF;
   if (swa_bitarray_read_then_set(level0->inUse, ix) == 0) {
      level0->nInUse++;
      already_present = False;
   } else {
      already_present = True;
   }
   vg_assert(level0->nInUse >= 1 && level0->nInUse <= 256);
   level0->words[ix] = val;

   return already_present;
}


Bool VG_(delFromSWA) ( SparseWA* swa,
                       UWord* oldK, UWord* oldV, UWord key )
{
   Int     i;
   UWord   ix;
   Level0* level0;
   LevelN* levelN;
   const Int _3_or_7 = sizeof(void*) - 1;

   LevelN* visited[_3_or_7];
   UWord   visitedIx[_3_or_7];
   Int     nVisited = 0;

   vg_assert(swa);
   levelN = swa->root;

   
   for (i = _3_or_7; i >= 1; i--) {
      
      if (!levelN) return False;
      vg_assert(levelN->level == i);
      vg_assert(levelN->nInUse > 0);
      ix = (key >> (i*8)) & 0xFF;
      visited[nVisited]     = levelN;
      visitedIx[nVisited++] = ix;
      levelN = levelN->child[ix];
   }

   
   level0 = (Level0*)levelN;
   if (!level0) return False;
   vg_assert(level0->magic == Level0_MAGIC);
   vg_assert(level0->nInUse > 0);
   ix = key & 0xFF;

   if (swa_bitarray_read_then_clear(level0->inUse, ix) == 0)
      return False;

   *oldK = key; 
   *oldV = level0->words[ix];

   level0->nInUse--;
   if (level0->nInUse > 0)
      return True;

   vg_assert(nVisited == _3_or_7);
   swa->dealloc( level0 );

   
   for (i = 1; i <= _3_or_7; i++) {
      
      nVisited--;
      vg_assert(visited[nVisited]->child[ visitedIx[nVisited] ]);
      visited[nVisited]->child[ visitedIx[nVisited] ] = NULL;
      visited[nVisited]->nInUse--;
      vg_assert(visited[nVisited]->nInUse >= 0);
      if (visited[nVisited]->nInUse > 0)
         return True;
      swa->dealloc(visited[nVisited]);
   }

   vg_assert(nVisited == 0);
   swa->root = NULL;
   return True;
}


static UWord swa_sizeSWA_wrk ( void* nd )
{
   Int   i;
   if (*(UWord*)nd == LevelN_MAGIC) {
      UWord sum = 0;
      LevelN* levelN = (LevelN*)nd;
      for (i = 0; i < 256; i++) {
         if (levelN->child[i]) {
            sum += swa_sizeSWA_wrk( levelN->child[i] );
         }
      }
      return sum;
   } else {
      Level0* level0;
      vg_assert(*(UWord*)nd == Level0_MAGIC);
      level0 = (Level0*)nd;
      return level0->nInUse;
   }
}
UWord VG_(sizeSWA) ( SparseWA* swa )
{
   if (swa->root)
      return swa_sizeSWA_wrk ( swa->root );
   else
      return 0;
}



