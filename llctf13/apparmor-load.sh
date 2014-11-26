#!/bin/sh
echo -n /home/nickolai/sp/talks/llctf13/plain > /sys/kernel/security/apparmor/.remove
/sbin/apparmor_parser ./apparmor-policy
