��2.uboot��ϵͳ��ֲ-��17����-
				2.17.�ں˵���ֲ1-�����ǹٷ��ں˿�ʼ��ֲ��

--------------------------------------------------------
			��ӭ���ʡ�����ʦ���������á��ٷ���վ
					www.zhulaoshi.org
				   �Ի�ȡ���γ̸�����Ϣ
--------------------------------------------------------
��һ���֡��½�Ŀ¼
2.17.1.�ں���ֲ������
2.17.2.������ֲ�Կ���������Ϣ
2.17.3.�ں��л������ȷ��
2.17.4.����ں������еĴ���
2.17.5.iNand������Ͱ���
2.17.6.������������ֲ������ʵ��
2.17.7.�ں�������һ�׶εĵ��Է���


�ڶ����֡��½ڽ���
2.17.1.�ں���ֲ������
	����Ϊ�ں���ֲ�ĵ�һ�ڣ�����ѡ���ô���ֲ��Դ�룬Ȼ�󹹽���ֲ���������ҽ��л������޸ĺ����ñ��룬�ٸ���ʵ��������к�������
2.17.2.������ֲ�Կ���������Ϣ	
	���ڿθ����Ͻڵ�ʵ�������������Ⲣ�ҳ��Խ�����⣬���մﵽ���ں�������Ϣ���Դ�ӡ������
2.17.3.�ں��л������ȷ��
	���ڽ����ں��и�mach-xx�Ļ����������ȷ���ģ���˷����ҵ����ǵ�ƽ̨��Ӧ��Ӳ����ʼ�������λ�á�
2.17.4.����ں������еĴ���
	���ڿ������ں˴���OOPS��Ȼ�������δ��ں�oops��Ϣ���ҵ����������������ҽ�������е����⡣
2.17.5.iNand������Ͱ���
	���ڷ���iNand������Ͳ��ܹ���rootfs��ԭ����Ϊʱ���ϵ���������ʱû�ܴ�����Ҫ�ȵ������������ֿ�ʼʱ��ȥ���ϡ�
2.17.6.������������ֲ������ʵ��
	���ڿν���������������ֲ����ҪĿ����ͨ����ֲ�ô�ҳ�����ʶ��linux�е�������ܡ�����������������˼�룬�ں�������uboot����������ͬ��Ͳ�ͬ��ȡ�
2.17.7.�ں�������һ�׶εĵ��Է���	
	���ڲ��佲һ���ں˵�һЩ�����ַ�����ҪĿ����Ϊ��������µ��Լ��ɣ�����ѧϰ����������
	


�������֡����ü�¼
2.17.1.�ں���ֲ������
2.17.1.1�����ǹٷ���ֲ���ں˻�ȡ
(1)����������Դ�����
(2)����ļ���������������ǵ�SMDKV210�����帽���Ĺ�������
2.17.1.2��������ֲ����
(1)Windows�½���SI����
(2)ubuntu�½�ѹ

2.17.1.3�����ñ������س���
(1)���Makefile��ARCH��CROSS_COMPILE
(2)make xx_defconfig
(3)make menuconfig
(4)make -j4
Ĭ�������ֱ��make���ֱ�ӵ��̱߳��롣�������make -j4���4�̱߳��롣

2.17.1.4������Ҫ�������飺
(1)����õ���zImageȥ�������У������
(2)���ݽ��ȥ��������ԭ��Ȼ��ȥ���Խ����Щ���⡣


2.17.2.������ֲ�Կ���������Ϣ
2.17.2.1����������
(1)�������н�����������֣�linux�ں˵��Խ�ѹ���붼û�����У���Ϊû�п�����Uncompressing Linux... done, booting the kernel.��
(2)˵��zImage����û�б���ѹ�ɹ����ں˴��������û�б����У���Ȼû�������Ϣ�ˡ�����������ڽ�ѹ��صĲ��֡�
(3)��������ں����õĽ�ѹ�������õ��ڴ��ַ����
(4)�ں����õĽ�ѹ��ַӦ�õ������ӵ�ַ�������Խ�ѹ֮���ں��޷����С����������ɣ���һ���ں˵����ӵ�ַ���ڶ��٣��ڶ����ں������õĽ�ѹ��ַ�Ƕ��٣�
(5)�����滹�и����⣺�ں˵����ӵ�ַ��һ�������ַ�����Խ�ѹ�����ѹ�ں�ʱ��Ҫ������ַ���������˵�ĵ��ڣ���ʵ�����ӵ�ַ��Ӧ��������ַ�����Խ�ѹ��ַ��
(6)���ӵ�ַ������Ӧ��������ַ��head.S�п��Բ鵽���ֱ���0xC0008000��0x30008000����ô�Խ�ѹ�������õĽ�ѹ��ַӦ����30008000.
(7)�Խ�ѹ�����Ӧ���Խ�ѹ��ַ��mach/Makefile.boot�ļ��С��������޸ģ��������У�
# override for SMDKV210
zreladdr-$(CONFIG_MACH_SMDKV210)	:= 0x30008000
params_phys-$(CONFIG_MACH_SMDKV210)	:= 0x30000100
(8)ͬ�����룬���ұ��룬�õ���zImage���Ƶ�/tftpboot��Ȼ�������������в鿴�����
(9)������ǣ�����û���У�������Ч�����Խ�ѹ�����ѹ��ӡ��Ϣ�Ѿ������ˡ������ں˻�û����

2.17.2.2���������
(1)�����������ַ���ԣ���20000000�ĵ�30000000����


2.17.3.�ں��л������ȷ��
2.17.3.1��MACHINE_START��
(1)�������������һ������������ݽṹ�ġ�������ʹ����ʵ����������һ���ṹ������Ϊmachine_desc���͵Ľṹ���������Ϊ__mach_desc_SMDKV210������ṹ������ᱻ���嵽һ���ض���.arch.info.init���������ṹ����������ᱻ���������ӵ����.arch.info.init���С�

static const struct machine_desc __mach_desc_SMDKV210	\
 __used							\
 __attribute__((__section__(".arch.info.init"))) = {	\
	.nr		= MACH_TYPE_SMDKV210,		\
	.name		= "SMDKV210",
	.phys_io	= S3C_PA_UART & 0xfff00000,
	.io_pg_offst	= (((u32)S3C_VA_UART) >> 18) & 0xfffc,
	.boot_params	= S5P_PA_SDRAM + 0x100,
	.init_irq	= s5pv210_init_irq,
	.map_io		= smdkv210_map_io,
	.init_machine	= smdkv210_machine_init,
	.timer		= &s5p_systimer,
};
(2)��������������һ��mach-xxx.c�ļ��ж�����һ��������Ŀ������machine_desc�ṹ�����������ṹ������ŵ�.arch.info.init���к���ô�ͱ�ʾ��ǰ�ں˿���֧�����������Ŀ����塣
(3)��ʵ����ǰ������͵�ǰ�ں�������������ǰ������ֲ��Ŀ�꿪����ʹ��S5PV210��CPU�����������ֽ�X210.���������ǹٷ��汾���ں������Ҳ���mach-x210.c�ģ����������ֲ�����㿪ʼȥ��ֲ��������ǵ�˼·����������ֲ��mach-s5pv210Ŀ¼����һ��mach-xx.c���������������ǵ�X210��������Ϊ�ӽ���Ȼ���Դ�Ϊ��������ֲ��
(4)�����鿴������mach-s5pc110.c��mach-s5pv210.c�����ǵ�X210��������Ϊ�ӽ�������һ��ȷ����һ��ԭ���ǣ������ǵĿ���������ǹٷ����ĸ���������Ϊ���ơ����ǵ�X210�����峭�������ǵ�SMDKV210�����Ҫ�������Ӧ���Ǹ��ļ���
(5)���mach-s5pv210Ŀ¼�µ�Makefile����������֪.config�ж�����CONFIG_MACH_SMDKV210��ʵ�ʰ󶨵���mach-smdkc110.c����ļ�������ʵ����mach-smdkv210.c����ļ�����û�õ�����ʾ���ǲ�Ҫ�⿴���֡�

2.17.3.2��Ӳ�������ļ��غͳ�ʼ������ִ��
(1).init_machine	= smdkc110_machine_init,
(2)���Ԫ�ض�����һ������Ӳ����ʼ����������������ǳ���Ҫ����������а����������������linux�ں����������л��ʼ���ĸ���Ӳ������Ϣ��


2.17.4.����ں������еĴ���
2.17.4.1����ʶ�ں�����OOPS
(1)�ں���������д�ӡ��Ϣ����ӡ��Ϣ���������������ڡ������ȥ���������ӡ��Ϣ�������ҵ��ԵĻ��ߴ����һЩ��ϢƬ�Σ����ܰ��������ҵ����⣬�Ӷ�������⡣
(2)�ں������еĴ�����Ϣ��һЩ������
Unable to handle kernel NULL pointer dereference at virtual address 00000060
Internal error: Oops: 5 [#1] PREEMPT
PC is at dev_driver_string+0xc/0x44
LR is at max8698_pmic_probe+0x150/0x32c
(3)�����ϴ�����Ϣ�е�PC��LR��ֵ���Կ�����������ִ�е�dev_driver_string����max8698_pmic_probe���������Ǻ������߻���еı�ţ����Ų��ֵ�ʱ������ˡ����Ǿʹ����������ų���ȥѰ�ҡ�˼�����ܳ����ĵط�Ȼ����ͼȥ�����

2.17.4.2������׷�ݼ�������
(1)max8698_pmic_probe��������max8698�����Դ����IC��������װ�������ֳ����ˣ�Ӧ�������ǵĿ�����ϵͳ��������֧�������Դ����IC�����Ǻ�����ʱȥ����������������������ڼ���ִ�еĹ����г�����OOPS�ˡ�
(2)����ΪʲôҪ����֧����������������������ΪʲôҪ������
(3)�������X210�������Ӳ��ʵ�����������������X210�������ϸ�����û��max8698�����Դ����IC����ȻӲ����û������ִ���˿϶��������
(4)���䵱ʱ�����ǰ汾��uboot��ֲ��ʱ����uboot��lowlevel_init.S��Ҳ�е��ø���Դ����IC��ʼ��������PMIC_init������������İ취�������ε�����������ĵ��ã�uboot�ͳɹ�������ȥ�ˡ�
(5)Ϊʲô���ǵ�uboot���ں���Ĭ�϶������������Դ����IC�ĳ�ʼ�����룿ԭ��������ǵ�SMDKV210��������������max8698�����Դ����IC�ģ��������ǵ�uboot��kernel�ж���Ĭ��֧�����������X210����û�õģ���˶���Ҫȥ����
(6)��ô�������uboot����ֱ�Ӹ�Դ�������ε��Ǹ���ʼ����������ģ����ں��в�����ô�ɣ���Ϊlinux kernel�Ǹ߶�ģ�黯�߶ȿ����õģ��ں���ÿһ��ģ�鶼�Ǳ����������������˵ģ����Ҫȥ��ĳ��ģ���֧�֣�ֻ��Ҫ��������ȥ��ѡ��ɣ����ø�Դ���롣�������ǵĹؼ�����Ҫ������Ӧ�������
(7)����������make menuconfig��Ȼ��/����"MAX8698"�⼸���ؼ��֣�Ȼ�󿴵�����������·����Ȼ��·����ȥ��N��ȥ�����ģ���֧�֣����棬���±��뼴�ɡ�
(8)ʵ��֤�����ⱻ����ˣ������ں��ٴ�������ֱ�����е�����rootfs�ų�����

2.17.4.3���������ܽ�
(1)���������⾿������ô������ģ��漰�ļ�������
����ԭ������CONFIG_MFD_MAX8698������úꡣ������ú�����˺ܶණ��
��һ��������ú������driversĿ¼�µ�max8698��Ӧ����������Դ�����Ƿ񱻱���
�ڶ���������ú������kernel�����������Ƿ�����һЩmax8698����صĴ���

(2)�ܽ᣺kernel�Ǹ߶�ģ�黯�Ϳ����û��ģ��������ں������κ����飨����һ��ģ�顢����һ��ģ�顢ȥ��һ��ģ�飩�����밴���ں��趨�ķ������������ߡ�


2.17.5.iNand������Ͱ���
2.17.5.1���������
(1)�õ����ں˴�����Ϣ��Kernel panic - not syncing: VFS: Unable to mount root fs on unknown-block(0,0)���Ӵ�����Ϣ������˼�������������ں���ͼ���ظ��ļ�ϵͳʱʧ�ܣ�ʧ�ܵ�ԭ����unknown-block������ʶ��Ŀ��豸��
(2)backstrace���������Ե�֪������Ϣ����Դ���ٽ��֮ǰ���ں��������̷������͸���ȷ���˳����ĵط���
(3)��һ�����⣺�������������ֵ�ԭ��unknown-block(0,0)����kernel����ʱuboot�ᴫ���ں�һ��cmdline��������root=xx��ָ����rootfs���ĸ��豸�ϣ��ں˾ͻᵽ��Ӧ�ĵط�ȥ����rootfs��Ʃ�����Ǵ����У�root=/dev/mmcblk0p2�������/dev/mmcblk0p2����rootfs���豸��ַ������豸�ļ���ŵĺ������mmc�豸0�ĵ�2���������豸0������SD0ͨ���ϵ��豸��Ҳ����iNand����������������û�ҵ�mmc�豸0�ĵ�2������
(4)��һ�����⣺Ϊʲôû�ҵ�mmc�豸0�ĵ�2������һ������Ϊkernel���������м���mmc������ʱ�������⣬����û�з���mmc�豸0.���ⶨλ��MMC��ص��������档
(5)�ԱȾŶ��汾���ں�������Ϣ�����ɷ������ǵ��ں�������û���ҵ�MMC�豸�����õ�iNand�����õ�SD����û�ҵ�����û�ҵ��϶������������⣬���Ҫȥ��ֲMMC�����ˡ�

2.17.5.2���������
(1)SD/iNand����������һ��һ����������ɵģ���������н�����210������ʱ��BL1��SD����1������ʼ�����ţ�SD����0�����ǲ��õġ�SD����0��������������MBR�ġ�
(2)MBR���������������豸�ķ�����Ϣ�ģ����ȶ�����һ��ͨ�õ����ݽṹ���������豸�ķ���������ֻҪ���������׼��������Ϣд��MBR�м��ɶԸ��豸��ɷ�����MBRĬ�Ͼ����ڿ��豸�ĵ�0�������ϴ�ŵġ�
(3)�����ں��ж���iNand��4��������������������ģ�uboot����һ������fdisk -c 0ʱ�Ͷ�iNand�����˷�����uboot��fdisk�����ڲ��Ѿ�д����iNand�ķ����������ں���ʱ�ں�ֱ�Ӷ�ȡMBR��֪���˷�����������uboot���ں�֮��iNand�豸�ķ�����Ϣ�ǿ�iNand�Լ����ݵģ�����uboot���ø��ں˴���ʱ���ݷ�������Ϣ��
(4)����������õ���nandFlash�Ļ���������һ�������ں����Լ��ô��빹���ġ�����nand�汾���ں���ֲ��ʱ��һ�㶼��Ҫȥ��ֲ����nand��������

2.17.5.3���������
(1)��ʱ�������������⡣

2.17.5.4�������γ̰���
(1)һ�ڿθ㶨������������ֲ��һ�ڿν���һЩ�ں���ֲ��С�����ͼ��ɣ�Ȼ��γ̽���
(2)������ֲ�Ŀγ̽�����������ļ�ϵͳ���֡�



2.17.6.������������ֲ������ʵ��
2.17.6.1����ֲ��׼
(1)����������ֲokʱ��������ϢΪ��
[    1.452008] dm9000 Ethernet Driver, V1.31
[    1.455870] eth0: dm9000c at e08f4300,e08f8304 IRQ 42 MAC: 00:09:c0:ff:ec:48 (platform data)
(2)��ǰ�ں�������������δ��ֲ������ں�����ʱ�д���Ĵ�ӡ��Ϣ��
[    1.130308] dm9000 Ethernet Driver, V1.31
[    1.133113] ERROR : resetting 
[    1.135700] dm9000 dm9000.0: read wrong id 0x2b2a2928
[    1.140915] dm9000 dm9000.0: read wrong id 0x2b2a2928
[    1.145941] dm9000 dm9000.0: read wrong id 0x2b2a2928
[    1.150963] dm9000 dm9000.0: read wrong id 0x2b2a2928
[    1.155992] dm9000 dm9000.0: read wrong id 0x2b2a2928
[    1.161018] dm9000 dm9000.0: read wrong id 0x2b2a2928
[    1.166041] dm9000 dm9000.0: read wrong id 0x2b2a2928
[    1.171070] dm9000 dm9000.0: read wrong id 0x2b2a2928
[    1.176092] dm9000 dm9000.0: wrong id: 0x2b2a2928
[    1.180774] dm9000 dm9000.0: not found (-19).
(3)��ֲ��Ŀ����������ǵİ汾���ں˿��Դ�ӡ����ȷ����µ�������Ϣ�������Ǿ������ں������������ǿ��Թ����ġ�

2.17.6.2��make menuconfig������DM9000֧��
(1)menuconfig��ѡ��Y
(2)��ʵ��һ����������Y�����������������ǲ��ùܵġ��������Լ�������һ���ں˿���Ĭ�ϲ���Y�����Ҫ���á�

2.17.6.3��mach-smdkc110.c���߼�����
(1)mach-smdkc110.c�е�smdkc110_machine_init�����������������Ӳ���ĳ�ʼ������������������˵�Ӳ����������ʱ�ͻᱻ��ʼ����������û�еĽ�������ʱ�Ͳ��ܡ�
(2)smdkc110_devices��smdkc110_dm9000_set()�������ط��Ǻ�DM9000�йصģ�Ҫ�ֱ�ȥ����ֲ��
(3)smdkc110_dm9000_set�����������DM9000��ص�SROM bank�ļĴ������ã��൱��uboot��dm9000��ֲʱ��dm9000_pre_init������ֻ�Ƕ�д�Ĵ����ĺ������Ʋ�ͬ�ˡ�

2.17.6.4���޸���Ӧ�����ò���
(1)DM9000��ص�����������arch/arm/plat-s5p/devs.c�и���
(2)��arch/arm/mach-s5pv210/include/mach/map.h�ж�����DM9000��IO����ַ����DM9000�����ĸ�bank�йء�
(3)����+2�ĳ�+4��IRQ_EINT9�ĳ�10���ɡ�

2.17.6.5������ʵ��
(1)ͬ�����롢��������zImage
(2)����������������Ϣ��


2.17.7.�ں�������һ�׶εĵ��Է���
2.17.7.1�����������
(1)�ں�������head.S�����Ƚ���������У�飨CPU id��У�顢�������У�顢tag��У�飩��Ȼ�󴴽�ҳ����Ȼ������һЩ��̫����������飬Ȼ��b start_kernel�������������е�start_kernel�ں���ֲ�Ͳ�̫��������ˡ�
(2)��ʱ����ֲ���ں�������������ǣ�����û��������Ϣ��������ʱ���п������ں����������˵������г�����û������������û�д�ӡ��Ϣ��Ҳ�п������ں˸���û�������С����п��ܵ���û��ȷ��������ϣ������һ�ֵ����ֶ���ȷ���������ڡ�

2.17.7.2�����Է�����ԭ��
(1)���Է����������ں������ĵ�һ�׶����ӻ�����led����/Ϩ��ķ����������������еĹ켣��
(2)������֮ǰ����л�����led����/Ϩ��Ĵ������������ճ����head.S�к���λ�á�Ȼ���ں����������led�ı��������������������С�

2.17.7.3�����ֲ���
(1)������led�����Ĵ���Σ���head.S�к��ʵĵط�����led���������Ȼ����head.S���ں���ʼ���н׶����ӵ���led������Ȼ�����±����ںˣ������ں˿���δ������ޱ����С�
(2)����������ˣ�֤�����������led�Ĳ���֮ǰ�Ĳ��ֶ���û����ģ���ô����д��϶������ں�ߣ����û�б�������֤��������֮ǰ����ô��Ҫȥ֮ǰ�Ĳ���debug��

2.17.7.4��ʵ����֤

































