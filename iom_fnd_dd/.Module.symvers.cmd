cmd_/root/work/dd/iom_fnd_dd/Module.symvers :=  sed 's/ko$$/o/'  /root/work/dd/iom_fnd_dd/modules.order | scripts/mod/modpost -m -a    -o /root/work/dd/iom_fnd_dd/Module.symvers -e -i Module.symvers -T - 