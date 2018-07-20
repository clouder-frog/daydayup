《1.11.ARM裸机第十一部分-NandFlash和iNand》

第一部分、章节目录
1.11.1.NandFlash的接口
1.11.2.NandFlash的结构
1.11.3.NandFlash的常见操作及流程分析
1.11.4.S5PV210的NandFlash控制器
1.11.5.Nand操作代码解析
1.11.6.iNand介绍
1.11.7.SD卡/iNand操作
1.11.8.SD/iNand代码实战分析1
1.11.9.SD/iNand代码实战分析2
1.11.10.SD/iNand代码实战分析3

第二部分、章节介绍
1.11.1.NandFlash的接口
	本节首先讲解NandFlash的型号命名规则，然后重点解析了NandFlash的结构框图，通过这份数据手册中提供的结构框图，希望大家对Nand的矩阵式存储有个轮廓印象和理解。
1.11.2.NandFlash的结构
	本节讲述Nand的内部结构，包括block、page等概念，带内数据及带外数据(oob)、ECC、坏块标志、Nand的多周期地址时序，Nand的命令码等。
1.11.3.NandFlash的常见操作及流程分析
	本节介绍了NandFlash的典型操作：块擦除、页读、页写。并且以数据手册中的流程图为引向大家讲解这些操作的顺序，以及涉及到的命令码、地址时序、状态寄存器检查等细节。
1.11.4.S5PV210的NandFlash控制器
	本节简单介绍S5PV210的NandFlash控制器，重点讲了Nand控制器的作用，有无控制器的差异，这个是理解Nand控制器的关键，最后简单浏览了S5PV210的Nand控制器的寄存器列表。
1.11.5.Nand操作代码解析
	本节讲解Nand操作代码，以调试好的Nand读写代码为原材料，对照数据手册中之前讲过的知识和流程图，讲述这些代码是怎么写出来的。本节的目的是教会大家如何学习，如何结合手头资源资料学习代码。
1.11.6.iNand介绍
	本节系统介绍iNand，将其与Nand、与SD卡等进行对比，最后得出准确结论，本节课的目的是让大家对iNand芯片有框架式的认可，先知道到底什么是iNand。
1.11.7.SD卡/iNand操作
	本节讲述iNand/SD卡的一些操作概念，包括：iNand的硬件接口、iNand的命令响应式工作模式、iNand的内部结构框图及SoC的iNand控制器的寄存器简介。
1.11.8.SD/iNand代码实战分析1
	本节以linux驱动中iNand操作的代码为原材料，逐行分析代码，讲述这些代码和iNand协议文档、数据手册之间的对应关系，试图告诉大家这些代码是怎样写出来的。一共3节，此为第1节。
1.11.9.SD/iNand代码实战分析2
	本节以linux驱动中iNand操作的代码为原材料，逐行分析代码，讲述这些代码和iNand协议文档、数据手册之间的对应关系，试图告诉大家这些代码是怎样写出来的。一共3节，此为第2节。
1.11.10.SD/iNand代码实战分析3
	本节以linux驱动中iNand操作的代码为原材料，逐行分析代码，讲述这些代码和iNand协议文档、数据手册之间的对应关系，试图告诉大家这些代码是怎样写出来的。一共3节，此为第3节。

第三部分、随堂记录
1.11.1.NandFlash的接口
1.11.1.1、Nand的型号与命名
(1)Nand的型号命名都有含义，就拿K9F2G08来示例分析一下：K9F表示是三星公司的NandFlash系列。2G表示Nand的大小是2Gbit（256MB）。08表示Nand是8位的（8位就是数据线有8根）
(2)Nand命名中可以看出：厂家、系列型号、容量大小、数据位数。

1.11.1.2、Nand的数据位
(1)Nand有8位数据位的，有16位数据位的。做电路时/写软件时应该根据自己实际采购的Nnad的位数来设计电路/写软件。
(2)说明Nand是并行接口的（8/16位）
(3)Nand的数据线上传递的不一定全部是有效数据，也可能有命令、地址等。

1.11.1.3、Nand的功能框图
(1)Nand的结构可以看成是一个矩阵式存储器，其中被分成一个一个的小块，每一小块可以存储一个bit位，然后彼此以一定单位组合成整个Nand。
(2)Nand中可以被单次访问的最小单元（就是说对Nand进行一次读写至少要读写这么多，或者是这么多的整数倍）叫做Page（页），在K9F2G08芯片中，Page的大小是2KB+64B。也就是说我们要读写K9F2G08，每次至少要读写2KB或者n*2KB，即使我们只是想要其中的一个字节。这就是我们说的典型的块设备（现在有些块设备为了方便，提供了一种random read模式，可以只读取1个字节）。
(3)页往上还有个Block（块）的概念，1个块等于若干个页（譬如在K9F2G08中1个块等于64页）。
(4)页往上就是整个Nand芯片了，叫做Device。一个Device是若干个Block，譬如K9F2F08一个Device有2028个block。所以整个Device大小为：2048×64×2K = 256MB
(5)块设备分page、block有什么意义？首先要明白，块设备不能完全按字节访问而必须块访问是物理上的限制，而不是人为设置的障碍。其次，Page和Block各有各的意义，譬如Nand中：Page是读写Nand的最小单位；Block是擦除Nand的最小单位。（这些规则都是Nand的物理原理和限制要求的，不是谁想要这样的，所以对于我们做软件的来说，只能去想办法适应硬件，不是想着超越硬件）。
(6)Nand芯片中主要包含2部分：Nand存储颗粒+Nand接口电路。存储颗粒就是纯粹的Nand原理的存储单元，类似于仓库；Nand接口电路是用来管理存储颗粒，并且给外界提供一个统一的Nand接口规格的访问接口的。
(7)Nand中有多个存储单元，每个单元都有自己的地址（地址是精确到字节的）。所以Nand是地址编排精确到字节，但是实际读写却只能精确到页（所以Nand的很多操作都要求给的地址是页对齐的，譬如2K、4K、512K等这样的地址，不能给3000B这样的地址）。Nand读写时地址传递是通过IO线发送的，因为地址有30位而IO只有8位，所以需要多个cycle才能发送完毕。一般的Nand都是4cycle或者5cycle发送地址（从这里把Nand分为了4cycle Nand和5cycle Nand）。
总结：Nand芯片内部有存储空间，并且有电路来管理这些存储空间，向外部提供统一的Nand接口的访问规则，然后外部的SoC可以使用Nand接口时序来读写这个Nand存储芯片。Nand接口是一种公用接口，是一种标准，理论上来说外部SoC可以直接模拟Nand接口来读写Nand芯片，但是实际上因为nand接口对时序要求非常严格，而且时序很复杂，所以一般的SoC都是通过专用的硬件的Nand控制器（这些控制器一般是作为SoC的内部外设来存在的）来操控Nand芯片的。

1.11.2.NandFlash的结构
1.11.2.1、Nand的单元组织：block与page（大页Nand与小页Nand）
(1)Nand的页和以前讲过的块设备（尤其是硬盘）的扇区是类似的。扇区最早在磁盘中是512字节，后来也有些高级硬盘扇区不是512字节而是1024字节/2048字节/4096字节等。Nand也是一样，不同的Nand的页的大小是不同的，也有512字节/1024字节/2048字节/4096字节等。
(2)一个block等于多少page也是不定的，不同的Nand也不同。一个Nand芯片有多少block也是不定的，不同的Nand芯片也不同。
总结：Nand的组织架构挺乱的，接口时序也不同，造成结构就是不同厂家的Nand芯片，或者是同一个厂家的不同系列型号存储容量的nand接口也不一样。所以nand有一个很大的问题就是一旦升级容量或者换芯片系列则硬件要重新做、软件要重新移植。

1.11.2.2、带内数据和带外数据（ECC与坏块标记）
(1)Nand的每个页由2部分组成，这2部分各自都有一定的存储空间。譬如K9F2G08中为2K+64字节。其中的2K字节属于带内数据，是我们真正的存储空间，将来存储在Nand中的有效数据就是存在这2K范围内的（我们平时计算nand的容量时也是只考虑这2KB）；64字节的带外数据不能用来存储有效数据，是作为别的附加用途的（譬如用来存储ECC数据、用来存储坏块标志等····）
(2)什么是ECC：（error correction code，错误校验码）。因为nand存储本身出错（位反转）概率高（Nand较Nor最大的缺点就是稳定性），所以当我们将有效信息存储到Nand中时都会同时按照一定算法计算一个ECC信息（譬如CRC16等校验算法），将ECC信息同时存储到Nand这个页的带外数据区。然后等将来读取数据时，对数据用同样的算法再计算一次ECC，并且和从带外数据区读出的ECC进行校验。如果校验通过则证明Nand的有效数据可信，如果校验不通过则证明这个数据已经被损坏（只能丢弃或者尝试修复）。
(3)坏块标志：Nand芯片用一段时间后，可能某些块会坏掉（这些块无法擦除了，或者无法读写了），nand的坏块非常类似于硬盘的坏道。坏块是不可避免的，而且随着Nand的使用坏块会越来越多。当坏块还不算太多时这个Nand都是可以用的，除非坏块太多了不划算使用了才会换新的。所以我们为了管理Nand发明了一种坏块标志机制。Nand的每个页的64字节的带外数据中，我们（一般是文件系统）定义一个固定位置（譬如定位第24字节）来标记这个块是好的还是坏的。文件系统在发现这个块已经坏了没法用了时会将这个块标记为坏块，以后访问nand时直接跳过这个块即可。

1.11.2.3、Nand的地址时序
(1)nand的地址有多位，分4/5周期通过IO引脚发送给Nand芯片来对Nand进行寻址。寻址的最小单位是字节，但是读写的最小单位是页。
(2)nand的地址在写代码时要按照Nand要求的时序和顺序去依次写入。

1.11.2.4、Nand的命令码
(1)外部SoC要想通过Nand控制器来访问Nand（实质就是通过Nand接口），就必须按照Nand接口给nand发送命令、地址、数据等信息来读写Nand。
(2)Nand芯片内部的管理电路本身可以接收外部发送的命令，然后根据这些命令来读写Nand内容与外部SoC交互。所以我们对nand进行的所有操作（擦除、读、写···）都要有命令、地址、数据的参与才能完成，而且必须按照Nand芯片规定的流程来做。

1.11.3.NandFlash的常见操作及流程分析
1.11.3.1、坏块检查
(1)Flash使用之前要先统一擦除（擦除的单位是块）。Flash类设备擦除后里面全是1，所以擦干净之后读出来的值是0xff。
(2)检查坏块的思路就是：先块擦除，然后将整块读出来，依次检测各自节是否为0xff，如果是则表明不是坏块，如果不是则表明是坏块。

1.11.3.2、页写（program）操作
(1)写之前确保这个页是被擦除干净的。如果不是擦除干净的（而是脏的、用过的）页，写进去的值就是错的，不是你想要的结果。
(2)写操作（write）在flash的操作中就叫编程（program）
(3)SoC写Flash时通过命令线、IO线依次发送写命令、写页地址、写数据等进入NandFlash。
(4)写的过程：SOC通过Nand控制器和Nand芯片完成顺序对接，然后按照时序要求将一页数据发给Nand芯片内部的接口电路。接口电路先接收收据到自己的缓冲区，然后再集中写入Nand芯片的存储区域中。Nand接口电路将一页数据从缓冲区中写入Nand存储系统中需要一定的时间，这段时间Nand芯片不能再响应SOC发过来的其他命令，所以SoC要等待Nnad接口电路忙完。等待方法是SoC不断读取状态寄存器（这个状态寄存器有2种情况：一种是SoC的Nand控制器自带的，另一种是SoC通过发命令得到命令响应得到的），然后通过检查这个状态寄存器的状态位就能知道Nand接口电路刚才写的那一页数据写完了没、写好了没。直到SoC收到正确的状态寄存器响应才能认为刚才要写的那一页数据已经ok。（如果SoC收到的状态一直不对，可以考虑重写或者认为这一页所在的块已经是坏块，或者整个Nand芯片已经挂掉了）。
(5)正常情况下到了第四步就已经完了。但是因为Nand的读写有不靠谱情况，因此我们为了安全会去做ECC校验。ECC校验有硬件式校验和软件式校验2种。软件式校验可以采用的策略有很多，其中之一（Nand芯片手册上推荐的方式是）：将刚才写入的1页数据读出来，和写入的内容进行逐一对比。如果读出的和写入的完全一样，说明刚才的写入过程正确完成了；如果读出来的和写入的不完全一样那就说明刚才的写入有问题。
(6)硬件式ECC：SoC的Nand控制器可以提供硬件式ECC（这个也是比较普遍的情况）。硬件式ECC就是在Nand的控制器中有个硬件模块专门做ECC操作。当我们操作Nand芯片时，只要按照SoC的要求按时打开ECC生成开关，则当我们写入Nand芯片时SoC的Nand控制器的ECC模块会自动生成ECC数据放在相应的寄存器中，然后我们只需要将这生成的ECC数据写入Nand芯片的带外数据区即可；在将来读取这块Nand芯片时，同样要打开硬件ECC开关，然后开始读，在读的过程当中硬件ECC会自动计算读进来的一页数据的ECC值并将之放到相应的寄存器中。然后我们再读取带外数据区中原来写入时存入的ECC值，和我们刚才读的时候得到的ECC值进行校验。校验通过则说明读写正确，校验不通过则说明不正确（放弃数据或者尝试修复）。

1.11.3.3、擦除（erase）操作
(1)擦除时必须给块对齐的地址。如果给了不对齐的地址，结果是不可知的（有些Nand芯片没关系，它内部会自动将其对齐，而有些Nand会返回地址错误）。
(2)读写时给的地址也是一样，要求是页对齐地址。如果给了不对齐的，也是有可能对有可能错。

1.11.3.4、页读（read）操作

1.11.4.S5PV210的NandFlash控制器
1.11.4.1、SoC的Nand控制器的作用
(1)Nand芯片本身通过Nand接口电路来存取数据，Nand接口电路和SOC之间通过Nand接口时序来通信。Nand接口时序相对复杂，如果要SoC完全用软件来实现Nand接口时序有一些不好（主要是：第一很难保证时序能满足、容易不稳定；第二代码很难写）。解决方案是：在SoC内部集成一个Nand控制器（实质就是一块硬件电路，这个硬件电路完全满足Nand接口时序的操作，然后将接口时序的操作寄存器化）。
(2)SOC和Nand芯片之间通信，在SoC没有Nand控制器时需要SoC自己来处理接口时序，编程很麻烦，需要程序员看Nand芯片的接口时序图，严格按照接口时序图中编程（尤其要注意各个时间参数）；在SoC有Nand控制器时SoC只需要编程操控Nand控制器的寄存器即可，Nand控制器内部硬件会根据寄存器值来生成合适的Nand接口时序和Nand芯片通信。所以在有Nand控制器时编程要简单很多，我们读写Nand芯片时再也不用关注Nand接口时序了，只要关注SoC的Nand控制器的寄存器即可。
(3)扩展来讲，现在的技术趋势就是：几乎所有的外设在SoC内部都有对应的控制器来与其通信，那么SoC内部集成的各种控制器（也就是各种内部外设）越多，则SoC硬件能完成的功能越多，将来用这个SoC来完成相应任务时软件编程越简单。譬如说图形处理和图像处理领域，2D图像编码（jpeg编码）、视频编码（h.264编码），现在大部分的application级别的SoC都有集成的内部编码器（像S5PV210就有、更复杂的譬如4418、6818就更不用说了，只会更多更先进），我们可以利用这些硬件编码器来进行快速编解码，这样软件工作量和难度降低了很多（这就是所谓的硬件加速）。

1.11.4.2、结构框图分析
(1)结构框图中关键点：SFR（我们后续编程的关键，编程时就是通过读写SFR来产生Nand接口时序以读写Nand芯片的） + Nand interface（硬件接口，将来和Nand芯片的相应引脚进行连接） + ECC生成器

1.11.4.3、S5PV210的Nand控制器的主要寄存器
NFCONF、NFCONT、NFCMMD、NFADDR、NFDATA、NFMECCD0&NFMECCD1、NFSECCD、NFSTAT


1.11.5.Nand操作代码解析
1.11.5.1、擦除函数

1.11.5.2、页读取函数

1.11.5.3、页写入函数

总结：
(1)像NandFlash这类芯片，通过专用的接口时序和SoC内部的控制器相连（这种连接方式是非常普遍的，像LCD、DDR等都是类似的连接）。这种接法和设计对我们编程来说，关键在于两点：SoC的控制器的寄存器理解和Nand芯片本身的文档、流程图等信息。
(2)对于我们来说，学习NandFlash，要注意的是：
第一，要结合SoC的数据手册、Nand芯片的数据手册、示例代码三者来理解。
第二，初学时不要尝试完全不参考自己写出Nand操作的代码，初学时应该是先理解实例代码，知道这些代码是怎么写出来的，必要时对照文档来理解代码。代码理解之后去做实践，实践成功后以后再考虑自己不参考代码只参考文档来写出nand操作的代码。


1.11.6.iNand介绍
1.11.6.1、iNand/eMMC/SDCard/MMCCard的关联
(1)最早出现的是MMC卡，卡片式结构，按照MMC协议设计。（相较于NandFlash芯片来说，MMC卡有2个优势：第一是卡片化，便于拆装；第二是统一了协议接口，兼容性好。）
(2)后来出现SD卡，兼容MMC协议。SD卡较MMC有一些改进，譬如写保护、速率、容量等。
(3)SD卡遵守SD协议，有多个版本。多个版本之间向前兼容。
(4)iNand/eMMC在SD卡的基础上发展起来，较SD卡的区别就是将SD卡芯片化了（解决卡的接触不良问题，便于设备迷你化）。
(5)iNand和eMMC的关联：eMMC是协议，iNand是Sandisk公司符合eMMC协议的一种芯片系列名称。

1.11.6.2、iNand/eMMC的结构框图及其与NandFlash的区别
(1)iNand内部也是由存储系统和接口电路构成（和Nand结构特性类似，不同之处在于接口电路功能不同）。
(2)iNand的接口电路挺复杂，功能很健全。譬如：
第一，提供eMMC接口协议，和SoC的eMMC接口控制器通信对接。
第二，提供块的ECC校验相关的逻辑，也就是说iNand本身自己完成存储系统的ECC功能，SoC使用iNand时自己不用写代码来进行ECC相关操作，大大简化了SoC的编程难度。（NandFlash分2种：SLC和MLC，SLC更稳定，但是容量小价格高；MLC容易出错，但是容量大价格低）
第三，iNand芯片内部使用MLC Nand颗粒，所以性价比很高。
第四，iNand接口电路还提供了cache机制，所以inand的操作速度很快。

1.11.6.3、iNand/eMMC的物理接口和SD卡物理接口的对比
(1)S5PV210芯片本身支持4通道的SD/MMC，在X210中实际是在SD/MMC0通道接了iNand芯片，而SD/MMC2接了SD卡（SD/MMC3也接了SD卡）。
(2)对比inand和SD卡接线，发现：这两个接线几乎是一样的，唯一的区别就是SD卡IO线有4根，而iNand的IO线有8根。
(3)这个告诉我们，我们在实际操作iNand芯片时和操作SD卡时几乎是一样的（物理接线几乎一样，软件操作协议几乎一样）。

1.11.6.4、结论：iNand/eMMC其实就是芯片化的SD/MMC卡，软件操作和SD卡相同。
分析iNand芯片的操作代码时，其实就是以前的SD卡的操作代码。一些细节的区别就是为了区分各种不同版本的SD卡、iNand的细节差异。

1.11.7.SD卡/iNand操作
1.11.7.1、硬件接口：DATA、CLK、CMD
(1)iNand的IO线有8根，支持1、4、8线并行传输模式；SD卡IO线有4根，支持1、4线并行传输模式。
(2)CMD线用来传输命令、CLK线用来传输时钟信号。
(3)接口有CLK线，工作时主机SoC通过CLK线传输时钟信号给SD卡/iNand芯片，说明：SD/iNand是同步的，SD/iNand的工作速率是由主机给它的CLK频率决定的。

1.11.7.2、命令响应的操作模式
(1)SD协议事先定义了很多标准命令（CMD0、CMD1·····），每个命令都有它的作用和使用条件和对应的响应。SD卡工作的时候就是一个一个的命令周期组合起来的，在一个命令周期中，主机先发送CMD给SD卡，然后SD卡解析这个命令并且执行这个命令，然后SD卡根据结果回发给主机SoC一个响应。（有些命令是不需要响应的，这时SD卡不会给主机回发响应，主机也不用等待响应）。标准的命令+响应的周期中，主机发完一个命令后应该等待SD卡的响应而不是接着发下一条命令。

1.11.7.3、SD/iNand的体系结构图
(1)SD卡内部有一个接口控制器，这个控制器类似于一个单片机，这个单片机的程序功能就是通过CMD线接收外部主机SoC发给SD卡的命令码，然后执行这个命令并且回发响应给主机SoC。这个单片机处理命令及回发响应遵循的就是SD协议。这个单片机同时可以控制SD卡内部的存储单元，可以读写存储单元。

1.11.7.4、SD/iNand的寄存器（重点是RCA寄存器）
(1)注意这里说的是SD卡内部的寄存器，而不是主机SoC的SD控制器的寄存器。（很多外置芯片内部都是有寄存器的，这些寄存器可以按照一定的规则访问，访问这些寄存器可以得知芯片的一些信息）。
(2)RCA（relative address，相对地址寄存器）。我们在访问SD卡时，实际上SD卡内部每个存储单元的地址没有绝对数字，都是使用相对地址。相对地址由SD卡自己决定的，存放在RCA寄存器中。

1.11.7.5、SoC的SD/MMC/iNand控制器简介
(1)不同的SoC可能在SD/MMC/iNand等支持方面有差异，但是如果支持都是通过内部提供SD控制器来支持的。
(2)S5PV210的SD卡控制器在Section8.7部分


1.11.8.SD/iNand代码实战分析1
1.11.8.1、命令码CMD和ACMD
(1)SD卡工作在命令+响应的模式下。
(2)SD协议的命令分2种：CMDx和ACMDx。CMD是单命令命令，就是单独发一个CMD即可表示一个意思。ACMD是一种扩展，就是发2个CMD加起来表示一个意思。可以认为ACMDx = CMDy+CMDz（y一般是55）

1.11.8.2、卡类型识别SD or MMC？
(1)MMC协议、SD协议、eMMC协议本身是一脉相承的，所以造成了一定的兼容性，所以当我们SoC控制器工作时连接到SoC上的可能是一个MMC卡、也可能是SD卡、也可能是iNand芯片。主机SoC需要去识别这个卡到底是什么版本的卡
(2)SoC如何区分卡种类？因为不同版本的卡内部协议不同的，所以对卡识别命令的响应也是不同的。SoC通过发送一些命令、听取响应就可以根据不同的响应判定卡的版本。

1.11.8.3、卡状态
(1)SD卡内部的接口控制器类似于一个单片机，这个单片机其实是一个状态机。所以SD卡任何时候都属于某一种状态（空闲状态、准备好状态、读写状态、出错状态····都是事先定义好的），在这种状态下能够接受的命令是一定的，接受到命令之后执行一定的操作然后根据操作结果会跳转为其他状态。如果主机发过来的命令和当前状态不符状态机就不响应，如果收到命令和当前状态相符就会执行相应操作，执行完之后根据结果跳转为其他状态。

1.11.8.4、卡回复类型
(1)一般来说，SD卡的命令都属于：命令+响应的模式。也有极少数的SD卡命令是不需要回复的。
(2)卡回复有R1、R7、R1B等8种类型，每种卡回复类型都有自己的解析规则。然后卡在特定状态下响应特定命令时有可能回复哪种响应都是SD协议事先规定好的，详细细节要查阅协议文档。

1.11.9.SD/iNand代码实战分析2
1.11.9.1、linux内核风格的寄存器定义
(1)定义一个基地址，然后定义要访问的寄存器和基地址之间的偏移量，在最终访问寄存器时地址就等于基地址+偏移量。
(2)给大家提供的代码中宏定义是不完整的，很多宏定义只能从字面意思来理解对应，无法通过语法完全获得。这样写代码的好处是可以见名知意，就算代码不全都能读。

1.11.9.2、SD/iNand相关的GPIO初始化
(1)GPG0相关的GPIO初始化，参考LED部分的设置技术
(2)时钟设置参考裸机第六部分时钟那一章，设置时使用到了位操作技巧，参考C高级第二部分
(3)要求能够在两三分钟之内完全看懂这些代码涉及到的知识，要能够在数据手册、原理图中找到相对应的点，要能够瞬间明白代码中涉及到的C语言语法技巧，这样才叫融会贯通，才能够从代码中学到东西。
1.11.9.3、SD/iNand相关的时钟系统设置

1.11.9.4、SD/iNand的时钟设置
(1)SD卡本身工作需要时钟，但是自己又没有时钟发生单元，依靠主机SoC的控制器通过SD接口中的CLK线传一个时钟过来给SD卡内部使用。所以主机SD卡控制器先初始化好自己的时钟，然后将自己的时钟传给SD卡。
(2)因为此时刚开始和SD卡通信，主机不清楚SD卡属于哪个版本（高版本和低版本的SD卡的读写速率不同，高版本的可以工作在低版本的速率下，低版本的SD卡不能工作在高版本速率下），所以先给SD卡发400KHz的低速率时钟，SD卡拿到这个时钟后就能工作了。然后在后面和SD卡进行进一步通信时去识别SD卡的版本号，识别后再根据SD卡的版本进一步给它更合适的时钟。


1.11.10.SD/iNand代码实战分析3
1.11.10.1、命令发送函数解析


1.11.10.2、卡类型识别操作时序及代码分析


1.11.10.3、卡读写时序及代码分析



// 首先将sd卡同步时钟信号设置为400k，等卡识别完毕再修改为24M 或 48M
// 设置时钟一般需要：disable clock、设置时钟并等待时钟稳定、enable clock




















