#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/ip.h>
#include <linux/tcp.h>
#include <linux/udp.h>
#include <linux/icmp.h>
#include <linux/in.h>


static struct nf_hook_ops nfho_in;
static struct nf_hook_ops nfho_out;


unsigned int hook_func_in(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)

{

    struct iphdr *ip_header;
    struct tcphdr *tcp_header;

    if (!skb)
        return NF_ACCEPT;

    ip_header = ip_hdr(skb);
    if (!ip_header)
        return NF_ACCEPT;

    if (ip_header->protocol == IPPROTO_ICMP) {
        printk(KERN_INFO "[Kernel Firewall] Dropped ICMP packet\n");
        return NF_DROP;
    }

    if (ip_header->protocol == IPPROTO_TCP) {
        tcp_header = tcp_hdr(skb);
        if (ntohs(tcp_header->dest) == 23) {
            printk(KERN_INFO "[Kernel Firewall] Dropped incoming Telnet packet\n");
            return NF_DROP;
        }
    }

    return NF_ACCEPT;

}


unsigned int hook_func_out(void *priv, struct sk_buff *skb, const struct nf_hook_state *state)

{

    struct iphdr *ip_header;
    struct udphdr *udp_header;
    struct tcphdr *tcp_header;

    if (!skb)
        return NF_ACCEPT;

    ip_header = ip_hdr(skb);
    if (!ip_header)
        return NF_ACCEPT;

    if (ip_header->protocol == IPPROTO_UDP) {
        udp_header = udp_hdr(skb);

        if (ip_header->daddr == in_aton("8.8.8.8") &&
            ntohs(udp_header->dest) == 53) {
            printk(KERN_INFO "[Kernel Firewall] Dropped DNS request to 8.8.8.8\n");
            return NF_DROP;
        }
    }

    if (ip_header->protocol == IPPROTO_TCP) {
        tcp_header = tcp_hdr(skb);

        if (ntohs(tcp_header->dest) == 23) {
            printk(KERN_INFO "[Kernel Firewall] Dropped outgoing Telnet packet\n");
            return NF_DROP;
        }
    }

    return NF_ACCEPT;

}


static int __init seedFilter_init(void)

{

    printk(KERN_INFO "[Kernel Firewall] Initializing module...\n");

    nfho_in.hook = hook_func_in;
    nfho_in.hooknum = NF_INET_LOCAL_IN;
    nfho_in.pf = PF_INET;
    nfho_in.priority = NF_IP_PRI_FIRST;

    nf_register_net_hook(&init_net, &nfho_in);

    nfho_out.hook = hook_func_out;
    nfho_out.hooknum = NF_INET_POST_ROUTING;
    nfho_out.pf = PF_INET;
    nfho_out.priority = NF_IP_PRI_FIRST;

    nf_register_net_hook(&init_net, &nfho_out);

    printk(KERN_INFO "[Kernel Firewall] Module loaded successfully\n");
    return 0;

}


static void __exit seedFilter_exit(void)

{

    printk(KERN_INFO "[Kernel Firewall] Removing module...\n");

    nf_unregister_net_hook(&init_net, &nfho_in);
    nf_unregister_net_hook(&init_net, &nfho_out);

    printk(KERN_INFO "[Kernel Firewall] Module removed successfully\n");

}

module_init(seedFilter_init);
module_exit(seedFilter_exit);
