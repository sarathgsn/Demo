ifneq ($(KERNELRELEASE),) 
   obj-m := kernel_logs.o
else 

KERNELDIR ?= /lib/modules/$(shell uname -r)/build 

PWD := $(shell pwd)

default: 
	make -C $(KERNELDIR) M=$(PWD) modules  
clean:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) clean
endif 
