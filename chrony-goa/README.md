
# Chrony to Goa

[Genode OS](https://genode.org/) [Goa](https://github.com/genodelabs/goa/) port of [Chrony](https://chrony-project.org).

The runscript is currently Linux-only (because it is hardwired to use
system_rtc-linux) and expects a DHCP server and NAT to the Internet
on tap0.

example networking script with dnsmasq and iptables-based NAT:

```

#!/bin/sh

set +e

IFACE_OUT=enp0s3

# tun/tap
# script is run as root, adapt user to your non-root user
ip tuntap add dev tap0 mode tap user ben
ip address flush dev tap0
ip addr add 10.0.2.1/24 dev tap0
ip link set dev tap0 up

# NAT
sysctl net.ipv4.ip_forward=1
iptables -F
iptables -t nat -F
iptables -t nat -A POSTROUTING -o $IFACE_OUT -j MASQUERADE
iptables -A FORWARD -i tap0 -o $IFACE_OUT -m state --state RELATED,ESTABLISHED -j ACCEPT
iptables -A FORWARD -i $IFACE_OUT -o tap0 -j ACCEPT

# DHCP
dnsmasq -d -C ~/tools/goa-dnsmasq.conf

# tear down nat
iptables -t nat -F
iptables -F
sysctl net.ipv4.ip_forward=0

# tear down tun/tap
ip link set dev tap0 down
ip addr del 10.0.2.1/24 dev tap0
ip tuntap del dev tap0 mode tap
```

`goa-dnsmasq.conf`:

```
port=5353
interface=tap0
domain=lan
dhcp-range=10.0.2.55,10.0.2.55,12h
# set Google name server
dhcp-option=6,8.8.8.8
```
