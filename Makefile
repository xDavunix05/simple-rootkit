obj-m += rootkit.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
cleanup:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
