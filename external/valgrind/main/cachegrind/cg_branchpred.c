

/*
   This file is part of Cachegrind, a Valgrind tool for cache
   profiling programs.

   Copyright (C) 2002-2012 Nicholas Nethercote
      njn@valgrind.org

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



#if defined(VGA_ppc32) || defined(VGA_ppc64) || defined(VGA_arm) \
    || defined(VGA_mips32)
#  define N_IADDR_LO_ZERO_BITS 2
#elif defined(VGA_x86) || defined(VGA_amd64)
#  define N_IADDR_LO_ZERO_BITS 0
#elif defined(VGA_s390x)
#  define N_IADDR_LO_ZERO_BITS 1
#else
#  error "Unsupported architecture"
#endif


/* Get a taken/not-taken prediction for the instruction (presumably a
   conditional branch) at instr_addr.  Once that's done, update the
   predictor state based on whether or not it was actually taken, as
   indicated by 'taken'.  Finally, return 1 for a mispredict and 0 for
   a successful predict.

   The predictor is an array of 16k (== 2^14) 2-bit saturating
   counters.  Given the address of the branch instruction, the array
   index to use is computed both from the low order bits of the branch
   instruction's address, and the global history - that is, from the
   taken/not-taken behaviour of the most recent few branches.  This
   makes the predictor able to correlate this branch's behaviour with
   that of other branches. 

   TODO: use predictor written by someone who understands this stuff.
   Perhaps it would be better to move to a standard GShare predictor
   and/or tournament predictor.
*/
#define N_HIST_BITS 7
#define N_IADD_BITS 7

#define N_BITS     (N_HIST_BITS + N_IADD_BITS)
#define N_COUNTERS (1 << N_BITS)

static UWord shift_register = 0;   
static UChar counters[N_COUNTERS]; 


static ULong do_cond_branch_predict ( Addr instr_addr, Word takenW )
{
   UWord indx;
   Bool  predicted_taken, actually_taken, mispredict;

   const UWord hist_mask = (1 << N_HIST_BITS) - 1;
   const UWord iadd_mask = (1 << N_IADD_BITS) - 1;
         UWord hist_bits = shift_register & hist_mask;
         UWord iadd_bits = (instr_addr >> N_IADDR_LO_ZERO_BITS)
                           & iadd_mask;

   tl_assert(hist_bits <= hist_mask);
   tl_assert(iadd_bits <= iadd_mask);
   indx = (hist_bits << N_IADD_BITS) | iadd_bits;
   tl_assert(indx < N_COUNTERS);
   if (0) VG_(printf)("index = %d\n", (Int)indx);

   tl_assert(takenW <= 1);
   predicted_taken = counters[ indx ] >= 2;
   actually_taken  = takenW > 0;

   mispredict = (actually_taken && (!predicted_taken))
                || ((!actually_taken) && predicted_taken);

   shift_register <<= 1;
   shift_register |= (actually_taken ? 1 : 0);

   if (actually_taken) {
      if (counters[indx] < 3)
         counters[indx]++;
   } else {
      if (counters[indx] > 0)
         counters[indx]--;
   }

   tl_assert(counters[indx] <= 3);

   return mispredict ? 1 : 0;
}


#define N_BTAC_BITS 9
#define N_BTAC      (1 << N_BTAC_BITS)
static Addr btac[N_BTAC]; 

static ULong do_ind_branch_predict ( Addr instr_addr, Addr actual )
{
   Bool mispredict;
   const UWord mask = (1 << N_BTAC_BITS) - 1;
         UWord indx = (instr_addr >> N_IADDR_LO_ZERO_BITS) 
                      & mask;
   tl_assert(indx < N_BTAC);
   mispredict = btac[indx] != actual;
   btac[indx] = actual;
   return mispredict ? 1 : 0;
}



