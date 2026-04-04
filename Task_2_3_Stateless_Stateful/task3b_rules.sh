#!/bin/bash
# Task 3B - Stateful Firewall with conntrack
iptables -A FORWARD -m conntrack --ctstate ESTABLISHED,RELATED -j ACCEPT
iptables -A FORWARD -i eth0 -o eth1 -p tcp -d 192.168.60.5 --dport 23 --syn -m conntrack --ctstate NEW -j ACCEPT
iptables -A FORWARD -i eth1 -o eth1 -m conntrack --ctstate NEW -j ACCEPT
iptables -A FORWARD -i eth1 -o eth0 -m conntrack --ctstate NEW -j ACCEPT
iptables -P FORWARD DROP
