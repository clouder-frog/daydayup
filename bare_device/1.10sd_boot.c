
10.1.1、软盘、硬盘、光盘、CD、磁带
	(1)存储原理当前主要使用的是磁存储, 现代存储的发展方向是Flash存储, 闪存技术是利用电学原理

10.1.2、纯粹的Flash：NandFlash、NorFlash
	(1)原始的Flash颗粒组成芯片, 只对存储单元做了最基本的读写接口, 外部SoC nand控制器提供读写时序
	(2)缺陷: 读写接口时序复杂, 内部无坏块处理机制, 需要SoC自己来管理Flash的坏块, 各家厂家的Flash接口不一致, 产品升级困难

10.1.3、SD卡、MMC卡、MicroSD、TF卡
	(1)这些卡内部就是Flash存储颗粒, 比直接的Nand芯片多了统一的外部封装和接口
	(2)卡有统一的规范标准	//SD卡的读写速度、读写接口时序、读写命令集、卡大小尺寸、引脚个数及定义

10.1.4、iNand、MoviNand、eSSD
	(3)现在主流使用iNand、MoviNand、eSSD等来做电子产品的存储芯片	//nand存储颗粒+块设备管理单元
		① 统一的接口标准		// sd卡
		② 以芯片的方式			// nand
		③ 内置Flash管理模块

10.2.1、SD卡和MMC卡的关系
	(1)/*MMC标准比SD标准早*/, SD标准兼容MMC标准。
	(2)MMC卡可以被SD读卡器读写, 而SD卡不可以被MMC读卡器读写

10.3.1、SD卡的物理接口
	(1)SD卡9个针脚	//2个地, 1个电源, 6个信号线
	

10.3.3、SPI协议特点（低速、接口操作时序简单、适合单片机）	//SD卡支持SPI协议, 单片机方便使用

10.3.4、SD协议特点（高速、接口时序复杂，适合有SDIO接口的SoC）
(1)SD协议是专门用来和SD卡通信的
(2)SD协议要求SoC中有SD控制器，运行在高速率下，要求SoC的主频不能太低

10.3.5、S5PV210的SD/MMC控制器
(1)数据手册Section8.7，为SD/MMC控制器-介绍
(2)SD卡内部除了存储单元Flash外，还有SD卡管理模块，
	我们SoC和SD卡通信时，通过9针引脚以SD协议/SPI协议向SD卡管理模块发送命令、时钟、数据等信息，
	然后从SD卡返回信息给SoC来交互。
	工作时每一个任务（譬如初始化SD卡、譬如读一个块、譬如写、譬如擦除····）
	都需要一定的时序来完成（所谓时序就是先向SD卡发送xx命令，SD卡回xx消息，然后再向SD卡发送xx命令···）

10.4.2、SD卡启动的难点在哪里（SRAM、DDR、SDCard）
(1)SRAM、DDR都是总线式访问的，SRAM不需初始化既可直接使用而DDR需要初始化后才能使用，
但是总之CPU可以直接和SRAM/DRAM打交道；而SD卡需要时序访问，CPU不能直接和SD卡打交道；
NorFlash读取时可以总线式访问，所以Norflash启动非常简单，可以直接启动，但是SD/NandFlash不行。
(2)以前只有Norflash可以作为启动介质，台式机笔记本的BIOS就是Norflash做的。
后来三星在2440中使用了SteppingStone的技术，让Nandflash也可以作为启动介质。
SteppingStone（翻译为启动基石）技术就是在SoC内部内置4KB的SRAM，
然后开机时SoC根据OMpin判断用户设置的启动方式，
如果是NandFlash启动，则SoC的启动部分的硬件直接从外部NandFlash中读取开头的4KB到内部SRAM作为启动内容。
(3)启动基石技术进一步发展，在6410芯片中得到完善，在210芯片时已经完全成熟
。210中有96KB的SRAM，并且有一段iROM代码作为BL0，BL0再去启动BL1
（210中的BL0做的事情在2440中也有，只不过那时候是硬件自动完成的，而且体系没有210中这么详细）。

10.4.3、S5PV210的启动过程回顾
(1)210启动首先执行内部的iROM（也就是BL0），BL0会判断OMpin来决定从哪个设备启动，如果启动设备是SD卡，则BL0会从SD卡读取前16KB（不一定是16，反正16是工作的）到SRAM中去启动执行（这部分就是BL1，这就是steppingstone技术）
(2)BL1执行之后剩下的就是软件的事情了，SoC就不用再去操心了。

10.4.4、SD卡启动流程（bin文件小于16KB时和大于16KB时）
(1)启动的第一种情况是整个镜像大小小于16KB。这时候相当于我的整个镜像作为BL1被steppingstone直接硬件加载执行了而已。
(2)启动的第二种情况就是整个镜像大小大于16KB。（只要大于16KB，哪怕是17KB，或者是700MB都是一样的）这时候就要把整个镜像分为2部分：第一部分16KB大小，第二部分是剩下的大小。然后第一部分作为BL1启动，负责去初始化DRAM并且将第二部分加载到DRAM中去执行（uboot就是这样做的）。
10.4.5、最重要的但是却隐含未讲的东西
(1)问题：iROM究竟是怎样读取SD卡/NandFlash的？
(2)三星在iROM中事先内置了一些代码去初始化外部SD卡/NandFlash，并且内置了读取各种SD卡/NandFlash的代码在iROM中。BL0执行时就是通过调用这些device copy function来读取外部SD卡/NandFlash中的BL1的。

10.5.S5PV210的SD卡启动详解2
10.5.1、SoC支持SD卡启动的秘密（iROM代码）
(1)三星系列SoC支持SD卡/NandFlash启动，主要是依靠SteppingStone技术，具体在S5PV210中支持steppingstone技术的是内部的iROM代码。
1.10.5.2、再看iROM application note：block device copy function

10.5.3、扇区和块的概念
(1)早期的块设备就是软盘硬盘这类磁存储设备，这种设备的存储单元不是以字节为单位，而是以扇区为单位。
	磁存储设备读写的最小单元就是扇区，不能只读取或写部分扇区。这个限制是磁存储设备本身物理方面的原因造成的，也成为了我们编程时必须遵守的规律。
(2)一个扇区有好多个字节（一般是512个字节）。早期的磁盘扇区是512字节，实际上后来的磁盘扇区可以做的比较大（譬如1024字节，譬如2048字节，譬如4096字节），
	但是因为原来最早是512字节，很多的软件（包括操作系统和文件系统）已经默认了512这个数字，
	因此后来的硬件虽然物理上可能支持更大的扇区，但是实际上一般还是兼容512字节扇区这种操作方法。
(3)一个扇区可以看成是一个块block（块的概念就是：不是一个字节，是多个字节组成一个共同的操作单元块），所以就把这一类的设备称为块设备。
	常见的块设备有：磁存储设备硬盘、软盘、DVD和Flash设备（U盘、SSD、SD卡、NandFlash、Norflash、eMMC、iNand）
(4)linux里有个mtd驱动，就是用来管理这类块设备的。
(5)磁盘和Flash以块为单位来读写，就决定了我们启动时device copy function只能以整块为单位来读取SD卡。

10.5.4、用函数指针方式调用 device copy function
(1)第一种方法：宏定义方式来调用。好处是简单方便，坏处是编译器不能帮我们做参数的静态类型检查。
(2)第二种方法：用函数指针方式来调用。

10.6.S5PV210的SD卡启动实战1
10.6.1、任务：大于16KB的bin文件使用SD卡启动
(1)总体思路：将我们的代码分为2部分：第一部分BL1小于等于16KB，第二部分为任意大小，iROM代码执行完成后从SD卡启动会自动读取BL1到SRAM中执行；
	BL1执行时负责初始化DDR，然后手动将BL2从SD卡copy到DDR中正确位置，然后BL1远跳转到BL2中执行BL2.
(2)细节1：程序怎么安排？程序整个分为2个文件夹BL1和BL2，各自管理各自的项目。
(3)细节2：BL1中要完成：关看门狗、设置栈、开iCache、初始化DDR、从SD卡复制BL2到DDR中特定位置，跳转执行BL2.
(4)细节3：BL1在SD卡中必须从Block1开始（Block0不能用，这个是三星官方规定的），长度为16KB内，我们就定为16KB（也就是32个block）；
	BL1理论上可以从33扇区开始，但是实际上为了安全都会留一些空扇区作为隔离，
	譬如可以从45扇区开始，长度由自己定（实际根据自己的BL2大小来分配长度，我们实验时BL2非常小，因此我们定义BL2长度为16KB，也就是32扇区）。
(5)细节4：DDR初始化好之后，整个DDR都可以使用了，这时在其中选择一段长度足够BL2的DDR空间即可。
	我们选0x23E00000（因为我们BL1中只初始化了DDR1，地址空间范围是0x20000000～0x2FFFFFFF）。

10.6.2、代码划分为2部分（BL1和BL2）

10.6.3、BL1中的重定位

10.6.4、BL2远跳转
(1)因为我们BL1和BL2其实是2个独立的程序，链接时也是独立分开链接的，所以不能像以前一样使用ldr pc, =main这种方式来通过链接地址实现元跳转到BL2.
(2)我们的解决方案是使用地址进行强制跳转。因为我们知道BL2在内存地址0x23E00000处，所以直接去执行这个地址即可。


10.7.S5PV210的SD卡启动实战2
10.7.1、烧录启动实验
10.7.2、代码分为2部分启动（上一节讲的）的缺陷
(1)代码分为2部分，这种技术叫分散加载。这种分散加载的方法可以解决问题，但是比较麻烦。
(2)分散加载的缺陷：第一，代码完全分2部分，完全独立，代码编写和组织上麻烦；
第二，无法让工程项目兼容SD卡启动和Nand启动、NorFlash启动等各种启动方式。
10.7.3、uboot中的做法
(1)第二种思路：程序代码仍然包括BL1和BL2两部分，但是组织形式上不分为2部分而是作为一个整体来组织。
它的实现方式是：iROM启动然后从SD卡的扇区1开始读取16KB的BL1然后去执行BL1，BL1负责初始化DDR，然后从SD卡中读取整个程序（BL1+BL2）到DDR中，然后从DDR中执行（利用ldr pc, =main这种方式以远跳转从SRAM中运行的BL1跳转到DDR中运行的BL2）。

10.7.4、再来分析uboot的SD卡启动细节
(1)uboot编译好之后有200多KB，超出了16KB。uboot的组织方式就是前面16KB为BL1，剩下的部分为BL2.
(2)uboot在烧录到SD卡的时候，先截取uboot.bin的前16KB（实际脚本截取的是8KB）烧录到SD卡的block1～bolck32；然后将整个uboot烧录到SD卡的某个扇区中（譬如49扇区）
(3)实际uboot从SD卡启动时是这样的：iROM先执行，根据OMpin判断出启动设备是SD卡，然后从S卡的block1开始读取16KB（8KB）到SRAM中执行BL1，BL1执行时负责初始化DDR，并且从SD卡的49扇区开始复制整个uboot到DDR中指定位置（0x23E00000）去备用；然后BL1继续执行直到ldr pc, =main时BL1跳转到DDR上的BL2中接着执行uboot的第二阶段。

总结：uboot中的这种启动方式比上节讲的分散加载的好处在于：能够兼容各种启动方式。

10.8.解决X210开发板的软开关按键问题
10.8.1、X210开发板的软启动电路详解
(1)210供电需要的电压比较稳定，而外部适配器的输出电压不一定那么稳定，因此板载了一个文稳压器件MP1482.这个稳压芯片的作用就是外部适配器电压在一定范围内变化时稳压芯片的输出电压都是5V。
(2)MP1482芯片有一个EN（Enable）引脚，这个引脚可以让稳压芯片输出或关闭输出。EN为高电平时有输出电压，EN引脚为低电平时稳压芯片无输出。
(3)两个因素可以影响EN引脚的电平：第一个是POWER按键（SW1），POWER按键按下时EN为高电平，POWER按键弹起时EN为低电平；第二个是POWER_LOCK（EINT0）引脚，这个引脚为POWER_LOCK模式下高电平，则EN为高；若这个引脚为EINT0模式或者为POWER_LOCK模式但输出为低电平，则EN为低。
(4)图中还有EINT1引脚，这个引脚的作用是用来做中断，提供给CPU用来唤醒的。

10.8.2、为什么要软启动
(1)一般的电路设计都是用拨码开关来做电源开关的（打到一侧则接通，打到另一侧则关闭）。这种方式的优点是设计简单，缺点是电路太简单，整个主板要么有电要么没电无法做休眠模式、低功耗模式等。
(2)软启动电路是比较接近于实际产品的，其他开发板的硬开关其实是简化版的，和实际产品还有差异。

10.8.3、开发板供电置锁原理和分析
(1)软开关在设计时有一个置锁电路，用EINT0（也就是GPH0_2）引脚来控制的。
(2)EINT0这个引脚是有复用设计（两个完全不相干的功能挤在同一个引脚上，同时我们只能让这个引脚用于其中一种功能，这就叫复用）的，一个是GPIO（也就是GPH0_2引脚）、一个是PS_HOLD_CONTROL。（注意：EINT0功能算是GPIO下的一个子功能）
(3)PS_HOLD在Section2.4 Power Management章节下的4.10.5.8节下。
(4)PS_HOLD_CONTROL寄存器（0xE010E81C），共有3个位有用。
	bit0, 0表示这个引脚为GPIO功能，1表示这个引脚为PS_HOLD功能
	bit9，0表示这个引脚方向为输入，1表示这个引脚方向为输出
	bit8，0表示这个引脚输出为低电平，1表示输出为高电平。
分析：我们要使用软启动置锁，则需要将bit0、8、9都置为1即可。

10.8.4、写代码+实验验证
(1)要想让开发板和普通的开发板一样，一按下按键程序运行后即可松手不会断电，则只要在程序的开头部分添加代码去置锁开关板即可。
(2)置锁代码的方法是：给PS_HOLD_CONTROL寄存器的bit0、8、9均写入1即可。
(3)注意：此时开发板已经置锁，POWER按键已经失效，关机时需要按下复位按键。




ls /dev/sd*

在Linux下一切设备都是文件，那么SD卡也是一个文件，文件描述符在 /dev/sd*里面，

它的文件号就是 /dev/sdb  /dev/sdb1 是它的分区，因为我们的SD卡只有一个分区

/dev/sda 就是硬盘  /dev/sda1  /dev/sda2 硬盘分区

s5pv210有多少个mmc/sd通道

	(*isr)();
	isr();
	*isr();		// error 

	make -C  进入子目录

	删掉了重定位相关代码









