
2.20.1.2�� linux+QT bsp	
	(1) uboot��xboot		// bootloader
	(2) kernel
	(3) buildroot			// rootfs
	(4) tool
	(5) mk					// mk�ű�����������ͱ�������bsp

2.20.1.3��mk�İ�����Ϣ		// mk -h, mk --help

2.20.2.mk�ļ�����

2.20.3.1��buildroot���ý���
	(2) ������빤����arm-linux-gcc������Ŀǰ���Ǵ�soc�ٷ�ֱ������ʹ�õģ��ٷ��Ĺ������Ӻζ�����
		ʵ���Ͻ�����빤����������gcc���ñ������ɵģ�������ñ�����̱Ƚϸ��ӣ�
	(3) buildroot����һ�����ɰ���������Ｏ���˽�����빤�������������Լ�����rootfs�����ñ�����̡�
		Ҳ����˵��ʹ��buildroot���Ժܼ��ĵõ�һ�����õ��ļ�����ʽ�ĸ��ļ�ϵͳ��
	(4) buildroot���ܶණ�����ɽ�������ֲ��linux kernel��make xxx_defconfig+make menuconfig��2�����÷�

2.20.3.2��make x210ii_defconfig
	(1) ��make xxx_defconfig
	(2) make menuconfig
	(3) make				// buildroot/output/images/rootfs.tar



