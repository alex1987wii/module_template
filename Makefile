ifneq ($(KERNELRELEASE),)
	obj-m = test_module.o
else
KDIR = /lib/modules/`uname -r`/build
PWD = $(shell pwd)
all:
	make -C $(KDIR) M=$(PWD) modules
clean:
	@find . ! -path "./Makefile" -a ! -path "./test_module.c" -a ! -path "." -a ! -path ".." -a ! -path "./.git*" | xargs rm -rf
endif
