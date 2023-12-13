cmd_/root/work/dd/iom_mydevice/iom_mydevice.mod := printf '%s\n'   iom_mydevice.o | awk '!x[$$0]++ { print("/root/work/dd/iom_mydevice/"$$0) }' > /root/work/dd/iom_mydevice/iom_mydevice.mod
