
	// make <board_name>_config
	
2.3.2.3、编译得到uboot.bin
	(1)检查当前编译环境或者主Makefile中编译工具链设置	// make "CROSS_COMPILE=xxx"有更高优先级
		// make or make -j4

2.3.3.2、各文件介绍
	(1 ) .gitignore
	(2 ) arm_config.mk 	// -D__ARM__
	(4 ) config.mk		// 主Makefile包含, 编译工具链的配置	-- LDFLAG += TEXT_BASE
	(10) Makefile
	(12) mkconfig		// 配置指定平台，确定编译时源文件路径(符号链接)

2.3.4.uboot的源码目录分析2
	(3) board
	(4) common		平台无关代码, (1)uboot系统命令--cmd (2)实现环境变量--env
	(5) cpu			SOC相关初始化和控制代码, 譬如CPU、中断、串口等SoC内部外设的, 包括/*起始代码*/start.S
					//warning: 硬件平台相关, 移植时一般无需修改

	(8) drivers		drivers from Linux devices driver // eth inand/sd nand...

	(10)fs			file system from linux src, 用来管理flash等资源

	(11)include		uboot和linux kernel在管理头文件时, 把所有的头文件全部集中存放在include目录下

	(12)lib_*		典型的lib_arm(arm架构)和lib_generic架构(其他架构通用)

	(13)libfdt		设备树相关
	
	(15)net			网络相关, 譬如uboot中的tftp nfs ping实现

	(18)sd_fusing	代码实现了烧录uboot镜像到SD卡 //important

	(19)tools		里面是一些工具类的代码, 譬如mkimage

	uboot文件:
		1. 版本相关 		include/version_autogenerated.h		// 编译生成
		2. 宏定义			include/autoconf.mk					// 编译生成
		3. 设备信息相关		include/config.mk					// 配置生成
        4. 头文件路径       include/config.h                    // 配置生成
		5. 工具链配置相关	./config.mk							// 源码
		6. uboot配置脚本 	./mkconfig							// 源码

    */源文件
        1. ./config.mk
        2. ./mkconfig
        3. ./include/version.h
        4. ./include/configs/x210_sd.h
        5. ./board/samsung/x210/u-boot.lds

    */配置后生成的文件:
        1. 执行mkconfig生成的文件:
            (1) include/config.mk           // param: ARCH ...
            (2) include/config.h            // #include <configs/x210_sd.h>
            (3) include/asm                 // 符号链接: asm    -> asm-arm
            (4) include/regs.h              // 符号链接: regs.h -> s5pc110.h
            (5) include/asm-arm/arch        // 符号链接: arch   -> arch-s5pc11x
            (6) include/asm-arm/proc        // 符号链接: proc   -> proc-armv
                // 确定ARCH...生成config.mk
                // 建立板相关的头文件./include/config.h
                // 建立指向其他文件的软链接

        2. board/samsung/x210/config.mk     // 变量定义: TEXT_BASE = 0xC3E0_0000
            // other special config.mk already in src code
            // ./arm_config.mk
            // ./cpu/s5pc11x/config.mk

    */编译后生成的文件:
        1. include/version_autogenerated.h      // version                      --|
        2. include/autoconf.mk                  // 变量定义 from x210_sd.h      --| --> 编译阶段很早生成

	*/config.mk
		./config.mk							// 编译器相关
		./include/config.mk					// cpu soc vendor
		./board/samsung/x210/config.mk		// 链接地址
		./arm_config.mk						// __ARM__平台
		./cpu/s5pc11x/config.mk				// 编译器相关

	*/important source file
		./cpu/s5pc11x/start.S
		./board/samsung/x210/lowlevel_init.S
		./board/samsung/x210/u-boot.lds
		./cpu/s5pc11x/s5pc110/cpu_init.S
		./lib_arm/board.c







		
        