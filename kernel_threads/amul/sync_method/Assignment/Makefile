
obj-m:=kmod.o 
KDIR:=/lib/modules/$(shell uname -r)/build 
PWD:=$(shell pwd)
LINK:=/lib/modules/$(shell uname -r)
all :
	$(MAKE) -C $(KDIR) M=$(PWD) modules
	$(MAKE) -C $(KDIR) M=$(PWD) modules_install
link : 
	 ln -s $(PWD)/*.ko ${LINK} 
clean: 
	$(MAKE) -C $(KDIR) M=$(PWD) clean
	@rm -f module.symvers app_kmod
	@rm -f $(LINK)/*.ko
	
