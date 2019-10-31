KERNELDIR := "/home/robert/wangbo/linux-3.2.0-04.06.00.08"
obj-m := buzz.o
build: kernel_modules
kernel_modules:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) modules
clean:
	$(MAKE) -C $(KERNELDIR) M=$(shell pwd) clean
