============================================================================
	-- modify -> git add -> git status:
	# on brach master
	# changes to be committed:
	# (use "git reset HEAD <file> ..." to unstage)  // where is head ? (working directory)(stage)(repository)
	#
	#   modified: readme.txt
	#

	git diff HEAD -- readme.txt命令可以查看工作区和版本库里面最新版本的区别

	公钥用来加密信息，私钥用来数字签名

	数字签名(digital signature) 数字证书(digital certificate)

	find -- 知道某个文件/文件夹名称, 却不知道路径
	grep -- 知道某个"xxx", 看在哪个文件中出现

	du -sh : 查看当前目录总共占的容量。而不单独列出各子项占用的容量 
	du -lh --max-depth=1 : 查看当前目录下一级子文件和子目录占用的磁盘容量

============================================================================
	// -----------------------------------------------
		设置查找高亮
		忽略大小写
		vi查找 (全词匹配)
	// -----------------------------------------------
		ctrl + shift + o/e
		ctrl + shift + n/p  //terminator 串口切换

	// 开发中不使用标准的C库

	// file u-boot
	// 移植代码一般不去修改前面写的, 尽量打补丁后面给覆盖上

		makefile中第一个目标为默认目标

		shell exit 1 && exit 0

	// -- 芯片在上电和休眠唤醒都需要对cache进行操作 v7_flush_dcache_all

============================================================================
	 -- static inline S5PC11X_TIMES	*S5PC11X_GetBase_TIMES(void) 	// inline
		{
			return (S5PC11X_TIMES *)ELFIN_TIMER_BASE;
		}

	// -- 磁盘的读写基本单位 -- 扇区; 操作系统读写磁盘的基本单位 -- 块
	// -- 文件系统是操作系统的一部分, 所以文件系统操作文件的最小单位是块  -- 块设备

	 -- printf data段, bss段起始地址
	 -- gcc编译不使用标准库

============================================================================
	 -- for test
	// 烧录后sd中bin文件, 其中应该有两份重复的BL1
	// movi.c 	line51:	 printf("MOVI_BL2_POS = %d\r\n", MOVI_BL2_POS); && ./sd_fusing/sd_fusing.sh BL2设置
	// start.S	line411: printf("_start_armboot = %d\r\n", _start_armboot);
	// start.S 	line57:  printf("reset = %p\r\n", reset);

	// arm程序中两种方法实现程序流程的跳转
	// (1) 专用的跳转指令(b, bl)
	// (2) 直接向程序计数器PC写入跳转地址值(mov lr, pc; mov pc, xxx)

============================================================================2018-7-31 21:38:24
// printf sprintf vsprintf vprintf

 -- int printf(const char *format, ...);
 -- int sprintf(char *s, const char *format, ...);
 -- int vsprintf(char *s, const char *format, va_list arg);
 -- int vprintf(const char *format, va_list arg);

int sprintf (char *s, const char *format, ...)
{
	int     iReturn ;
	va_list pArgs ;
	va_start (pArgs, szFormat) ;
	iReturn = vsprintf (szBuffer, szFormat, pArgs) ;
	va_end (pArgs) ;
	return iReturn ;
}

int printf(const char *fmt, ...)
{
	int i;
	int len;
	
	va_list args;

	va_start(args, fmt);
	len = vsprintf(g_pcOutBuf,fmt,args);	// 格式化输出到buf
	va_end(args);
	
	for (i = 0; i < strlen(g_pcOutBuf); i++)
	{
		putc(g_pcOutBuf[i]);
	}
	return len;
}

int printf(const char *fmt, ...)
{
	va_list args;
	
	va_start(args, fmt);
	vprintf(fmt, args);		// 格式化输出到stdout
	va_end(args);
}

============================================================================2018-7-31 21:38:33
// makefile
	GNU链接器开关项
	-lm -lc -lgcc				// libm.a libc.a(GCC标准C库) libgcc.c(GCC支持库)
	-g 可执行程序包含调试信息
	-o 指定输出文件名
	-c 只编译不链接

#LIBPATH = -lgcc -L/usr/local/arm/arm-2009q3/lib/gcc/arm-none-linux-gnueabi/4.4.1
LIBPATH	= /usr/local/arm/arm-2009q3/lib/gcc/arm-none-linux-gnueabi/4.4.1

uart.bin: start.o led.o uart.o speed.o main.o $(LIBPATH)/libgcc.a	// 链接静态库(1)
	#arm-linux-ld -Ttext 0x0 -o uart.elf $^ $(LIBPATH)	// 链接静态库(2)

============================================================================2018-8-3 22:23:16
	// 编译bootloader、kernel、裸机  -nostdlib	// 此类程序不需要 启动文件、标准库文件

============================================================================2018-8-8 23:44:17
	// #define DMC0_MEMCONFIG_0	0x20F01323 	// 0x38000000内存地址可以被访问
	// #define DMC0_MEMCONFIG_0 0x20F01333	// 仍可以工作

============================================================================
	分析一个工程的源码是如何链接的 -- Makefile

	grep "0xc3e00000" * -nR
	grep "LDFLAGS" * -nR

	LDFLAGS += -Bstatic -T $(LDSCRIPT) $(PLATFORM_LDFLAGS)
	ifneq ($(TEXT_BASE),)											# -Ttext	$(TEXT_BASE)
	LDFLAGS += -Ttext $(TEXT_BASE)
	endif

============================================================================2018-8-14 22:13:23
	//NorFlash与内存芯片接口相同, 读方式类似于内存读
	uint32_t *pDest, *pSrc;		// not uint32_t *pDest, pSrc;
	pDest = (uint32_t *)buf;
	pSrc  = (uint32_t *)start_addr;
	for (uint8_t i = 0; i < size/4; i++)
	{
		*(pDest + i) = *(pSrc + i);		// 可以类似读内存一样读取 -- 但是不能写
	}

	// 从nand启动，0地址对应的是memory			-- 可写
	// 从norflash启动，0地址对应的是norflash    -- 不可写

============================================================================
	uboot启动内核: (1)从flash中读取内核
						-- 分区表问题: 名称不重要，主要考虑到 addr + size
						-- 读取到哪里, 可以读取到memory任意位置(启动时, uboot会读取uImage的header, 判断是否需要relocate)
				   (2)启动

============================================================================
	U_BOOT_CMD 宏, 定义结构体并设置段属性为 .u_boot_cmd
	所有的uboot命令都集中在 自定义段中
	for (cmdtp = &__u_uboot_cmd_start; cmdtp != &__u_boot_cmd_end; cmdtp++)
	{
		
	}

	// PC硬盘有分区表, 换到任何PC可以使用
	// 嵌入式flash没有分区表, 分区信息通过code中写死	-- 关心 分区地址+长度

	uImage = head + 内核		// head(load: 加载地址 ep: 入口地址)
	// uImage的头部存在, image可以加载都memory中任意位置 -- 判断当前运行地址和加载地址是否相等
	如果相等直接跳转到入口地址去执行

============================================================================
	(1)uboot如何启动kernel		// uboot自身可启动
		|
		| -- 部署kernel (iNand or SD)
		|
		| -- 如何传参
			|
			| -- 命令体系
			|
			| -- 环境变量

============================================================================ 2018-8-18 17:58:28
vim多行复制: 鼠标右键
vim多行删除: 命令模式下, 命令输入: 32,65d

#!/bin/sh -x	// -- print shell command

============================================================================ 2018-8-25 22:53:55
	// movi write u-boot 0x30000000  -- 破坏inand中的uboot分区

	// uboot执行fastboot命令: error：no MBR is found at SD/MMC
	// 先fdisk -c 0去重新分区，然后再fastboot

============================================================================ 2018-8-25 22:54:02
	// 如何破坏flash中env分区




	
	
	
	

	