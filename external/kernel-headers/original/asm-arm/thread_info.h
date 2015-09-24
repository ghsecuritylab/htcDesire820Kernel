/*
 *  linux/include/asm-arm/thread_info.h
 *
 *  Copyright (C) 2002 Russell King.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#ifndef __ASM_ARM_THREAD_INFO_H
#define __ASM_ARM_THREAD_INFO_H

#ifdef __KERNEL__

#include <linux/compiler.h>
#include <asm/fpstate.h>

#define THREAD_SIZE_ORDER	1
#define THREAD_SIZE		8192
#define THREAD_START_SP		(THREAD_SIZE - 8)

#ifndef __ASSEMBLY__

struct task_struct;
struct exec_domain;

#include <asm/ptrace.h>
#include <asm/types.h>
#include <asm/domain.h>

typedef unsigned long mm_segment_t;

struct cpu_context_save {
	__u32	r4;
	__u32	r5;
	__u32	r6;
	__u32	r7;
	__u32	r8;
	__u32	r9;
	__u32	sl;
	__u32	fp;
	__u32	sp;
	__u32	pc;
	__u32	extra[2];		
};

struct thread_info {
	unsigned long		flags;		
	int			preempt_count;	
	mm_segment_t		addr_limit;	
	struct task_struct	*task;		
	struct exec_domain	*exec_domain;	
	__u32			cpu;		
	__u32			cpu_domain;	
	struct cpu_context_save	cpu_context;	
	__u8			used_cp[16];	
	unsigned long		tp_value;
	struct crunch_state	crunchstate;
	union fp_state		fpstate __attribute__((aligned(8)));
	union vfp_state		vfpstate;
	struct restart_block	restart_block;
};

#define INIT_THREAD_INFO(tsk)						\
{									\
	.task		= &tsk,						\
	.exec_domain	= &default_exec_domain,				\
	.flags		= 0,						\
	.preempt_count	= 1,						\
	.addr_limit	= KERNEL_DS,					\
	.cpu_domain	= domain_val(DOMAIN_USER, DOMAIN_MANAGER) |	\
			  domain_val(DOMAIN_KERNEL, DOMAIN_MANAGER) |	\
			  domain_val(DOMAIN_IO, DOMAIN_CLIENT),		\
	.restart_block	= {						\
		.fn	= do_no_restart_syscall,			\
	},								\
}

#define init_thread_info	(init_thread_union.thread_info)
#define init_stack		(init_thread_union.stack)

static inline struct thread_info *current_thread_info(void) __attribute_const__;

static inline struct thread_info *current_thread_info(void)
{
	register unsigned long sp asm ("sp");
	return (struct thread_info *)(sp & ~(THREAD_SIZE - 1));
}

extern struct thread_info *alloc_thread_info(struct task_struct *task);
extern void free_thread_info(struct thread_info *);

#define thread_saved_pc(tsk)	\
	((unsigned long)(pc_pointer(task_thread_info(tsk)->cpu_context.pc)))
#define thread_saved_fp(tsk)	\
	((unsigned long)(task_thread_info(tsk)->cpu_context.fp))

extern void crunch_task_disable(struct thread_info *);
extern void crunch_task_copy(struct thread_info *, void *);
extern void crunch_task_restore(struct thread_info *, void *);
extern void crunch_task_release(struct thread_info *);

extern void iwmmxt_task_disable(struct thread_info *);
extern void iwmmxt_task_copy(struct thread_info *, void *);
extern void iwmmxt_task_restore(struct thread_info *, void *);
extern void iwmmxt_task_release(struct thread_info *);
extern void iwmmxt_task_switch(struct thread_info *);

#endif

#define PREEMPT_ACTIVE	0x40000000

#define TIF_NOTIFY_RESUME	0
#define TIF_SIGPENDING		1
#define TIF_NEED_RESCHED	2
#define TIF_SYSCALL_TRACE	8
#define TIF_POLLING_NRFLAG	16
#define TIF_USING_IWMMXT	17
#define TIF_MEMDIE		18

#define _TIF_NOTIFY_RESUME	(1 << TIF_NOTIFY_RESUME)
#define _TIF_SIGPENDING		(1 << TIF_SIGPENDING)
#define _TIF_NEED_RESCHED	(1 << TIF_NEED_RESCHED)
#define _TIF_SYSCALL_TRACE	(1 << TIF_SYSCALL_TRACE)
#define _TIF_POLLING_NRFLAG	(1 << TIF_POLLING_NRFLAG)
#define _TIF_USING_IWMMXT	(1 << TIF_USING_IWMMXT)

#define _TIF_WORK_MASK		0x000000ff

#endif 
#endif 