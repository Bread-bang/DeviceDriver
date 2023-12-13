MODULE_FILES=iom_fnd_dd
TEST_PGM = test_iom_fnd_dd

obj-m += $(MODULE_FILES).o
KDIR = /lib/modules/$(shell uname -r)/build
PWD = $(shell pwd)

all: module test_pgm

module:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

test_pgm:
	$(CC) -o $(TEST_PGM) $(TEST_PGM).c

clean:
	@$(MAKE) -C $(KDIR) M=$(PWD) clean
	rm -rf Module.symvers modules.order
