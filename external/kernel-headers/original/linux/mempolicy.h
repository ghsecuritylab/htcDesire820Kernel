#ifndef _LINUX_MEMPOLICY_H
#define _LINUX_MEMPOLICY_H 1

#include <linux/errno.h>

/*
 * NUMA memory policies for Linux.
 * Copyright 2003,2004 Andi Kleen SuSE Labs
 */

#define MPOL_DEFAULT	0
#define MPOL_PREFERRED	1
#define MPOL_BIND	2
#define MPOL_INTERLEAVE	3

#define MPOL_MAX MPOL_INTERLEAVE

#define MPOL_F_NODE	(1<<0)	
#define MPOL_F_ADDR	(1<<1)	

#define MPOL_MF_STRICT	(1<<0)	
#define MPOL_MF_MOVE	(1<<1)	
#define MPOL_MF_MOVE_ALL (1<<2)	
#define MPOL_MF_INTERNAL (1<<3)	

#ifdef __KERNEL__

#include <linux/mmzone.h>
#include <linux/slab.h>
#include <linux/rbtree.h>
#include <linux/spinlock.h>
#include <linux/nodemask.h>

struct vm_area_struct;
struct mm_struct;

#ifdef CONFIG_NUMA

struct mempolicy {
	atomic_t refcnt;
	short policy; 	
	union {
		struct zonelist  *zonelist;	
		short 		 preferred_node; 
		nodemask_t	 nodes;		
		
	} v;
	nodemask_t cpuset_mems_allowed;	
};


extern void __mpol_free(struct mempolicy *pol);
static inline void mpol_free(struct mempolicy *pol)
{
	if (pol)
		__mpol_free(pol);
}

extern struct mempolicy *__mpol_copy(struct mempolicy *pol);
static inline struct mempolicy *mpol_copy(struct mempolicy *pol)
{
	if (pol)
		pol = __mpol_copy(pol);
	return pol;
}

#define vma_policy(vma) ((vma)->vm_policy)
#define vma_set_policy(vma, pol) ((vma)->vm_policy = (pol))

static inline void mpol_get(struct mempolicy *pol)
{
	if (pol)
		atomic_inc(&pol->refcnt);
}

extern int __mpol_equal(struct mempolicy *a, struct mempolicy *b);
static inline int mpol_equal(struct mempolicy *a, struct mempolicy *b)
{
	if (a == b)
		return 1;
	return __mpol_equal(a, b);
}
#define vma_mpol_equal(a,b) mpol_equal(vma_policy(a), vma_policy(b))


#define mpol_set_vma_default(vma) ((vma)->vm_policy = NULL)


struct sp_node {
	struct rb_node nd;
	unsigned long start, end;
	struct mempolicy *policy;
};

struct shared_policy {
	struct rb_root root;
	spinlock_t lock;
};

void mpol_shared_policy_init(struct shared_policy *info, int policy,
				nodemask_t *nodes);
int mpol_set_shared_policy(struct shared_policy *info,
				struct vm_area_struct *vma,
				struct mempolicy *new);
void mpol_free_shared_policy(struct shared_policy *p);
struct mempolicy *mpol_shared_policy_lookup(struct shared_policy *sp,
					    unsigned long idx);

extern void numa_default_policy(void);
extern void numa_policy_init(void);
extern void mpol_rebind_policy(struct mempolicy *pol, const nodemask_t *new);
extern void mpol_rebind_task(struct task_struct *tsk,
					const nodemask_t *new);
extern void mpol_rebind_mm(struct mm_struct *mm, nodemask_t *new);
extern void mpol_fix_fork_child_flag(struct task_struct *p);
#define set_cpuset_being_rebound(x) (cpuset_being_rebound = (x))

#ifdef CONFIG_CPUSET
#define current_cpuset_is_being_rebound() \
				(cpuset_being_rebound == current->cpuset)
#else
#define current_cpuset_is_being_rebound() 0
#endif

extern struct mempolicy default_policy;
extern struct zonelist *huge_zonelist(struct vm_area_struct *vma,
		unsigned long addr);
extern unsigned slab_node(struct mempolicy *policy);

extern int policy_zone;

static inline void check_highest_zone(int k)
{
	if (k > policy_zone)
		policy_zone = k;
}

int do_migrate_pages(struct mm_struct *mm,
	const nodemask_t *from_nodes, const nodemask_t *to_nodes, int flags);

extern void *cpuset_being_rebound;	

#else

struct mempolicy {};

static inline int mpol_equal(struct mempolicy *a, struct mempolicy *b)
{
	return 1;
}
#define vma_mpol_equal(a,b) 1

#define mpol_set_vma_default(vma) do {} while(0)

static inline void mpol_free(struct mempolicy *p)
{
}

static inline void mpol_get(struct mempolicy *pol)
{
}

static inline struct mempolicy *mpol_copy(struct mempolicy *old)
{
	return NULL;
}

struct shared_policy {};

static inline int mpol_set_shared_policy(struct shared_policy *info,
					struct vm_area_struct *vma,
					struct mempolicy *new)
{
	return -EINVAL;
}

static inline void mpol_shared_policy_init(struct shared_policy *info,
					int policy, nodemask_t *nodes)
{
}

static inline void mpol_free_shared_policy(struct shared_policy *p)
{
}

static inline struct mempolicy *
mpol_shared_policy_lookup(struct shared_policy *sp, unsigned long idx)
{
	return NULL;
}

#define vma_policy(vma) NULL
#define vma_set_policy(vma, pol) do {} while(0)

static inline void numa_policy_init(void)
{
}

static inline void numa_default_policy(void)
{
}

static inline void mpol_rebind_policy(struct mempolicy *pol,
					const nodemask_t *new)
{
}

static inline void mpol_rebind_task(struct task_struct *tsk,
					const nodemask_t *new)
{
}

static inline void mpol_rebind_mm(struct mm_struct *mm, nodemask_t *new)
{
}

static inline void mpol_fix_fork_child_flag(struct task_struct *p)
{
}

#define set_cpuset_being_rebound(x) do {} while (0)

static inline struct zonelist *huge_zonelist(struct vm_area_struct *vma,
		unsigned long addr)
{
	return NODE_DATA(0)->node_zonelists + gfp_zone(GFP_HIGHUSER);
}

static inline int do_migrate_pages(struct mm_struct *mm,
			const nodemask_t *from_nodes,
			const nodemask_t *to_nodes, int flags)
{
	return 0;
}

static inline void check_highest_zone(int k)
{
}
#endif 
#endif 

#endif