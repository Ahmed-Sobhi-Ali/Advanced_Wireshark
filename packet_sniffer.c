
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Ahmed Sobhi Ali");
MODULE_DESCRIPTION("A Kernel Module for Real-time Packet Sniffing");
MODULE_VERSION("1.0");

static struct nf_hook_ops netfilter_ops;

static unsigned int packet_sniffer_hook(void *priv, struct sk_buff *skb, const struct nf_hook_state *state) {
    printk(KERN_INFO "Packet captured!\n");
    return NF_ACCEPT; // Allow packet to continue through the stack
}

static int __init packet_sniffer_init(void) {
    printk(KERN_INFO "Initializing Packet Sniffer Module\n");
    netfilter_ops.hook = packet_sniffer_hook;
    netfilter_ops.hooknum = NF_INET_PRE_ROUTING;
    netfilter_ops.pf = PF_INET;
    netfilter_ops.priority = NF_IP_PRI_FIRST;
    nf_register_hook(&netfilter_ops);
    return 0;
}

static void __exit packet_sniffer_exit(void) {
    printk(KERN_INFO "Removing Packet Sniffer Module\n");
    nf_unregister_hook(&netfilter_ops);
}

module_init(packet_sniffer_init);
module_exit(packet_sniffer_exit);
