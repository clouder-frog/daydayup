
	// ������ϵͳ����̨ -- �����նˡ�SecureCRT��minicom

1.3.4.0���ƻ�iNand�е�bootloader
	step1: busybox dd if=/dev/zero of=/dev/block/mmcblk0 bs=512 seek=1 count=1 conv=sync
	step2: sync
	// ʹ��linux dd �����д����
	// if: input file 	/dev/zero				// �����豸 ��Ӧȫ0    --  ��0д�뵽inand��
	// of: output file  /dev/block/mmcblk0 		// ����豸��Ӧinand
	// bs: block size ������С512�ֽ�
	// seek: ��һ������(��ʼ)					// bootloader������1��ʼ
	// count: ��������

	// first bootУ��Ͳ�ͨ����ӡ: SD checksum Error, ������ִ��second boot

1.3.4.1����������SD������ʵ������¼uboot��SD���У� // windows tool or linux dd

1.3.4.2��fastboot����
	fastboot��uboot������/*�������ؾ���*/��һ������, fastbootͬʱ����һ��windows�ϵ����
	//fastbootͨ��USB����, fastboot��װ����

1.3.4.3��fastboot����	//X210 Android����
	����λ�ã�A��\tools\USB����\x210_android_driver //�����Զ���װ

1.3.4.4��fastboot��������
	(1)������uboot�����ն���ִ��"fastboot"����(windows�豸����������adb device)
	(2)��windows cmd��ִ��fastbootӦ�ó���, ִ����������	// ��: fastboot devices

1.3.4.5��ʹ��fastboot��¼android4.0.4����
	��cmd��ʹ���������������������¼
	fastboot flash bootloader android4.0/uboot.bin		//uboot
	fastboot flash kernel android4.0/zImage-android		//linux kernel
	fastboot flash system android4.0/x210.img			//android rom

	uboot�Ĳ�������: set bootcmd 'movi read kernel 30008000; bootm 30008000'  // default param
	ˢlinux+QT�����, uboot�Ĳ��������޸�(ˢ����linux+QT���Ƶ�uboot, Ĭ�ϲ���Ӧ����Ӧ�޸�)

	// fastboot flash��inand��, û�����ص�SD���� -- write readд��channel0

1.3.9.3��x210��dnwˢ��
	step1: ˢx210_usb.bin, ��ַ0xd0020010
	step2: ˢuboot.bin,    ��ַ0x23e00000
	uboot����������, ��fdisk -c 0 ���·���, ��fastboot		// fdisk -c 0

1.3.10.linux��ʹ��dd����ˢдuboot

1.3.10.1��SD��������linux��
	���ӽ�linux�У����������У�ls /dev/sd*�鿴, һ����/dev/sdb
	ִ�� ./nand_fusing.sh /dev/sdb

1.3.10.3��ʹ��SD������
	��ȷ���������Ǵ�SD��������
	Ȼ��ȷ�������ڵ�iNand�е�uboot�Ǳ��ƻ��ģ�����������
	SD������SD2ͨ�����������ɡ�������(����û��Ҫfdisk -c 0������)ʹ��fastboot����ˢ��

======================================================================================
1.3.11.2��ˢ���������⼰��������
(8)Windows����ʾ��װ����������������о�������uboot����linux+QT����ʱ�����USB������WindowsҲ���ᷢ�ֿ����壻
	������uboot��ִ����fastboot����������ͻ���ʾװfastboot��������������������androidϵͳ�������ͻ���ʾװfastboot������
	��������������USB������������ʱ�ͻ���ʾװdnw������

1.3.12.����-linux��dnw�����ʹ��
1.3.12.1��linux��dnw��ȡ
(1)Դ�����ȡ
(2)����Ͱ�װ

1.3.12.2�����������ӵ�linux��
	(1)����������USB������������windows�豸����������ʾ������Ӳ��
	(2)VMware�˵��������->���ƶ��豸->Samsung S5PC110 SEC Test B/D���������
	(3)�ɹ����Ӻ�����1��Windows���豸������û�ˣ�2��ls /dev/secbulk0 �豸�ڵ��Զ�����

1.3.12.3��ʹ��dnw��������uboot.bin
	(1)dnw -a 0xd0020010 x210_usb.bin 
	(2)dnw -a 0x23e00000 uboot.bin
	�ɹ���־��SecureCRT�гɹ�������uboot��������Ϣ�����ҽ�����uboot�����С�

1.3.12.4��uboot�������ˢ��ע������
	(1)��ȷ��uboot������һ��Ҫ��fdisk -c 0���з�����Ȼ����fastboot
	(2)uboot�Ĳ�����bootcmd��bootargsһ��Ҫ��ȷ��
	set bootcmd 'movi read kernel 30008000; bootm 30008000'
	set bootargs console=ttySAC2,115200 root=/dev/mmcblk0p2 rw init=/linuxrc rootfstype=ext3











