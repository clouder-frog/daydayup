
第二部分、章节介绍
7.1.MP4文件格式解析1
	本节讲解MP4文件的格式，包括各个box，如ftyp、moov等。
7.2.MP4文件格式解析2
	本节接着介绍MP4格式，重点是moov box内部的细节。
7.3.MP4Info工具使用
	本节介绍MP4Info工具，该工具可以帮助我们解析一个MP4文件的box详情。
7.4.mp4v2移植和播放实战1
	本节主要是下载配置编译移植MP4V2库，这个开源库实现了对MP4文件的打包等操作。
7.5.mp4v2移植和播放实战2
	本节主要是部署和运行打包代码，测试打包生成的MP4文件。
7.6.MP4打包源码解析
	本节讲解MP4打包代码，核心是对相关API的使用。
7.7.mp4v2结合MP4Info学习分析
	本节讲解如何结合MP4Info软件和mp4v2打包代码进行分析和学习。
7.8.添加网络telnet调试
	本节讲解如何在开发板上添加telnet远程登录方式进行调试。
7.9.海思proc文件系统调试接口
	本节引入并介绍海思的proc文件系统的调试接口，这个是海思提供的很有利的调试武器。



7.1.MP4文件格式解析1
7.1.1、视频文件总体介绍
	(1) 视频文件的本质：记录压缩后的视频帧并且能被播放器还原解码播放
	(2) 视频文件的关键：高效率记录信息、兼容性(很多标准、很多box)
	(3) 视频文件的信息：索引信息、有效信息

7.1.2、MP4格式总体介绍
	(1) MP4由MP3升级而来，包含video和audio在内
	(2) MP4是h.264的最主流打包格式
	(3) MP4文件内部采用网络字节序（大端模式）

7.1.3、MP4学习路线
	(1) 学习MP4的组织形式和box解析
	(2) 移植和使用mp4v2开源库来打包MP4
	(3) 进一步研究MP4解包播放和mp4v2源码
	(4) 自己编程进行MP4的打包、解包、分割等

7.1.4、正式开始MP4的组织形式的学习

7.2.MP4文件格式解析2
	(1) 整个MP4文件由若干个各种不同的box组成，打包和解包时都是以box为单位的
	(2) MP4中有且只有一个ftyp box，该box位于整个MP4的开头位置

7.3.MP4Info工具使用

7.4.mp4v2移植和播放实战1
7.4.1、下载mp4v2
	(1) https://launchpad.net/ubuntu/+source/mp4v2/2.0.0~dfsg0-6
	(2) 解压，并在目录内创建_install目录作为安装目录

7.4.2、配置并编译
	(1) sudo PATH=$PATH:/opt/hisi-linux/x86-arm/arm-hisiv300-linux/target/bin CC=arm-hisiv300-linux-gcc CXX=arm-hisiv300-linux-gcc ./configure --host=arm-hisiv300-linux --prefix=/home/aston/sambashare/mp4v2-2.0.0/_install  --disable-option-checking --disable-debug --disable-optimize --disable-fvisibility --disable-gch --disable-largefile --disable-util --disable-dependency-tracking --disable-libtool-lock
	(2) make
	(3) make install
	(4) 检查各必要文件

7.4.3、部署
	(1) 生成的lib加到mpp lib里面
	(2) include下文件添加到mpp/include中去
	(3) lib/*so* */加到开发板lib目录下

7.4.4、编译sample
	(1) 用提供的sample替换掉原来的sample
	(2) make

7.5.mp4v2移植和播放实战2
7.5.1、准备TF卡
(1)TF卡格式化为FAT32文件系统，若失败可试试低层格式化软件如SDFormat之类
(2)开机后将TF卡进行挂载  mount -t vfat /dev/mmcblk0p1 /usr/mmc
(3)先检测下TF卡可用

7.5.2、运行和测试
(1)运行sample_venc，用rtsp测试确认有图像
(2)终止程序，取出TF卡用读卡器接电脑查看

7.6.MP4打包源码解析

7.7.mp4v2结合MP4Info学习分析
7.7.1、思路
(1)修改MP4打包源码，用MP4Info查看录制的MP4细节
(2)再深度：修改mp4v2源码中细节，再打包查看
7.7.2、实践1：去掉sps
7.7.3、实践2：去掉pps

7.8.添加网络telnet调试
7.8.1、为什么添加telnet调试
(1)linux系统的用户界面就是commandline，本质上由busybox提供
(2)busybox的命令行只有1个，一旦前台被占用就无法做其他操作
(3)解决方案有2个：一个是建立多个commandline，一个是开放其他用户界面。
7.8.2、telnet调试的原理
(1)在开发板中提前运行telnetd
(2)远程通过telnet的client连接server，构建一个用户界面
(3)这是非常传统典型的远程登录的方式···其实用过的
7.8.3、在HI3518E开发板上telnet远程登录调试实战
(1)命令行执行telnetd &，然后Windows打开CRT配置SSH至192.168.1.10开发板网口
(2)输入ssid：root，password：直接回车，进入
(3)问题：若遇到不断重启，将etc/profile 中的加载项移至/etc/init.d中的rcS文件中。这是因为因为开启telnet服务会多次加载profile
(4)可以将telnetd &加入rcS中开机默认加载


7.9.海思proc文件系统调试接口
7.9.1、proc文件系统的原理
7.9.2、海思proc文件系统调试的文档说明
7.9.3、额外提供的调试经验文档








