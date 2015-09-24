
#include <linux/netfilter_bridge/ebtables.h>
#include <linux/module.h>
#include <linux/if_bridge.h>
#include <linux/brlock.h>

static struct ebt_entries initial_chain =
  {0, "BROUTING", 0, EBT_ACCEPT, 0};

static struct ebt_replace initial_table =
{
  "broute", 1 << NF_BR_BROUTING, 0, sizeof(struct ebt_entries),
  { [NF_BR_BROUTING]&initial_chain}, 0, NULL, (char *)&initial_chain
};

static int check(const struct ebt_table_info *info, unsigned int valid_hooks)
{
	if (valid_hooks & ~(1 << NF_BR_BROUTING))
		return -EINVAL;
	return 0;
}

static struct ebt_table broute_table =
{
  {NULL, NULL}, "broute", &initial_table, 1 << NF_BR_BROUTING,
  RW_LOCK_UNLOCKED, check, NULL
};

static int ebt_broute(struct sk_buff **pskb)
{
	int ret;

	ret = ebt_do_table(NF_BR_BROUTING, pskb, (*pskb)->dev, NULL,
	   &broute_table);
	if (ret == NF_DROP)
		return 1; 
	return 0; 
}

static int __init init(void)
{
	int ret;

	ret = ebt_register_table(&broute_table);
	if (ret < 0)
		return ret;
	br_write_lock_bh(BR_NETPROTO_LOCK);
	
	br_should_route_hook = ebt_broute;
	br_write_unlock_bh(BR_NETPROTO_LOCK);
	return ret;
}

static void __exit fini(void)
{
	br_write_lock_bh(BR_NETPROTO_LOCK);
	br_should_route_hook = NULL;
	br_write_unlock_bh(BR_NETPROTO_LOCK);
	ebt_unregister_table(&broute_table);
}

module_init(init);
module_exit(fini);
EXPORT_NO_SYMBOLS;
MODULE_LICENSE("GPL");
