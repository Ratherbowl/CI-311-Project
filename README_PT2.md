# Task 2 & 3 - Stateless and Stateful Firewall Rules

## Network Interfaces
- eth0 = external (10.9.0.0/24)
- eth1 = internal (192.168.60.0/24)

## Task 2A - Protect the Router
Allows ping to router, blocks all other INPUT/OUTPUT.

## Task 2B - Protect Internal Network
Internal hosts can ping outside, outside cannot ping internal.

## Task 2C - Protect Internal Servers (Stateless)
Outside can only telnet to 192.168.60.5.
Internal hosts can telnet each other.
Internal hosts cannot reach external servers.

## Task 3A - Connection Tracking Observations
- ICMP: tracked with ~30 second timeout
- UDP: tracked as UNREPLIED, ~30 second timeout
- TCP: tracked as ESTABLISHED/ASSURED, ~120 second timeout after close

## Task 3B - Stateful Firewall (conntrack)
Same as 2C but uses conntrack ESTABLISHED,RELATED.
Internal hosts can now also reach external servers.
