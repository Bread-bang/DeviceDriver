cmd_/root/work/dd/iom_virtual_dd/iom_virtual_dd.mod := printf '%s\n'   iom_virtual_dd.o | awk '!x[$$0]++ { print("/root/work/dd/iom_virtual_dd/"$$0) }' > /root/work/dd/iom_virtual_dd/iom_virtual_dd.mod