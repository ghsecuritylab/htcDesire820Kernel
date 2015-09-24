
/*
  This file is part of DRD, a thread error detector.

  Copyright (C) 2006-2012 Bart Van Assche <bvanassche@acm.org>.

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


#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <assert.h>         
#include <errno.h>
#include <pthread.h>        
#include <semaphore.h>      
#include <stdint.h>         
#include <stdio.h>          
#include <stdlib.h>         
#include <unistd.h>         
#include "config.h"         
#ifdef HAVE_USABLE_LINUX_FUTEX_H
#include <asm/unistd.h>     
#include <linux/futex.h>    
#ifndef FUTEX_PRIVATE_FLAG
#define FUTEX_PRIVATE_FLAG 0
#endif
#endif
#include "drd_basics.h"     
#include "drd_clientreq.h"
#include "pub_tool_redir.h" 



#ifdef VGO_darwin
static int never_true;
#define PTH_FUNC(ret_ty, zf, implf, argl_decl, argl)                    \
   ret_ty VG_WRAP_FUNCTION_ZZ(VG_Z_LIBPTHREAD_SONAME,zf) argl_decl;     \
   ret_ty VG_WRAP_FUNCTION_ZZ(VG_Z_LIBPTHREAD_SONAME,zf) argl_decl      \
   {									\
      ret_ty pth_func_result = implf argl;				\
         \
      	\
      if (never_true)							\
	 fflush(stdout);						\
      return pth_func_result;						\
   }
#else
#define PTH_FUNC(ret_ty, zf, implf, argl_decl, argl)                    \
   ret_ty VG_WRAP_FUNCTION_ZZ(VG_Z_LIBPTHREAD_SONAME,zf) argl_decl;     \
   ret_ty VG_WRAP_FUNCTION_ZZ(VG_Z_LIBPTHREAD_SONAME,zf) argl_decl      \
   { return implf argl; }
#endif

#define PTH_FUNCS(ret_ty, zf, implf, argl_decl, argl)           \
   PTH_FUNC(ret_ty, zf, implf, argl_decl, argl);                \
   PTH_FUNC(ret_ty, zf ## ZAZa, implf, argl_decl, argl);        \
   PTH_FUNC(ret_ty, zf ## ZDZa, implf, argl_decl, argl);

#undef __always_inline 
#if __GNUC__ > 3 || __GNUC__ == 3 && __GNUC_MINOR__ >= 2
#define __always_inline __inline__ __attribute__((always_inline))
#else
#define __always_inline __inline__
#endif


typedef struct {
   pthread_mutex_t mutex;
   int counter;
   int waiters;
} DrdSema;

typedef struct
{
   void* (*start)(void*);
   void* arg;
   int   detachstate;
   DrdSema* wrapper_started;
} DrdPosixThreadArgs;



static void DRD_(init)(void) __attribute__((constructor));
static void DRD_(check_threading_library)(void);
static void DRD_(set_main_thread_state)(void);
static void DRD_(sema_init)(DrdSema* sema);
static void DRD_(sema_destroy)(DrdSema* sema);
static void DRD_(sema_down)(DrdSema* sema);
static void DRD_(sema_up)(DrdSema* sema);



static void DRD_(init)(void)
{
   DRD_(check_threading_library)();
   DRD_(set_main_thread_state)();
}

static void DRD_(sema_init)(DrdSema* sema)
{
   DRD_IGNORE_VAR(sema->counter);
   pthread_mutex_init(&sema->mutex, NULL);
   sema->counter = 0;
   sema->waiters = 0;
}

static void DRD_(sema_destroy)(DrdSema* sema)
{
   pthread_mutex_destroy(&sema->mutex);
}

static void DRD_(sema_down)(DrdSema* sema)
{
   int res = ENOSYS;

   pthread_mutex_lock(&sema->mutex);
   if (sema->counter == 0) {
      sema->waiters++;
      while (sema->counter == 0) {
         pthread_mutex_unlock(&sema->mutex);
#ifdef HAVE_USABLE_LINUX_FUTEX_H
         if (syscall(__NR_futex, (UWord)&sema->counter,
                     FUTEX_WAIT | FUTEX_PRIVATE_FLAG, 0) == 0)
            res = 0;
         else
            res = errno;
#endif
         if (res != 0 && res != EWOULDBLOCK)
            sched_yield();
         pthread_mutex_lock(&sema->mutex);
      }
      sema->waiters--;
   }
   sema->counter--;
   pthread_mutex_unlock(&sema->mutex);
}

static void DRD_(sema_up)(DrdSema* sema)
{
   pthread_mutex_lock(&sema->mutex);
   sema->counter++;
#ifdef HAVE_USABLE_LINUX_FUTEX_H
   if (sema->waiters > 0)
      syscall(__NR_futex, (UWord)&sema->counter,
              FUTEX_WAKE | FUTEX_PRIVATE_FLAG, 1);
#endif
   pthread_mutex_unlock(&sema->mutex);
}

static MutexT DRD_(pthread_to_drd_mutex_type)(const int kind)
{
   if (kind == PTHREAD_MUTEX_RECURSIVE)
      return mutex_type_recursive_mutex;
   else if (kind == PTHREAD_MUTEX_ERRORCHECK)
      return mutex_type_errorcheck_mutex;
   else if (kind == PTHREAD_MUTEX_NORMAL)
      return mutex_type_default_mutex;
   else if (kind == PTHREAD_MUTEX_DEFAULT)
      return mutex_type_default_mutex;
#if defined(HAVE_PTHREAD_MUTEX_ADAPTIVE_NP)
   else if (kind == PTHREAD_MUTEX_ADAPTIVE_NP)
      return mutex_type_default_mutex;
#endif
   else
   {
      return mutex_type_invalid_mutex;
   }
}

#define IS_ALIGNED(p) (((uintptr_t)(p) & (sizeof(*(p)) - 1)) == 0)

static __always_inline MutexT DRD_(mutex_type)(pthread_mutex_t* mutex)
{
#if defined(HAVE_PTHREAD_MUTEX_T__M_KIND)
   
   if (IS_ALIGNED(&mutex->__m_kind))
   {
      const int kind = mutex->__m_kind & 3;
      return DRD_(pthread_to_drd_mutex_type)(kind);
   }
#elif defined(HAVE_PTHREAD_MUTEX_T__DATA__KIND)
   
   if (IS_ALIGNED(&mutex->__data.__kind))
   {
      const int kind = mutex->__data.__kind & 3;
      return DRD_(pthread_to_drd_mutex_type)(kind);
   }
#else
#endif
   return mutex_type_unknown;
}

static void DRD_(set_joinable)(const pthread_t tid, const int joinable)
{
   assert(joinable == 0 || joinable == 1);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__SET_JOINABLE,
                                   tid, joinable, 0, 0, 0);
}

static __always_inline void DRD_(entering_pthread_create)(void)
{
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__ENTERING_PTHREAD_CREATE,
                                   0, 0, 0, 0, 0);
}

static __always_inline void DRD_(left_pthread_create)(void)
{
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__LEFT_PTHREAD_CREATE,
                                   0, 0, 0, 0, 0);
}

static void* DRD_(thread_wrapper)(void* arg)
{
   DrdPosixThreadArgs* arg_ptr;
   DrdPosixThreadArgs arg_copy;

   arg_ptr = (DrdPosixThreadArgs*)arg;
   arg_copy = *arg_ptr;

   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__SET_PTHREADID,
                                   pthread_self(), 0, 0, 0, 0);

   DRD_(set_joinable)(pthread_self(),
                      arg_copy.detachstate == PTHREAD_CREATE_JOINABLE);

   DRD_(sema_up)(arg_copy.wrapper_started);

   return (arg_copy.start)(arg_copy.arg);
}

static int DRD_(detected_linuxthreads)(void)
{
#if defined(linux)
#if defined(_CS_GNU_LIBPTHREAD_VERSION)
   
   char buffer[256];
   unsigned len;
   len = confstr(_CS_GNU_LIBPTHREAD_VERSION, buffer, sizeof(buffer));
   assert(len <= sizeof(buffer));
   return len > 0 && buffer[0] == 'l';
#else
   
   return 1;
#endif
#else
   
   return 0;
#endif
}

static void DRD_(check_threading_library)(void)
{
   if (DRD_(detected_linuxthreads)())
   {
      if (getenv("LD_ASSUME_KERNEL"))
      {
         fprintf(stderr,
"Detected the LinuxThreads threading library. Sorry, but DRD only supports\n"
"the newer NPTL (Native POSIX Threads Library). Please try to rerun DRD\n"
"after having unset the environment variable LD_ASSUME_KERNEL. Giving up.\n"
);
      }
      else
      {
         fprintf(stderr,
"Detected the LinuxThreads threading library. Sorry, but DRD only supports\n"
"the newer NPTL (Native POSIX Threads Library). Please try to rerun DRD\n"
"after having upgraded to a newer version of your Linux distribution.\n"
"Giving up.\n"
);
      }
      abort();
   }
}

static void DRD_(set_main_thread_state)(void)
{
   
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__SET_PTHREADID,
                                   pthread_self(), 0, 0, 0, 0);
}


static __always_inline
int pthread_create_intercept(pthread_t* thread, const pthread_attr_t* attr,
                             void* (*start)(void*), void* arg)
{
   int    ret;
   OrigFn fn;
   DrdSema wrapper_started;
   DrdPosixThreadArgs thread_args;

   VALGRIND_GET_ORIG_FN(fn);

   DRD_(sema_init)(&wrapper_started);
   thread_args.start           = start;
   thread_args.arg             = arg;
   thread_args.wrapper_started = &wrapper_started;
   thread_args.detachstate = PTHREAD_CREATE_JOINABLE;
   if (attr)
   {
      if (pthread_attr_getdetachstate(attr, &thread_args.detachstate) != 0)
         assert(0);
   }
   assert(thread_args.detachstate == PTHREAD_CREATE_JOINABLE
          || thread_args.detachstate == PTHREAD_CREATE_DETACHED);

   DRD_(entering_pthread_create)();
   CALL_FN_W_WWWW(ret, fn, thread, attr, DRD_(thread_wrapper), &thread_args);
   DRD_(left_pthread_create)();

   if (ret == 0) {
      
      DRD_(sema_down)(&wrapper_started);
   }

   DRD_(sema_destroy)(&wrapper_started);

   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__DRD_START_NEW_SEGMENT,
                                   pthread_self(), 0, 0, 0, 0);

   return ret;
}

PTH_FUNCS(int, pthreadZucreate, pthread_create_intercept,
          (pthread_t *thread, const pthread_attr_t *attr,
           void *(*start) (void *), void *arg),
          (thread, attr, start, arg));

static __always_inline
int pthread_join_intercept(pthread_t pt_joinee, void **thread_return)
{
   int      ret;
   OrigFn   fn;

   VALGRIND_GET_ORIG_FN(fn);
   ANNOTATE_IGNORE_READS_AND_WRITES_BEGIN();
   CALL_FN_W_WW(ret, fn, pt_joinee, thread_return);
   if (ret == 0)
   {
      VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_THREAD_JOIN,
                                      pt_joinee, 0, 0, 0, 0);
   }
   ANNOTATE_IGNORE_READS_AND_WRITES_END();
   return ret;
}

PTH_FUNCS(int, pthreadZujoin, pthread_join_intercept,
          (pthread_t pt_joinee, void **thread_return),
          (pt_joinee, thread_return));

static __always_inline
int pthread_detach_intercept(pthread_t pt_thread)
{
   int ret;
   OrigFn fn;

   VALGRIND_GET_ORIG_FN(fn);
   CALL_FN_W_W(ret, fn, pt_thread);
   DRD_(set_joinable)(pt_thread, 0);

   return ret;
}

PTH_FUNCS(int, pthreadZudetach, pthread_detach_intercept,
          (pthread_t thread), (thread));

#if 0

static __always_inline
int pthread_cancel_intercept(pthread_t pt_thread)
{
   int ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_THREAD_CANCEL,
                                   pt_thread, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, pt_thread);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_THREAD_CANCEL,
                                   pt_thread, ret==0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZucancel, pthread_cancel_intercept,
          (pthread_t thread), (thread))
#endif

static __always_inline
int pthread_once_intercept(pthread_once_t *once_control,
                           void (*init_routine)(void))
{
   int ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   DRD_IGNORE_VAR(*once_control);
   ANNOTATE_IGNORE_READS_AND_WRITES_BEGIN();
   CALL_FN_W_WW(ret, fn, once_control, init_routine);
   ANNOTATE_IGNORE_READS_AND_WRITES_END();
   DRD_STOP_IGNORING_VAR(*once_control);
   return ret;
}

PTH_FUNCS(int, pthreadZuonce, pthread_once_intercept,
          (pthread_once_t *once_control, void (*init_routine)(void)),
          (once_control, init_routine));

static __always_inline
int pthread_mutex_init_intercept(pthread_mutex_t *mutex,
                                 const pthread_mutexattr_t* attr)
{
   int ret;
   OrigFn fn;
   int mt;
   VALGRIND_GET_ORIG_FN(fn);
   mt = PTHREAD_MUTEX_DEFAULT;
   if (attr)
      pthread_mutexattr_gettype(attr, &mt);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_MUTEX_INIT,
                                   mutex, DRD_(pthread_to_drd_mutex_type)(mt),
                                   0, 0, 0);
   CALL_FN_W_WW(ret, fn, mutex, attr);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_MUTEX_INIT,
                                   mutex, 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZumutexZuinit, pthread_mutex_init_intercept,
          (pthread_mutex_t *mutex, const pthread_mutexattr_t* attr),
          (mutex, attr));

static __always_inline
int pthread_mutex_destroy_intercept(pthread_mutex_t* mutex)
{
   int ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_MUTEX_DESTROY,
                                   mutex, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, mutex);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_MUTEX_DESTROY,
                                   mutex, DRD_(mutex_type)(mutex), 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZumutexZudestroy, pthread_mutex_destroy_intercept,
          (pthread_mutex_t *mutex), (mutex));

static __always_inline
int pthread_mutex_lock_intercept(pthread_mutex_t* mutex)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_MUTEX_LOCK,
                                   mutex, DRD_(mutex_type)(mutex), 0, 0, 0);
   CALL_FN_W_W(ret, fn, mutex);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_MUTEX_LOCK,
                                   mutex, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZumutexZulock, pthread_mutex_lock_intercept,
          (pthread_mutex_t *mutex), (mutex));

static __always_inline
int pthread_mutex_trylock_intercept(pthread_mutex_t* mutex)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_MUTEX_LOCK,
                                   mutex, DRD_(mutex_type)(mutex), 1, 0, 0);
   CALL_FN_W_W(ret, fn, mutex);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_MUTEX_LOCK,
                                   mutex, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZumutexZutrylock, pthread_mutex_trylock_intercept,
          (pthread_mutex_t *mutex), (mutex));

static __always_inline
int pthread_mutex_timedlock_intercept(pthread_mutex_t *mutex,
                                      const struct timespec *abs_timeout)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_MUTEX_LOCK,
                                   mutex, DRD_(mutex_type)(mutex), 0, 0, 0);
   CALL_FN_W_WW(ret, fn, mutex, abs_timeout);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_MUTEX_LOCK,
                                   mutex, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZumutexZutimedlock, pthread_mutex_timedlock_intercept,
          (pthread_mutex_t *mutex, const struct timespec *abs_timeout),
          (mutex, abs_timeout));

static __always_inline
int pthread_mutex_unlock_intercept(pthread_mutex_t *mutex)
{
   int ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_MUTEX_UNLOCK,
                                   mutex, DRD_(mutex_type)(mutex), 0, 0, 0);
   CALL_FN_W_W(ret, fn, mutex);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_MUTEX_UNLOCK,
                                   mutex, 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZumutexZuunlock, pthread_mutex_unlock_intercept,
          (pthread_mutex_t *mutex), (mutex));

static __always_inline
int pthread_cond_init_intercept(pthread_cond_t* cond,
                                const pthread_condattr_t* attr)
{
   int ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_COND_INIT,
                                   cond, 0, 0, 0, 0);
   CALL_FN_W_WW(ret, fn, cond, attr);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_COND_INIT,
                                   cond, 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZucondZuinit, pthread_cond_init_intercept,
          (pthread_cond_t* cond, const pthread_condattr_t* attr),
          (cond, attr));

static __always_inline
int pthread_cond_destroy_intercept(pthread_cond_t* cond)
{
   int ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_COND_DESTROY,
                                   cond, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, cond);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_COND_DESTROY,
                                   cond, 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZucondZudestroy, pthread_cond_destroy_intercept,
          (pthread_cond_t* cond), (cond));

static __always_inline
int pthread_cond_wait_intercept(pthread_cond_t *cond, pthread_mutex_t *mutex)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_COND_WAIT,
                                   cond, mutex, DRD_(mutex_type)(mutex), 0, 0);
   CALL_FN_W_WW(ret, fn, cond, mutex);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_COND_WAIT,
                                   cond, mutex, 1, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZucondZuwait, pthread_cond_wait_intercept,
          (pthread_cond_t *cond, pthread_mutex_t *mutex),
          (cond, mutex));

static __always_inline
int pthread_cond_timedwait_intercept(pthread_cond_t *cond,
                                     pthread_mutex_t *mutex,
                                     const struct timespec* abstime)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_COND_WAIT,
                                   cond, mutex, DRD_(mutex_type)(mutex), 0, 0);
   CALL_FN_W_WWW(ret, fn, cond, mutex, abstime);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_COND_WAIT,
                                   cond, mutex, 1, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZucondZutimedwait, pthread_cond_timedwait_intercept,
          (pthread_cond_t *cond, pthread_mutex_t *mutex,
           const struct timespec* abstime),
          (cond, mutex, abstime));


static __always_inline
int pthread_cond_signal_intercept(pthread_cond_t* cond)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_COND_SIGNAL,
                                   cond, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, cond);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_COND_SIGNAL,
                                   cond, 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZucondZusignal, pthread_cond_signal_intercept,
          (pthread_cond_t* cond), (cond));

static __always_inline
int pthread_cond_broadcast_intercept(pthread_cond_t* cond)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_COND_BROADCAST,
                                   cond, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, cond);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_COND_BROADCAST,
                                   cond, 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZucondZubroadcast, pthread_cond_broadcast_intercept,
          (pthread_cond_t* cond), (cond));

#if defined(HAVE_PTHREAD_SPIN_LOCK)
static __always_inline
int pthread_spin_init_intercept(pthread_spinlock_t *spinlock, int pshared)
{
   int ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_SPIN_INIT_OR_UNLOCK,
                                   spinlock, 0, 0, 0, 0);
   CALL_FN_W_WW(ret, fn, spinlock, pshared);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_SPIN_INIT_OR_UNLOCK,
                                   spinlock, 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZuspinZuinit, pthread_spin_init_intercept,
          (pthread_spinlock_t *spinlock, int pshared), (spinlock, pshared));

static __always_inline
int pthread_spin_destroy_intercept(pthread_spinlock_t *spinlock)
{
   int ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_MUTEX_DESTROY,
                                   spinlock, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, spinlock);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_MUTEX_DESTROY,
                                   spinlock, mutex_type_spinlock, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZuspinZudestroy, pthread_spin_destroy_intercept,
          (pthread_spinlock_t *spinlock), (spinlock));

static __always_inline
int pthread_spin_lock_intercept(pthread_spinlock_t *spinlock)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_MUTEX_LOCK,
                                   spinlock, mutex_type_spinlock, 0, 0, 0);
   CALL_FN_W_W(ret, fn, spinlock);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_MUTEX_LOCK,
                                   spinlock, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZuspinZulock, pthread_spin_lock_intercept,
          (pthread_spinlock_t *spinlock), (spinlock));

static __always_inline
int pthread_spin_trylock_intercept(pthread_spinlock_t *spinlock)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_MUTEX_LOCK,
                                   spinlock, mutex_type_spinlock, 0, 0, 0);
   CALL_FN_W_W(ret, fn, spinlock);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_MUTEX_LOCK,
                                   spinlock, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZuspinZutrylock, pthread_spin_trylock_intercept,
          (pthread_spinlock_t *spinlock), (spinlock));

static __always_inline
int pthread_spin_unlock_intercept(pthread_spinlock_t *spinlock)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_SPIN_INIT_OR_UNLOCK,
                                   spinlock, mutex_type_spinlock, 0, 0, 0);
   CALL_FN_W_W(ret, fn, spinlock);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_SPIN_INIT_OR_UNLOCK,
                                   spinlock, 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZuspinZuunlock, pthread_spin_unlock_intercept,
          (pthread_spinlock_t *spinlock), (spinlock));
#endif   


#if defined(HAVE_PTHREAD_BARRIER_INIT)
static __always_inline
int pthread_barrier_init_intercept(pthread_barrier_t* barrier,
                                   const pthread_barrierattr_t* attr,
                                   unsigned count)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_BARRIER_INIT,
                                   barrier, pthread_barrier, count, 0, 0);
   CALL_FN_W_WWW(ret, fn, barrier, attr, count);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_BARRIER_INIT,
                                   barrier, pthread_barrier, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZubarrierZuinit, pthread_barrier_init_intercept,
          (pthread_barrier_t* barrier, const pthread_barrierattr_t* attr,
           unsigned count), (barrier, attr, count));

static __always_inline
int pthread_barrier_destroy_intercept(pthread_barrier_t* barrier)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_BARRIER_DESTROY,
                                   barrier, pthread_barrier, 0, 0, 0);
   CALL_FN_W_W(ret, fn, barrier);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_BARRIER_DESTROY,
                                   barrier, pthread_barrier, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZubarrierZudestroy, pthread_barrier_destroy_intercept,
          (pthread_barrier_t* barrier), (barrier));

static __always_inline
int pthread_barrier_wait_intercept(pthread_barrier_t* barrier)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_BARRIER_WAIT,
                                   barrier, pthread_barrier, 0, 0, 0);
   CALL_FN_W_W(ret, fn, barrier);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_BARRIER_WAIT,
                              barrier, pthread_barrier,
                              ret == 0 || ret == PTHREAD_BARRIER_SERIAL_THREAD,
                              ret == PTHREAD_BARRIER_SERIAL_THREAD, 0);
   return ret;
}

PTH_FUNCS(int, pthreadZubarrierZuwait, pthread_barrier_wait_intercept,
          (pthread_barrier_t* barrier), (barrier));
#endif   


static __always_inline
int sem_init_intercept(sem_t *sem, int pshared, unsigned int value)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_SEM_INIT,
                                   sem, pshared, value, 0, 0);
   CALL_FN_W_WWW(ret, fn, sem, pshared, value);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_SEM_INIT,
                                   sem, 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, semZuinit, sem_init_intercept,
          (sem_t *sem, int pshared, unsigned int value), (sem, pshared, value));

static __always_inline
int sem_destroy_intercept(sem_t *sem)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_SEM_DESTROY,
                                   sem, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, sem);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_SEM_DESTROY,
                                   sem, 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, semZudestroy, sem_destroy_intercept, (sem_t *sem), (sem));

static __always_inline
sem_t* sem_open_intercept(const char *name, int oflag, mode_t mode,
                          unsigned int value)
{
   sem_t *ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_SEM_OPEN,
                                   name, oflag, mode, value, 0);
   CALL_FN_W_WWWW(ret, fn, name, oflag, mode, value);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_SEM_OPEN,
                                   ret != SEM_FAILED ? ret : 0,
                                   name, oflag, mode, value);
   return ret;
}

PTH_FUNCS(sem_t *, semZuopen, sem_open_intercept,
          (const char *name, int oflag, mode_t mode, unsigned int value),
          (name, oflag, mode, value));

static __always_inline int sem_close_intercept(sem_t *sem)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_SEM_CLOSE,
                                   sem, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, sem);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_SEM_CLOSE,
                                   sem, 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, semZuclose, sem_close_intercept, (sem_t *sem), (sem));

static __always_inline int sem_wait_intercept(sem_t *sem)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_SEM_WAIT,
                                   sem, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, sem);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_SEM_WAIT,
                                   sem, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, semZuwait, sem_wait_intercept, (sem_t *sem), (sem));

static __always_inline int sem_trywait_intercept(sem_t *sem)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_SEM_WAIT,
                                   sem, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, sem);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_SEM_WAIT,
                                   sem, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, semZutrywait, sem_trywait_intercept, (sem_t *sem), (sem));

static __always_inline
int sem_timedwait_intercept(sem_t *sem, const struct timespec *abs_timeout)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_SEM_WAIT,
                                   sem, 0, 0, 0, 0);
   CALL_FN_W_WW(ret, fn, sem, abs_timeout);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_SEM_WAIT,
                                   sem, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, semZutimedwait, sem_timedwait_intercept,
          (sem_t *sem, const struct timespec *abs_timeout),
          (sem, abs_timeout));

static __always_inline int sem_post_intercept(sem_t *sem)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_SEM_POST,
                                   sem, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, sem);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_SEM_POST,
                                   sem, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int, semZupost, sem_post_intercept, (sem_t *sem), (sem));

#if defined(HAVE_PTHREAD_RWLOCK_T)

static __always_inline
int pthread_rwlock_init_intercept(pthread_rwlock_t* rwlock,
                                  const pthread_rwlockattr_t* attr)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_RWLOCK_INIT,
                                   rwlock, 0, 0, 0, 0);
   CALL_FN_W_WW(ret, fn, rwlock, attr);
   return ret;
}

PTH_FUNCS(int,
          pthreadZurwlockZuinit, pthread_rwlock_init_intercept,
          (pthread_rwlock_t* rwlock, const pthread_rwlockattr_t* attr),
          (rwlock, attr));

static __always_inline
int pthread_rwlock_destroy_intercept(pthread_rwlock_t* rwlock)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   CALL_FN_W_W(ret, fn, rwlock);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_RWLOCK_DESTROY,
                                   rwlock, 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int,
          pthreadZurwlockZudestroy, pthread_rwlock_destroy_intercept,
          (pthread_rwlock_t* rwlock), (rwlock));

static __always_inline
int pthread_rwlock_rdlock_intercept(pthread_rwlock_t* rwlock)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_RWLOCK_RDLOCK,
                                   rwlock, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, rwlock);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_RWLOCK_RDLOCK,
                                   rwlock, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int,
          pthreadZurwlockZurdlock, pthread_rwlock_rdlock_intercept,
          (pthread_rwlock_t* rwlock), (rwlock));

static __always_inline
int pthread_rwlock_wrlock_intercept(pthread_rwlock_t* rwlock)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_RWLOCK_WRLOCK,
                                   rwlock, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, rwlock);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_RWLOCK_WRLOCK,
                                   rwlock, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int,
          pthreadZurwlockZuwrlock, pthread_rwlock_wrlock_intercept,
          (pthread_rwlock_t* rwlock), (rwlock));

static __always_inline
int pthread_rwlock_timedrdlock_intercept(pthread_rwlock_t* rwlock)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_RWLOCK_RDLOCK,
                                   rwlock, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, rwlock);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_RWLOCK_RDLOCK,
                                   rwlock, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int,
          pthreadZurwlockZutimedrdlock, pthread_rwlock_timedrdlock_intercept,
          (pthread_rwlock_t* rwlock), (rwlock));

static __always_inline
int pthread_rwlock_timedwrlock_intercept(pthread_rwlock_t* rwlock)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_RWLOCK_WRLOCK,
                                   rwlock, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, rwlock);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_RWLOCK_WRLOCK,
                                   rwlock, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int,
          pthreadZurwlockZutimedwrlock, pthread_rwlock_timedwrlock_intercept,
          (pthread_rwlock_t* rwlock), (rwlock));

static __always_inline
int pthread_rwlock_tryrdlock_intercept(pthread_rwlock_t* rwlock)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_RWLOCK_RDLOCK,
                                   rwlock, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, rwlock);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_RWLOCK_RDLOCK,
                                   rwlock, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int,
          pthreadZurwlockZutryrdlock, pthread_rwlock_tryrdlock_intercept,
          (pthread_rwlock_t* rwlock), (rwlock));

static __always_inline
int pthread_rwlock_trywrlock_intercept(pthread_rwlock_t* rwlock)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_RWLOCK_WRLOCK,
                                   rwlock, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, rwlock);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_RWLOCK_WRLOCK,
                                   rwlock, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int,
          pthreadZurwlockZutrywrlock, pthread_rwlock_trywrlock_intercept,
          (pthread_rwlock_t* rwlock), (rwlock));

static __always_inline
int pthread_rwlock_unlock_intercept(pthread_rwlock_t* rwlock)
{
   int   ret;
   OrigFn fn;
   VALGRIND_GET_ORIG_FN(fn);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__PRE_RWLOCK_UNLOCK,
                                   rwlock, 0, 0, 0, 0);
   CALL_FN_W_W(ret, fn, rwlock);
   VALGRIND_DO_CLIENT_REQUEST_STMT(VG_USERREQ__POST_RWLOCK_UNLOCK,
                                   rwlock, ret == 0, 0, 0, 0);
   return ret;
}

PTH_FUNCS(int,
          pthreadZurwlockZuunlock, pthread_rwlock_unlock_intercept,
          (pthread_rwlock_t* rwlock), (rwlock));

#endif 
