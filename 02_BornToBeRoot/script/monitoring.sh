#!/bin/bash

# show system
arch=$(uname -a)

# show CPU
cpu_physical=$(grep "^physical id" /proc/cpuinfo | wc -l)

# show virtual CPU
cpu_virtual=$(grep "^processor" /proc/cpuinfo | wc -l)

# RAM
ram_total=$(free --mega | grep "^Mem:" | awk '{print $2}')
ram_used=$(free --mega | grep "^Mem:" | awk '{print $3}')
ram_percent=$(awk -v ram_used="$ram_used" -v ram_total="$ram_total" 'BEGIN {printf "%.2f", ram_used * 100 / ram_total}')

# DISK
hd_total=$(df -m | grep "^/dev/" | grep -v "/boot" | awk '{total += $2} END {print total}')
hd_used=$(df -m | grep "^/dev/" | grep -v "/boot" | awk '{total += $3} END {print total}')
hd_gb=$(awk "BEGIN {printf \"%.1f\", $hd_total / 1024}")
hd_percent=$(awk -v hd_used="$hd_used" -v hd_total="$hd_total" 'BEGIN {printf "%.2f", hd_used * 100 / hd_total}')

# CPU LOAD
#cpu=$(top -bn2 | grep "Cpu(s)" | tail -n1 | awk '{print 100 - $8 "%"}')
cpu_idle=$(vmstat 1 2 | tail -1 | awk '{print $15}')
cpu=$(awk -v cpu_idle="$cpu_idle" 'BEGIN {printf "%.1f", 100 - cpu_idle}')

# BOOT TIME
boot=$(uptime -s)

# LOGICAL VOLUME MANAGER
lvm=$(lsblk -o TYPE | grep -q "lvm" && echo "yes" || echo "no")

# CONNECTIONS STABLISHED
tcp=$(ss -s | grep "^TCP:" | awk '{print $2}')

# USERS CONNECTED
users=$(who | wc -l)

# IP MAC
ip=$(hostname -I)
mac=$(ip link show | grep "link/ether" | awk '{print $2}')

wall "
#Architecture: $arch
#CPU physical: $cpu_physical
#vCPU: $cpu_virtual
#Memory Usage: $ram_used/${ram_total}MB ($ram_percent%)
#Disk Usage: $hd_used/${hd_gb}Gb ($hd_percent%)
#CPU load: $cpu
#Last boot: $boot
#LVM use: $lvm
#TCP Connections: $tcp ESTABLISHED
#User log: $users
#Network: IP $ip ($mac)
"
