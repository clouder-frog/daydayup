
	/*
		./Makefile
		./arch/arm/configs/x210ii_qt_defconfig
		./.config
		
		arch/arm/kernel/vmlinux.lds.S
		
		arch/arm/kernel/head.S
		arch/arm/kernel/head_common.S
		./init/main.c
		
		include/kernel/		-- �ں˻���ͷ�ļ�
		include/net/		-- �����������ܲ���ͷ�ļ�
		include/asm/		-- include/asm-xxx/������
		
		kernel				-- arch/arm/kernel		// lib, mm, include
	*/

2.16.1.3��Makefile����
	(4)	Makefile�иտ�ʼ������kernel�汾��		// ��ģ�黯������װʱ����Ҫ�õ�

	(5)	make�����ں�ʱ����		// make O=xxxָ������Ŀ¼

	(6)	kernel�Ķ���Makefile��������Ҫ����: ARCH, CROSS_COMPILE

	/* Makefile���� */
	// make O=/tmp/mykernel 	\
			ARCH=arm 			\
			CROSS_COMPILE=/usr/local/arm/arm-2009q3/bin/arm-none-linux-gnueabi-

2.16.1.4�����ӽű�����
	(1) ��������		// kernel -- head.S 	uboot -- start.S

	(2)	kernel�����ӽű�: ����vmlinux.lds.S����vmlinux.lds	// ������Ϊ��ʹ�����������ԭ��

		// link addr = 0x30008000 (0xC0008000)

2.16.2.3���ں����е�Ӳ������	/* NOTE: comment */
	(1)	��ѹ��������ʱ�Ƚ�zImage��ε��ں˽�ѹ����Ȼ����ȥ���������������ں����

	(2)	�ں�������һ�����Ⱦ�����	/* uboot����kernel�������� */

		// theKernel(0, machid, bd->bi_boot_params)
		// r0 = 0, r1 = macid, r2 = bd->bi_boot_params

2.16.3.�ں������Ļ��׶�
	// У�������Ϸ��ԡ�������ʽӳ���ҳ������MMU
	// ����C�������л���(����data��, ��bss��)
	// b start_kernel

2.16.4.�ں�������C���Խ׶�1
	(2)	�����ں������Ĵ�ӡ��Ϣ���з���

	(1)	����uboot��kernel���ε�Ӱ���ʵ��
	(2)	Ӳ����ʼ������������
	(3)	�ں�������Ľ�������

2.16.5.2����ӡ�ں˰汾��Ϣ
	(1) printk()		// ��ӡ��������
	(6)	linux_banner	// �궨����include/generated/

2.16.6.2��Machine����
	(1)	setup_arch()		// ȷ����ǰ�ں˶�Ӧ������arch, machine

	(2)	setup_machine(machine_arch_type)	// #define machine_arch_type	2456
		// include/generated/mach-types.h

	(3) -- head-common.S
	     |
		 | -- lookup_machine_type
		 |
		 | -- __lookup_machine_type

		// ��β���ȡ������δ��
		// ����ʱ�����о�����ͬ�����ԵĶ����ӵ�һ��
		|											// arch/arm/include/asm/procinfo.h
		| -- ����: struct proc_info_list{ ... }		// include/asm-arm/procinfo.h
		|
		| -- ʵ��: __arm920_proc_info:				// arch/arm/mm/proc-arm920.S
		|
		| -- ����: .proc.info.init��				// arch/arm/kernel/vmlinux.lds
		|--------------------------------------------------------------------------
		| -- ����: struct proc_info_list{ ... }		// arch/arm/include/asm/mach/arch.h
		|
		| -- ʵ��: MACHINE_START(S3C2440, "SDMK2440")	// arch/arm/mach-s3c2440/mach-smdk2440.c
		|
		| -- ����: .arch.info.init��				// arch/arm/kernel/vmlinux.lds

		// ͨ��machine_id����ָ����, ���Ҳ�����machine_desc������(�ṹ��ָ��)

		/* adr r3, 4b */		// 4�Ƿ���
		/* NOTE: CONFIG_XXX ע��CONFIG��ͷ�ĺ� .config */

2.16.7.�ں�������C���Խ׶�4
	-- setup_arch()��cmdline���		// cmdline: uboot��kernel����ʱ���������������� -- bootargs
	 |
	 | -- parse_tags();
	 |
	 | -- parse_cmdline();

	// static char default_command_line[COMMAND_LINE_SIZE] __initdata = CONFIG_CMDLINE;
	// __tagtable(ATAG_CMDLINE, parse_tag_cmdline);
	
	-- setup_arch(char **cmdline_p)
	 |
	 | -- struct tag *tags = (struct tag *)&init_tags
	 | -- struct machine_desc *mdesc

	 
	 // bootargs=console=ttySAC2,115200 root=/dev/mmcblk0p2 rw init=/linuxrc rootfstype=ext3
	 // $$$$$$$$$cmdline:console=ttySAC2,115200 root=/dev/mmcblk0p2 rw init=/linuxrc rootfstype=ext3
	 
2.16.8.4��rest_init

	// �ܽ�: -- start_kernel()	\
			  |					\
			  | -- setup_arch()		// ���������, uboot�ں˴������	\
			  |															\
			  | -- rest_init()

2.16.9.�ں�������C���Խ׶�6		// os��ؽ���
	(1)	rest_init()�е���kernel_thread()������2���ں��߳�: kernel_init��kthreadd
	(2)	schedule()�������ں˵ĵ���ϵͳ
	(3)	kernel������ɵ���cpu_idle()

2.16.9.2��ʲô���ں��߳�
	(2)	��linuxϵͳ�У��̺߳ͽ��̷ǳ�����
	(3)	Ӧ�ò�����һ������͹���һ���û�����
		�ں�������һ������(������ʵ����һ������)�͹�����һ���ں˽���/�߳�

2.16.9.3������0������1������2
	(2)	���̺Ŵ�0��ʼ, ����0�����û�����, �����ں˽���
	(5)	����0��idle���̣����н���
		����1��kernel_init�������ǽ���1��init����
		����2��kthreadd�������ǽ���2��linux�ں˵��ػ����̡�������֤linux�ں���������

	// ps -aux 		-- in ubuntu
	// man 1 ps

2.16.10.init�������1
2.16.10.1��init��������˴��ں�̬���û�̬��ת��
(1)һ������2��״̬��init���̸տ�ʼ���е�ʱ�����ں�̬��������һ���ں��̣߳�
	Ȼ�����Լ�������һ���û�̬����ĳ������Լ�ǿ��ת�����û�̬��
	��Ϊinit������������˴��ں�̬���û�̬�Ĺ��ȣ���˺������������̶����Թ������û�̬�����ˡ�
(2)�ں�̬������ʲô���ص������һ�����飬���ǹ��ظ��ļ�ϵͳ����ͼ�ҵ��û�̬�µ��Ǹ�init����init����Ҫ���Լ�ת���û�̬�ͱ�������һ���û�̬��Ӧ�ó������Ӧ�ó�������һ��Ҳ��init����Ҫ�������Ӧ�ó���ͱ�����ҵ����Ӧ�ó���Ҫ�ҵ����ͱ���ù��ظ��ļ�ϵͳ����Ϊ���е�Ӧ�ó������ļ�ϵͳ�С�
�ں�Դ�����е����к��������ں�̬����ģ�ִ���κ�һ�������������ں�̬��Ӧ�ó�����벻�����ں�Դ���룬�������ܱ�֤�Լ����û�̬��Ҳ����˵��������ִ�е����init������ں˲���һ�����������ṩ�ġ��ṩ���init������Ǹ��˾��Ǹ��ļ�ϵͳ��

	// init���������û�̬�±���õ�

(3)�û�̬������ʲô��init���̴󲿷�������Ĺ����������û�̬�½��еġ�init���̶����ǲ���ϵͳ���������ڣ��������е��û����̶�ֱ�ӻ��߼��������init���̡�

(4)��δ��ں�̬��Ծ���û�̬�����ܻ�������
init�������ں�̬����ʱ��ͨ��һ������kernel_execve��ִ��һ���û��ռ�������ӵ�Ӧ�ó������Ծ���û�̬�ˡ�ע�������Ծ�����н��̺���û�иı�ģ�����һֱ�ǽ���1.�����Ծ�����ǵ���ģ�Ҳ����˵һ��ִ����init����ת�����û�̬����������ϵͳ������������ת�����ˣ��Ժ�ֻ�����û�̬�¹����ˣ��û�̬����Ҫ�����ں�ֻ̬����API��һ��·�ˡ�

2.16.10.2��init���̹������û���������
(1)init�����������û����̵������ڡ�linuxϵͳ��һ�����̵Ĵ�����ͨ���丸���̴��������ġ������������ֻҪ��һ�������̾�������һ����������ˡ�
(2)init������login���̡������н��̡�shell����
(3)shell���������������û����̡������к�shellһ�������ˣ��û��Ϳ�������������ͨ��./xx�ķ�ʽ��ִ������Ӧ�ó���ÿһ��Ӧ�ó�������о���һ�����̡�

�ܽ᣺���ڵ���ҪĿ�����ô����ʶ��init�������һ������չ��Ϊ����ƽʱ���������ֲ���ϵͳ�����ӡ�


2.16.11.init�������2
2.16.11.1���򿪿���̨
(1)linuxϵͳ��ÿ�����̶����Լ���һ���ļ������������д洢���Ǳ����̴򿪵��ļ���
(2)linuxϵͳ����һ��������һ�н����ļ��������豸Ҳ�����ļ��ķ�ʽ�����ʵġ�����Ҫ����һ���豸����Ҫȥ������豸��Ӧ���ļ���������Ʃ��/dev/fb0����豸�ļ��ʹ���LCD��ʾ���豸��/dev/buzzer����������豸��/dev/console�������̨�豸��
(3)�������Ǵ���/dev/console�ļ������Ҹ�����2���ļ���������һ���õ���3���ļ����������������ļ��������ֱ���0��1��2.�������ļ�������������ν�ģ���׼���롢��׼�������׼����
(4)����1����������׼�����������ļ�����˺����Ľ���1�������������еĽ���Ĭ�϶�������3��������������

2.16.11.2�����ظ��ļ�ϵͳ
(1)prepare_namespace�����й��ظ��ļ�ϵͳ
(2)���ļ�ϵͳ��������ļ�ϵͳ���ļ�ϵͳ������ʲô�� ubootͨ�������������ں���Щ��Ϣ��
uboot�����е�root=/dev/mmcblk0p2 rw ��һ����Ǹ����ں˸��ļ�ϵͳ������
uboot�����е�rootfstype=ext3��һ����Ǹ����ں�rootfs�����͡�
(3)����ں˹��ظ��ļ�ϵͳ�ɹ�������ӡ����VFS: Mounted root (ext3 filesystem) on device 179:2.
������ظ��ļ�ϵͳʧ�ܣ�����ӡ��No filesystem could mount root, tried:  yaffs2
(4)����ں�����ʱ����rootfsʧ�ܣ������϶�û��ִ���ˣ��϶��������ں�������������ʧ����Ϣ5s�Զ������Ļ��ƣ����������Զ�������������ʱ���һῴ�����������������
(5)�������rootfsʧ�ܣ����ܵ�ԭ���У�
	����Ĵ������uboot��bootargs���ò��ԡ�
	rootfs��¼ʧ�ܣ�fastboot��¼�����׳�����ǰ���ֹ���¼�����׳���
	rootfs��������ʧ�ܵġ����������Լ�����rootfs�����߱��˸��ĵ�һ���ã�

2.16.11.3��ִ���û�̬�µĽ���1����
(1)����һ������rootfs�ɹ��������rootfs��Ѱ��Ӧ�ó����init���������������û��ռ�Ľ���1.�ҵ�����run_init_processȥִ����
(2)�������ȷ��init������˭�������ǣ�
�ȴ�uboot����cmdline�п���û��ָ���������ָ����ִ��cmdline��ָ���ĳ���cmdline�е�init=/linuxrc�������ָ��rootfs���ĸ�������init���������ָ����ʽ�ͱ�ʾ����rootfs�ĸ�Ŀ¼�����и����ֽ�linuxrc�ĳ�������������init����
���uboot����cmdline��û��init=xx����cmdline��ָ�������xxִ��ʧ�ܣ����б��÷�������һ���ã�/sbin/init���ڶ����ã�/etc/init���������ã�/bin/init�����ı��ã�/bin/sh��
������϶����ɹ����������ˣ����ˡ�


2.16.12.cmdline���ò���
2.16.12.1����ʽ���
(1)��ʽ�����ɺܶ����Ŀ�ÿո�����������У�ÿ����Ŀ�ж�����Ŀ��=��Ŀֵ
(2)����cmdline�ᱻ�ں�����ʱ������������һ��һ������Ŀ��=��Ŀֵ���ַ�������Щ�ַ����ֻᱻ�ٴν����Ӷ�Ӱ���������̡�
2.16.12.2��root=
(1)���������ָ�����ļ�ϵͳ�������
(2)һ���ʽ��root=/dev/xxx��һ�������nandflash����/dev/mtdblock2�������inand/sd�Ļ���/dev/mmcblk0p2��
(3)�����nfs��rootfs����root=/dev/nfs��

2.16.12.3��rootfstype=
(1)���ļ�ϵͳ���ļ�ϵͳ���ͣ�һ����jffs2��yaffs2��ext3��ubi
2.16.12.4��console=
(1)����̨��Ϣ������Ʃ��console=/dev/ttySAC0,115200��ʾ����̨ʹ�ô���0����������115200.
(2)��������£��ں�������ʱ������console=�����Ŀ����ʼ��Ӳ���������ض�λconsole�������һ�������ϣ���������Ĵ��λ�Ӱ������Ƿ��ܴӴ����ն��Ͻ��յ��ں˵���Ϣ��

2.16.12.5��mem=
(1)mem=���������ں˵�ǰϵͳ���ڴ��ж���

2.16.12.6��init=
(1)init=����ָ������1�ĳ���pathname��һ�㶼��init=/linuxrc

2.16.12.7������cmdline����
(1)console=ttySAC2,115200 root=/dev/mmcblk0p2 rw init=/linuxrc rootfstype=ext3
��һ�����ַ�ʽ��Ӧrootfs��SD/iNand/Nand/Nor������洢���ϡ����ֶ�Ӧ��Ʒ��ʽ��������ʱ�������

(2)root=/dev/nfs nfsroot=192.168.1.141:/root/s3c2440/build_rootfs/aston_rootfs ip=192.168.1.10:192.168.1.141:192.168.1.1:255.255.255.0::eth0:off  init=/linuxrc console=ttySAC0,115200 
�ڶ������ַ�ʽ��Ӧrootfs��nfs�ϣ����ֶ�Ӧ����ʵ���ҿ�����Ʒ�����Ե�ʱ��


2.16.13.�ں��мܹ���ش�����
2.16.13.1���ں˴��������Ϊ3��
(1)arch��		��Ŀ¼��ȫ��cpu�ܹ��йصĴ���
(2)drivers		��Ŀ¼��ȫ��Ӳ��������
(3)����			��ͬ������Щ���붼��Ӳ���޹أ����ϵͳ��ֲ������������ʱ����Щ���뼸�����ǲ��ù�ע�ġ�

2.16.13.2���ܹ���صĳ���Ŀ¼��������
(1)mach����mach����machine architecture����arch/armĿ¼�µ�һ��mach-xxĿ¼�ͱ�ʾһ��machine�Ķ��壬����machine�Ĺ�ͬ���Ƕ���xx���cpu������оƬ����Ʃ��mach-s5pv210����ļ������涼��s5pv210�����оƬ�Ŀ�����machine����mach-xxĿ¼�����һ��mach-yy.c�ļ��ж�����һ�������壨һ���������Ӧһ�������룩������ǿ��Ա���չ�ġ�
(2)plat��plat��platform����д��������ƽ̨��plat������������ΪSoC��Ҳ����˵���platĿ¼�¶���SoC�����һЩӲ�����ڲ����裩��ص�һЩ���롣
���ں��а�SoC�ڲ�������ص�Ӳ����������ͽ���ƽ̨�豸������
(3)include�����includeĿ¼�е����д��붼�Ǽܹ���ص�ͷ�ļ�����linux�ں�ͨ�õ�ͷ�ļ����ں�Դ������Ŀ¼�µ�includeĿ¼�

2.16.13.3������
(1)�ں��е��ļ��ṹ���Ӵ󡢺����ң���ͬ�汾���ں˿���һ���ļ���ŵ�λ���ǲ�ͬ�ģ���������ǳ�ѧ�ߴ���һ�������š�
(2)ͷ�ļ�Ŀ¼include�кü�����Ʃ�磺
	kernel/include		�ں�ͨ��ͷ�ļ�
	kernel/arch/arm/include		�ܹ���ص�ͷ�ļ�
		kernel/arch/arm/include/asm
			kernel\arch\arm\include\asm\mach
	kernel\arch\arm\mach-s5pv210\include\mach
	kernel\arch\arm\plat-s5p\include\plat
(3)�ں��а���ͷ�ļ�ʱ��һЩ��ʽ

#include <linux/kernel.h>		kernel/include/linux/kernel.h
#include <asm/mach/arch.h>		kernel/arch/arm/include/asm/mach/arch.h
#include <asm/setup.h>			kernel\arch\arm\include\asm/setup.h
#include <plat/s5pv210.h>		kernel\arch\arm\plat-s5p\include\plat/s5pv210.h

(4)��Щͬ����ͷ�ļ����а�����ϵ�ģ���ʱ��������Ҫ����ĳ��ͷ�ļ�ʱ���ܲ�����ֱ�Ӱ����������ǰ���һ������������ͷ�ļ���
