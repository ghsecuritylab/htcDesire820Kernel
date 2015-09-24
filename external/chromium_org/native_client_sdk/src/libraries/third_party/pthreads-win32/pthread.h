/* This is an implementation of the threads API of POSIX 1003.1-2001.
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

#if !defined( PTHREAD_H )
#define PTHREAD_H

#define PTW32_VERSION 2,9,1,0
#define PTW32_VERSION_STRING "2, 9, 1, 0\0"


#if !defined( __CLEANUP_SEH ) && !defined( __CLEANUP_CXX ) && !defined( __CLEANUP_C )
# define __CLEANUP_C
#endif

#if defined( __CLEANUP_SEH ) && ( !defined( _MSC_VER ) && !defined(PTW32_RC_MSC))
#error ERROR [__FILE__, line __LINE__]: SEH is not supported for this compiler.
#endif

#if !defined(RC_INVOKED)

#undef PTW32_LEVEL

#if defined(_POSIX_SOURCE)
#define PTW32_LEVEL 0
#endif

#if defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 199309
#undef PTW32_LEVEL
#define PTW32_LEVEL 1
#endif

#if defined(INCLUDE_NP)
#undef PTW32_LEVEL
#define PTW32_LEVEL 2
#endif

#define PTW32_LEVEL_MAX 3

#if ( defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200112 )  || !defined(PTW32_LEVEL)
#define PTW32_LEVEL PTW32_LEVEL_MAX
#endif

#if defined(_UWIN)
#   define HAVE_STRUCT_TIMESPEC 1
#   define HAVE_SIGNAL_H        1
#   undef HAVE_PTW32_CONFIG_H
#   pragma comment(lib, "pthread")
#endif

/*
 * -------------------------------------------------------------
 *
 *
 * Module: pthread.h
 *
 * Purpose:
 *      Provides an implementation of PThreads based upon the
 *      standard:
 *
 *              POSIX 1003.1-2001
 *  and
 *    The Single Unix Specification version 3
 *
 *    (these two are equivalent)
 *
 *      in order to enhance code portability between Windows,
 *  various commercial Unix implementations, and Linux.
 *
 *      See the ANNOUNCE file for a full list of conforming
 *      routines and defined constants, and a list of missing
 *      routines and constants not defined in this implementation.
 *
 * Authors:
 *      There have been many contributors to this library.
 *      The initial implementation was contributed by
 *      John Bossom, and several others have provided major
 *      sections or revisions of parts of the implementation.
 *      Often significant effort has been contributed to
 *      find and fix important bugs and other problems to
 *      improve the reliability of the library, which sometimes
 *      is not reflected in the amount of code which changed as
 *      result.
 *      As much as possible, the contributors are acknowledged
 *      in the ChangeLog file in the source code distribution
 *      where their changes are noted in detail.
 *
 *      Contributors are listed in the CONTRIBUTORS file.
 *
 *      As usual, all bouquets go to the contributors, and all
 *      brickbats go to the project maintainer.
 *
 * Maintainer:
 *      The code base for this project is coordinated and
 *      eventually pre-tested, packaged, and made available by
 *
 *              Ross Johnson <rpj@callisto.canberra.edu.au>
 *
 * QA Testers:
 *      Ultimately, the library is tested in the real world by
 *      a host of competent and demanding scientists and
 *      engineers who report bugs and/or provide solutions
 *      which are then fixed or incorporated into subsequent
 *      versions of the library. Each time a bug is fixed, a
 *      test case is written to prove the fix and ensure
 *      that later changes to the code don't reintroduce the
 *      same error. The number of test cases is slowly growing
 *      and therefore so is the code reliability.
 *
 * Compliance:
 *      See the file ANNOUNCE for the list of implemented
 *      and not-implemented routines and defined options.
 *      Of course, these are all defined is this file as well.
 *
 * Web site:
 *      The source code and other information about this library
 *      are available from
 *
 *              http://sources.redhat.com/pthreads-win32/
 *
 * -------------------------------------------------------------
 */

#if (defined(__MINGW64__) || defined(__MINGW32__)) && defined(__cplusplus)
#define PTW32_INCLUDE_WINDOWS_H
#endif

#if defined(PTW32_INCLUDE_WINDOWS_H)
#include <windows.h>
#endif

#if defined(_MSC_VER) && _MSC_VER < 1300 || defined(__DMC__)
typedef unsigned long DWORD_PTR;
typedef unsigned long ULONG_PTR;
#endif

#if defined(HAVE_PTW32_CONFIG_H)
#include "config.h"
#endif 

#if !defined(NEED_FTIME)
#include <time.h>
#else 
#endif 

#if defined(HAVE_SIGNAL_H)
#include <signal.h>
#endif 

#include <limits.h>

enum {
  PTW32_FALSE = 0,
  PTW32_TRUE = (! PTW32_FALSE)
};


#if !defined(PTW32_CONFIG_H)
#  if defined(WINCE)
#    define NEED_ERRNO
#    define NEED_SEM
#  endif
#  if defined(__MINGW64__)
#    define HAVE_STRUCT_TIMESPEC
#    define HAVE_MODE_T
#  elif defined(_UWIN) || defined(__MINGW32__)
#    define HAVE_MODE_T
#  endif
#endif


#if PTW32_LEVEL >= PTW32_LEVEL_MAX
#if defined(NEED_ERRNO)
#include "need_errno.h"
#else
#include <errno.h>
#endif
#endif 

#if !defined(ENOTSUP)
#  define ENOTSUP 48   
#endif

#if !defined(ETIMEDOUT)
#  define ETIMEDOUT 10060 
#endif

#if !defined(ENOSYS)
#  define ENOSYS 140     
#endif

#if !defined(EDEADLK)
#  if defined(EDEADLOCK)
#    define EDEADLK EDEADLOCK
#  else
#    define EDEADLK 36     
#  endif
#endif

#if !defined(EOWNERDEAD)
#  define EOWNERDEAD 43
#endif
#if !defined(ENOTRECOVERABLE)
#  define ENOTRECOVERABLE 44
#endif

#include <sched.h>

#if !defined(PTW32_INCLUDE_WINDOWS_H)
#if !defined(HANDLE)
# define PTW32__HANDLE_DEF
# define HANDLE void *
#endif
#if !defined(DWORD)
# define PTW32__DWORD_DEF
# define DWORD unsigned long
#endif
#endif

#if !defined(HAVE_STRUCT_TIMESPEC)
#define HAVE_STRUCT_TIMESPEC
#if !defined(_TIMESPEC_DEFINED)
#define _TIMESPEC_DEFINED
struct timespec {
        time_t tv_sec;
        long tv_nsec;
};
#endif 
#endif 

#if !defined(SIG_BLOCK)
#define SIG_BLOCK 0
#endif 

#if !defined(SIG_UNBLOCK)
#define SIG_UNBLOCK 1
#endif 

#if !defined(SIG_SETMASK)
#define SIG_SETMASK 2
#endif 

#if defined(__cplusplus)
extern "C"
{
#endif                          


#undef _POSIX_THREADS
#define _POSIX_THREADS 200809L

#undef _POSIX_READER_WRITER_LOCKS
#define _POSIX_READER_WRITER_LOCKS 200809L

#undef _POSIX_SPIN_LOCKS
#define _POSIX_SPIN_LOCKS 200809L

#undef _POSIX_BARRIERS
#define _POSIX_BARRIERS 200809L

#undef _POSIX_THREAD_SAFE_FUNCTIONS
#define _POSIX_THREAD_SAFE_FUNCTIONS 200809L

#undef _POSIX_THREAD_ATTR_STACKSIZE
#define _POSIX_THREAD_ATTR_STACKSIZE 200809L

#undef _POSIX_THREAD_ATTR_STACKADDR
#define _POSIX_THREAD_ATTR_STACKADDR -1

#undef _POSIX_THREAD_PRIO_INHERIT
#define _POSIX_THREAD_PRIO_INHERIT -1

#undef _POSIX_THREAD_PRIO_PROTECT
#define _POSIX_THREAD_PRIO_PROTECT -1

#undef _POSIX_THREAD_PRIORITY_SCHEDULING
#define _POSIX_THREAD_PRIORITY_SCHEDULING -1

#undef _POSIX_THREAD_PROCESS_SHARED
#define _POSIX_THREAD_PROCESS_SHARED -1


#undef _POSIX_THREAD_DESTRUCTOR_ITERATIONS
#define _POSIX_THREAD_DESTRUCTOR_ITERATIONS     4

#undef PTHREAD_DESTRUCTOR_ITERATIONS
#define PTHREAD_DESTRUCTOR_ITERATIONS           _POSIX_THREAD_DESTRUCTOR_ITERATIONS

#undef _POSIX_THREAD_KEYS_MAX
#define _POSIX_THREAD_KEYS_MAX                  128

#undef PTHREAD_KEYS_MAX
#define PTHREAD_KEYS_MAX                        _POSIX_THREAD_KEYS_MAX

#undef PTHREAD_STACK_MIN
#define PTHREAD_STACK_MIN                       0

#undef _POSIX_THREAD_THREADS_MAX
#define _POSIX_THREAD_THREADS_MAX               64

  
#undef PTHREAD_THREADS_MAX
#define PTHREAD_THREADS_MAX                     2019

#undef _POSIX_SEM_NSEMS_MAX
#define _POSIX_SEM_NSEMS_MAX                    256

  
#undef SEM_NSEMS_MAX
#define SEM_NSEMS_MAX                           1024

#undef _POSIX_SEM_VALUE_MAX
#define _POSIX_SEM_VALUE_MAX                    32767

#undef SEM_VALUE_MAX
#define SEM_VALUE_MAX                           INT_MAX


#if defined(__GNUC__) && !defined(__declspec)
# error Please upgrade your GNU compiler to one that supports __declspec.
#endif

#if !defined(PTW32_STATIC_LIB)
#  if defined(PTW32_BUILD)
#    define PTW32_DLLPORT __declspec (dllexport)
#  else
#    define PTW32_DLLPORT __declspec (dllimport)
#  endif
#else
#  define PTW32_DLLPORT
#endif

#define PTW32_CDECL __cdecl

#if defined(_UWIN) && PTW32_LEVEL >= PTW32_LEVEL_MAX
#   include     <sys/types.h>
#else
typedef struct {
    void * p;                   
    unsigned int x;             
} ptw32_handle_t;

typedef ptw32_handle_t pthread_t;
typedef struct pthread_attr_t_ * pthread_attr_t;
typedef struct pthread_once_t_ pthread_once_t;
typedef struct pthread_key_t_ * pthread_key_t;
typedef struct pthread_mutex_t_ * pthread_mutex_t;
typedef struct pthread_mutexattr_t_ * pthread_mutexattr_t;
typedef struct pthread_cond_t_ * pthread_cond_t;
typedef struct pthread_condattr_t_ * pthread_condattr_t;
#endif
typedef struct pthread_rwlock_t_ * pthread_rwlock_t;
typedef struct pthread_rwlockattr_t_ * pthread_rwlockattr_t;
typedef struct pthread_spinlock_t_ * pthread_spinlock_t;
typedef struct pthread_barrier_t_ * pthread_barrier_t;
typedef struct pthread_barrierattr_t_ * pthread_barrierattr_t;


enum {
  PTHREAD_CREATE_JOINABLE       = 0,  
  PTHREAD_CREATE_DETACHED       = 1,

  PTHREAD_INHERIT_SCHED         = 0,
  PTHREAD_EXPLICIT_SCHED        = 1,  

  PTHREAD_SCOPE_PROCESS         = 0,
  PTHREAD_SCOPE_SYSTEM          = 1,  

  PTHREAD_CANCEL_ENABLE         = 0,  
  PTHREAD_CANCEL_DISABLE        = 1,

  PTHREAD_CANCEL_ASYNCHRONOUS   = 0,
  PTHREAD_CANCEL_DEFERRED       = 1,  

  PTHREAD_PROCESS_PRIVATE       = 0,
  PTHREAD_PROCESS_SHARED        = 1,

  PTHREAD_MUTEX_STALLED         = 0,  
  PTHREAD_MUTEX_ROBUST          = 1,

  PTHREAD_BARRIER_SERIAL_THREAD = -1
};

#define PTHREAD_CANCELED       ((void *)(size_t) -1)


#define PTHREAD_ONCE_INIT       { PTW32_FALSE, 0, 0, 0}

struct pthread_once_t_
{
  int          done;        
  void *       lock;
  int          reserved1;
  int          reserved2;
};


#define PTHREAD_MUTEX_INITIALIZER ((pthread_mutex_t)(size_t) -1)
#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER ((pthread_mutex_t)(size_t) -2)
#define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER ((pthread_mutex_t)(size_t) -3)

#define PTHREAD_RECURSIVE_MUTEX_INITIALIZER_NP PTHREAD_RECURSIVE_MUTEX_INITIALIZER
#define PTHREAD_ERRORCHECK_MUTEX_INITIALIZER_NP PTHREAD_ERRORCHECK_MUTEX_INITIALIZER

#define PTHREAD_COND_INITIALIZER ((pthread_cond_t)(size_t) -1)

#define PTHREAD_RWLOCK_INITIALIZER ((pthread_rwlock_t)(size_t) -1)

#define PTHREAD_SPINLOCK_INITIALIZER ((pthread_spinlock_t)(size_t) -1)


enum
{
  
  PTHREAD_MUTEX_FAST_NP,
  PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_TIMED_NP = PTHREAD_MUTEX_FAST_NP,
  PTHREAD_MUTEX_ADAPTIVE_NP = PTHREAD_MUTEX_FAST_NP,
  
  PTHREAD_MUTEX_NORMAL = PTHREAD_MUTEX_FAST_NP,
  PTHREAD_MUTEX_RECURSIVE = PTHREAD_MUTEX_RECURSIVE_NP,
  PTHREAD_MUTEX_ERRORCHECK = PTHREAD_MUTEX_ERRORCHECK_NP,
  PTHREAD_MUTEX_DEFAULT = PTHREAD_MUTEX_NORMAL
};


typedef struct ptw32_cleanup_t ptw32_cleanup_t;

#if defined(_MSC_VER)
#pragma warning( disable : 4229 )
#endif

typedef void (* PTW32_CDECL ptw32_cleanup_callback_t)(void *);

#if defined(_MSC_VER)
#pragma warning( default : 4229 )
#endif

struct ptw32_cleanup_t
{
  ptw32_cleanup_callback_t routine;
  void *arg;
  struct ptw32_cleanup_t *prev;
};

#if defined(__CLEANUP_SEH)

#define pthread_cleanup_push( _rout, _arg ) \
        { \
            ptw32_cleanup_t     _cleanup; \
            \
        _cleanup.routine        = (ptw32_cleanup_callback_t)(_rout); \
            _cleanup.arg        = (_arg); \
            __try \
              { \

#define pthread_cleanup_pop( _execute ) \
              } \
            __finally \
                { \
                    if( _execute || AbnormalTermination()) \
                      { \
                          (*(_cleanup.routine))( _cleanup.arg ); \
                      } \
                } \
        }

#else 

#if defined(__CLEANUP_C)


#define pthread_cleanup_push( _rout, _arg ) \
        { \
            ptw32_cleanup_t     _cleanup; \
            \
            ptw32_push_cleanup( &_cleanup, (ptw32_cleanup_callback_t) (_rout), (_arg) ); \

#define pthread_cleanup_pop( _execute ) \
            (void) ptw32_pop_cleanup( _execute ); \
        }

#else 

#if defined(__CLEANUP_CXX)


        class PThreadCleanup {
      ptw32_cleanup_callback_t cleanUpRout;
          void    *       obj;
          int             executeIt;

        public:
          PThreadCleanup() :
            cleanUpRout( 0 ),
            obj( 0 ),
            executeIt( 0 )
            {
            }

          PThreadCleanup(
             ptw32_cleanup_callback_t routine,
                         void    *       arg ) :
            cleanUpRout( routine ),
            obj( arg ),
            executeIt( 1 )
            {
            }

          ~PThreadCleanup()
            {
              if ( executeIt && ((void *) cleanUpRout != (void *) 0) )
                {
                  (void) (*cleanUpRout)( obj );
                }
            }

          void execute( int exec )
            {
              executeIt = exec;
            }
        };

#define pthread_cleanup_push( _rout, _arg ) \
        { \
            PThreadCleanup  cleanup((ptw32_cleanup_callback_t)(_rout), \
                                    (void *) (_arg) );

#define pthread_cleanup_pop( _execute ) \
            cleanup.execute( _execute ); \
        }

#else

#error ERROR [__FILE__, line __LINE__]: Cleanup type undefined.

#endif 

#endif 

#endif 


PTW32_DLLPORT int PTW32_CDECL pthread_attr_init (pthread_attr_t * attr);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_destroy (pthread_attr_t * attr);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_getdetachstate (const pthread_attr_t * attr,
                                         int *detachstate);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_getstackaddr (const pthread_attr_t * attr,
                                       void **stackaddr);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_getstacksize (const pthread_attr_t * attr,
                                       size_t * stacksize);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_setdetachstate (pthread_attr_t * attr,
                                         int detachstate);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_setstackaddr (pthread_attr_t * attr,
                                       void *stackaddr);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_setstacksize (pthread_attr_t * attr,
                                       size_t stacksize);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_getschedparam (const pthread_attr_t *attr,
                                        struct sched_param *param);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_setschedparam (pthread_attr_t *attr,
                                        const struct sched_param *param);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_setschedpolicy (pthread_attr_t *,
                                         int);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_getschedpolicy (const pthread_attr_t *,
                                         int *);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_setinheritsched(pthread_attr_t * attr,
                                         int inheritsched);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_getinheritsched(const pthread_attr_t * attr,
                                         int * inheritsched);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_setscope (pthread_attr_t *,
                                   int);

PTW32_DLLPORT int PTW32_CDECL pthread_attr_getscope (const pthread_attr_t *,
                                   int *);

PTW32_DLLPORT int PTW32_CDECL pthread_create (pthread_t * tid,
                            const pthread_attr_t * attr,
                            void *(PTW32_CDECL *start) (void *),
                            void *arg);

PTW32_DLLPORT int PTW32_CDECL pthread_detach (pthread_t tid);

PTW32_DLLPORT int PTW32_CDECL pthread_equal (pthread_t t1,
                           pthread_t t2);

PTW32_DLLPORT void PTW32_CDECL pthread_exit (void *value_ptr);

PTW32_DLLPORT int PTW32_CDECL pthread_join (pthread_t thread,
                          void **value_ptr);

PTW32_DLLPORT pthread_t PTW32_CDECL pthread_self (void);

PTW32_DLLPORT int PTW32_CDECL pthread_cancel (pthread_t thread);

PTW32_DLLPORT int PTW32_CDECL pthread_setcancelstate (int state,
                                    int *oldstate);

PTW32_DLLPORT int PTW32_CDECL pthread_setcanceltype (int type,
                                   int *oldtype);

PTW32_DLLPORT void PTW32_CDECL pthread_testcancel (void);

PTW32_DLLPORT int PTW32_CDECL pthread_once (pthread_once_t * once_control,
                          void (PTW32_CDECL *init_routine) (void));

#if PTW32_LEVEL >= PTW32_LEVEL_MAX
PTW32_DLLPORT ptw32_cleanup_t * PTW32_CDECL ptw32_pop_cleanup (int execute);

PTW32_DLLPORT void PTW32_CDECL ptw32_push_cleanup (ptw32_cleanup_t * cleanup,
                                 ptw32_cleanup_callback_t routine,
                                 void *arg);
#endif 

PTW32_DLLPORT int PTW32_CDECL pthread_key_create (pthread_key_t * key,
                                void (PTW32_CDECL *destructor) (void *));

PTW32_DLLPORT int PTW32_CDECL pthread_key_delete (pthread_key_t key);

PTW32_DLLPORT int PTW32_CDECL pthread_setspecific (pthread_key_t key,
                                 const void *value);

PTW32_DLLPORT void * PTW32_CDECL pthread_getspecific (pthread_key_t key);


PTW32_DLLPORT int PTW32_CDECL pthread_mutexattr_init (pthread_mutexattr_t * attr);

PTW32_DLLPORT int PTW32_CDECL pthread_mutexattr_destroy (pthread_mutexattr_t * attr);

PTW32_DLLPORT int PTW32_CDECL pthread_mutexattr_getpshared (const pthread_mutexattr_t
                                          * attr,
                                          int *pshared);

PTW32_DLLPORT int PTW32_CDECL pthread_mutexattr_setpshared (pthread_mutexattr_t * attr,
                                          int pshared);

PTW32_DLLPORT int PTW32_CDECL pthread_mutexattr_settype (pthread_mutexattr_t * attr, int kind);
PTW32_DLLPORT int PTW32_CDECL pthread_mutexattr_gettype (const pthread_mutexattr_t * attr, int *kind);

PTW32_DLLPORT int PTW32_CDECL pthread_mutexattr_setrobust(
                                           pthread_mutexattr_t *attr,
                                           int robust);
PTW32_DLLPORT int PTW32_CDECL pthread_mutexattr_getrobust(
                                           const pthread_mutexattr_t * attr,
                                           int * robust);

PTW32_DLLPORT int PTW32_CDECL pthread_barrierattr_init (pthread_barrierattr_t * attr);

PTW32_DLLPORT int PTW32_CDECL pthread_barrierattr_destroy (pthread_barrierattr_t * attr);

PTW32_DLLPORT int PTW32_CDECL pthread_barrierattr_getpshared (const pthread_barrierattr_t
                                            * attr,
                                            int *pshared);

PTW32_DLLPORT int PTW32_CDECL pthread_barrierattr_setpshared (pthread_barrierattr_t * attr,
                                            int pshared);

PTW32_DLLPORT int PTW32_CDECL pthread_mutex_init (pthread_mutex_t * mutex,
                                const pthread_mutexattr_t * attr);

PTW32_DLLPORT int PTW32_CDECL pthread_mutex_destroy (pthread_mutex_t * mutex);

PTW32_DLLPORT int PTW32_CDECL pthread_mutex_lock (pthread_mutex_t * mutex);

PTW32_DLLPORT int PTW32_CDECL pthread_mutex_timedlock(pthread_mutex_t * mutex,
                                    const struct timespec *abstime);

PTW32_DLLPORT int PTW32_CDECL pthread_mutex_trylock (pthread_mutex_t * mutex);

PTW32_DLLPORT int PTW32_CDECL pthread_mutex_unlock (pthread_mutex_t * mutex);

PTW32_DLLPORT int PTW32_CDECL pthread_mutex_consistent (pthread_mutex_t * mutex);

PTW32_DLLPORT int PTW32_CDECL pthread_spin_init (pthread_spinlock_t * lock, int pshared);

PTW32_DLLPORT int PTW32_CDECL pthread_spin_destroy (pthread_spinlock_t * lock);

PTW32_DLLPORT int PTW32_CDECL pthread_spin_lock (pthread_spinlock_t * lock);

PTW32_DLLPORT int PTW32_CDECL pthread_spin_trylock (pthread_spinlock_t * lock);

PTW32_DLLPORT int PTW32_CDECL pthread_spin_unlock (pthread_spinlock_t * lock);

PTW32_DLLPORT int PTW32_CDECL pthread_barrier_init (pthread_barrier_t * barrier,
                                  const pthread_barrierattr_t * attr,
                                  unsigned int count);

PTW32_DLLPORT int PTW32_CDECL pthread_barrier_destroy (pthread_barrier_t * barrier);

PTW32_DLLPORT int PTW32_CDECL pthread_barrier_wait (pthread_barrier_t * barrier);

PTW32_DLLPORT int PTW32_CDECL pthread_condattr_init (pthread_condattr_t * attr);

PTW32_DLLPORT int PTW32_CDECL pthread_condattr_destroy (pthread_condattr_t * attr);

PTW32_DLLPORT int PTW32_CDECL pthread_condattr_getpshared (const pthread_condattr_t * attr,
                                         int *pshared);

PTW32_DLLPORT int PTW32_CDECL pthread_condattr_setpshared (pthread_condattr_t * attr,
                                         int pshared);

PTW32_DLLPORT int PTW32_CDECL pthread_cond_init (pthread_cond_t * cond,
                               const pthread_condattr_t * attr);

PTW32_DLLPORT int PTW32_CDECL pthread_cond_destroy (pthread_cond_t * cond);

PTW32_DLLPORT int PTW32_CDECL pthread_cond_wait (pthread_cond_t * cond,
                               pthread_mutex_t * mutex);

PTW32_DLLPORT int PTW32_CDECL pthread_cond_timedwait (pthread_cond_t * cond,
                                    pthread_mutex_t * mutex,
                                    const struct timespec *abstime);

PTW32_DLLPORT int PTW32_CDECL pthread_cond_signal (pthread_cond_t * cond);

PTW32_DLLPORT int PTW32_CDECL pthread_cond_broadcast (pthread_cond_t * cond);

PTW32_DLLPORT int PTW32_CDECL pthread_setschedparam (pthread_t thread,
                                   int policy,
                                   const struct sched_param *param);

PTW32_DLLPORT int PTW32_CDECL pthread_getschedparam (pthread_t thread,
                                   int *policy,
                                   struct sched_param *param);

PTW32_DLLPORT int PTW32_CDECL pthread_setconcurrency (int);
 
PTW32_DLLPORT int PTW32_CDECL pthread_getconcurrency (void);

PTW32_DLLPORT int PTW32_CDECL pthread_rwlock_init(pthread_rwlock_t *lock,
                                const pthread_rwlockattr_t *attr);

PTW32_DLLPORT int PTW32_CDECL pthread_rwlock_destroy(pthread_rwlock_t *lock);

PTW32_DLLPORT int PTW32_CDECL pthread_rwlock_tryrdlock(pthread_rwlock_t *);

PTW32_DLLPORT int PTW32_CDECL pthread_rwlock_trywrlock(pthread_rwlock_t *);

PTW32_DLLPORT int PTW32_CDECL pthread_rwlock_rdlock(pthread_rwlock_t *lock);

PTW32_DLLPORT int PTW32_CDECL pthread_rwlock_timedrdlock(pthread_rwlock_t *lock,
                                       const struct timespec *abstime);

PTW32_DLLPORT int PTW32_CDECL pthread_rwlock_wrlock(pthread_rwlock_t *lock);

PTW32_DLLPORT int PTW32_CDECL pthread_rwlock_timedwrlock(pthread_rwlock_t *lock,
                                       const struct timespec *abstime);

PTW32_DLLPORT int PTW32_CDECL pthread_rwlock_unlock(pthread_rwlock_t *lock);

PTW32_DLLPORT int PTW32_CDECL pthread_rwlockattr_init (pthread_rwlockattr_t * attr);

PTW32_DLLPORT int PTW32_CDECL pthread_rwlockattr_destroy (pthread_rwlockattr_t * attr);

PTW32_DLLPORT int PTW32_CDECL pthread_rwlockattr_getpshared (const pthread_rwlockattr_t * attr,
                                           int *pshared);

PTW32_DLLPORT int PTW32_CDECL pthread_rwlockattr_setpshared (pthread_rwlockattr_t * attr,
                                           int pshared);

#if PTW32_LEVEL >= PTW32_LEVEL_MAX - 1

PTW32_DLLPORT int PTW32_CDECL pthread_kill(pthread_t thread, int sig);


PTW32_DLLPORT int PTW32_CDECL pthread_mutexattr_setkind_np(pthread_mutexattr_t * attr,
                                         int kind);
PTW32_DLLPORT int PTW32_CDECL pthread_mutexattr_getkind_np(pthread_mutexattr_t * attr,
                                         int *kind);

PTW32_DLLPORT int PTW32_CDECL pthread_delay_np (struct timespec * interval);
PTW32_DLLPORT int PTW32_CDECL pthread_num_processors_np(void);
PTW32_DLLPORT unsigned __int64 PTW32_CDECL pthread_getunique_np(pthread_t thread);

PTW32_DLLPORT int PTW32_CDECL pthread_win32_process_attach_np(void);
PTW32_DLLPORT int PTW32_CDECL pthread_win32_process_detach_np(void);
PTW32_DLLPORT int PTW32_CDECL pthread_win32_thread_attach_np(void);
PTW32_DLLPORT int PTW32_CDECL pthread_win32_thread_detach_np(void);

PTW32_DLLPORT int PTW32_CDECL pthread_win32_test_features_np(int);
enum ptw32_features {
  PTW32_SYSTEM_INTERLOCKED_COMPARE_EXCHANGE = 0x0001, 
  PTW32_ALERTABLE_ASYNC_CANCEL              = 0x0002  
};

PTW32_DLLPORT void * PTW32_CDECL pthread_timechange_handler_np(void *);

#endif 

#if PTW32_LEVEL >= PTW32_LEVEL_MAX

PTW32_DLLPORT HANDLE PTW32_CDECL pthread_getw32threadhandle_np(pthread_t thread);
PTW32_DLLPORT DWORD PTW32_CDECL pthread_getw32threadid_np (pthread_t thread);


PTW32_DLLPORT int PTW32_CDECL pthreadCancelableWait (HANDLE waitHandle);
PTW32_DLLPORT int PTW32_CDECL pthreadCancelableTimedWait (HANDLE waitHandle,
                                        DWORD timeout);

#endif 

#if !defined(_UWIN)
#  if defined(NEED_ERRNO)
     PTW32_DLLPORT int * PTW32_CDECL _errno( void );
#  else
#    if !defined(errno)
#      if (defined(_MT) || defined(_DLL))
         __declspec(dllimport) extern int * __cdecl _errno(void);
#        define errno   (*_errno())
#      endif
#    endif
#  endif
#endif

#if defined(__BORLANDC__)
#  define _ftime ftime
#  define _timeb timeb
#endif

#if defined(__cplusplus)

class ptw32_exception {};
class ptw32_exception_cancel : public ptw32_exception {};
class ptw32_exception_exit   : public ptw32_exception {};

#endif

#if PTW32_LEVEL >= PTW32_LEVEL_MAX

PTW32_DLLPORT DWORD PTW32_CDECL ptw32_get_exception_services_code(void);

#endif 

#if !defined(PTW32_BUILD)

#if defined(__CLEANUP_SEH)

#define __except( E ) \
        __except( ( GetExceptionCode() == ptw32_get_exception_services_code() ) \
                 ? EXCEPTION_CONTINUE_SEARCH : ( E ) )

#endif 

#if defined(__CLEANUP_CXX)

#if defined(_MSC_VER)

#if !defined(PtW32NoCatchWarn)

#pragma message("Specify \"/DPtW32NoCatchWarn\" compiler flag to skip this message.")
#pragma message("------------------------------------------------------------------")
#pragma message("When compiling applications with MSVC++ and C++ exception handling:")
#pragma message("  Replace any 'catch( ... )' in routines called from POSIX threads")
#pragma message("  with 'PtW32CatchAll' or 'CATCHALL' if you want POSIX thread")
#pragma message("  cancelation and pthread_exit to work. For example:")
#pragma message("")
#pragma message("    #if defined(PtW32CatchAll)")
#pragma message("      PtW32CatchAll")
#pragma message("    #else")
#pragma message("      catch(...)")
#pragma message("    #endif")
#pragma message("        {")
#pragma message("          /* Catchall block processing */")
#pragma message("        }")
#pragma message("------------------------------------------------------------------")

#endif

#define PtW32CatchAll \
        catch( ptw32_exception & ) { throw; } \
        catch( ... )

#else 

#define catch( E ) \
        catch( ptw32_exception & ) { throw; } \
        catch( E )

#endif 

#endif 

#endif 

#if defined(__cplusplus)
}                               
#endif                          

#if defined(PTW32__HANDLE_DEF)
# undef HANDLE
#endif
#if defined(PTW32__DWORD_DEF)
# undef DWORD
#endif

#undef PTW32_LEVEL
#undef PTW32_LEVEL_MAX

#endif 

#endif 