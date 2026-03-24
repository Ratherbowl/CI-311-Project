# CI-311-Project
This `README.md` is designed for a professional, academic GitHub repository. It ensures that all three team members stay synchronized while navigating the complexities of kernel modules and network protocols.

---

# SEED Labs: Firewall Exploration Project
**Course:** Cybersecurity Lab  
[cite_start]**Environment:** SEED Ubuntu 20.04 VM / Docker Containers [cite: 23, 27]

## 🚀 Overview
This project explores the implementation and configuration of both stateless and stateful firewalls. [cite_start]We utilize **Linux Kernel Modules (LKM)** with **Netfilter** for low-level packet filtering and **iptables** for high-level network policy management. [cite: 8, 86, 290]

---

## 🛠 Lab Setup
[cite_start]To ensure the network topology is consistent across all team members, use the following commands within the SEED VM: [cite: 23, 44]

1.  **Clone the Repo:** `git clone <repo-url>`
2.  **Initialize Containers:** Navigate to the `Labsetup` directory and run:
    * `dcbuild` (Builds the images)
    * `dcup` (Starts the network)
3.  **Accessing the Router:** `docksh <router-id>` (Most `iptables` work happens here)



---

## 👥 Contributor Roles & Directory Structure

### 1. John: Kernel Developer (`/Task1_Kernel`)
* **Focus:** Task 1
* **Responsibilities:**
    * Implement `seedFilter.c` using Netfilter hooks (`LOCAL_IN`, `POST_ROUTING`).
    * Logic for blocking DNS (8.8.8.8), Ping, and Telnet at the kernel level.
    * **Safety:** Must ensure `removeFilter` unregisters all hooks to prevent kernel panics.

### 2. Brody: Policy Lead (`/Task2_3_Iptables`)
* **Focus:** Tasks 2 & 3
* **Responsibilities:**
    * Configure stateless `iptables` rules for the router and internal network.
    * Transition to stateful rules using the `conntrack` module.
    * Manage the `FORWARD` chain and `ESTABLISHED,RELATED` states.

### 3. Darius: Traffic Engineer (`/Task4_5_Advanced`)
* **Focus:** Tasks 4 & 5
* **Responsibilities:**
    * Implement rate-limiting rules using the `limit` module.
    * Configure load balancing across internal servers (.5, .6, and .7) using the `statistic` module.
    * Handle `nth` (round-robin) and `random` (probability) balancing modes.
