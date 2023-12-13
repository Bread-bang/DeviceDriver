cmd_/root/work/dd/iom_led_dd/iom_led_dd.mod := printf '%s\n'   iom_led_dd.o | awk '!x[$$0]++ { print("/root/work/dd/iom_led_dd/"$$0) }' > /root/work/dd/iom_led_dd/iom_led_dd.mod
