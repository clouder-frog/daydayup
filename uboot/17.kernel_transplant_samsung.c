2.17.1.3�����ñ������س���
(1) Makefile: ARCH, CROSS_COMPILE
(2) make xx_defconfig				// arch/arm/configs/...
(3) make menuconfig
(4) make -j4

2.17.2.1����������
(1) ����δ����Uncompressing Linux... done, booting the kernel.	// Linux�Խ�ѹ����û��ִ��
	�޸ģ�arch/arm/mach-s5pv210/mach/Makefile.boot		// link addr

(2) ����kernel�޴�ӡ��Ϣ
	�޸ģ�link addr

2.17.3.�ں��л������ȷ��
// mach-smdkc110.c --  line1245

2.17.3.2��Ӳ�������ļ��غͳ�ʼ������ִ��
(1).init_machine	= smdkc110_machine_init		// not smdkv210_machine_init when define CONFIG_MACH_SMDKV210

2.17.4.1����ʶ�ں�����OOPS
(1) ��Դ����IC
// CONFIG_MFD_MAX8698: 	����driversĿ¼�µ�max8698��Ӧ����������Դ�����Ƿ񱻱���		\
						����kernel�����������Ƿ�����һЩmax8698����صĴ���
(2) ����rootfs
	// SD/iNand��������һ��һ�����������
	// x210������ʱ��BL1��SD����1������ʼ��SD����0����Ĭ�ϱ���(MBR: �������豸�ķ�����Ϣ)  -- ��������Ϣ����Ҫ�趨
	// fdisk -c 0

	// nand������һ�������ں����ô��빹��

(3) ��������
	�� make menuconfig���DM9000֧��
	�� mach-smdkc100.c -- smdkc110_machine_init		//�������������е�Ӳ����ʼ��
	�� ��ֲsmdkc110_devices��smdkc110_dm9000_set()

2.17.6.4���޸���Ӧ�����ò���
	(1)DM9000��ص�����������arch/arm/plat-s5p/devs.c�и���
	(2)��arch/arm/mach-s5pv210/include/mach/map.h�ж�����DM9000��IO����ַ����DM9000�����ĸ�bank�йء�
	(3)����+2�ĳ�+4��IRQ_EINT9�ĳ�10���ɡ�
