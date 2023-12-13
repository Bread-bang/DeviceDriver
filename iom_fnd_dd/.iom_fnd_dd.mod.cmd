cmd_/root/work/dd/iom_fnd_dd/iom_fnd_dd.mod := printf '%s\n'   iom_fnd_dd.o | awk '!x[$$0]++ { print("/root/work/dd/iom_fnd_dd/"$$0) }' > /root/work/dd/iom_fnd_dd/iom_fnd_dd.mod
