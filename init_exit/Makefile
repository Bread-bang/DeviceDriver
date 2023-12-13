MODULE_FILES=init_exit
obj-m += $(MODULE_FILES).o
KDIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

all: module

module:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	@$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -rf Module.symvers modules.order
