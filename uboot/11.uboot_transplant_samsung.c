
	//源码: android_uboot_smdkv210.tar.bz2

2.11.1.3、sshsecureshell
	(1)Linux编辑工具: vim, gedit
	(2)windows中安装sshsecureshell客户端
	(3)虚拟机重启网卡命令: ifdown eth0; ifup eth0
	(4)/etc/network/interfaces	一般联外网设置为dhcp方式	// nat方式不需要设置网卡
	(5)ping通开发板, 有线网卡, 静态ip绑定

2.11.2.2、搭建openssh环境
	(1)安装ssh-server(sudo apt-get install openssh-server)如果报错提示依赖错误, 参考: http://www.cnblogs.com/mliudong/p/4094519.html
	(2)securecrt登录
	(3)sshsecureshell登录
		ssh登录不上, 要修改/etc/ssh/sshd_config, 参考：http://blog.sina.com.cn/s/blog_5f435c130102v6pv.html
		修改完重启时如果/etc/init.d/ssh restart不起作用
		可以使用：ps -e | grep ssh，看sshd的进程号，然后kill -9 进程号杀死ssh进程以达到重启的目的
		或者直接重启ubuntu系统

2.11.3.1、直接编译三星移植版uboot尝试运行
	(2)检查Makefile中的交叉编译工具链	// 编译源码: ①源码 ②编译工具链
	(3)配置时使用：make smdkv210single_config, 对应include/configs/smdkv210single.h头文件
	(4)config -> compile -> load
	(5)uboot/sd_fusing/sd_fusing.sh
		// bl1_position=1
		// uboot_position=49  -- dd iflag=dsync oflag=dsync if=./u-boot.bin of=$1 seek=$uboot_position  -- 整个uboot bin

		// 需要在sd_fusing中先make clean  // make distclean没有对sd_fusing目录中生成文件删除
		// file mkbl1 -- x86-64

		make clean && make; 	file mkbl1 -- Inter 80386

		PMIC	// iic interface

2.11.4.3、ddr配置信息的更改

	(1)ddr controller reg config		// ddr硬件配置
		#define DMC0_MEMCONFIG_0	0x20E01323
		#define DMC0_MEMCONFIG_0	0x30E01323		// E0 -> F0
		
	(2)sdram base && sdram bank size	// ddr软件配置
		#define MEMORY_BASE_ADDRESS	0x20000000
		#define MEMORY_BASE_ADDRESS	0x30000000
		#define MEMORY_SIZE			0x10000000

2.11.5.4、虚拟地址映射表中相应修改
	(1) asm中mmu table配置
	(2) C中virt_to_phy_smdkc110(ulong addr)
	
	// 内存映射相关问题, 检查与内存相关操作

// 将所有动作都添加到脚本中
// 以前0x20E0_1323是OK, 如果将kernel链接到0x2xxx开头位置也是error, 这样配置0x2xxx内存有问题, 3xxx开头的没有问题

2.11.6.2、修改修改虚拟地址到物理地址的映射函数
(1)修改uboot/board/samsung/smdkc110/smdkc110.c中的virt_to_phy_smdkc110，
	将其中的20000000改为30000000即可。
(2)同步代码，然后重新编译烧录运行。

2.11.6.3、总结：牵一发而动全身


2.11.7.inand驱动问题的解决
2.11.7.1、先从现象出发定位问题
(1)解决问题的第一步，是定位问题。所谓定位问题就是找到源代码当中导致这个问题的那一句或者那几句代码。
	有时候解决这个问题需要修改的代码和直接导致这个问题的代码是不同的。
	我们这里说的定位问题指的是定位到出问题的代码处，也就是运行了这一句代码时发生了这个错误。
(2)定位了问题之后，实际修改程序解决问题不一定改的是这一句代码。
	但是肯定和这一句代码有关联，我们要通过自己分析来找到这种关联，从而从定位的错误点找到真正需要修改的点，然后去修改他。
(3)实战方法：从打印出来的错误信息中挑选一个关键词，然后去源代码中搜索这个关键字，通过这种搜索的方法定位问题。
	通过搜索将问题定位在drivers/mmc/mmc.c的818行。
(4)然后就是解决问题了。

2.11.7.2、网络搜索解决方案
(1)初步的解决方案是自己先浏览一遍这个问题点周边代码上下文。
	通过浏览代码上下文，发现这个函数是在读取SD/iNand的ext_csd寄存器的值。
	通过浏览代码结合出错地方，可以判断出：从卡端读取ext_csd寄存器是成功的，并且从读取结果中拿到了卡的版本号信息。
	然后代码对版本号进行了判断，并且如果版本号大于5就会报错并且函数错误退出。这就是问题所正。
(2)问题就是：我们使用的iNand卡的版本号大于5，而uboot代码本身不处理版本号大于5的卡，因此出错了。
(3)怎么解决？第一可能，换卡；第二可能，软件修复。
(4)网络搜索错误关键字，然后逐个去查阅，看看哪个可以给我们提供解决问题的思路和方法。
	http://blog.csdn.net/wang_shuai_ww/article/details/22308853

CSD寄存器: card specific data

// mmc_read_extended_csd() // 读取高版本sd卡扩展csd寄存器
// host->version 		   // sd控制器version

2.11.7.3、尝试修改代码解决问题
(1)解决方法就是修改uboot中的代码，把判断的5改成更大的数字。譬如8，然后跳过这个错误。

2.11.7.4、推测和实验验证（SD卡和iNand的区别）
(1)当前板子上有一个iNand接在SD0上，有一个外置SD卡接在SD2上。那uboot中初始化的这个是iNand而不是SD卡。
	也就是说uboot中实际用的是SD0而不是SD2.
(2)大家可以尝试，使用外置SD卡时，这个版本号的问题不会出现。从这里可以推测出SD卡和iNand的区别，
	至少从一个角度可以看出：SD卡版本低，iNand的版本比较高。// 有很多属性inand具备, sd卡具备

// uboot代码初始化的是inand, 虽然从sd卡启动,但是初始化的仍是inand
// mmc.c line1166		mmc = find_mmc_device(0)

// ./sd_fusing.sh /dev/sdb

2.11.8.一些小问题的修补
2.11.8.1、控制台串口更换为串口0
(1)uboot中默认使用串口2来做控制台输入输出的。
(2)SOC中一共有4个串口（串口0、1、2、3），开发板X210上用DB9接口引出了2个串口，分别是串口2和串口0.
	（靠边的是串口2，靠里那个是串口0）。
(3)三星公司推荐使用串口2来作为调试串口，所以在三星移植的uboot和内核版本中都是以串口2默认为控制台串口的。
(4)有时候项目需要将调试串口修改为另外的串口（譬如串口0），这时候需要修改uboot的代码，
	做移植让uboot工作在串口0的控制台下。
(5)uboot中真正去硬件初始化串口控制器的代码在lowlevel_init.S中的uart_asm_init中，
	其中初始化串口的寄存器用ELFIN_UART_CONSOLE_BASE宏作为串口n的寄存器的基地址，结合偏移量对寄存器进行寻址初始化。
	所以uart_asm_init中到底初始化的是串口几（从0到3）？取决于ELFIN_UART_CONSOLE_BASE宏。
	这个宏的值又由CONFIG_SERIALn（n是从1到4）来决定
(6)同步代码、编译烧录运行，发现串口线插在串口2上，crt上只打印：SD checksum error.
（这个是内部iROM打印出来的，内部iNand校验失败的信息）；然后将串口线改插到串口0上，启动，所有的信息出现。实验成功。

2.11.8.2、修改默认网络地址设置
(1)修改配置头文件smdkv210single.h中的CONFIG_IPADDR等宏，则可以修改uboot的默认环境变量。
(2)更改完成后如果环境变量还是原来的，正常。因为原来uboot执行过saveenv，
	因此环境变量已经被保存到iNand中的ENV分区中去了。
	uboot启动后校验时iNand的ENV分区中的环境变量是正确的，
	因此会优先加载。我们在uboot源代码中修改的只是默认的环境变量。
	解决方案是擦除掉iNand中的那一份环境变量，然后迫使uboot启动时使用uboot代码中自带的默认的这一份环境变量，
	就可以看到了。
(3)可以使用mmc write 0 30000000 11# 32
（表示将DDR的0x30000000开头的一段内存中的内容写入iNand中的第17个扇区开始的32个扇区内，写入长度是32个扇区长度（16KB））

2.11.8.3、修改行提示符
(1)#define CFG_PROMPT              "ASTON210 # " 

2.11.8.4、总结
(1)结论就是对uboot的整体结构和过程了解之后，移植非常简单。


2.11.9.1、网卡芯片与开发板的连接方式
(1)SoC的SROM bank和网卡芯片的CS引脚（SROM就是SRAM/ROM）
	SoC的SROMController其实就是SoC提供的对外总线式连接SRAM/ROM的接口
	如果SoC要外部外接一些SRAM/ROM类的存储芯片（或者伪装成SROM接口的芯片，譬如网卡芯片）就要通过SROM Controller来连接
	网卡接在SROM中好处就是网卡芯片好像一个存储芯片一样被扩展在SoC的一个地址空间中
	主机SoC可以直接用一个地址来访问网卡芯片内部寄存器
(2)网卡芯片内部寄存器使用相对地址访问。
	网卡芯片内部很多寄存器有一个地址，这个地址是从00开始的，但是实际上我们SoC不能用0地址去访问这个网卡的芯片内部寄存器
	SoC访问网卡芯片00寄存器时的地址应该是：起始地址+00这里的起始地址就是网卡芯片对应接在SROM bankn中的bankn对应的基地址。
(3)主机SoC上网，其实就是通过操控网卡芯片内部的寄存器、缓冲区等资源来上网的。
	也就是说其实SoC是通过网卡芯片来间接上网的。
(4)总结：实际上也是一种总线式连接方式。优势是SoC内部不需要内置网卡控制器，所有的SFR全都在外部网卡芯片中，
	而且还可以通过地址直接访问（IO与内存统一编址），不用像Nand/SD接口一样使用时序来访问。
(5)从逻辑上来看，网卡更像是串口，而不像是SD/Nand。

// soc与外设连接, 两种情况: 
// 总线式扩展(ddr) 通过地址总线直接操作
// 非总线式扩展	通过一定的时序(发命令, 发地址)

// x210的SROM控制器允许8/16bit的接口
// 网线有8根线, Tx-和Tx+, Rx+和Rx-, 4GND
// X210上将DM9000的CS引脚接到了CSn1上，对应SROM bank1（推断出DM9000的总线地址基地址是0x88000000）

(4)DM9000的CMD引脚接到了S5PV210的ADDR2引脚上
	DM9000为了减少芯片引脚数，数据线和地址线是复用的
	（DATA0到DATA15这16根线是有时候做数据线传输数据，有时候做地址线传输地址的。什么时候做什么用就由CMD引脚决定。）
	通过查询数据手册知道：当CMD为高电平时对应传输是DATA，当CMD为低电平时对应传输为INDEX（offset，寄存器地址）。

注明：这些引脚上的电平变化都是控制器自动的，不需要程序员手工干预。
	程序员所需要做的就是在配置寄存器值时充分考虑到硬件电路的接法，然后给相应寄存器配置正确的数值即可。


2.11.10.1、网卡驱动文件介绍
(1)uboot中本来就提供了很多网卡芯片的驱动程序，在uboot/drivers/net/dm9000x.c和dm9000x.h。这个驱动来自于linux kernel源代码。
	所以我们uboot中是移植而不是编写。
(2)要想彻底看懂这个驱动，必须对linux的驱动模型中网络设备驱动有一定的理解才可以。因为我们还没学驱动，因此这个源代码就不用看了。
(3)这个驱动是linux内核中做好的，根本不用动可以在uboot中直接使用的。
	而且因为linux驱动设计的很合理
	（数据和代码是分开的，这里驱动主要是代码，数据是由硬件开发板中的接法决定的，数据由一定的数据结构来提供。）
	所以驱动本身具有可移植性。这个就决定了我们移植DM9000驱动时这个驱动文件dm9000x.c和h不用动，要动的是数据。
2.11.10.2、网卡移植的关键：初始化
(1)uboot在第二阶段init_sequences中进行了一系列的初始化，其中就有网卡芯片的初始化。
	这个初始化就是关键，在这里的初始化中只要将网卡芯片正确的初始化了，则网卡芯片就能工作
	（意思是网卡驱动dm9000x.c和dm9000x.h依赖于这里的初始化而工作）。
(2)网卡初始化代码地方在：
start_armboot
	init_sequence
		board_init
			dm9000_pre_init		这个函数就是移植的关键
(3)dm9000_pre_init函数主要功能就是初始化DM9000网卡
	这个初始化过程和我们开发板上DM9000网卡芯片的硬件连接方式有关。
	必须要结合开发板原理图来分析，然后决定这个函数怎么编程。
(4)原来的代码是三星的工程师根据三星的开发板SMDKV210的硬件接法来写的程序，我们要根据自己的开发板的硬件接法去修改这个程序，
	让网卡在我们的开发板上能工作。
(5)#define DM9000_16BIT_DATA这个宏用来表示DM9000工作在16位总线模式下。
	根据上节课的硬件原理图的分析，可以看到我们开发板上DM9000确实工作在16位模式下。
(6)从三星版本的代码中可以看出，它操作的是bit20-bit23，对照数据手册中寄存器定义，可以看出三星的开发板DM9000是接在Bank5上的。
而我们接在bank1上的，因此我们需要操作的bit位是bit4-bit7
(7)总结：三个寄存器的修改。主要是三星的开发板DM9000接在bank5，我们接在了bank1上，因此要做一些修改。

2.11.10.3、基地址的配置等
(1)之前说过，驱动分为2部分：代码和数据。代码不用动，数据要修改。
(2)CONFIG_DM9000_BASE是DM9000网卡通过SROM bank映射到SoC中地址空间中的地址。
	这个地址的值取决于硬件接到了哪个bank，这个bank的基地址是SoC自己定义好的。
	譬如我们这里接到了bank1上，bank1的基地址是0x88000000.
(3)DM9000_IO表示访问芯片IO的基地址，直接就是CONFIG_DM9000_BASE；
	DM9000_DATA表示我们访问数据时的基地址，因为DM9000芯片的CMD引脚接到了ADDR2，因此这里要+4（0b100，对应ADDR2）
(4)本来这样配置就完了，重新编译运行网卡就应该工作了。
	但是实际测试发现不工作，要怎么样修改呢？修改方式是将CONFIG_DM9000_BASE改成0x88000300就工作了。
	问题？这个0x300从哪里来的？我得出的感觉最靠谱的解释是：跟DM9000网卡芯片型号版本有关，我认为这个0x300是DM9000网卡本身的问题
	他本身的内部寄存器就有一个0x300的一个偏移量

2.11.11.1、网卡移植代码实践
(1)经过实践，网卡驱动移植成功
(2)其实还可以做一些实验。譬如说对网卡驱动初始化部分寄存器的设置，还有网卡CONFIG_DM9000_BASE也可以配成0x88000000再去试一试

2.11.11.2、linux系统中网卡驱动的典型工作方式简介
(1)在linux系统中，网卡算是一个设备，这个设备驱动工作后会生成一个设备名叫ethn（n是0、1、2、····）
	（无线网卡名字一般叫wlan0、wlan1····）。然后linux系统用一些专用命令来操作网卡，譬如ifconfig命令
(2)linux下的应用程序如何使用网卡驱动来进行网络通信？最通用的方法就是socket接口
	linux系统中有一系列的API和库函数，提供了一个socket编程接口
	linux下的应用程序都是通过socket来实现上网的，socket内部就是间接调用的网卡驱动实现网络通信的
(3)linux设计是非常完备的，应用层和驱动层是严格分离的
	也就是说写网络编程应用层的人根本不用管驱动，只要会用socket接口即可
	写底层驱动的人根本不用管应用层，只要面向linux的网络驱动框架模型即可

2.11.11.3、uboot中网卡驱动的工作方式简介
(1)一定要记住：uboot本身是一个裸机程序，是一个整体，没有分层。所以uboot中根本没有驱动和应用的概念
(2)按照逻辑来说，ping这样的命令实现的代码就是网络应用的应用程序，像dm9000x.c和dm9000x.h这样的代码属于驱动程序
	所以在uboot中这些东西是揉在一起的，应用是直接调用驱动实现的
	也就是说ping命令内部是直接调用了dm9000的网卡驱动中的函数来实现自己的

2.11.11.4、以ping命令为例查找代码验证分析
(1)ping命令是uboot的众多命令之一，ping命令实现的函数叫do_ping
(2)函数的调用关系：
do_ping
	NetLoop
		PingStart
			PingSend
				ArpRequest
					eth_send（dm9000x.c中）
(3)验证了2.11.11.3中说的uboot中应用程序（ping）调用驱动程序（dm9000x.c）的方式。这就是一种直接调用的方式。

注：lcd驱动与logo显示，在2.13.uboot杂记-logo显示和fastboot原理等中详解


2.11.12.使用自己移植的uboot启动内核
2.11.12.1、问题：当前uboot不能启动内核
(1)用同样的方法（使用tftp 0x30008000 zImage-qt; 然后bootm 0x30008000）
	分别使用我们自己移植的uboot和使用九鼎移植版本的uboot去启动内核，发现九鼎移植版本的可以启动，但是我们自己移植的不可以启动
	到此我们就断定我们的uboot有问题，不能启动内核。	// 确认实验方法OK
(2)做基本检查：首先怀疑是机器码不对。经过和九鼎移植版本的uboot对比发现machid都是2456，说明机器码没错	// bdinfo
(3)想到一个问题，我们之前做实验时将串口改为了串口0，而内核zImage-qt的串口输出在串口2
	怀疑可能的问题是uboot使用了串口0而内核使用了串口2所以在uboot后看不到内核的启动信息

// 注意bootcmd, bootargs设置(参见裸机第三章)

2.11.12.2、解决第一步：将串口改回串口2
(1)在smdkv210single.h中修改串口编号即可。

2.11.12.3、根据现象分析，定位问题并试图解决
(1)如果已经启动了内核，那没什么好说的了。应该是可以直接启动了
(2)如何内核没有启动，是smdkv210single.h中没有定义bootm传参需要的那几个宏造成的
	#define CONFIG_SETUP_MEMORY_TAGS	// 传参时的内存信息
	#define CONFIG_CMDLINE_TAG			// 启动信息











