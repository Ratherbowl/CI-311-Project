#!/bin/bash

iptables -F
iptables -X
iptables -t nat -F

iptables -P INPUT ACCEPT
iptables -P OUTPUT ACCEPT
iptables -P FORWARD DROP

echo "[Firewall] Default policies set"

iptables -A INPUT -p icmp -j DROP
iptables -A FORWARD -p icmp -j DROP
echo "[Firewall] ICMP blocked"

iptables -A OUTPUT -p udp -d 8.8.8.8 --dport 53 -j DROP
iptables -A FORWARD -p udp -d 8.8.8.8 --dport 53 -j DROP
echo "[Firewall] DNS to 8.8.8.8 blocked"

iptables -A INPUT -p tcp --dport 23 -j DROP
iptables -A OUTPUT -p tcp --dport 23 -j DROP
iptables -A FORWARD -p tcp --dport 23 -j DROP
echo "[Firewall] Telnet blocked"

iptables -A FORWARD -j ACCEPT

echo "[Firewall] Stateless rules applied successfully"
