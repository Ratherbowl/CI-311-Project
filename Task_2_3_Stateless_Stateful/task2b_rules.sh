#!/bin/bash
# Task 2B - Protect Internal Network (ICMP)
iptables -A FORWARD -i eth1 -p icmp --icmp-type echo-request -j ACCEPT
iptables -A FORWARD -o eth1 -p icmp --icmp-type echo-reply -j ACCEPT
iptables -P FORWARD DROP

