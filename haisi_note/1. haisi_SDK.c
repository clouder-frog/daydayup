
1.3.0��demo�����
	(5) ������Ƶ����������/mnt/sample_venc		// /home/aston/rootfs
	(6) ��vlc�������ַ���������ʵʱ����
		�˵�����ý��->�����紮��->���磬���룺rtsp://192.168.1.10:554/stream_chn0.h264
		��ѡ����ʾ����ѡ������ڻ���������Ϊ300��ԭ����1000��

1.3.1����������
	(2) ԭʼ��Ƶ��������ͷ��sensor
	(3) ͼ����ISP(image signal processing)
	(4) ��Ƶ����ѹ����h.264/h.265ѹ���㷨�����㣬����DSP����ѹ������
	(5) ��Ƶ�����䣺���紫�䡢http/rtsp��
	(6) ��Ƶ�洢�������MP4�ȸ�ʽ�洢���ȴ�����
	(7) ��Ƶ�طţ�����+����

1.4.1��HI3518EӲ����Ϣ
	(1) HI3518EV200��оƬ�ṩ��CPU+DSP+��64MB DDR+ETHERNET MAC
	(2) spi flash��sdCard��usb wifi��sensor�ӿڡ�����

	// ��Ʒ����һ��ʹ��8Mflash
	// һ��kernel���Ծ���1M��
	// 4G emmc 20+

1.6.1��2ƪ����ĵ�		// linux����������uboot��������
1.6.2��SDK�����Ƶ�linuxԭ��Ŀ¼�в���ѹ		// tar -xvf 
1.6.3��SDK�������Ľű������о� // ��Ҫ������Ŀ¼��3���ű� -- ִ�в��ɹ�ͨ��source xxx.sh
							   
// which sh
// ls -l bash
// ln -s /bin/bash /bin/sh

1.8.��ubuntu16.0403X64�ϰ�װ��˼������빤����
1.8.2����ubuntu16.0403X64��װ32λ���ݰ�
	(1) �ο���http://blog.csdn.net/ma57457/article/details/68923623
		���ߣ�https://www.cnblogs.com/leaven/p/5084902.html
	(2) ��aptitude��ʽ��װlib32z1��ʹ��sudo apt-get install lib32z1������װ���ˡ�
		ԭ����ubuntu̫���ˣ�����ܶ�ⶼ���°汾�ģ����ǻ�������°汾��lib32z1��
		û�У����Բ���װ���������������aptitude������װ����ǰ���γ̡�Ƕ��ʽlinux
		������������ĵ�6�ڵ�6.3���֡�
	(3) ����ִ��arm-xxx-gcc -v����ʾ�Ҳ���stdc++����
		./arm-hisiv300-linux-uclibcgnueabi-gcc -v
		./arm-hisiv300-linux-uclibcgnueabi-gcc: error while loading shared libraries: libstdc++.so.6: cannot open shared object file: No such file or directory
	(4) ����aptitude��ʽ��װlib32stdc++6-4.8-dbg
		sudo aptitude install lib32stdc++6-4.8-dbg
		�ٴβ���arm-xxx-gcc -v�����ڿ��������ˡ�

1.8.3���ٴβ����������osdrv
	(1) ��Ȼ��ʾ�Ҳ���arm-hisiv300-linux-gcc
	(2) �޸�Makefile��OSDRV_CROSS��·����������У�����ԭ���ǣ������д��θ�����
	(3) export�����������������ο�����γ�1.4�ڣ���ʽΪ��
		export PATH=/home/aston/sambashare/Hi3518E_SDK_V1.0.3.0/osdrv/arm-hisiv300-linux/bin:$PATH

		// vi ~/.bashrc
		// export ...
		// source ~/.bashrc

		ֱ�Ӳ��Կ���ִ���ˣ����Ǳ��뻹�ǳ�������ԭ�����ֲ���
	(4) ���������2����һ�����޸�makeʱ���ε����֣�
		��һ���Ǹ���װ�õĽ�����빤���������������ӡ�
		ʵ�ʳ��Ժ��ֵ�һ��MakefileҪ�ĵ�̫�࣬�����ߵ�2�֡�

1.8.4��ʹ��install�ű���װ������빤����
	(1) install��/optĿ¼�²�������������
	(2) ������PATH�����Կ���ִ��
	(3) �ٴα���

1.9.����osdrv
1.9.1��������Ժͷ����о�
	(1)������룬�������������⡣
		// /uboot/tools/mkimage

	(2)���ֱ��룬��Ҫ�Ĳ��ֵ��������Ĳ��֡�
1.9.2������uboot
1.9.3������kernel

1.10.1��ȱzlib����
	����compr_zlib.c:39:18: fatal error: zlib.h: No such file or directory
	��Ϊ�Ҳ���zlib.h���Ա������
	zlib.h��tools/pc/zlib/tmp/includeĿ¼���У�
	ֻ��Ҫ���Ƶ�tools/pc/jffs2_tool/tmp/includeĿ¼�м��ɡ�ע��ͬʱҪ��
	zconf.hҲ���ƹ�ȥ�ġ����У�Ҫ��tools/pc/jffs2_tool/tmp/libĿ¼��
	��libz.a  libz.so  libz.so.1  libz.so.1.2.7��4���ļ����Ƶ�
	tools/pc/jffs2_tool/tmp/libĿ¼�£���Ȼһ������ñ���

1.10.2����������
	������Ͳ����ˣ���ʱ�Ѿ�����mkfs.jffs2�ˣ����Ǿ���ֻҪ������ѣ��ֹ�
	���临�Ƶ�osdrv/pub/bin/pcĿ¼�¼��ɡ�

1.10.2������
	������Ϣ��serve_image.c:32:18: error: storage size of ��hints�� isn��t known
	����������ο���http://blog.csdn.net/mtbiao/article/details/77052659

1.10.3����32λubuntu�б���ʱ��һ������
	�������/usr/bin/ld: i386:x86-64 architecture of input 
	file `mkyaffs2image.o' is incompatible with i386 output
	�������Ϊsdk�б���������64λϵͳ�±����.o�ļ����������õ���32λ��
	ubuntu������취�ǽ���tools/pc/mkyaffs2image/mkyaffs2imageĿ¼�£�
	rm *.o������make clean��ɾ������֮ǰ����ĺۼ����ɡ�ʵ�������ǰ�����
	�õ���spi flash��������jffs2�ļ�ϵͳ�����Բ�����yaffs2�ļ�ϵͳ��
	�������Ҫ��Ҫ������ν�ġ�

1.10.4���ֹ���������rootfs
	(1) mkfs.jffs2 -d rootfs_uclibc -l -e 0x10000 -o rootfs_uclibc_64k.jffs2

1.12.1�������¼uboot
	(1) ��λ��HiTool + isp

1.12.2��flash����	// �ֶ�ָ������
	(1) bootloader	// 0x00000000 - 0x00100000 1M
	(2) kernel		// 0x00100000 - 0x00400000 3M
	(3) rootfs		// 0x00400000 - 0x01000000 12M

1.16.1��mpp���ļ��ṹ���
	(1) ko			// cp ko / -r
	(2) lib			// cp lib/* /usr/lib/		-- /lib ϵͳ��
	(3) sample
	(4) ��������

1.16.2�������������Զ���������
	(1) ��profile�������������IP��ַ
	(2) ��profile������Զ���������nfs������
		mount -t nfs -o nolock 192.168.1.141:/home/aston/rootfs /mnt

		/home/aston/rootfs	// sudo showmount -e

1.16.3������ko�ļ�	// mpp/ko/xxx.sh
	./load3518e -i -sensor ar0130 -osmem 32 -total 64

	// insert_moudle()
	// insmod xxx
	
	// himm 0x2000f007C 0x1;		himm�����ʼ��sensor

1.16.4������lib�ļ�

1.18.sample�ı���Ͳ���		// sample/venc/		¼����
1.18.1��sample�ı���
	(1) sample�ṹ�����		// *.ko *.so *.a��Ҫ����roofs; *.h����ʱ��
	(2) Makefile�о�			// mpp/sample/Makefile.param	-- ����chip_id sensor_type
	(3) ����õ�sample_venc

1.18.2��sample�Ĳ���Ͳ���
	(1) nfs��ʽ����sample			// ������board��ֱ������ -- flash��С
	(2) �õ�¼���ļ�xx.h264
	(3) ����xx.h264��windows����vlc������������֤

1.18.3��������������
	(1) �ڱ���Ŀ¼��osdev/pub/���ҵ�rootfs_uclibc.tgz����ѹ��
	(2) �����Ͻںͱ�����֤�ɹ��Ĳ����貿������rootfs
	(3) �ֹ�����rootfs.jffs2��������¼���Լ���
		osdrv/pub/bin/pc/mkfs.jffs2 -d osdrv/pub/rootfs_uclibc -l -e 0x10000 -o osdrv/pub/rootfs_uclibc_64k.jffs2

	SDRAM		// 80000000 - 83FFFFFF 		64M
	linux		// 80000000 - 81FFFFFF		32M
	MMZ			// 82000000 - 83FFFFFF		32M

// ---------------------------------------------------------
tftp���²�������дkernel���������У�
mw.b 0x82000000 ff 0x300000
tftp 0x82000000 uImage_hi3518ev200
sf probe 0
sf erase 0x100000 0x300000
sf write 0x82000000 0x100000 0x300000
---------------------------------------------------
tftp���²�������дrootfs���������У�
mw.b 0x82000000 ff 0xc00000
tftp 0x82000000 rootfs_uclibc_64k.jffs2
sf probe 0
sf erase 0x400000 0xc00000
sf write 0x82000000 0x400000 0xc00000

set bootcmd 'sf probe 0;sf read 0x82000000 0x100000 0x300000;bootm 0x82000000'
set bootargs mem=32M console=ttyAMA0,115200 root=/dev/mtdblock2 rootfstype=jffs2 mtdparts=hi_sfc:1024K(boot),3072K(kernel),12288K(rootfs)
// cat /proc/cmdline

root=/dev/mtdblock2 	// block0 - uboot, block1 - kernel, block2 - root


