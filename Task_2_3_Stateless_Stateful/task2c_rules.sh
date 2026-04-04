#!/bin/bash
# Task 2C - Protect Internal Servers (stateless)
iptables -A FORWARD -i eth0 -o eth1 -p tcp -d 192.168.60.5 --dport 23 -j ACCEPT
iptables -A FORWARD -i eth1 -o eth0 -p tcp -s 192.168.60.5 --sport 23 ! --syn -j ACCEPT
iptables -A FORWARD -i eth1 -o eth1 -p tcp --dport 23 -j ACCEPT
iptables -A FORWARD -i eth1 -o eth1 -p tcp --sport 23 ! --syn -j ACCEPT
iptables -P FORWARD DROP
