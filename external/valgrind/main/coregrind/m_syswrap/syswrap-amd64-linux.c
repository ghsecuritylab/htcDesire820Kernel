

/*
   This file is part of Valgrind, a dynamic binary instrumentation
   framework.

   Copyright (C) 2000-2012 Nicholas Nethercote
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

#if defined(VGP_amd64_linux)

#include "pub_core_basics.h"
#include "pub_core_vki.h"
#include "pub_core_vkiscnums.h"
#include "pub_core_libcsetjmp.h"    
#include "pub_core_threadstate.h"
#include "pub_core_aspacemgr.h"
#include "pub_core_debuglog.h"
#include "pub_core_options.h"
#include "pub_core_libcbase.h"
#include "pub_core_libcassert.h"
#include "pub_core_libcprint.h"
#include "pub_core_libcproc.h"
#include "pub_core_libcsignal.h"
#include "pub_core_scheduler.h"
#include "pub_core_sigframe.h"
#include "pub_core_signals.h"
#include "pub_core_syscall.h"
#include "pub_core_syswrap.h"
#include "pub_core_tooliface.h"
#include "pub_core_stacks.h"        

#include "priv_types_n_macros.h"
#include "priv_syswrap-generic.h"   
#include "priv_syswrap-linux.h"     
#include "priv_syswrap-linux-variants.h" 
#include "priv_syswrap-main.h"



__attribute__((noreturn))
void ML_(call_on_new_stack_0_1) ( Addr stack,
			          Addr retaddr,
			          void (*f)(Word),
                                  Word arg1 );
asm(
".text\n"
".globl vgModuleLocal_call_on_new_stack_0_1\n"
"vgModuleLocal_call_on_new_stack_0_1:\n"
"   movq   %rdi, %rsp\n"   
"   pushq  %rsi\n"         
"   pushq  %rdx\n"         
"   pushq  %rcx\n"         
"   movq $0, %rax\n"       
"   movq $0, %rbx\n" 
"   movq $0, %rcx\n"
"   movq $0, %rdx\n"
"   movq $0, %rsi\n"
"   movq $0, %rdi\n"
"   movq $0, %rbp\n"
"   movq $0, %r8\n"
"   movq $0, %r9\n"
"   movq $0, %r10\n"
"   movq $0, %r11\n"
"   movq $0, %r12\n"
"   movq $0, %r13\n"
"   movq $0, %r14\n"
"   movq $0, %r15\n"
"   popq   %rdi\n"         
"   ret\n"                 
"   ud2\n"                 
".previous\n"
);

#define __NR_CLONE        VG_STRINGIFY(__NR_clone)
#define __NR_EXIT         VG_STRINGIFY(__NR_exit)

extern
Long do_syscall_clone_amd64_linux ( Word (*fn)(void *), 
                                    void* stack, 
                                    Long  flags, 
                                    void* arg,
                                    Long* child_tid, 
                                    Long* parent_tid, 
                                    vki_modify_ldt_t * );
asm(
".text\n"
".globl do_syscall_clone_amd64_linux\n"
"do_syscall_clone_amd64_linux:\n"
        
"       subq    $16, %rsi\n"            
"       movq    %rcx, 8(%rsi)\n"        
"       movq    %rdi, 0(%rsi)\n"        
        
        
"       movq    $"__NR_CLONE", %rax\n"  
"       movq    %rdx,     %rdi\n"       
        
"       movq    %r9,      %rdx\n"       
"       movq    %r8,      %r10\n"       
"       movq    8(%rsp),  %r8\n"        

"       syscall\n"                      

"       testq   %rax, %rax\n"           
"       jnz     1f\n"

        
"       pop     %rax\n"                 
"       pop     %rdi\n"                 
"       call    *%rax\n"                

        
"       movq    %rax, %rdi\n"           
"       movq    $"__NR_EXIT", %rax\n"

"       syscall\n"

        
"       ud2\n"

"1:\n"  
"       ret\n"
".previous\n"
);

#undef __NR_CLONE
#undef __NR_EXIT


static void setup_child ( ThreadArchState*, ThreadArchState* );

static SysRes do_clone ( ThreadId ptid, 
                         ULong flags, Addr rsp, 
                         Long* parent_tidptr, 
                         Long* child_tidptr, 
                         Addr tlsaddr )
{
   static const Bool debug = False;

   ThreadId     ctid = VG_(alloc_ThreadState)();
   ThreadState* ptst = VG_(get_ThreadState)(ptid);
   ThreadState* ctst = VG_(get_ThreadState)(ctid);
   UWord*       stack;
   NSegment const* seg;
   SysRes       res;
   Long         rax;
   vki_sigset_t blockall, savedmask;

   VG_(sigfillset)(&blockall);

   vg_assert(VG_(is_running_thread)(ptid));
   vg_assert(VG_(is_valid_tid)(ctid));

   stack = (UWord*)ML_(allocstack)(ctid);
   if (stack == NULL) {
      res = VG_(mk_SysRes_Error)( VKI_ENOMEM );
      goto out;
   }

   setup_child( &ctst->arch, &ptst->arch );

   ctst->arch.vex.guest_RAX = 0;

   if (rsp != 0)
      ctst->arch.vex.guest_RSP = rsp;

   ctst->os_state.parent = ptid;

   
   ctst->sig_mask = ptst->sig_mask;
   ctst->tmp_sig_mask = ptst->sig_mask;

   ctst->os_state.threadgroup = ptst->os_state.threadgroup;

   seg = VG_(am_find_nsegment)((Addr)rsp);
   if (seg && seg->kind != SkResvn) {
      ctst->client_stack_highest_word = (Addr)VG_PGROUNDUP(rsp);
      ctst->client_stack_szB = ctst->client_stack_highest_word - seg->start;

      VG_(register_stack)(seg->start, ctst->client_stack_highest_word);

      if (debug)
	 VG_(printf)("tid %d: guessed client stack range %#lx-%#lx\n",
		     ctid, seg->start, VG_PGROUNDUP(rsp));
   } else {
      VG_(message)(Vg_UserMsg,
                   "!? New thread %d starts with RSP(%#lx) unmapped\n",
		   ctid, rsp);
      ctst->client_stack_szB  = 0;
   }

   vg_assert(VG_(owns_BigLock_LL)(ptid));
   VG_TRACK ( pre_thread_ll_create, ptid, ctid );

   if (flags & VKI_CLONE_SETTLS) {
      if (debug)
	 VG_(printf)("clone child has SETTLS: tls at %#lx\n", tlsaddr);
      ctst->arch.vex.guest_FS_ZERO = tlsaddr;
   }

   flags &= ~VKI_CLONE_SETTLS;

   
   VG_(sigprocmask)(VKI_SIG_SETMASK, &blockall, &savedmask);

   
   rax = do_syscall_clone_amd64_linux(
            ML_(start_thread_NORETURN), stack, flags, &VG_(threads)[ctid],
            child_tidptr, parent_tidptr, NULL
         );
   res = VG_(mk_SysRes_amd64_linux)( rax );

   VG_(sigprocmask)(VKI_SIG_SETMASK, &savedmask, NULL);

  out:
   if (sr_isError(res)) {
      
      VG_(cleanup_thread)(&ctst->arch);
      ctst->status = VgTs_Empty;
      
      VG_TRACK( pre_thread_ll_exit, ctid );
   }

   return res;
}



void VG_(cleanup_thread) ( ThreadArchState *arch )
{  
}  

void setup_child (  ThreadArchState *child, 
                     ThreadArchState *parent )
{  
   
   child->vex = parent->vex;
   child->vex_shadow1 = parent->vex_shadow1;
   child->vex_shadow2 = parent->vex_shadow2;
}  



#define PRE(name)       DEFN_PRE_TEMPLATE(amd64_linux, name)
#define POST(name)      DEFN_POST_TEMPLATE(amd64_linux, name)

DECL_TEMPLATE(amd64_linux, sys_clone);
DECL_TEMPLATE(amd64_linux, sys_rt_sigreturn);
DECL_TEMPLATE(amd64_linux, sys_socket);
DECL_TEMPLATE(amd64_linux, sys_setsockopt);
DECL_TEMPLATE(amd64_linux, sys_getsockopt);
DECL_TEMPLATE(amd64_linux, sys_connect);
DECL_TEMPLATE(amd64_linux, sys_accept);
DECL_TEMPLATE(amd64_linux, sys_accept4);
DECL_TEMPLATE(amd64_linux, sys_sendto);
DECL_TEMPLATE(amd64_linux, sys_recvfrom);
DECL_TEMPLATE(amd64_linux, sys_sendmsg);
DECL_TEMPLATE(amd64_linux, sys_recvmsg);
DECL_TEMPLATE(amd64_linux, sys_shutdown);
DECL_TEMPLATE(amd64_linux, sys_bind);
DECL_TEMPLATE(amd64_linux, sys_listen);
DECL_TEMPLATE(amd64_linux, sys_getsockname);
DECL_TEMPLATE(amd64_linux, sys_getpeername);
DECL_TEMPLATE(amd64_linux, sys_socketpair);
DECL_TEMPLATE(amd64_linux, sys_semget);
DECL_TEMPLATE(amd64_linux, sys_semop);
DECL_TEMPLATE(amd64_linux, sys_semtimedop);
DECL_TEMPLATE(amd64_linux, sys_semctl);
DECL_TEMPLATE(amd64_linux, sys_msgget);
DECL_TEMPLATE(amd64_linux, sys_msgrcv);
DECL_TEMPLATE(amd64_linux, sys_msgsnd);
DECL_TEMPLATE(amd64_linux, sys_msgctl);
DECL_TEMPLATE(amd64_linux, sys_shmget);
DECL_TEMPLATE(amd64_linux, wrap_sys_shmat);
DECL_TEMPLATE(amd64_linux, sys_shmdt);
DECL_TEMPLATE(amd64_linux, sys_shmdt);
DECL_TEMPLATE(amd64_linux, sys_shmctl);
DECL_TEMPLATE(amd64_linux, sys_arch_prctl);
DECL_TEMPLATE(amd64_linux, sys_ptrace);
DECL_TEMPLATE(amd64_linux, sys_fadvise64);
DECL_TEMPLATE(amd64_linux, sys_mmap);
DECL_TEMPLATE(amd64_linux, sys_syscall184);


PRE(sys_clone)
{
   ULong cloneflags;

   PRINT("sys_clone ( %lx, %#lx, %#lx, %#lx, %#lx )",ARG1,ARG2,ARG3,ARG4,ARG5);
   PRE_REG_READ2(int, "clone",
                 unsigned long, flags,
                 void *, child_stack);

   if (ARG1 & VKI_CLONE_PARENT_SETTID) {
      if (VG_(tdict).track_pre_reg_read) {
         PRA3("clone", int *, parent_tidptr);
      }
      PRE_MEM_WRITE("clone(parent_tidptr)", ARG3, sizeof(Int));
      if (!VG_(am_is_valid_for_client)(ARG3, sizeof(Int), VKI_PROT_WRITE)) {
         SET_STATUS_Failure( VKI_EFAULT );
         return;
      }
   }
   if (ARG1 & VKI_CLONE_SETTLS) {
      if (VG_(tdict).track_pre_reg_read) {
         PRA4("clone", vki_modify_ldt_t *, tlsinfo);
      }
      PRE_MEM_READ("clone(tlsinfo)", ARG4, sizeof(vki_modify_ldt_t));
      if (!VG_(am_is_valid_for_client)(ARG4, sizeof(vki_modify_ldt_t), 
                                             VKI_PROT_READ)) {
         SET_STATUS_Failure( VKI_EFAULT );
         return;
      }
   }
   if (ARG1 & (VKI_CLONE_CHILD_SETTID | VKI_CLONE_CHILD_CLEARTID)) {
      if (VG_(tdict).track_pre_reg_read) {
         PRA5("clone", int *, child_tidptr);
      }
      PRE_MEM_WRITE("clone(child_tidptr)", ARG4, sizeof(Int));
      if (!VG_(am_is_valid_for_client)(ARG4, sizeof(Int), VKI_PROT_WRITE)) {
         SET_STATUS_Failure( VKI_EFAULT );
         return;
      }
   }

   cloneflags = ARG1;

   if (!ML_(client_signal_OK)(ARG1 & VKI_CSIGNAL)) {
      SET_STATUS_Failure( VKI_EINVAL );
      return;
   }

   
   switch (cloneflags & (VKI_CLONE_VM | VKI_CLONE_FS 
                         | VKI_CLONE_FILES | VKI_CLONE_VFORK)) {
   case VKI_CLONE_VM | VKI_CLONE_FS | VKI_CLONE_FILES:
      
      SET_STATUS_from_SysRes(
         do_clone(tid,
                  ARG1,          
                  (Addr)ARG2,    
                  (Long *)ARG3,  
                  (Long *)ARG4,  
                  (Addr)ARG5));  
      break;

   case VKI_CLONE_VFORK | VKI_CLONE_VM: 
      
      cloneflags &= ~(VKI_CLONE_VFORK | VKI_CLONE_VM);

   case 0: 
      SET_STATUS_from_SysRes(
         ML_(do_fork_clone)(tid,
                       cloneflags,      
                       (Int *)ARG3,     
                       (Int *)ARG4));   
      break;

   default:
      
      VG_(message)(Vg_UserMsg,
                   "Unsupported clone() flags: 0x%lx\n", ARG1);
      VG_(message)(Vg_UserMsg,
                   "\n");
      VG_(message)(Vg_UserMsg,
                   "The only supported clone() uses are:\n");
      VG_(message)(Vg_UserMsg,
                   " - via a threads library (LinuxThreads or NPTL)\n");
      VG_(message)(Vg_UserMsg,
                   " - via the implementation of fork or vfork\n");
      VG_(unimplemented)
         ("Valgrind does not support general clone().");
   }

   if (SUCCESS) {
      if (ARG1 & VKI_CLONE_PARENT_SETTID)
         POST_MEM_WRITE(ARG3, sizeof(Int));
      if (ARG1 & (VKI_CLONE_CHILD_SETTID | VKI_CLONE_CHILD_CLEARTID))
         POST_MEM_WRITE(ARG4, sizeof(Int));

      *flags |= SfYieldAfter;
   }
}

PRE(sys_rt_sigreturn)
{

   ThreadState* tst;
   PRINT("sys_rt_sigreturn ( )");

   vg_assert(VG_(is_valid_tid)(tid));
   vg_assert(tid >= 1 && tid < VG_N_THREADS);
   vg_assert(VG_(is_running_thread)(tid));

   tst = VG_(get_ThreadState)(tid);
   tst->arch.vex.guest_RSP -= sizeof(Addr);

   ML_(fixup_guest_state_to_restart_syscall)(&tst->arch);

   VG_(sigframe_destroy)(tid, True);

   *flags |= SfNoWriteResult;
   SET_STATUS_Success(0);

   
   *flags |= SfPollAfter;
}

PRE(sys_arch_prctl)
{
   ThreadState* tst;
   PRINT( "arch_prctl ( %ld, %lx )", ARG1, ARG2 );

   vg_assert(VG_(is_valid_tid)(tid));
   vg_assert(tid >= 1 && tid < VG_N_THREADS);
   vg_assert(VG_(is_running_thread)(tid));

   
   PRE_REG_READ2(long, "arch_prctl",
                 int, option, unsigned long, arg2);
   
   

   
   if (ARG1 == VKI_ARCH_SET_FS) {
      tst = VG_(get_ThreadState)(tid);
      tst->arch.vex.guest_FS_ZERO = ARG2;
   }
   else if (ARG1 == VKI_ARCH_GET_FS) {
      PRE_MEM_WRITE("arch_prctl(addr)", ARG2, sizeof(unsigned long));
      tst = VG_(get_ThreadState)(tid);
      *(unsigned long *)ARG2 = tst->arch.vex.guest_FS_ZERO;
      POST_MEM_WRITE(ARG2, sizeof(unsigned long));
   }
   else {
      VG_(core_panic)("Unsupported arch_prtctl option");
   }

   SET_STATUS_Success( 0 );
}

PRE(sys_ptrace)
{
   PRINT("sys_ptrace ( %ld, %ld, %#lx, %#lx )", ARG1,ARG2,ARG3,ARG4);
   PRE_REG_READ4(int, "ptrace", 
                 long, request, long, pid, long, addr, long, data);
   switch (ARG1) {
   case VKI_PTRACE_PEEKTEXT:
   case VKI_PTRACE_PEEKDATA:
   case VKI_PTRACE_PEEKUSR:
      PRE_MEM_WRITE( "ptrace(peek)", ARG4, 
		     sizeof (long));
      break;
   case VKI_PTRACE_GETREGS:
      PRE_MEM_WRITE( "ptrace(getregs)", ARG4, 
		     sizeof (struct vki_user_regs_struct));
      break;
   case VKI_PTRACE_GETFPREGS:
      PRE_MEM_WRITE( "ptrace(getfpregs)", ARG4, 
		     sizeof (struct vki_user_i387_struct));
      break;
   case VKI_PTRACE_SETREGS:
      PRE_MEM_READ( "ptrace(setregs)", ARG4, 
		     sizeof (struct vki_user_regs_struct));
      break;
   case VKI_PTRACE_SETFPREGS:
      PRE_MEM_READ( "ptrace(setfpregs)", ARG4, 
		     sizeof (struct vki_user_i387_struct));
      break;
   case VKI_PTRACE_GETEVENTMSG:
      PRE_MEM_WRITE( "ptrace(geteventmsg)", ARG4, sizeof(unsigned long));
      break;
   case VKI_PTRACE_GETSIGINFO:
      PRE_MEM_WRITE( "ptrace(getsiginfo)", ARG4, sizeof(vki_siginfo_t));
      break;
   case VKI_PTRACE_SETSIGINFO:
      PRE_MEM_READ( "ptrace(setsiginfo)", ARG4, sizeof(vki_siginfo_t));
      break;
   default:
      break;
   }
}

POST(sys_ptrace)
{
   switch (ARG1) {
   case VKI_PTRACE_PEEKTEXT:
   case VKI_PTRACE_PEEKDATA:
   case VKI_PTRACE_PEEKUSR:
      POST_MEM_WRITE( ARG4, sizeof (long));
      break;
   case VKI_PTRACE_GETREGS:
      POST_MEM_WRITE( ARG4, sizeof (struct vki_user_regs_struct));
      break;
   case VKI_PTRACE_GETFPREGS:
      POST_MEM_WRITE( ARG4, sizeof (struct vki_user_i387_struct));
      break;
   case VKI_PTRACE_GETEVENTMSG:
      POST_MEM_WRITE( ARG4, sizeof(unsigned long));
      break;
   case VKI_PTRACE_GETSIGINFO:
      POST_MEM_WRITE( ARG4, sizeof(vki_siginfo_t));
      break;
   default:
      break;
   }
}

PRE(sys_socket)
{
   PRINT("sys_socket ( %ld, %ld, %ld )",ARG1,ARG2,ARG3);
   PRE_REG_READ3(long, "socket", int, domain, int, type, int, protocol);
}
POST(sys_socket)
{
   SysRes r;
   vg_assert(SUCCESS);
   r = ML_(generic_POST_sys_socket)(tid, VG_(mk_SysRes_Success)(RES));
   SET_STATUS_from_SysRes(r);
}

PRE(sys_setsockopt)
{
   PRINT("sys_setsockopt ( %ld, %ld, %ld, %#lx, %ld )",ARG1,ARG2,ARG3,ARG4,ARG5);
   PRE_REG_READ5(long, "setsockopt",
                 int, s, int, level, int, optname,
                 const void *, optval, int, optlen);
   ML_(generic_PRE_sys_setsockopt)(tid, ARG1,ARG2,ARG3,ARG4,ARG5);
}

PRE(sys_getsockopt)
{
   PRINT("sys_getsockopt ( %ld, %ld, %ld, %#lx, %#lx )",ARG1,ARG2,ARG3,ARG4,ARG5);
   PRE_REG_READ5(long, "getsockopt",
                 int, s, int, level, int, optname,
                 void *, optval, int, *optlen);
   ML_(linux_PRE_sys_getsockopt)(tid, ARG1,ARG2,ARG3,ARG4,ARG5);
}
POST(sys_getsockopt)
{
   vg_assert(SUCCESS);
   ML_(linux_POST_sys_getsockopt)(tid, VG_(mk_SysRes_Success)(RES),
                                       ARG1,ARG2,ARG3,ARG4,ARG5);
}

PRE(sys_connect)
{
   *flags |= SfMayBlock;
   PRINT("sys_connect ( %ld, %#lx, %ld )",ARG1,ARG2,ARG3);
   PRE_REG_READ3(long, "connect",
                 int, sockfd, struct sockaddr *, serv_addr, int, addrlen);
   ML_(generic_PRE_sys_connect)(tid, ARG1,ARG2,ARG3);
}

PRE(sys_accept)
{
   *flags |= SfMayBlock;
   PRINT("sys_accept ( %ld, %#lx, %ld )",ARG1,ARG2,ARG3);
   PRE_REG_READ3(long, "accept",
                 int, s, struct sockaddr *, addr, int, *addrlen);
   ML_(generic_PRE_sys_accept)(tid, ARG1,ARG2,ARG3);
}
POST(sys_accept)
{
   SysRes r;
   vg_assert(SUCCESS);
   r = ML_(generic_POST_sys_accept)(tid, VG_(mk_SysRes_Success)(RES),
                                         ARG1,ARG2,ARG3);
   SET_STATUS_from_SysRes(r);
}

PRE(sys_accept4)
{
   *flags |= SfMayBlock;
   PRINT("sys_accept4 ( %ld, %#lx, %ld, %ld )",ARG1,ARG2,ARG3,ARG4);
   PRE_REG_READ4(long, "accept4",
                 int, s, struct sockaddr *, addr, int, *addrlen, int, flags);
   ML_(generic_PRE_sys_accept)(tid, ARG1,ARG2,ARG3);
}
POST(sys_accept4)
{
   SysRes r;
   vg_assert(SUCCESS);
   r = ML_(generic_POST_sys_accept)(tid, VG_(mk_SysRes_Success)(RES),
                                         ARG1,ARG2,ARG3);
   SET_STATUS_from_SysRes(r);
}

PRE(sys_sendto)
{
   *flags |= SfMayBlock;
   PRINT("sys_sendto ( %ld, %#lx, %ld, %lu, %#lx, %ld )",ARG1,ARG2,ARG3,ARG4,ARG5,ARG6);
   PRE_REG_READ6(long, "sendto",
                 int, s, const void *, msg, int, len, 
                 unsigned int, flags, 
                 const struct sockaddr *, to, int, tolen);
   ML_(generic_PRE_sys_sendto)(tid, ARG1,ARG2,ARG3,ARG4,ARG5,ARG6);
}

PRE(sys_recvfrom)
{
   *flags |= SfMayBlock;
   PRINT("sys_recvfrom ( %ld, %#lx, %ld, %lu, %#lx, %#lx )",ARG1,ARG2,ARG3,ARG4,ARG5,ARG6);
   PRE_REG_READ6(long, "recvfrom",
                 int, s, void *, buf, int, len, unsigned int, flags,
                 struct sockaddr *, from, int *, fromlen);
   ML_(generic_PRE_sys_recvfrom)(tid, ARG1,ARG2,ARG3,ARG4,ARG5,ARG6);
}
POST(sys_recvfrom)
{
   vg_assert(SUCCESS);
   ML_(generic_POST_sys_recvfrom)(tid, VG_(mk_SysRes_Success)(RES),
                                       ARG1,ARG2,ARG3,ARG4,ARG5,ARG6);
}

PRE(sys_sendmsg)
{
   *flags |= SfMayBlock;
   PRINT("sys_sendmsg ( %ld, %#lx, %ld )",ARG1,ARG2,ARG3);
   PRE_REG_READ3(long, "sendmsg",
                 int, s, const struct msghdr *, msg, int, flags);
   ML_(generic_PRE_sys_sendmsg)(tid, "msg", (struct vki_msghdr *)ARG2);
}

PRE(sys_recvmsg)
{
   *flags |= SfMayBlock;
   PRINT("sys_recvmsg ( %ld, %#lx, %ld )",ARG1,ARG2,ARG3);
   PRE_REG_READ3(long, "recvmsg", int, s, struct msghdr *, msg, int, flags);
   ML_(generic_PRE_sys_recvmsg)(tid, "msg", (struct vki_msghdr *)ARG2);
}
POST(sys_recvmsg)
{
   ML_(generic_POST_sys_recvmsg)(tid, "msg", (struct vki_msghdr *)ARG2, RES);
}

PRE(sys_shutdown)
{
   *flags |= SfMayBlock;
   PRINT("sys_shutdown ( %ld, %ld )",ARG1,ARG2);
   PRE_REG_READ2(int, "shutdown", int, s, int, how);
}

PRE(sys_bind)
{
   PRINT("sys_bind ( %ld, %#lx, %ld )",ARG1,ARG2,ARG3);
   PRE_REG_READ3(long, "bind",
                 int, sockfd, struct sockaddr *, my_addr, int, addrlen);
   ML_(generic_PRE_sys_bind)(tid, ARG1,ARG2,ARG3);
}

PRE(sys_listen)
{
   PRINT("sys_listen ( %ld, %ld )",ARG1,ARG2);
   PRE_REG_READ2(long, "listen", int, s, int, backlog);
}

PRE(sys_getsockname)
{
   PRINT("sys_getsockname ( %ld, %#lx, %#lx )",ARG1,ARG2,ARG3);
   PRE_REG_READ3(long, "getsockname",
                 int, s, struct sockaddr *, name, int *, namelen);
   ML_(generic_PRE_sys_getsockname)(tid, ARG1,ARG2,ARG3);
}
POST(sys_getsockname)
{
   vg_assert(SUCCESS);
   ML_(generic_POST_sys_getsockname)(tid, VG_(mk_SysRes_Success)(RES),
                                          ARG1,ARG2,ARG3);
}

PRE(sys_getpeername)
{
   PRINT("sys_getpeername ( %ld, %#lx, %#lx )",ARG1,ARG2,ARG3);
   PRE_REG_READ3(long, "getpeername",
                 int, s, struct sockaddr *, name, int *, namelen);
   ML_(generic_PRE_sys_getpeername)(tid, ARG1,ARG2,ARG3);
}
POST(sys_getpeername)
{
   vg_assert(SUCCESS);
   ML_(generic_POST_sys_getpeername)(tid, VG_(mk_SysRes_Success)(RES),
                                          ARG1,ARG2,ARG3);
}

PRE(sys_socketpair)
{
   PRINT("sys_socketpair ( %ld, %ld, %ld, %#lx )",ARG1,ARG2,ARG3,ARG4);
   PRE_REG_READ4(long, "socketpair",
                 int, d, int, type, int, protocol, int*, sv);
   ML_(generic_PRE_sys_socketpair)(tid, ARG1,ARG2,ARG3,ARG4);
}
POST(sys_socketpair)
{
   vg_assert(SUCCESS);
   ML_(generic_POST_sys_socketpair)(tid, VG_(mk_SysRes_Success)(RES),
                                         ARG1,ARG2,ARG3,ARG4);
}

PRE(sys_semget)
{
   PRINT("sys_semget ( %ld, %ld, %ld )",ARG1,ARG2,ARG3);
   PRE_REG_READ3(long, "semget", vki_key_t, key, int, nsems, int, semflg);
}

PRE(sys_semop)
{
   *flags |= SfMayBlock;
   PRINT("sys_semop ( %ld, %#lx, %lu )",ARG1,ARG2,ARG3);
   PRE_REG_READ3(long, "semop",
                 int, semid, struct sembuf *, sops, unsigned, nsoops);
   ML_(generic_PRE_sys_semop)(tid, ARG1,ARG2,ARG3);
}

PRE(sys_semtimedop)
{
   *flags |= SfMayBlock;
   PRINT("sys_semtimedop ( %ld, %#lx, %lu, %#lx )",ARG1,ARG2,ARG3,ARG4);
   PRE_REG_READ4(long, "semtimedop",
                 int, semid, struct sembuf *, sops, unsigned, nsoops,
                 struct timespec *, timeout);
   ML_(generic_PRE_sys_semtimedop)(tid, ARG1,ARG2,ARG3,ARG4);
}

PRE(sys_semctl)
{
   switch (ARG3 & ~VKI_IPC_64) {
   case VKI_IPC_INFO:
   case VKI_SEM_INFO:
      PRINT("sys_semctl ( %ld, %ld, %ld, %#lx )",ARG1,ARG2,ARG3,ARG4);
      PRE_REG_READ4(long, "semctl",
                    int, semid, int, semnum, int, cmd, struct seminfo *, arg);
      break;
   case VKI_IPC_STAT:
   case VKI_SEM_STAT:
   case VKI_IPC_SET:
      PRINT("sys_semctl ( %ld, %ld, %ld, %#lx )",ARG1,ARG2,ARG3,ARG4);
      PRE_REG_READ4(long, "semctl",
                    int, semid, int, semnum, int, cmd, struct semid_ds *, arg);
      break;
   case VKI_GETALL:
   case VKI_SETALL:
      PRINT("sys_semctl ( %ld, %ld, %ld, %#lx )",ARG1,ARG2,ARG3,ARG4);
      PRE_REG_READ4(long, "semctl",
                    int, semid, int, semnum, int, cmd, unsigned short *, arg);
      break;
   default:
      PRINT("sys_semctl ( %ld, %ld, %ld )",ARG1,ARG2,ARG3);
      PRE_REG_READ3(long, "semctl",
                    int, semid, int, semnum, int, cmd);
      break;
   }
   ML_(generic_PRE_sys_semctl)(tid, ARG1,ARG2,ARG3|VKI_IPC_64,ARG4);
}
POST(sys_semctl)
{
   ML_(generic_POST_sys_semctl)(tid, RES,ARG1,ARG2,ARG3|VKI_IPC_64,ARG4);
}

PRE(sys_msgget)
{
   PRINT("sys_msgget ( %ld, %ld )",ARG1,ARG2);
   PRE_REG_READ2(long, "msgget", vki_key_t, key, int, msgflg);
}

PRE(sys_msgsnd)
{
   PRINT("sys_msgsnd ( %ld, %#lx, %ld, %ld )",ARG1,ARG2,ARG3,ARG4);
   PRE_REG_READ4(long, "msgsnd",
                 int, msqid, struct msgbuf *, msgp, vki_size_t, msgsz, int, msgflg);
   ML_(linux_PRE_sys_msgsnd)(tid, ARG1,ARG2,ARG3,ARG4);
   if ((ARG4 & VKI_IPC_NOWAIT) == 0)
      *flags |= SfMayBlock;
}

PRE(sys_msgrcv)
{
   PRINT("sys_msgrcv ( %ld, %#lx, %ld, %ld, %ld )",ARG1,ARG2,ARG3,ARG4,ARG5);
   PRE_REG_READ5(long, "msgrcv",
                 int, msqid, struct msgbuf *, msgp, vki_size_t, msgsz,
                 long, msgytp, int, msgflg);
   ML_(linux_PRE_sys_msgrcv)(tid, ARG1,ARG2,ARG3,ARG4,ARG5);
   if ((ARG4 & VKI_IPC_NOWAIT) == 0)
      *flags |= SfMayBlock;
}
POST(sys_msgrcv)
{
   ML_(linux_POST_sys_msgrcv)(tid, RES,ARG1,ARG2,ARG3,ARG4,ARG5);
}

PRE(sys_msgctl)
{
   PRINT("sys_msgctl ( %ld, %ld, %#lx )",ARG1,ARG2,ARG3);
   PRE_REG_READ3(long, "msgctl",
                 int, msqid, int, cmd, struct msqid_ds *, buf);
   ML_(linux_PRE_sys_msgctl)(tid, ARG1,ARG2,ARG3);
}
POST(sys_msgctl)
{
   ML_(linux_POST_sys_msgctl)(tid, RES,ARG1,ARG2,ARG3);
}

PRE(sys_shmget)
{
   PRINT("sys_shmget ( %ld, %ld, %ld )",ARG1,ARG2,ARG3);
   PRE_REG_READ3(long, "shmget", vki_key_t, key, vki_size_t, size, int, shmflg);
}

PRE(wrap_sys_shmat)
{
   UWord arg2tmp;
   PRINT("wrap_sys_shmat ( %ld, %#lx, %ld )",ARG1,ARG2,ARG3);
   PRE_REG_READ3(long, "shmat",
                 int, shmid, const void *, shmaddr, int, shmflg);
   arg2tmp = ML_(generic_PRE_sys_shmat)(tid, ARG1,ARG2,ARG3);
   if (arg2tmp == 0)
      SET_STATUS_Failure( VKI_EINVAL );
   else
      ARG2 = arg2tmp;  
}
POST(wrap_sys_shmat)
{
   ML_(generic_POST_sys_shmat)(tid, RES,ARG1,ARG2,ARG3);
}

PRE(sys_shmdt)
{
   PRINT("sys_shmdt ( %#lx )",ARG1);
   PRE_REG_READ1(long, "shmdt", const void *, shmaddr);
   if (!ML_(generic_PRE_sys_shmdt)(tid, ARG1))
      SET_STATUS_Failure( VKI_EINVAL );
}
POST(sys_shmdt)
{
   ML_(generic_POST_sys_shmdt)(tid, RES,ARG1);
}

PRE(sys_shmctl)
{
   PRINT("sys_shmctl ( %ld, %ld, %#lx )",ARG1,ARG2,ARG3);
   PRE_REG_READ3(long, "shmctl",
                 int, shmid, int, cmd, struct shmid_ds *, buf);
   ML_(generic_PRE_sys_shmctl)(tid, ARG1,ARG2|VKI_IPC_64,ARG3);
}
POST(sys_shmctl)
{
   ML_(generic_POST_sys_shmctl)(tid, RES,ARG1,ARG2|VKI_IPC_64,ARG3);
}

PRE(sys_fadvise64)
{
   PRINT("sys_fadvise64 ( %ld, %ld, %lu, %ld )", ARG1,ARG2,ARG3,ARG4);
   PRE_REG_READ4(long, "fadvise64",
                 int, fd, vki_loff_t, offset, vki_size_t, len, int, advice);
}

PRE(sys_mmap)
{
   SysRes r;

   PRINT("sys_mmap ( %#lx, %llu, %ld, %ld, %d, %ld )",
         ARG1, (ULong)ARG2, ARG3, ARG4, (Int)ARG5, ARG6 );
   PRE_REG_READ6(long, "mmap",
                 unsigned long, start, unsigned long, length,
                 unsigned long, prot,  unsigned long, flags,
                 unsigned long, fd,    unsigned long, offset);

   r = ML_(generic_PRE_sys_mmap)( tid, ARG1, ARG2, ARG3, ARG4, ARG5, ARG6 );
   SET_STATUS_from_SysRes(r);
}



PRE(sys_syscall184)
{
   Int err;


   if (!VG_(strstr)(VG_(clo_kernel_variant), "bproc")) {
      PRINT("non-existent syscall! (syscall 184)");
      PRE_REG_READ0(long, "ni_syscall(184)");
      SET_STATUS_Failure( VKI_ENOSYS );
      return;
   }

   err = ML_(linux_variant_PRE_sys_bproc)( ARG1, ARG2, ARG3, 
                                           ARG4, ARG5, ARG6 );
   if (err) {
      SET_STATUS_Failure( err );
      return;
   }
   
   *flags |= SfMayBlock; 
}

POST(sys_syscall184)
{
   ML_(linux_variant_POST_sys_bproc)( ARG1, ARG2, ARG3, 
                                      ARG4, ARG5, ARG6 );
}

#undef PRE
#undef POST



#define PLAX_(const, name)    WRAPPER_ENTRY_X_(amd64_linux, const, name) 
#define PLAXY(const, name)    WRAPPER_ENTRY_XY(amd64_linux, const, name) 


static SyscallTableEntry syscall_table[] = {
   GENXY(__NR_read,              sys_read),           
   GENX_(__NR_write,             sys_write),          
   GENXY(__NR_open,              sys_open),           
   GENXY(__NR_close,             sys_close),          
   GENXY(__NR_stat,              sys_newstat),        

   GENXY(__NR_fstat,             sys_newfstat),       
   GENXY(__NR_lstat,             sys_newlstat),       
   GENXY(__NR_poll,              sys_poll),           
   LINX_(__NR_lseek,             sys_lseek),          
   PLAX_(__NR_mmap,              sys_mmap),           

   GENXY(__NR_mprotect,          sys_mprotect),       
   GENXY(__NR_munmap,            sys_munmap),         
   GENX_(__NR_brk,               sys_brk),            
   LINXY(__NR_rt_sigaction,      sys_rt_sigaction),   
   LINXY(__NR_rt_sigprocmask,    sys_rt_sigprocmask), 

   PLAX_(__NR_rt_sigreturn,      sys_rt_sigreturn),   
   LINXY(__NR_ioctl,             sys_ioctl),          
   GENXY(__NR_pread64,           sys_pread64),        
   GENX_(__NR_pwrite64,          sys_pwrite64),       
   GENXY(__NR_readv,             sys_readv),          

   GENX_(__NR_writev,            sys_writev),         
   GENX_(__NR_access,            sys_access),         
   LINXY(__NR_pipe,              sys_pipe),           
   GENX_(__NR_select,            sys_select),         
   LINX_(__NR_sched_yield,       sys_sched_yield),    

   GENX_(__NR_mremap,            sys_mremap),         
   GENX_(__NR_msync,             sys_msync),          
   GENXY(__NR_mincore,           sys_mincore),        
   GENX_(__NR_madvise,           sys_madvise),        
   PLAX_(__NR_shmget,            sys_shmget),         

   PLAXY(__NR_shmat,             wrap_sys_shmat),     
   PLAXY(__NR_shmctl,            sys_shmctl),         
   GENXY(__NR_dup,               sys_dup),            
   GENXY(__NR_dup2,              sys_dup2),           
   GENX_(__NR_pause,             sys_pause),          

   GENXY(__NR_nanosleep,         sys_nanosleep),      
   GENXY(__NR_getitimer,         sys_getitimer),      
   GENX_(__NR_alarm,             sys_alarm),          
   GENXY(__NR_setitimer,         sys_setitimer),      
   GENX_(__NR_getpid,            sys_getpid),         

   LINXY(__NR_sendfile,          sys_sendfile),       
   PLAXY(__NR_socket,            sys_socket),         
   PLAX_(__NR_connect,           sys_connect),        
   PLAXY(__NR_accept,            sys_accept),         
   PLAX_(__NR_sendto,            sys_sendto),         

   PLAXY(__NR_recvfrom,          sys_recvfrom),       
   PLAX_(__NR_sendmsg,           sys_sendmsg),        
   PLAXY(__NR_recvmsg,           sys_recvmsg),        
   PLAX_(__NR_shutdown,          sys_shutdown),       
   PLAX_(__NR_bind,              sys_bind),           

   PLAX_(__NR_listen,            sys_listen),         
   PLAXY(__NR_getsockname,       sys_getsockname),    
   PLAXY(__NR_getpeername,       sys_getpeername),    
   PLAXY(__NR_socketpair,        sys_socketpair),     
   PLAX_(__NR_setsockopt,        sys_setsockopt),     

   PLAXY(__NR_getsockopt,        sys_getsockopt),     
   PLAX_(__NR_clone,             sys_clone),          
   GENX_(__NR_fork,              sys_fork),           
   GENX_(__NR_vfork,             sys_fork),           
   GENX_(__NR_execve,            sys_execve),         

   GENX_(__NR_exit,              sys_exit),           
   GENXY(__NR_wait4,             sys_wait4),          
   GENX_(__NR_kill,              sys_kill),           
   GENXY(__NR_uname,             sys_newuname),       
   PLAX_(__NR_semget,            sys_semget),         

   PLAX_(__NR_semop,             sys_semop),          
   PLAXY(__NR_semctl,            sys_semctl),         
   PLAXY(__NR_shmdt,             sys_shmdt),          
   PLAX_(__NR_msgget,            sys_msgget),         
   PLAX_(__NR_msgsnd,            sys_msgsnd),         

   PLAXY(__NR_msgrcv,            sys_msgrcv),         
   PLAXY(__NR_msgctl,            sys_msgctl),         
   LINXY(__NR_fcntl,             sys_fcntl),          
   GENX_(__NR_flock,             sys_flock),          
   GENX_(__NR_fsync,             sys_fsync),          

   GENX_(__NR_fdatasync,         sys_fdatasync),      
   GENX_(__NR_truncate,          sys_truncate),       
   GENX_(__NR_ftruncate,         sys_ftruncate),      
   GENXY(__NR_getdents,          sys_getdents),       
   GENXY(__NR_getcwd,            sys_getcwd),         

   GENX_(__NR_chdir,             sys_chdir),          
   GENX_(__NR_fchdir,            sys_fchdir),         
   GENX_(__NR_rename,            sys_rename),         
   GENX_(__NR_mkdir,             sys_mkdir),          
   GENX_(__NR_rmdir,             sys_rmdir),          

   GENXY(__NR_creat,             sys_creat),          
   GENX_(__NR_link,              sys_link),           
   GENX_(__NR_unlink,            sys_unlink),         
   GENX_(__NR_symlink,           sys_symlink),        
   GENX_(__NR_readlink,          sys_readlink),       

   GENX_(__NR_chmod,             sys_chmod),          
   GENX_(__NR_fchmod,            sys_fchmod),         
   GENX_(__NR_chown,             sys_chown),          
   GENX_(__NR_fchown,            sys_fchown),         
   GENX_(__NR_lchown,            sys_lchown),         

   GENX_(__NR_umask,             sys_umask),          
   GENXY(__NR_gettimeofday,      sys_gettimeofday),   
   GENXY(__NR_getrlimit,         sys_getrlimit),      
   GENXY(__NR_getrusage,         sys_getrusage),      
   LINXY(__NR_sysinfo,           sys_sysinfo),        

   GENXY(__NR_times,             sys_times),          
   PLAXY(__NR_ptrace,            sys_ptrace),         
   GENX_(__NR_getuid,            sys_getuid),         
   LINXY(__NR_syslog,            sys_syslog),         
   GENX_(__NR_getgid,            sys_getgid),         

   GENX_(__NR_setuid,            sys_setuid),         
   GENX_(__NR_setgid,            sys_setgid),         
   GENX_(__NR_geteuid,           sys_geteuid),        
   GENX_(__NR_getegid,           sys_getegid),        
   GENX_(__NR_setpgid,           sys_setpgid),        

   GENX_(__NR_getppid,           sys_getppid),        
   GENX_(__NR_getpgrp,           sys_getpgrp),        
   GENX_(__NR_setsid,            sys_setsid),         
   GENX_(__NR_setreuid,          sys_setreuid),       
   GENX_(__NR_setregid,          sys_setregid),       

   GENXY(__NR_getgroups,         sys_getgroups),      
   GENX_(__NR_setgroups,         sys_setgroups),      
   LINX_(__NR_setresuid,         sys_setresuid),      
   LINXY(__NR_getresuid,         sys_getresuid),      
   LINX_(__NR_setresgid,         sys_setresgid),      

   LINXY(__NR_getresgid,         sys_getresgid),      
   GENX_(__NR_getpgid,           sys_getpgid),        
   LINX_(__NR_setfsuid,          sys_setfsuid),       
   LINX_(__NR_setfsgid,          sys_setfsgid),       
   GENX_(__NR_getsid,            sys_getsid),         

   LINXY(__NR_capget,            sys_capget),         
   LINX_(__NR_capset,            sys_capset),         
   LINXY(__NR_rt_sigpending,     sys_rt_sigpending),  
   LINXY(__NR_rt_sigtimedwait,   sys_rt_sigtimedwait),
   LINXY(__NR_rt_sigqueueinfo,   sys_rt_sigqueueinfo),

   LINX_(__NR_rt_sigsuspend,     sys_rt_sigsuspend),  
   GENXY(__NR_sigaltstack,       sys_sigaltstack),    
   LINX_(__NR_utime,             sys_utime),          
   GENX_(__NR_mknod,             sys_mknod),          
   

   LINX_(__NR_personality,       sys_personality),    
   
   GENXY(__NR_statfs,            sys_statfs),         
   GENXY(__NR_fstatfs,           sys_fstatfs),        
   

   GENX_(__NR_getpriority,             sys_getpriority),             
   GENX_(__NR_setpriority,             sys_setpriority),             
   LINXY(__NR_sched_setparam,          sys_sched_setparam),          
   LINXY(__NR_sched_getparam,          sys_sched_getparam),          
   LINX_(__NR_sched_setscheduler,      sys_sched_setscheduler),      

   LINX_(__NR_sched_getscheduler,      sys_sched_getscheduler),      
   LINX_(__NR_sched_get_priority_max,  sys_sched_get_priority_max),  
   LINX_(__NR_sched_get_priority_min,  sys_sched_get_priority_min),  
   LINXY(__NR_sched_rr_get_interval,   sys_sched_rr_get_interval),   
   GENX_(__NR_mlock,                   sys_mlock),                   

   GENX_(__NR_munlock,           sys_munlock),        
   GENX_(__NR_mlockall,          sys_mlockall),       
   LINX_(__NR_munlockall,        sys_munlockall),     
   LINX_(__NR_vhangup,           sys_vhangup),        
   

   
   LINXY(__NR__sysctl,           sys_sysctl),         
   LINXY(__NR_prctl,             sys_prctl),          
   PLAX_(__NR_arch_prctl,	 sys_arch_prctl),     
   LINXY(__NR_adjtimex,          sys_adjtimex),       

   GENX_(__NR_setrlimit,         sys_setrlimit),      
   GENX_(__NR_chroot,            sys_chroot),         
   GENX_(__NR_sync,              sys_sync),           
   
   GENX_(__NR_settimeofday,      sys_settimeofday),   

   LINX_(__NR_mount,             sys_mount),          
   LINX_(__NR_umount2,           sys_umount),         
   
   
   

   
   
   GENX_(__NR_iopl,              sys_iopl),           
   LINX_(__NR_ioperm,            sys_ioperm),         
   GENX_(__NR_create_module,     sys_ni_syscall),     

   LINX_(__NR_init_module,       sys_init_module),    
   LINX_(__NR_delete_module,     sys_delete_module),  
   
   
   LINX_(__NR_quotactl,          sys_quotactl),       

   
   
   
   
   PLAXY(184,                    sys_syscall184),     

   
   LINX_(__NR_gettid,            sys_gettid),         
   LINX_(__NR_readahead,         sys_readahead),      
   LINX_(__NR_setxattr,          sys_setxattr),       
   LINX_(__NR_lsetxattr,         sys_lsetxattr),      

   LINX_(__NR_fsetxattr,         sys_fsetxattr),      
   LINXY(__NR_getxattr,          sys_getxattr),       
   LINXY(__NR_lgetxattr,         sys_lgetxattr),      
   LINXY(__NR_fgetxattr,         sys_fgetxattr),      
   LINXY(__NR_listxattr,         sys_listxattr),      

   LINXY(__NR_llistxattr,        sys_llistxattr),     
   LINXY(__NR_flistxattr,        sys_flistxattr),     
   LINX_(__NR_removexattr,       sys_removexattr),    
   LINX_(__NR_lremovexattr,      sys_lremovexattr),   
   LINX_(__NR_fremovexattr,      sys_fremovexattr),   

   LINXY(__NR_tkill,             sys_tkill),             
   GENXY(__NR_time,              sys_time),  
   LINXY(__NR_futex,             sys_futex),             
   LINX_(__NR_sched_setaffinity, sys_sched_setaffinity), 
   LINXY(__NR_sched_getaffinity, sys_sched_getaffinity), 

   
   LINXY(__NR_io_setup,          sys_io_setup),       
   LINX_(__NR_io_destroy,        sys_io_destroy),     
   LINXY(__NR_io_getevents,      sys_io_getevents),   
   LINX_(__NR_io_submit,         sys_io_submit),      

   LINXY(__NR_io_cancel,         sys_io_cancel),      
   
   LINXY(__NR_lookup_dcookie,    sys_lookup_dcookie), 
   LINXY(__NR_epoll_create,      sys_epoll_create),   
   

   
   
   GENXY(__NR_getdents64,        sys_getdents64),     
   LINX_(__NR_set_tid_address,   sys_set_tid_address),
   

   PLAX_(__NR_semtimedop,        sys_semtimedop),     
   PLAX_(__NR_fadvise64,         sys_fadvise64),      
   LINXY(__NR_timer_create,      sys_timer_create),   
   LINXY(__NR_timer_settime,     sys_timer_settime),  
   LINXY(__NR_timer_gettime,     sys_timer_gettime),  

   LINX_(__NR_timer_getoverrun,  sys_timer_getoverrun), 
   LINX_(__NR_timer_delete,      sys_timer_delete),   
   LINX_(__NR_clock_settime,     sys_clock_settime),  
   LINXY(__NR_clock_gettime,     sys_clock_gettime),  
   LINXY(__NR_clock_getres,      sys_clock_getres),   

   LINXY(__NR_clock_nanosleep,   sys_clock_nanosleep),
   LINX_(__NR_exit_group,        sys_exit_group),     
   LINXY(__NR_epoll_wait,        sys_epoll_wait),     
   LINX_(__NR_epoll_ctl,         sys_epoll_ctl),      
   LINXY(__NR_tgkill,            sys_tgkill),         

   GENX_(__NR_utimes,            sys_utimes),         
   
   LINX_(__NR_mbind,             sys_mbind),          
   LINX_(__NR_set_mempolicy,     sys_set_mempolicy),  
   LINXY(__NR_get_mempolicy,     sys_get_mempolicy),  

   LINXY(__NR_mq_open,           sys_mq_open),        
   LINX_(__NR_mq_unlink,         sys_mq_unlink),      
   LINX_(__NR_mq_timedsend,      sys_mq_timedsend),   
   LINXY(__NR_mq_timedreceive,   sys_mq_timedreceive),
   LINX_(__NR_mq_notify,         sys_mq_notify),      

   LINXY(__NR_mq_getsetattr,     sys_mq_getsetattr),  
   
   LINXY(__NR_waitid,            sys_waitid),         
   LINX_(__NR_add_key,           sys_add_key),        
   LINX_(__NR_request_key,       sys_request_key),    

   LINXY(__NR_keyctl,            sys_keyctl),         
   LINX_(__NR_ioprio_set,        sys_ioprio_set),     
   LINX_(__NR_ioprio_get,        sys_ioprio_get),     
   LINX_(__NR_inotify_init,	 sys_inotify_init),   
   LINX_(__NR_inotify_add_watch, sys_inotify_add_watch), 

   LINX_(__NR_inotify_rm_watch,	 sys_inotify_rm_watch), 
   LINXY(__NR_openat,		 sys_openat),           
   LINX_(__NR_mkdirat,		 sys_mkdirat),          
   LINX_(__NR_mknodat,		 sys_mknodat),          

   LINX_(__NR_fchownat,		 sys_fchownat),         
   LINX_(__NR_futimesat,	 sys_futimesat),        
   LINXY(__NR_newfstatat,	 sys_newfstatat),       
   LINX_(__NR_unlinkat,		 sys_unlinkat),         
   LINX_(__NR_renameat,		 sys_renameat),         

   LINX_(__NR_linkat,		 sys_linkat),           
   LINX_(__NR_symlinkat,	 sys_symlinkat),        
   LINX_(__NR_readlinkat,	 sys_readlinkat),       
   LINX_(__NR_fchmodat,		 sys_fchmodat),         
   LINX_(__NR_faccessat,	 sys_faccessat),        

   LINX_(__NR_pselect6,		 sys_pselect6),         
   LINXY(__NR_ppoll,		 sys_ppoll),            
   LINX_(__NR_set_robust_list,	 sys_set_robust_list),  
   LINXY(__NR_get_robust_list,	 sys_get_robust_list),  

   LINX_(__NR_splice,            sys_splice),           
   LINX_(__NR_tee,               sys_tee),              
   LINX_(__NR_sync_file_range,   sys_sync_file_range),  
   LINXY(__NR_vmsplice,          sys_vmsplice),         
   LINXY(__NR_move_pages,        sys_move_pages),       

   LINX_(__NR_utimensat,         sys_utimensat),        
   LINXY(__NR_epoll_pwait,       sys_epoll_pwait),      
   LINXY(__NR_signalfd,          sys_signalfd),         
   LINXY(__NR_timerfd_create,    sys_timerfd_create),   
   LINX_(__NR_eventfd,           sys_eventfd),          

   LINX_(__NR_fallocate,         sys_fallocate),        
   LINXY(__NR_timerfd_settime,   sys_timerfd_settime),  
   LINXY(__NR_timerfd_gettime,   sys_timerfd_gettime),  
   PLAXY(__NR_accept4,           sys_accept4),          
   LINXY(__NR_signalfd4,         sys_signalfd4),        

   LINX_(__NR_eventfd2,          sys_eventfd2),         
   LINXY(__NR_epoll_create1,     sys_epoll_create1),    
   LINXY(__NR_dup3,              sys_dup3),             
   LINXY(__NR_pipe2,             sys_pipe2),            
   LINXY(__NR_inotify_init1,     sys_inotify_init1),    

   LINXY(__NR_preadv,            sys_preadv),           
   LINX_(__NR_pwritev,           sys_pwritev),          
   LINXY(__NR_rt_tgsigqueueinfo, sys_rt_tgsigqueueinfo),
   LINXY(__NR_perf_event_open,   sys_perf_event_open),  
   LINXY(__NR_recvmmsg,          sys_recvmmsg),         

   LINXY(__NR_prlimit64,         sys_prlimit64),        

   LINXY(__NR_sendmmsg,          sys_sendmmsg),         
   LINXY(__NR_getcpu,            sys_getcpu),           

   LINXY(__NR_process_vm_readv,  sys_process_vm_readv), 
   LINX_(__NR_process_vm_writev, sys_process_vm_writev) 
};

SyscallTableEntry* ML_(get_linux_syscall_entry) ( UInt sysno )
{
   const UInt syscall_table_size
      = sizeof(syscall_table) / sizeof(syscall_table[0]);

   
   if (sysno < syscall_table_size) {
      SyscallTableEntry* sys = &syscall_table[sysno];
      if (sys->before == NULL)
         return NULL; 
      else
         return sys;
   }

   
   return NULL;
}

#endif 

