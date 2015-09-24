/*
 * pthread_mutex_consistent.c
 *
 * Description:
 * This translation unit implements mutual exclusion (mutex) primitives.
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

#if !defined(_UWIN)
#endif
#include "pthread.h"
#include "implement.h"

INLINE
int
ptw32_robust_mutex_inherit(pthread_mutex_t * mutex)
{
  int result;
  pthread_mutex_t mx = *mutex;
  ptw32_robust_node_t* robust = mx->robustNode;

  switch ((LONG)PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG(
            (PTW32_INTERLOCKED_LONGPTR)&robust->stateInconsistent,
            (PTW32_INTERLOCKED_LONG)PTW32_ROBUST_INCONSISTENT,
            (PTW32_INTERLOCKED_LONG)-1 ))
    {
      case -1L:
          result = EOWNERDEAD;
          break;
      case (LONG)PTW32_ROBUST_NOTRECOVERABLE:
          result = ENOTRECOVERABLE;
          break;
      default:
          result = 0;
          break;
    }

  return result;
}


INLINE
void
ptw32_robust_mutex_add(pthread_mutex_t* mutex, pthread_t self)
{
  ptw32_robust_node_t** list;
  pthread_mutex_t mx = *mutex;
  ptw32_thread_t* tp = (ptw32_thread_t*)self.p;
  ptw32_robust_node_t* robust = mx->robustNode;

  list = &tp->robustMxList;
  mx->ownerThread = self;
  if (NULL == *list)
    {
      robust->prev = NULL;
      robust->next = NULL;
      *list = robust;
    }
  else
    {
      robust->prev = NULL;
      robust->next = *list;
      (*list)->prev = robust;
      *list = robust;
    }
}

INLINE
void
ptw32_robust_mutex_remove(pthread_mutex_t* mutex, ptw32_thread_t* otp)
{
  ptw32_robust_node_t** list;
  pthread_mutex_t mx = *mutex;
  ptw32_robust_node_t* robust = mx->robustNode;

  list = &(((ptw32_thread_t*)mx->ownerThread.p)->robustMxList);
  mx->ownerThread.p = otp;
  if (robust->next != NULL)
    {
      robust->next->prev = robust->prev;
    }
  if (robust->prev != NULL)
    {
      robust->prev->next = robust->next;
    }
  if (*list == robust)
    {
      *list = robust->next;
    }
}


int
pthread_mutex_consistent (pthread_mutex_t* mutex)
{
  pthread_mutex_t mx = *mutex;
  int result = 0;

  if (mx == NULL)
    {
      return EINVAL;
    }

  if (mx->kind >= 0
        || (PTW32_INTERLOCKED_LONG)PTW32_ROBUST_INCONSISTENT != PTW32_INTERLOCKED_COMPARE_EXCHANGE_LONG(
                                                (PTW32_INTERLOCKED_LONGPTR)&mx->robustNode->stateInconsistent,
                                                (PTW32_INTERLOCKED_LONG)PTW32_ROBUST_CONSISTENT,
                                                (PTW32_INTERLOCKED_LONG)PTW32_ROBUST_INCONSISTENT))
    {
      result = EINVAL;
    }

  return (result);
}

