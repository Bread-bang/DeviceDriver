cmd_/root/work/dd/iom_virtual_dd/Module.symvers :=  sed 's/ko$$/o/'  /root/work/dd/iom_virtual_dd/modules.order | scripts/mod/modpost -m -a    -o /root/work/dd/iom_virtual_dd/Module.symvers -e -i Module.symvers -T - 
