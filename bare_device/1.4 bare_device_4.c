
4.1.2、dnw工具介绍
	dnw软件(Samsung): 通过USB线连接开发板和PC，然后从主机下载文件镜像到开发板中去烧录系统
	dnw软件使用注意1：dnw是需要装usb驱动的，驱动在“X210光盘资料\A盘\tools\USB驱动”目录中
	dnw软件使用注意2：dnw使用时通过usb线下载，所以一定要插USB线。
	dnw软件使用注意3：dnw下载时需要设置dnw下载/*内存地址*/。在dnw软件的菜单“Configuration”中设置Download Address为0xd0020010，确认即可

4.1.4、裸机程序下载地址设置
	从usb启动做裸机实验时，因为不需要16字节的校验头，所以直接下载到0xd0020010	// dnw直接load到ram中(当作BL1来执行)

	// Microsoft USB设备驱动签名政策
4.2.裸机实验体验之SD卡下载
	/*从SD启动*/时会先从iNand(SD0)启动执行, 当iNand启动做校验和时失败才会转为启动SD2
	裸机实验时是通过SD2来提供裸机程序镜像, 因此需要先破坏内部iNand的uboot

4.3.2、linux中装软件的特点
	linux常用安装软件方法:
	(1) 在线安装				//ubuntu apt-get install vim
	(2) 自己下载安装包来安装	//不确定安装包是否和系统匹配  -- 交叉编译工具链(arm-linux-gcc)
	(3) 源代码安装

4.3.4、交叉编译工具链的安装
	// windows file -> linux file 	// 共享文件夹、Samba、cuteftp
	linux中的目录管理方法:
	(1) 技术角度: linux中所有目录性质都是一样, 把软件安装到哪里都一样
	(2) 实际使用: ()/bin目录放置一些系统自带的用户使用的应用程序		// /usr/local/arm
			      ()/sbin/*super bin*/目录下存放的是系统自带的系统管理方面的应用程序

4.3.5、安装后的测试
	./arm-none-linux-gnueabi-gcc -v		// 当前软件版本号	-- gcc version 4.4.1 

4.3.1、环境变量的意义
	(1) 环境变量就是操作系统的全局变量, 环境变量对操作系统来说命名和意义都是唯一的
	(2) linux系统环境变量一部分linux系统自带的, 一部分是自己扩充的
	(3) PATH(系统自带): 系统在查找可执行程序时搜索的路径范围
		 ~/.bashrc	export PATH=/usr/local/arm/arm-2009q3/bin:$PATH

	// bash是linux标准默认的shell (linux一般默认使用bash作为shell脚本解释器)
	// 很多linux发行版里默认带的就是bash shell
	// 一般情况下, 并不严格区分Bourne Shell和Bourne Again Shell, 所以也不区分#!/bin/sh或#!/bin/bash
	// 一般情况下, 一个shell script可以在很多种shell中使用
	// #!向系统指定, 该路径所指定的程序, 是解释, 此脚本文件的shell程序

4.5.3、Makefile中的一些基本概念
	// 命令 是加工 依赖 生成 目标 的方法
	// 注意Makefile在windows下编辑, 命令前的tab被解析成空格
	// 第一个目标是默认目标

4.5.4、Makefile的基本工作原理
	其一，当我们执行 make xx 的时候，Makefile会自动执行xx这个目标下面的命令语句。
	其二，当我们make xx的时候，是否执行命令是取决于依赖的。依赖如果成立就会执行命令，否则不执行。
	其三，我们直接执行make 和make 第一个目标  效果是一样的。（第一个目标其实就是默认目标）
4.5.6、进一步学习Makefile的资料
	我们学习Makefile的思路就是：先学会基本的概念和应用，先理解Makefile的概念和使用方法、工作原理。先自己会写简单的Makefile来管理工程。一般先学到这里就可以了，更深入的内容可以随同稍后的课程一起来学习，我们讲到课程的时候会再次提及并且逐步深入。
	对于我们有一定基础的同学，同时还有时间，可以深入学习Makefile，看《跟我一起学Makefile》（作者：陈皓）	
4.6.mkv210_image.c文件详解1
4.6.1、mkv210_image.c的使用演示
	裸机程序中的Makefile（实际上真正的项目的Makefile都是这样的）是把程序的编译和链接过程分开的。（平时我们用gcc a.c -o exe这种方式来编译时，实际上把编译和链接过程一步完成了。在内部实际上编译和链接永远是分开独立进行的，编译要使用编译器gcc，链接要使用链接器ld）
	%.o : %.S
	arm-linux-gcc -o $@ $< -c  
   // 【两个自动变量】     $@ 代表 %.o      $< 代表 %.s
	链接器得到led.elf其实就是我们的可执行程序，（如果是在操作系统下，这个led.elf就可以执行了）但是在嵌入式裸机中我们需要的是可以烧写的文件（可烧写的文件就叫镜像image），因此我们需要用这个led.elf为原材料来制作镜像，制作工具是交叉编译工具链中的arm-linux-objcopy
	我们使用arm-linux-objdump工具进行反编译（反汇编），反汇编其实就是把编译后的elf格式的可执行程序给反过来的到对应的汇编程序，的到它的汇编源代码。我们使用反汇编主要是用来学习，见本部分最后一节。
	mkv210_image.c这个程序其实最终不是在开发板上执行的，而是在主机linux（就是用来执行make对整个项目进行编译的那个机器）中执行的，因此编译这个程序用gcc而不是用arm-linux-gcc。这个.c文件编译后得到一个可执行程序mkmini210，目的是通过执行这个mkmini210程序而由led.bin得到210.bin。（210.bin是通过SD卡启动时的裸机镜像，这个镜像需要由led.bin来加工的到，加工的具体方法和原理要看mkv210_image.c）
4.6.2、背景知识：S5PV210的启动过程回顾
	分析启动过程可知；210启动后先执行内部iROM中的BL0，BL0执行完后会根据OMpin的配置选择一个外部设备来启动（有很多，我们实际使用的有2个：usb启动和SD卡启动）。在usb启动时内部BL0读取到BL1后不做校验，直接从BL1的实质内部0xd0020010开始执行，因此usb启动的景象led.bin不需要头信息，因此我们从usb启动时直接将镜像下载到0xd0020010去执行即可，不管头信息了；从SD启动时，BL0会首先读取sd卡得到完整的镜像（完整指的是led.bin和16字节的头），然后BL0会自己根据你的实际镜像（指led.bin）来计算一个校验和checksum，然后和你完整镜像的头部中的checksum来比对。如果对应则执行BL1，如果不对应则启动失败（会转入执行2st启动，即SD2启动。如果这里已经是2st启动了，这里校验通不过就死定了）。
4.6.3、mkv210_image.c的作用：为BL1添加校验头
	我们编译链接时只得到了led.bin，这个210.bin的得到和交叉编译工具链是完全无关的。由led.bin得到210.bin的过程是三星的S5PV210所特有的，因此需要我们自己去完成，为此我们写了mkv210_image.c来完成。
4.6.4、整个程序工作流分析
	整个程序中首先申请一个16KB大小的buffer，然后把所有内容按照各自的位置填充进去，最终把填充好的buffer写入到一个文件（名叫210.bin）就形成了我们想要的镜像。
4.7.mkv210_image.c文件详解2
4.7.1、代码详解
	第1步：检验用户传参是不是3个。
	第2步：分配16K Bbuffer并且填充为0. 【malloc分配到堆内存就立即清零】
	第3步：·········
4.7.2、main函数两个形参的作用
	main函数接收2个形参：argc和argv。
	argc是用户（通过命令行来）执行这个程序时，实际传递的参数个数。注意这个个数是包含程序执行本身的
	argv是一个字符串数组，这个数组中存储的字符串就是一个个的传参。
	譬如我们执行程序时使用./mkx210 led.bin 210.bin
	则argc = 3
	则argv[0] = "./mkx210"  argv[1] = led.bin  argv[2] = 210.bin
4.7.3、glibc读写文件接口
	linux中要读取一个文件，可以使用fopen打开文件，fread读取文件，读完之后fclose关闭文件。
	要写文件用fwrite来写。这些函数是glibc的库函数，在linux中用man 3 可以查找。
	如果你本身就知道这些函数的用法，只是记不起来可以man查找；如果你本身根本就不会用这些接口，建议先去baidu。
4.7.4、校验和的计算方法
	算法：校验和其实就是需要校验的内存区域中，所有内存中的内容按照字节为单位来进行相加，最终相加的和极为校验和。
	实现时大家要注意指针的类型为char *
4.9.一步步点亮LED2_数据手册查阅及相关寄存器浏览
	GPIO:general purpose input output 通用输入输出
4.9.3、GPIO相关的寄存器介绍
	回忆下之前说过的，软件操作硬件的接口是：寄存器。
	我们当前要操作的硬件是LED，但是LED实际是通过GPIO来间接控制的，所以当前我们实际要操作的设备其实是SoC的GPIO。要操作这些GPIO，必须通过设置他们的寄存器。
	查阅数据手册可知，GPJ0相关的寄存器有以下：
	GPJ0CON, （GPJ0 control）GPJ0控制寄存器，用来配置各引脚的工作模式
	GPJ0DAT, （GPJ0 data）当引脚配置为input/output模式时，寄存器的相应位和引脚的电平高低相对应。
	GPJ0PUD, （pull up down）控制引脚内部弱上拉、下拉
	GPJ0DRV, （driver）配置GPIO引脚的驱动能力
	GPJ0CONPDN，（记得是低功耗模式下的控制寄存器）
	GPJ0PUDPDN  （记得是低功耗模式下的上下拉寄存器）
	注：在驱动LED点亮时，应该将GPIO配置为output模式。
	实际上真正操控LED的硬件，主要的有：GPJ0CON, GPJ0DAT 这么2个。
	如何点亮LED，编程的步骤是：
	1、操控GPJ0CON寄存器中，选中output模式
	2、操控GPJ0DAT寄存器，相应的位设置为0
4.10.一步步点亮LED3_从零开始手写汇编点亮LED
4.10.1、GPxCON、GPxDAT寄存器分析
	GPJ0端口一共有8个引脚，分别记住：GPJ0_0 ～ GPJ0_7，相关重要寄存器就是GPJ0CON和GPJ0DAT
	GPJ0CON寄存器中设置8个引脚的工作模式（32/8=4，每个引脚可以分到4位，譬如GPJ0_0对应的bit位为bit0~bit3，GPJ0_3对应的位为bit12~bit15。工作方法是：给相应的寄存器位写入相应的值，该引脚硬件就会按照相应的模式去工作。譬如给bit12～bit15写入0b0001，GPJ0_3引脚就成为输出模式了）
4.10.2、从零开始写代码操作寄存器
	需要哪些先决条件才能写呢？
	1. 硬件接法和引脚：GPJ0_3 GPJ0_4 GPJ0_5	低电平亮/高电平灭
	2. GPJ0CON（0xE0200240）寄存器和GPJ0DAT（0xE0200244）寄存器
	【ldr r0, =0x11111111 】
	【ldr r1, =0xE0200240 】
	【str r0, [r1]】---------寄存器间接寻址,(哪个是数据, 哪个是地址)
    【一般用 r0 - r7】	
	3. 工程管理：Makefile等
	根据以上分析，我们就知道代码的写法了，代码所要完成的动作就是：
	把相应的配置数据写入相应的寄存器即可。
4.10.4、总结和回顾（软件控制硬件思想、寄存器意义、原理图数据手册的作用）
	软件到底是怎么控制硬件的？为什么程序一运行硬件就能跟着动？
	软件编程控制硬件的接口就是：寄存器
4.11.一步步点亮LED4_使用位运算实现复杂点亮要求
	上节回顾：代码写的更漂亮一些
	1. 用宏定义来定义寄存器名字，再来操作。
	2. 用 b . 来实现死循环
	3. 用.global把_start链接属性改为外部，消除链接时的警告
   【arm-linux-ld: warning: cannot find entry symbol _start; defaulting to 00000000】
   【-ld, 表示程序是在链接的时候, _start是汇编程序的入口,所有的汇编程序都是从这个符号开始】
   【_start 等符号默认都是文件内作用域, 外部其他文件都是看不见】
	
4.11.1、问题提出：如何只点亮中间1颗（两边是熄灭的）LED
	分析：程序其实就是写了GPJ0CON和GPJ0DAT这2个寄存器而已，功能更改也要从这里下手。
	GPJ0CON寄存器不需要修改，GPJ0DAT中设置相应的输出值即可。
4.11.2、直接解法（不使用位运算）和它的弊端
	GPJ0DAT = 0x28
	代码见<3.led_s>
	总结：1. 这样写可以完成任务。
		  2. 这样写有缺陷。缺陷就是需要人为的去计算这个特定的设置值，而且看代码的也不容易看懂。
	解决方案：在写代码时用位运算去让编译器帮我们计算这个特定值。
	【只是增加编译时间】	
4.11.3、常用位运算：与、或、非、移位
	位与(&)  位或(|)  位非（取反 ~） 移位（左移<< 右移>>）
4.11.4、使用位运算实现功能
	1<<3  等于 0b1000
	1<<5  等于 0b100000
	(1<<3)|(1<<5)  等于 0b101000
4.11.5、扩展一下：如何只熄灭中间1颗而点亮旁边2颗
	ldr r0, =((0<<3) | (1<<4) | (0<<5))
4.12.4、汇编编写及调用函数的方式
	汇编中调用函数用bl指令，子函数中最后用mov pc, lr来返回。
4.14.反汇编工具objdump的使用简介	
4.14.1、反汇编的原理&为什么要反汇编
	arm-linux-objdump -D led.elf > led_elf.dis
	objdump是gcc工具链中的反汇编工具，作用是由编译链接好的elf格式的可执行程序反过来得到汇编源代码
	-D表示反汇编	> 左边的是elf的可执行程序（反汇编时的原材料），>右边的是反汇编生成的反汇编程序
	反汇编的原因有以下：
		1.逆向破解。
		2.调试程序时，反汇编代码可以帮助我们理解程序（我们学习时使用objdump主要目的是这个），尤其是在理解链接脚本、链接地址等概念时。
		3. 把C语言源代码编译链接生成的可执行程序反汇编后得到对应的汇编代码，可以帮助我们理解C语言和汇编语言之间的对应关系。非常有助于深入理解C语言。
4.14.2、反汇编文件的格式和看法
	（汇编 assembly   反汇编 dissembly）
	标号地址、标号名字、指令地址、指令机器码、指令机器码反汇编到的指令
	扩展：ARM汇编中用地址池方式来实现非法立即数	
4.14.3、初识指令地址
	下载烧录执行的bin文件，内部其实是一条一条的指令机器码。这些指令每一条都有一个指令地址，这个地址是连接的时候ld给指定的（ld根据我们写的链接脚本来指定）
4.14.4、展望：反汇编工具帮助我们分析链接脚本
	反汇编的时候得到的指令地址是链接器考虑了链接脚本之后得到的地址，而我们写代码时通过指定连接脚本来让链接器给我们链接合适的地址。
	但是有时候我们写的链接脚本有误（或者我们不知道这个链接脚本会怎么样），这时候可以通过看反汇编文件来分析这个链接脚本的效果，看是不是我们想要的，如果不是可以改了再看。
	
	



