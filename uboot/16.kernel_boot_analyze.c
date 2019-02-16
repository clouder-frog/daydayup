
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

2.16.2.3���ں����е�Ӳ������	/* note: comment */
	(1)	��ѹ��������ʱ�Ƚ�zImage��ε��ں˽�ѹ����Ȼ����ȥ���������������ں����

	(2)	�ں�������һ�����Ⱦ�����	/* uboot����kernel�������� */

		// theKernel(0, machid, bd->bi_boot_params)
		// r0 = 0, r1 = macid, r2 = bd->bi_boot_params

2.16.3.�ں������Ļ��׶�
	// У�������Ϸ��ԡ�������ʽӳ���ҳ������MMU
	// ����C�������л���(����data��, ��bss��)
	// b start_kernel

2.16.4.�ں�������C���Խ׶�1
	(1)	�����ں������Ĵ�ӡ��Ϣ���з���
	(2)	����uboot��kernel���ε�Ӱ���ʵ��
	(3)	Ӳ����ʼ������������
	(4)	�ں�������Ľ�������

2.16.6.1��start_kernel
	-- start_kernel()
	 |
	 | -- printk(linux_banner)	// include/generated
	 |
	 | -- setup_arch()
	 |
	 | -- console_init()
	 |
	 | -- rest_init()

	(1)-- setup_arch()			// cmdline���: uboot��kernel����ʱ���������������� -- bootargs
	    |
	    | -- parse_tags();		// ATAG_MEM, ATAG_CMDLINE
	    |
	    | -- parse_cmdline();

	// static char default_command_line[COMMAND_LINE_SIZE] __initdata = CONFIG_CMDLINE;
	// __tagtable(ATAG_CMDLINE, parse_tag_cmdline);

	-- ��֤uboot��kernel���ε�cmdline(bootargs)
	// bootargs=console=ttySAC2,115200 root=/dev/mmcblk0p2 rw init=/linuxrc rootfstype=ext3
	// $$$$$$$$$cmdline:console=ttySAC2,115200 root=/dev/mmcblk0p2 rw init=/linuxrc rootfstype=ext3

	-- linux����, Android�����������ļ�, linux etcĿ¼(����ʱ����)		// �����޸�Դ�룬����Ҫ���±���

	(1)	-- setup_arch()		// ȷ����ǰ�ں˶�Ӧ������arch, machine
		 |
		 | -- struct tag *tags = (struct tag *)&init_tags
		 | -- struct machine_desc *mdesc
		 | -- char *from = default_command_line
		 |
		 | -- setup_processor()
		 |
		 | -- mdesc = setup_machine(machine_arch_type)	// include/generated/mach-types.h
			|											// #define machine_arch_type	2456
			| -- mdesc = lookup_machine_type(nr)

	(1) -- head-common.S
	     |
		 | -- lookup_machine_type
		 |
		 | -- __lookup_machine_type

		// ��β���ȡ������δ��
		// ����ʱ�����о�����ͬ�����ԵĶ����ӵ�һ��
		// ͨ��machine_id����ָ����, ���Ҳ�����machine_desc������(�ṹ��ָ��)
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


		/* adr r3, 4b */		// 4�Ƿ���
		/* note: CONFIG_XXXע��CONFIG��ͷ�ĺ� .config */

	(2) -- console_init()
		 |
		 | -- // console driver init

	(3) -- rest_init()
		 |
		 | -- kernel_thread(kernel_init)		// ����1 -- kernel_init()��Ҫ��schedule��ע��
		 | -- kernel_thread(kthreadd)
		 |
		 | -- cpu_idle()

	(3) -- kernel_init()
		 |
		 | -- sys_open("/dev/console")
		 | -- (void)sys_dup(0)
		 | -- (void)sys_dup(0)
		 |
		 | -- prepare_namespace()
		    |
			| -- mount_block_root()
			   |
			   | -- do_mount_root()
			      |
				  | -- printk("VFS: Mounted root (%s filesystem) on device %u:%u.\n")
		 |
		 | -- init_post()
		    |
			| -- run_init_process()
			   |
			   | -- kernel_execve("/linuxrc")

2.16.9.3������0������1������2
	(2)	���̺Ŵ�0��ʼ, ����0�����ں˽���, ���û��ռ俴����
	(5)	����0��idle����
		����1��kernel_init		// init����
		����2��kthreadd			// linux�ں˵��ػ�����, ������֤linux�ں���������

	// ps -aux 		-- in ubuntu
	// man 1 ps

2.16.10.1��init��������˴��ں�̬���û�̬��ת��
	// һ������2��״̬: \
		init���̸տ�ʼ���ں�̬(�ں��߳�)	-- ���ظ��ļ�ϵͳ���ҵ��û�̬�µ�init����	\
		�����û�̬��init����ת���û�̬		-- kernel_execve("/sbin/init")

	// ���ں�̬ת���û�̬ʱ, init���̺�û�б� -- ����1

	// init���������û�̬�±���õ�, �ɸ��ļ�ϵͳ���ṩ

	// �˺��������̶��������û�̬��, �������е��û����̶�ֱ�ӻ��߼��������init����

	// init������login���̡������н���(��ȡ����)��shell����(��������, ������������)

	// �ӽ���Ĭ�ϼ̳и��������е��ļ�������-- ��������Ĭ�϶��б�׼���롢���������(�ļ�������>3)

	// �û�̬�����ں�̬��Ҫ����API

2.16.11.2�����ظ��ļ�ϵͳ��ִ�н���1
	(1)	���ظ��ļ�ϵͳ: prepare_namespace()

	(2)	���ļ�ϵͳ��������ļ�ϵͳ���ļ�ϵͳ������ʲô��
		root=/dev/mmcblk0p2 rw			// SD/MMC Channel0(inand) partition2 -- 0-uboot 1-kernel 2-rootfs
		rootfstype=ext3

	(3)	����rootfs�ɹ��������rootfs��Ѱ��Ӧ�ó����init����(����1)		// run_init_process()
		init=/linuxrc

2.16.12.cmdline���ò���
2.16.12.1����ʽ���
	(1)	��ʽ�����ɺܶ����Ŀ�ÿո�����������У�ÿ����Ŀ�ж�����Ŀ��=��Ŀֵ
	(2)	����cmdline�ᱻ�ں�����ʱ������������һ��һ������Ŀ��=��Ŀֵ���ַ�����
		��Щ�ַ����ֻᱻ�ٴν����Ӷ�Ӱ���������̡�
2.16.12.2��root=
	(1)���������ָ�����ļ�ϵͳ�������
	(2)һ���ʽ��root=/dev/xxx��һ�������nandflash����/dev/mtdblock2�������inand/sd�Ļ���/dev/mmcblk0p2��
	(3)�����nfs��rootfs����root=/dev/nfs��

2.16.12.3��rootfstype=
	(1)���ļ�ϵͳ���ļ�ϵͳ���ͣ�һ����jffs2��yaffs2��ext3��ubi
2.16.12.4��console=
	(1)����̨��Ϣ������Ʃ��console=/dev/ttySAC0,115200��ʾ����̨ʹ�ô���0����������115200.
	(2)��������£��ں�������ʱ������console=�����Ŀ����ʼ��Ӳ����
		�����ض�λconsole�������һ�������ϣ���������Ĵ��λ�Ӱ������Ƿ��ܴӴ����ն��Ͻ��յ��ں˵���Ϣ��

2.16.12.5��mem=
(1)mem=���������ں˵�ǰϵͳ���ڴ��ж���

2.16.12.6��init=
(1)init=����ָ������1�ĳ���pathname��һ�㶼��init=/linuxrc

2.16.12.7������cmdline����
(1)console=ttySAC2,115200 root=/dev/mmcblk0p2 rw init=/linuxrc rootfstype=ext3
��һ�����ַ�ʽ��Ӧrootfs��SD/iNand/Nand/Nor������洢���ϡ����ֶ�Ӧ��Ʒ��ʽ��������ʱ�������

(2)root=/dev/nfs nfsroot=192.168.1.141:/root/s3c2440/build_rootfs/aston_rootfs ip=192.168.1.10:192.168.1.141:192.168.1.1:255.255.255.0::eth0:off  init=/linuxrc console=ttySAC0,115200 
�ڶ������ַ�ʽ��Ӧrootfs��nfs�ϣ����ֶ�Ӧ����ʵ���ҿ�����Ʒ�����Ե�ʱ��

