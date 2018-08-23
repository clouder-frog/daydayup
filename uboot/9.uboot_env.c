
2.9.1.1、环境变量的作用
(1)不修改uboot的源代码，而是通过修改环境变量来影响uboot运行时的一些数据和特性
	譬如说通过修改bootdelay环境变量就可以更改系统开机自动启动时倒数的秒数。

	// 环境变量与全局变量的区别: 两次复位上电, 环境变量具有相关性

2.9.1.2、环境变量的优先级
(1)uboot代码当中有一个值，环境变量中也有一个值。
	uboot程序实际运行时规则是：如果环境变量为空则使用代码中的值；
								如果环境变量不为空则优先使用环境变量对应的值
(2)譬如machid（机器码）。uboot中在x210_sd.h中定义了一个机器码2456，写死在程序中的不能更改
	如果要修改uboot中配置的机器码，可以修改x210_sd.h中的机器码，但是修改源代码后需要重新编译烧录
	比较简单的方法就是使用环境变量machid。
	set machid 0x998 类似这样，有了machid环境变量后，系统启动时会优先使用machid对应的环境变量，这就是优先级问题

	// Bootm.c do_bootm_linux() 	s = getenv("machid");  if (NULL = s){}

2.9.1.3、环境变量在uboot中工作方式
(1)默认环境变量，在uboot/common/env_common.c中default_environment，
	这东西本质是一个字符数组，大小为CFG_ENV_SIZE（16kb），里面内容就是很多个环境变量连续分布组成的，
	每个环境变量最末端以'\0'结束。
	// gcc提供的语法支持 多个字符串"" "" ""自动连接, "aaa"的'\0'编译器给省略掉, 所以手动添加'\0'

(2)SD卡中环境变量分区，在uboot的raw分区中。SD卡中其实就是给了个分区，专门用来存储而已。存储时其实是把DDR中的环境变量整体的写入SD卡中分区里。所以当我们saveenv时其实整个所有的环境变量都被保存了一遍，而不是只保存更改了的。
(3)DDR中环境变量，在default_environment中，实质是字符数组。在uboot中其实是一个全局变量，链接时在数据段，重定位时default_environment就被重定位到DDR中一个内存地址处了。这个地址处这个全局字符数组就是我们uboot运行时的DDR中的环境变量了。

总结：刚烧录的系统中环境变量分区是空白的，uboot第一次运行时加载的是uboot代码中自带的一份环境变量，叫默认环境变量。我们在saveenv时DDR中的环境变量会被更新到SD卡中的环境变量中，就可以被保存下来，下次开机会在环境变量relocate时会SD卡中的环境变量会被加载到DDR中去。

default_environment中的内容虽然被uboot源代码初始化为一定的值（这个值就是我们的默认环境变量），但是在uboot启动的第二阶段，env_relocate时代码会去判断SD卡中的env分区的crc是否通过。如果crc校验通过说明SD卡中有正确的环境变量存储，则relocate函数会从SD卡中读取环境变量来覆盖default_environment字符数组，从而每次开机可以保持上一次更改过的环境变量。

	// 读取SD卡env分区, CRC校验通过则覆盖default_environment[], 校验不通过则直接使用default_environment[]
	// 

2.9.2.环境变量相关命令源码解析1
2.9.2.1、printenv
(1)找到printenv命令所对应的函数。通过printenv的help可以看出，这个命令有2种使用方法。第一种直接使用不加参数则打印所有的环境变量；第二种是printenv name则只打印出name这个环境变量的值。
(2)分析do_printenv函数。
(3)do_printenv函数首先区分argc=1还是不等于1的情况，若argc=1那么就循环打印所有的环境变量出来；如果argc不等于1，则后面的参数就是要打印的环境变量，给哪个就打印哪个。
(4)argc=1时用双重for循环来依次处理所有的环境变量的打印。第一重for循环就是处理各个环境变量。所以有多少个环境变量则第一重就执行循环多少圈。
(5)这个函数要看懂，首先要明白整个环境变量在内存中如何存储的问题。
(6)关键点：第一要明白环境变量在内存中存储的方式；第二要C语言处理字符串的功底要好。

	// cmd_nvedit.c 字符串解析 do_printenv()  -- 环境变量在内存中的存储方式

2.9.3.环境变量相关命令源码解析2
2.9.3.1、setenv
(1)命令定义和对应的函数在uboot/common/cmd_nvedit.c中，对应的函数为do_setenv。
(2)setenv的思路就是：先去DDR中的环境变量处寻找原来有没有这个环境变量，如果原来就有则需要覆盖原来的环境变量，如果原来没有则在最后新增一个环境变量即可。
第1步：遍历DDR中环境变量的数组，找到原来就有的那个环境变量对应的地址。168-174行。
第2步：擦除原来的环境变量，259-265行
第3步：写入新的环境变量，266-273行。
(3)本来setenv做完上面的就完了，但是还要考虑一些附加的问题。
问题一：环境变量太多超出DDR中的字符数组，溢出的解决方法。
问题二：有些环境变量如baudrate、ipaddr等，在gd中有对应的全局变量。这种环境变量在set更新的时候要同时去更新对应的全局变量，否则就会出现在本次运行中环境变量和全局变量不一致的情况。

// -- do_setenv()	// 没有下划线的可以修改
	|
	| -- _do_setenv()	// 	一个下划线的系统自己使用
	|
	| -- __do_setenv() 	// 两个下划线是系统内部自己用
	|
	| -- ___do_setenv() // warning
	
2.9.4.环境变量相关命令源码解析2
2.9.4.1、saveenv
(1)在uboot/common/cmd_nvedit.c中，对应函数为do_saveenv
(2)从uboot实际执行saveenv命令的输出，和x210_sd.h中的配置（#define CFG_ENV_IS_IN_AUTO）可以分析出：我们实际使用的是env_auto.c中相关的内容。没有一种芯片叫auto的，env_auto.c中是使用宏定义的方式去条件编译了各种常见的flash芯片（如movinand、norflash、nand等）。然后在程序中读取INF_REG（OMpin内部对应的寄存器）从而知道我们的启动介质，然后调用这种启动介质对应的操作函数来操作。
(3)do_saveenv内部调用env_auto.c中的saveenv函数来执行实际的环境变量保存操作。
(4)寄存器地址：E010F000+0C=E010_F00C，含义是用户自定义数据。我们在start.S中判断启动介质后将#BOOT_MMCSD（就是3，定义在x210_sd.h）写入了这个寄存器，所以这里读出的肯定是3，经过判断就是movinand。所以实际执行的函数是：saveenv_movinand
(5)真正执行保存环境变量操作的是：cpu/s5pc11x/movi.c中的movi_write_env函数，这个函数肯定是写sd卡，将DDR中的环境变量数组（其实就是default_environment这个数组，大小16kb，刚好32个扇区）写入iNand中的ENV分区中。
(6)raw_area_control是uboot中规划iNnad/SD卡的原始分区表，这个里面记录了我们对iNand的分区，env分区也在这里，下标是2.追到这一层就够了，再里面就是调用驱动部分的写SD卡/iNand的底层函数了。

	void movi_write_env(ulong addr)
	{
		movi_write(raw_area_control.image[2].start_blk, 
			raw_area_control.image[2].used_blk, addr)
	}
	// param1: image[2] -- env分区; start_blk -- 起始扇区号
	// param2: used_blk = 32 -- x210_sd.h配置

2.9.5.uboot内部获取环境变量
2.9.5.1、getenv
(1)应该是不可重入的。
(2)实现方式就是去遍历default_environment数组，挨个拿出所有的环境变量比对name，找到相等的直接返回这个环境变量的首地址即可。

2.9.5.2、getenv_r
(1)可重入版本。（可自行搜索补充可重入函数的概念）
(2)getenv函数是直接返回这个找到的环境变量在DDR中环境变量处的地址，而getenv_r函数的做法是找到了DDR中环境变量地址后，将这个环境变量复制一份到提供的buf中，而不动原来DDR中环境变量。
所以差别就是：getenv中返回的地址只能读不能随便乱写，而getenv_r中返回的环境变量是在自己提供的buf中，是可以随便改写加工的。
2.9.5.3、总结
(1)功能是一样的，但是可重入版本会比较安全一些，建议使用。
(2)有关于环境变量的所有操作，主要理解了环境变量在DDR中的存储方法，理解了环境变量和gd全局变量的关联和优先级，理解了环境变量在存储介质中的存储方式（专用raw分区），整个环境变量相关的都清楚了。




