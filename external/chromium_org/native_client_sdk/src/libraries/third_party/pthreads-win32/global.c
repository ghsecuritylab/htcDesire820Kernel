/*
 * global.c
 *
 * Description:
 * This translation unit instantiates data associated with the implementation
 * as a whole.
 *
 * --------------------------------------------------------------------------
 *
 *      Pthreads-win32 - POSIX Threads Library for Win32
 *      Copyright(C) 1998 John E. Bossom
 *      Copyright(C) 1999,2005 Pthreads-win32 contributors
 * 
 *      Contact Email: rpj@callisto.canberra.edu.au
 * 
 *      The current list of contributors is contained
 *      in the file CONTRIBUTORS included with the source
 *      code distribution. The list can also be seen at the
 *      following World Wide Web location:
 *      http://sources.redhat.com/pthreads-win32/contributors.html
 * 
 *      This library is free software; you can redistribute it and/or
 *      modify it under the terms of the GNU Lesser General Public
 *      License as published by the Free Software Foundation; either
 *      version 2 of the License, or (at your option) any later version.
 * 
 *      This library is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *      Lesser General Public License for more details.
 * 
 *      You should have received a copy of the GNU Lesser General Public
 *      License along with this library in the file COPYING.LIB;
 *      if not, write to the Free Software Foundation, Inc.,
 *      59 Temple Place - Suite 330, Boston, MA 02111-1307, USA
 */

#include "pthread.h"
#include "implement.h"


int ptw32_processInitialized = PTW32_FALSE;
ptw32_thread_t * ptw32_threadReuseTop = PTW32_THREAD_REUSE_EMPTY;
ptw32_thread_t * ptw32_threadReuseBottom = PTW32_THREAD_REUSE_EMPTY;
pthread_key_t ptw32_selfThreadKey = NULL;
pthread_key_t ptw32_cleanupKey = NULL;
pthread_cond_t ptw32_cond_list_head = NULL;
pthread_cond_t ptw32_cond_list_tail = NULL;

int ptw32_concurrency = 0;

int ptw32_features = 0;

unsigned __int64 ptw32_threadSeqNumber = 0;

DWORD (*ptw32_register_cancelation) (PAPCFUNC, HANDLE, DWORD) = NULL;

ptw32_mcs_lock_t ptw32_thread_reuse_lock = 0;

ptw32_mcs_lock_t ptw32_mutex_test_init_lock = 0;

ptw32_mcs_lock_t ptw32_cond_test_init_lock = 0;

ptw32_mcs_lock_t ptw32_rwlock_test_init_lock = 0;

ptw32_mcs_lock_t ptw32_spinlock_test_init_lock = 0;

ptw32_mcs_lock_t ptw32_cond_list_lock = 0;

#if defined(_UWIN)
int pthread_count = 0;
#endif