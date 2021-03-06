
2.5.1.1 u-boot.lds中找到start.S
	(1)C语言中整个项目的入口就是main函数
	(2)在uboot中包含汇编阶段, 因此程序的入口在链接脚本中ENTRY声明的位置: ENTRY(_start) // not main()

2.5.2.1、头文件包含
	(1)#include <config.h>  // < > not " "  -- SRCTREE/include 路径导出到PATH环境变量中?
		config.h在include目录下, 配置过程中自动生成的文件   //#include <configs/x210_sd.h>
	(3)#include <version.h>
		// #ifndef __VERSION_H__  -- #define文件作用域, 且又没有包含其他头文件, 肯定没有定义__VERSION_H_
		// #include "version_autogenerated"  -- #define U_BOOT_VERSION  "xxx"
	(4)#include <asm/proc/domain.h> // asm -> asm-arm;  proc -> proc->armv
	(6)uboot不能在windows的共享文件夹下配置编译, windows中没有符号链接
		// 共享文件夹中执行.bat文件失败, 运行Python脚本失败

2.5.3.1、启动代码的16字节头部
	(1)SD卡启动/Nand启动等整个镜像开头需要16字节的校验头 // usb启动不需要, sd卡启动通过mkv210image.c来制作镜像
	(2)uboot这里start.S中在开头位置放了16字节的/*填充占位*/, 后面去计算校验和再重新填充
		// uboot从SD/Nand等启动时的16字节校验头和异常向量表的建立
		// -- 应该和单片机start.s文件一样, 编译链接后, bin文件的起始就是中断向量表 -- 且这16个字节校验在bin文件最前面

2.5.3.4、TEXT_BASE   // ./board/samsung/x210/config.mk
	(2)源代码中和配置Makefile中很多变量是可以互相运送, 有些符号的值可以从Makefile中传递到源代码中
		// 生成file ./include/version_autogenerated -- makefile -> src file U_BOOT_VERSION

2.5.4.1、设置CPU为SVC模式
	(1)msr	cpsr_c, #0xd3	将CPU设置为禁止FIQ IRQ, ARM状态, SVC模式
		// 中断一开始设置为禁止, 防止一开始中断处理未设置OK, 程序上电产生中断跑飞
	(2)其实ARM CPU在复位时默认就会进入SVC模式, 但是这里还是使用软件将其置为SVC模式, /软件不依赖于硬件的预设
		整个uboot工作时CPU一直处于SVC模式	// cpu裸机都是在SVC模式下?

2.5.4.3、识别并暂存启动介质选择
	(1)启动是由SoC的OM5:OM0这6个引脚的高低电平决定
	(2)在210内部有一个寄存器(0xE000_0004), 寄存器中的值是硬件根据OM引脚的设置而自动设置值	//not in datasheet
		// moveq r3, #BOOT_MMCSD
		// str 	 r3, [0xE010_F00C] 	// user defined information register

2.5.4.4、设置栈
	(2)在调用函数前初始化栈, 主要原因是在被调用的函数内/*再次执行了调用函数*/
		bl将返回地址存储到lr中, 再次执行函数调用前要先将lr入栈, 否则函数返回时第一层的返回地址就被覆盖了
		// setup stack in sram      // ddr not init, insure stack_pointer in legal addr

		//push	{lr}	lr 		-> memory
		//pop	{pc}	memory 	-> pc

2.5.5.1、检查复位状态
	(1)复杂CPU允许多种复位情况: 直接冷上电, 热启动, 睡眠(低功耗)状态下的唤醒等
		//冷上电时ddr需要初始化和code的重定位, 而热启动或者低功耗状态下的复位则不需要再次初始化ddr

2.5.5.5、供电锁存
	// orr r1, r1, #0x301       // error

2.5.6.1、判断当前代码执行位置  // line 110-115
	(1)代码运行地址在sram中还是在ddr中     // bl1(uboot的前16K)

	(2)bic	r1, pc, r0  //r1 = pc & ~(r0)

		// bl system_clock_init
		// bl mem_ctrl_asm_init

2.5.6.2、system_clock_init

2.5.7.1、mem_ctrl_asm_init   // uboot/cpu/s5pc11x/s5pc110/cpu_init.S
	(4)DMC0_MEMCONFIG_0: 在裸机中配置值为0x20E01323
						 在uboot中配置为0x30F01313
						 在裸机中DMC0的256MB内存地址范围是  0x20000000 - 0x2FFFFFFF
						 在uboot中DMC0的256MB内存地址范围为 0x30000000 - 0x3FFFFFFF
	(5)从分析九鼎移植的uboot可以看出: DMC0上允许的地址范围是20000000-3FFFFFFF // 512MB
	(6) 在uboot中, 可用的物理地址范围为: 0x30000000-0x4FFFFFFF //512MB
		其中 30000000-3FFFFFFF为DMC0, 40000000-4FFFFFFF为DMC1
	(7)//x210_sd.h内存相关的配置值  // line 438-468
	(8)在uboot中DMC0和DMC1都可以工作

2.5.7.2、uart_asm_init

2.5.7.4 pop {pc}以返回
	(1)返回前通过串口打印'K'	//lowlevel_init.S执行成功串口打印出"OK"

	//lowlevel_init.S -- clock_init, ddr_init, uart_init && print"OK"

===========================================================================================================
===========================================================================================================

2.5.8.1、再次设置栈（DDR中的栈）
	(2)第一次设置栈: 调用lowlevel_init前     //start.S line284-287
	   第二次设置栈: 将栈设置在ddr中         //start.S line297-299
	   // stack location: 0x33E0_0000, 在uboot的代码段的下面

2.5.8.2、再次判断当前地址以决定是否重定位
	(1)第二次判断程序运行在sram还是在ddr     // need relocate?
	(2)重定位: 	冷启动时加载sd卡的前8KB在sram中运行, uboot的第二部分(整个uboot.bin)在sd卡中
				uboot第一阶段完成必要初始化, 运行结束之前把第二部分加载到ddr的链接地址处0x33E0_0000

	// 默认sd卡启动, inand(SD通道0)中uboot被破坏 -- SD Checksum Error

	// second boot: SD卡的channel2

2.5.9.uboot重定位详解
	(1)0xD003_7488这个内存地址在sram中, 用来确定通道 		// first boot采用SD/MMC, 则默认是通道0
		硬件根据实际电路中sd卡在哪个通道设置变量值     		// -- SD0通道(EB00_0000) SD2通道(EB20_0000)
	(3)重定位是通过调用movi_bl2_copy()  // uboot/cpu/s5pc11x/movi.c

	// -- typedef u32(* copy_sd_mmc_to_mem)(u32 channel, u32 start_block, u16 block_size, u32 *trg, u32 init)
	// -- copy_sd_mmc_to_mem copy_bl2 = (copy_sd_mmc_to_mem) (*(u32 *) (0xD003E008));
	// -- copy_bl2(2, MOVI_BL2_POS, MOVI_BL2_BLKCNT, CFG_PHY_UBOOT_BASE, 0)

	MOVI_BL2_POS: bl2(整个uboot.bin)的起始扇区	// 注意应和烧录sd卡时, bl2起始扇区相同

	MOVI_BL2_POS = (eFUSE_SIZE / MOVI_BLKSIZE) + MOVI_BL1_BLKCNT + MOVI_ENV_BLKCNT = 1 + 16 + 32 = 49
		eFUSE_SIZE		= 512
		MOVI_BLKSIZE	= 512
		MOVI_BL1_BLKCNT	= SS_SIZE / MOVI_BLKSIZE		// 8KB	/ 512
		MOVI_ENV_BLKCNT = CFG_ENV_SIZE / MOVI_BLKSIZE	// 16KB	/ 512

===========================================================================================================
===========================================================================================================

2.5.10.1、什么是虚拟地址、物理地址
	(3)虚拟地址在软件操作和硬件被操作之间增加一个层次: 虚拟地址映射层
		映射层建立一个虚拟地址到物理地址的映射表
		当软件运行的时候, 软件中使用的虚拟地址在映射表中查询得到对应的物理地址再发给硬件去执行
		// 没有使用虚拟内存的机器, 虚拟地址直接送到内存总线上, 使具有相同地址的物理存储器被读写
		// 使用虚拟内存的机器, 虚拟地址不是被直接送到内存地址总线, 而是送到内存管理单元-MMU

2.5.10.2、MMU单元的作用
	(1)MMU: memory management unit(内存管理单元)
		MMU实际上是SOC中一个硬件单元, 它的主要功能就是实现虚拟地址到物理地址的映射
	(2)MMU在CP15协处理器中进行控制, 对MMU进行控制就是对cp15协处理器的寄存器进行编程
	// MMU一般存在协处理器中, 其功能是把虚拟地址映射为物理地址

2.5.10.3、地址映射的额外收益1：访问控制
	(1)访问控制: //内存块: read write execute
		在管理上对内存进行分块, 然后每块进行独立的虚拟地址映射, 同时在映射关系中还实现了访问控制
	(2)C语言中编程: Segmentation fault
		实际上这个段错误就和MMU实现的访问控制有关, 当前程序只能操作自己有权操作的地址范围(若干个内存块)
		如果当前程序指针出错访问了不该访问的内存块则就会触发段错误

2.5.10.4、地址映射的额外收益2：cache   //cache的工作和虚拟地址映射有关系

2.5.11.1、使能域访问（cp15的c3寄存器）
	(1)cp15协处理器内部有c0到c15共16个寄存器, 通过mrc和mcr指令来访问这些寄存器
	(2)c3寄存器在mmu中的作用是控制域访问, 域访问是和MMU的访问控制有关

2.5.11.2、设置TTB（cp15的c2寄存器）
	(1)TTB: translation table base(转换表基地址)
	(2)转换表是建立一套虚拟地址映射的关键
		转换表分2部分，表索引和表项。表索引对应虚拟地址，表项对应物理地址。
		一对表索引和表项构成一个转换表单元，能够对一个内存块进行虚拟地址转换
		（映射中基本规定中规定了内存映射和管理是以块为单位的，至于块有多大，
		要看你的MMU的支持和你自己的选择。在ARM中支持3种块大小，细表1KB、粗表4KB、段1MB）
		真正的转换表就是由若干个转换表单元构成的，每个单元负责1个内存块，
		总体的转换表负责整个内存空间（0-4G）的映射
	(3)整个建立虚拟地址映射的主要工作就是建立这张转换表
	(4)转换表放置在内存中的，放置时要求起始地址在内存中要xx位对齐
		转换表不需要软件去干涉使用，而是将基地址TTB设置到cp15的c2寄存器中，然后MMU工作时会自动去查转换表

2.5.11.3、使能MMU单元（cp15的c1寄存器）
	(1)cp15的c1寄存器的bit0控制MMU的开关。只要将这一个bit置1即可开启MMU。
		开启MMU之后上层软件层的地址就必须经过TT的转换才能发给下层物理层去执行。

	// 虚拟地址->页, 物理地址->页框, 页和页框的大小必须相同

2.5.11.4、找到映射表待分析
	(1)转换表: //lowlevel_init.S -- line593

		.rept 0x100 // 循环
		FL_SECTION_ENTRY    __base, 3, 0, 0, 0
		.set __base, __base+1
		.endr

		.macro  FL_SECTION_ENTRY base, ap, d, c, b     // 声明宏   宏名 + 参数
			.word (xxx) //宏体 .word声明一个四字节变量, 来构建一个表项
		.endm           // 宏体结束

		// 硬编码(很多地址以纯数字的编辑方式), 很难进行修改配置， 一般以宏的方式

	2.5.11.5、S5PV210的2种虚拟地址管理

	2.5.12.start.S解析10
	2.5.12.1、FL_SECTION_ENTRY
	2.5.12.2、页表项各bit位含义
	2.5.12.3、段式页表详解
	2.5.12.4、实验操作验证
	2.5.12.5、总结：关于MMU和虚拟地址映射的学习

	宏观上理解转换表：整个转换表可以看作是一个int类型的数组，数组中的一个元素就是一个表索引和表项的单元。
	数组中的元素值就是表项，这个元素的数组下标就是表索引。
	ARM的段式映射中长度为1MB，因此一个映射单元只能管1MB内存，那我们整个4G范围内需要4096个映射单元
	也就是说这个数组的元素个数是4096，实际上我们做的时候并没有依次单个处理这4096个单元，
	而是把4096个分成几部分，然后每部分用for循环做相同的处理。

===========================================================================================================
===========================================================================================================

2.5.13.1、再次设置栈      // U_BOOT_BASE 0x33e0_0000 or 0xc3e0_0000
	(1)第三次设置栈(in ddr appropriate location): 设置在/*uboot起始地址*//*上方2MB处*/

	// line405-415 clear_bss	-- bss in ddr

2.5.13.3 ldr	pc, _start_armboot
	(1)void start_armboot(void): ./lib_arm/board.c		//这个函数开始uboot的第二阶段(uboot boundary)
		使用远跳转直接跳转到/*DDR中*/的第二阶段开始地址处
	(2)远跳转: /*加载的地址*/和当前运行地址/*current pc*/无关, 而和链接地址有关
		 实现: uboot_step1(in sram) jump to uboot_step2(in ddr)

// 链接时将start.s放在前8K
// ddr中uboot的第一阶段永远不会执行 -- 在ddr中运行, 肯定是从start_armboot开始 -- test adr加载时, pc指针的值
-- 应该不会执行, reset的地址是一定的
-- 如果休眠后不是由reset开始? . . .

===========================================================================================================
===========================================================================================================

2.5.13.4、总结：uboot的第一阶段做了哪些工作
(1)构建异常向量表          // like mcu start.s
(2)设置CPU为SVC模式
(3)关看门狗
(4)开发板供电置锁
(5)时钟初始化
(6)DDR初始化
(7)串口初始化并打印"OK"
(8)重定位
(9)建立映射表并开启MMU
(10)跳转到第二阶段

