#ubuntu的内核源码树，如果要编译在ubuntu中安装的模块就打开这2个
#KERN_VER = $(shell uname -r)
#KERN_DIR = /lib/modules/$(KERN_VER)/build	


# 开发板的linux内核的源码树目录
KERN_DIR = ~/src/kernel
CC_DIR   = /usr/local/arm/arm-2009q3/bin

obj-m	+= wei_button_irq.o

all:
	make -C $(KERN_DIR) M=`pwd` modules
	$(CC_DIR)/arm-linux-gcc wei_button_irq_app.c -o app
	
.PHONY: clean
clean:
	make -C $(KERN_DIR) M=`pwd` modules clean
	rm -r app
	

