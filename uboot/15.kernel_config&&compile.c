
2.15.1.2������Դ��Ŀ¼�µĵ����ļ�
	// Kbuild(kernel build)��Kconfig
	// Makefile��mk

2.15.2.linux�ں�Դ��Ŀ¼�ṹ2
	(10)ipc	inter process communication, ���̼�ͨ��, linux֧�ֵ�IPC�Ĵ���ʵ��

	(12)lib	��ͬ��C���Եı�׼�⺯��
			�ں˱���в���ʹ��C���Ա�׼�⺯��, lib�µĿ⺯���������C��׼�⺯��
			�ں˱����Ҫ���ַ���ת������ֻ����libĿ¼�µ�atoi����, �����ñ�׼C���е�atoi
			�ں˱����Ҫ��ӡʹ��libĿ¼�µ�printk, �����ñ�׼C���е�printf

	// important: arch��drivers

2.15.3.1����ȷ��Makefile
	// ARCH=arm
	// CROSS_COMPILE = /usr/local/arm/arm-2009q3/bin/arm-none-linux-gnueabi-

2.15.3.1�����ñ���
	step1: make x210ii_qt_defconfig		// cp arch/arm/configs/x210ii_qt_defconfig .config

	step2: make menuconfig		// apt-get install libncurses5-dev -- ��װncurse��

	step3: make		// arch/arm/boot/zImage

2.15.4.2�����õĹؼ��ǵõ�.config�ļ�	// -- ������x210_sd.h
	// ��ȡ.config��������, ָ�������������ӹ���

2.15.5.menuconfig��ʹ�ú���ʾ
	ģ�黯: �������ӳ�һ���ں�ģ��.ko�ļ�(����ں˻��߱��ģ��), linuxϵͳ�ں���������Զ�̬�ļ��ػ�ж�����ģ��

2.15.6.1��menuconfig������һ�����֧��
	// scripts/kconfig/lxdialog -- menuconfigԴ��

2.15.7.1��Kconfig�ĸ�ʽ
(2)	������ֲ�ȹ���ʱ, ��Ҫ�޸�Kconfig�е�������, ��ĳ���豸������ӵ��ں˵�������Ŀ��
(7)	�ں�Դ��Ŀ¼����ÿһ��Kconfig����/*source������������Ŀ¼�µ�Kconfig*/, �Ӷ����е�Kconfig��Ŀ����������menuconfig

2.15.7.2��tristate��bool�ĺ���
(1)	tristate��̬(Y��N��M)
	bool(Y��N)

	// ע��Kconfig�ļ��е�depends
	// menuconfig�еĲ˵��Kconfig�е������.config�е�һ�С�Makefile�е�һ��


