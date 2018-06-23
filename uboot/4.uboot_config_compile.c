
// uboot配置目的, 指定需要用到的源文件路径, 配置uboot version
// 学习uboot类似复杂项目, 首先确定该项目是如何管理(整体代码架构, 管理方式), 代码细节是另一个层次

// 1, 执行make_xx_config 传入ARCH, CPU, BOARD, SOC参数    --> 生成config.mk
// 2, mkconfig根据参数在include文件夹: 1.创建symbolic link; 2.生成config.h
// 3, 执行make分别调用各子目录的Makefile生成.obj文件和.a文件
// 4, 链接目标文件, 生成镜像


2.4.1.uboot主Makefile分析1
	2.4.1.1 uboot version
		(2)Makefile生成一个变量: U_BOOT_VERSION
		(3)/*uboot编译后*/生成include/version_autogenerated.h 	//	#define U_BOOT_VERSION	xxx

	2.4.1.2、HOSTARCH和HOSTOS
		(1)shell中执行uname -m得到i686(当前CPU版本号)
		(2)shell中的|叫做管道
			管道的作用: 把管道前面一个运算式的输出作为后面一个的输入再去做处理, 最终的输出才是整个式子的输出
		(4)HOSTARCH: 主机的CPU架构; HOSTOS: 主机的操作系统		// 判断HOSTARCH与ARCH是否相等

2.4.2.uboot主Makefile分析2
	2.4.2.1、静默编译	// line50-54
		(1)静默编译: 屏蔽编译信息(后台编译)
		(2)使用方法就是编译时make -s, -s会作为MAKEFLAGS传给Makefile	// MAKEFLAGS
			XECHO变量赋值	// default: echo

	2.4.2.2、2种编译方法	//line 78-123
		(1)编译复杂项目, Makefile提供2种编译管理方法
			原地编译: .o文件放在当前.c文件夹中
			    //缺点: 污染了源文件目录 \
					  一套源代码只能按照一种配置和编译方法进行处理, 无法同时维护多个配置编译方式
			单独输出文件夹方式的编译:	// linux kernel, uboot
				基本思路就是在编译时另外指定一个输出目录, 存放.o和其他生成的文件
				源代码目录不做任何污染, 输出目录存放/*本次配置编译的所有结果*/

		(2)具体用法:
			默认为原地编译
			指定具体的输出目录编译:
				①: make O=输出目录							// high priority, not MAKEFLAGS
				②: export BUILD_DIR=输出目录 然后再make		// contrast(对照) PATH

2.4.3.uboot主Makefile分析3
	2.4.3.1、OBJTREE、SRCTREE、TOPDIR
		(1)OBJTREE: 编译输出目录
		(2)SRCTREE: 源代码根目录
			//在默认编译下OBJTREE和SRCTREE相等; 在O=xx这种编译下OBJTREE和SRCTREE不相等

    2.4.3.2、MKCONFIG // line101
        (1)Makefile定义的一个变量: MKCONFIG := $(SRCTREE)/mkconfig
            //mkconfig是uboot配置阶段的配置脚本

	2.4.3.3 include $(obj)include/config.mk // line133
		(1)include/config.mk要在配置过程生成(make x210_sd_config)
		(3)自动配置思想: 编译前配置"make x210_sd_config" 自动生成config.mk文件, 从而可以导出以上环境变量
		(4)//line2589 -- @$(MKCONFIG) $(@:_config=) arm s5pc11x x210 samsung s5pc110
           //generated file: include/config.mk

	2.4.3.4 ARCH CROSS_COMPILE
		(1)ARCH: 配置过程中指定		//ARCH -> CROSS_COMPILE // path(/usr/local/arm) + name(arm-linux-*)
		(2)CROSS_COMPILE: 交叉编译工具 前缀 + 路径
			//不同CPU架构上的交叉编译工具链, 前缀不一样, 后缀一样
			//设置CROSS_COMPILE: 交叉编译工具链的绝对路径或相对路径
			//可以在Makefile中去更改设置CROSS_COMPILE的值 -- 修改导出的环境变量CROSS_COMPILE
			//编译时用"make CROSS_COMPILE=xxxx", 而且编译时传参可以覆盖Makefile内部设置, 优先级较高

			//makefile文件下编译, 与cmdline下编译, 本质是相同的

2.4.4.uboot主Makefile分析4
	2.4.4.1、$(TOPDIR)/config.mk	// line 185
		//设置交叉编译工具链属性: 预处理属性, 编译属性, 链接属性

	2.4.4.2、编译工具定义
		//交叉编译工具链是一系列工具的集合
		//config.mk line97-107完整交叉编译工具链定义

	2.4.4.3、包含开发板配置项目
		(1)include/autoconf.mk编译后生成
		(2)文件内容: 很多CONFIG_开头的变量(宏)
		   文件作用: 指导整个uboot的编译过程(条件编译)
			//条件编译是用来实现可移植性(uboot包含了各种开发板的适用代码, 源码用条件编译组合一起)
		(3)配置过程所需要的源文件 // inlcude/configs/x210_sd.h
			//头文件里面全都是宏定义, 这些宏定义是对当前开发板的移植			\
			  每个开发板的移植对应这个目录下的一个头文件						\
			  这些配置的宏定义就是移植uboot的关键所在	// 强调开发板

2.4.5.uboot主Makefile分析5
    2.4.5.1、链接脚本    // line 142-149
        (1)宏CONFIG_NAND_U_BOOT设置链接脚本: u-boot-nand.lds or u-boot.lds
        (3)u-boot.lds: board\samsung\x210    // $(TOPDIR)/board/$(BOARDDIR)/u-boot.lds

    2.4.5.2、TEXT_BASE   // line 156-158
        (1)makefile在配置过程中: board/samsung/x210/config.mk    // TEXT_BASE = 0xc3e0_0000
        (2)TEXT_BASE是整个uboot链接时指定的链接地址, uboot中启用了虚拟地址映射
            //因此0xC3E0_0000地址就相当于0x33E0_0000(uboot中虚拟地址映射的设置)
        (3)回顾裸机中讲的链接地址的问题
            //dnw方式先下载x210_usb.bin, 然后再下载uboot.bin时设置第二个地址: 0x23E0_0000

2.4.6.uboot主Makefile分析6
    (1)主Makefile中/*第一个目标*/: all //默认目标, 在uboot根目录下make其实就等于make all
    (2)u-boot.elf
    (3)x210_sd_config: unconfig

2.4.7.uboot配置过程详解1
    (1)mkconfig脚本的6个参数
        $1:	x210_sd     // BOARD_NAME
        $2:	arm         // ARC
        $3: s5pc11x     // CPU
        $4:	x210        // BOARD
        $5: samsumg     // VENDOR
        $6:	s5pc110     // SOC
        // $# = 6

    (6)创建的符号链接：
        ① ./include/asm             -> ./include/asm-arm
        ② ./include/asm-arm/arch    -> ./include/asm-arm/arch-s5pc110  // for transplant tmp
        ③ ./include/regs.h          -> ./include/s5pc110.h
        ④ ./include/asm-arm/arch    -> ./include/asm-arm/arch-s5pc11x
        ⑤ ./include/asm-arm/proc    -> ./include/asm-arm/proc-armv

2.4.8.uboot配置过程详解2
    (1)创建include/config.mk   // for 主Makefile line123
    (3)uboot的/*配置*/和/*编译*/过程的配合:
        编译的时候需要ARCH=arm、CPU=xx等这些变量来指导编译, 配置的时候就是为编译阶段提供这些变量
        //为什么不在Makefile中直接定义这些变量去使用, 而要在mkconfig脚本中创建config.mk文件然后又在Makefile中include这些文件
    (4)分析脚本时需要注意current dir
    (6)创建config.h    //#include <configs/x210_sd.h>，
        这个头文件是移植x210开发板时, 对开发板的宏定义配置文件  // 特定开发板移植的主要文件 
    (7)x210_sd.h文件会被用来生成autoconfig.mk文件, 这个文件会被主Makefile引入, 指导整个编译过程
        文件中的宏定义会影响对uboot中大部分.c文件中一些条件编译的选择, 从而实现最终的可移植性

2.4.9.uboot的链接脚本
    (2)ENTRY(_start)用来指定整个程序的入口地址。
        所谓入口地址就是整个程序的开头地址, 可以认为就是整个程序的第一句指令     // C main
    (3)指定程序的链接地址的2种方法:
        ① Makefile中ld的flags用-Ttext 0x20000000
        ② 在链接脚本的SECTIONS开头  .=0x20000000
        // 两个都指定以-Ttext指定的为准
    (4)uboot的最终链接起始地址在Makefile中用-Ttext指定   // 配置时设定: TEXT_BASE = 0xC3E0_0000
    (5)在代码段中注意文件排列的顺序   //理论上main链接到后面地址也是可以正常运行, 但是bootROM仅加载前16K
    (6)链接脚本中除了.text  .data .rodata .bss段等/*编译工具*/自带的段之外
        编译工具还允许自定义段, 譬如uboot总的.u_boot_cmd段就是自定义段    //自定义段很重要

    
    // mkconfig主要做了三件事:
        创建相应软链接
        生成./include/config.mk
        生成./include/config.h		// #include <configs/x210_sd.h>


















        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        




