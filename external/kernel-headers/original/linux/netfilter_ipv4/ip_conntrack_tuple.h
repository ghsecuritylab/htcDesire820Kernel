#ifndef _IP_CONNTRACK_TUPLE_H
#define _IP_CONNTRACK_TUPLE_H

#include <linux/types.h>
#include <linux/netfilter/nf_conntrack_tuple_common.h>


union ip_conntrack_manip_proto
{
	
	u_int16_t all;

	struct {
		__be16 port;
	} tcp;
	struct {
		u_int16_t port;
	} udp;
	struct {
		u_int16_t id;
	} icmp;
	struct {
		u_int16_t port;
	} sctp;
	struct {
		__be16 key;	
	} gre;
};

struct ip_conntrack_manip
{
	u_int32_t ip;
	union ip_conntrack_manip_proto u;
};

struct ip_conntrack_tuple
{
	struct ip_conntrack_manip src;

	
	struct {
		u_int32_t ip;
		union {
			
			u_int16_t all;

			struct {
				u_int16_t port;
			} tcp;
			struct {
				u_int16_t port;
			} udp;
			struct {
				u_int8_t type, code;
			} icmp;
			struct {
				u_int16_t port;
			} sctp;
			struct {
				__be16 key;	
			} gre;
		} u;

		
		u_int8_t protonum;

		
		u_int8_t dir;
	} dst;
};

#define IP_CT_TUPLE_U_BLANK(tuple) 				\
	do {							\
		(tuple)->src.u.all = 0;				\
		(tuple)->dst.u.all = 0;				\
	} while (0)

#ifdef __KERNEL__

#define DUMP_TUPLE(tp)						\
DEBUGP("tuple %p: %u %u.%u.%u.%u:%hu -> %u.%u.%u.%u:%hu\n",	\
       (tp), (tp)->dst.protonum,				\
       NIPQUAD((tp)->src.ip), ntohs((tp)->src.u.all),		\
       NIPQUAD((tp)->dst.ip), ntohs((tp)->dst.u.all))

#define DIRECTION(h) ((enum ip_conntrack_dir)(h)->tuple.dst.dir)

struct ip_conntrack_tuple_hash
{
	struct list_head list;

	struct ip_conntrack_tuple tuple;
};

#endif 

static inline int ip_ct_tuple_src_equal(const struct ip_conntrack_tuple *t1,
				        const struct ip_conntrack_tuple *t2)
{
	return t1->src.ip == t2->src.ip
		&& t1->src.u.all == t2->src.u.all;
}

static inline int ip_ct_tuple_dst_equal(const struct ip_conntrack_tuple *t1,
				        const struct ip_conntrack_tuple *t2)
{
	return t1->dst.ip == t2->dst.ip
		&& t1->dst.u.all == t2->dst.u.all
		&& t1->dst.protonum == t2->dst.protonum;
}

static inline int ip_ct_tuple_equal(const struct ip_conntrack_tuple *t1,
				    const struct ip_conntrack_tuple *t2)
{
	return ip_ct_tuple_src_equal(t1, t2) && ip_ct_tuple_dst_equal(t1, t2);
}

static inline int ip_ct_tuple_mask_cmp(const struct ip_conntrack_tuple *t,
				       const struct ip_conntrack_tuple *tuple,
				       const struct ip_conntrack_tuple *mask)
{
	return !(((t->src.ip ^ tuple->src.ip) & mask->src.ip)
		 || ((t->dst.ip ^ tuple->dst.ip) & mask->dst.ip)
		 || ((t->src.u.all ^ tuple->src.u.all) & mask->src.u.all)
		 || ((t->dst.u.all ^ tuple->dst.u.all) & mask->dst.u.all)
		 || ((t->dst.protonum ^ tuple->dst.protonum)
		     & mask->dst.protonum));
}

#endif 