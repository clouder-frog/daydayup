
2.6.1.3����۷�����uboot�ڶ��׶�Ӧ����ʲô
	(1)uboot step1: ��Ҫ��ʼ����SoC�ڲ���һЩ����(���Ź���ʱ��), Ȼ���ʼ��ddr��������ض�λ
	(2)uboot step2: init SoC�弶Ӳ��(iNand������оƬ��), uboot�����һЩ����(uboot���������������)
					���ճ�ʼ����ɺ����uboot��������׼����������

2.6.1.4��˼����uboot�ڶ��׶�����ںδ�
	(2)����û�û�и������ִ��bootcmd�����Զ������ں�����, ubootִ�����
	(3)uboot����������һ����ѭ��, ѭ�����ڲ����ظ�: ��������, ��������, ִ������

2.6.2.2��DECLARE_GLOBAL_DATA_PTR   			// �ṹ��ָ��᲻���ظ�����? -- ����һ��declare
	(1)#define DECLARE_GLOBAL_DATA_PTR     register volatile gd_t *gd asm ("r8")	//gd: global data

2.6.3.2���ڴ��Ų�
	(1)uboot code	// | 0xC3E0_0000	// #define CONFIG_MEMORY_UPPER_CODE
	(2)reserved		// |
	(3)bd			// |
	(4)gd			// | addr
	(5)ENV			// |
	(6)����			// |
	(7)ջ��			// ��

	// (5) (6) (7) ����˳�� -- board.c start_armboot() line530

	// CFG_UBOOT_BASE	0xC3E0_0000
	// CFG_UBOOT_SIZE	2*1024*1024

	// CFG_MALLOC_LEN	CFG_ENV_SIZE + 896*1024
	// CFG_ENV_SIZE		0x4000
	// CFG_STACK_SIZE	512*1024
	// sizeof(gd_t) = 36 sizeof(bd) = 44

	gd->bd = (bd_t*)((char*)gd - sizeof(bd_t))	// �ṹ������׵�ַ�ڵ͵�ַ, bd->bi_baudrate�ڵ͵�ַ

	//compile optimization barrier: �ڴ���, Ϊ�˷�ֹ�߰汾��gcc���Ż���ɴ���

2.6.4.1��init_sequence��init_fnc_t

	(1)typedef int (init_fnc_t) (void)		// ��������  -- init_fnc_t *init_sequence[] = {}
	(2)init_fnc_t **init_fnc_ptr			// ����ָ��  -> ָ������ 
											// �ɵ�һ�� * -- init_fnc_t *init_sequence[]
	// ���غ���ָ��: ��ָ��һ��ָ��, ��ָ��ָ������ -- ָ������
	// һ�㽫����ָ�����Ϊָ������

	(1)init_fnc_t *init_sequence[]	//����ָ������ -- init_fnc_t *
	(3)init_fnc_t **init_fnc_ptr	//���غ���ָ�� -- init_fnc_t **		init_fnc_ptr ָ�� init_sequence	

	// array_name not &array_name
	// init_fnc_ptr++ (+4) 		-- ����ָ����������

2.6.4.2��board_init
	(1)eth init: config controller's gpio, controller control regs
	(2)gd->bd->bi_arch_number		// board mac id
	(3)gd->bd->bi_boot_params

	// PC���豸��׼��, Ƕ��ʽ�豸���ƻ���Ӳ���ɲü�
	// ǿ������ת�����ڴ��ַ��ֵ  	ָ�� -> ����(�ڴ�)
	// ʵ����: 		 				��   -> ����
	// ����̨�ǻ��ڴ���, ����̨����ʵ�ֱ�׼�������
	// hang()/*����*/

2.6.4.3��dram_init	//	ddr������
	(1)Ӳ����ʼ��: ddr������������	// lowlevel_init

	(2)�����ʼ��: ����ܹ���һЩddr��ص���������, ��ַ����
		// uboot&&linux��λ�ȡ��ǰϵͳ�ڴ������Ϣ, ��: �ڴ�����, �ڴ�������, ��ʼ��ַ��
		��: x210_sd.h���ú궨��ָ��, Ȼ��ubootֱ��ʹ����Щ��Ϣ
		��: ������PC��BIOSͨ����ȡӲ����Ϣ��ȷ��

2.6.4.4��interrupt_init
		(1)TIM4 init
			read_reg -> r,m,p,s -> get_pllclk() -> get_hclk -> get_pclk() -> timer_load_val

2.6.6.2��env_init
	(2)�������ֻ�Ƕ�/*�ڴ�*/��ά������һ��uboot��env���˻����ĳ�ʼ��	// judge valid or not -- no
	   ��ǰenvû�д�SD����DDR�е�relocate/*only relocate firmware*/	    // -- current env invalid
	(4)��start_armboot������(line776)����env_relocate(), ����env��SD���е�DDR�е��ض�λ
		�ض�λ֮����Ҫ��������ʱ�ſ��Դ�DDR��ȥȡ, �ض�λ֮ǰ���Ҫʹ�û�������ֻ�ܴ�SD����ȥ��ȡ -- // ?

		// only relocate uboot.bin not relocate env.bin

2.6.7.1��init_baudrate
	(2)getenv_r����������ȡ����������ֵ	// ��ȡ����Ϊstring���Ͷ�����int���� -- simple_strtoul() -- // ?

2.6.8.1��console_init_f
	(1)console_init_f��console(����̨)�ĵ�һ�׶γ�ʼ��, _f��ʾ�ǵ�һ�׶γ�ʼ��, _r��ʾ�ڶ��׶γ�ʼ��
	//��ʱ���ʼ����������һ�����, �м����Ҫ����һЩ���� -- line826 console_init_r

2.6.8.2��display_banner		// ���U_BOOT_VERSION	
	(1) ./common/console.c/printf -- CR600 tool.c/printfʵ��
	(2) printf() -> puts()
	(4) ����̨����һ�����������������豸, ����豸��һ��ר�õ�ͨ�ź���(���͡�����...)
		����̨��ͨ�ź���/*���ջ�ӳ�䵽Ӳ����ͨ�ź�������ʵ��*/
		uboot��ʵ���Ͽ���̨��ͨ�ź�����ֱ��ӳ�䵽Ӳ�����ڵ�ͨ�ź�����
	(5)	�����ڱ����ϵ�У�����̨��ͨ�ź���ӳ�䵽Ӳ��ͨ�ź���ʱ�������������һЩ�м��Ż���Ʃ��˵�������
		������ϵͳ�еĿ���̨��ʹ���˻�����ƣ�������ʱ������printf�����ݵ�����Ļ�ϲ�û�п��������Ϣ��
		������Ϊ�������ˡ������������Ϣֻ�ǵ���console��buffer�У�buffer��û�б�ˢ�µ�Ӳ������豸�ϣ�
		������������豸��LCD��Ļʱ��

// cpu���������� ��ӻ������

2.6.8.3��print_cpuinfo	// cpu clock && usart message

2.6.9.3��ubootѧϰʵ��
	(1)��ubootԴ����������޸�
	(2)make distcleanȻ��make x210_sd_configȻ��make
	(3)������ɵõ�u-boot.bin��Ȼ��ȥ��¼����¼������������������ֽ���linux��ʹ��dd��������д�ķ�������д��
	(4)��д���̣�
		��һ��������sd_fusingĿ¼��		// file mkbl1  ,,,x64
		�ڶ�����make clean
		��������make
		���Ĳ�������sd����ls /dev/sd*�õ�SD����ubuntu�е��豸��(һ����/dev/sdb)
		���岽��./sd_fusing.sh /dev/sdb�����¼(ע�ⲻ��sd_fusing2.sh)

	//����ʵ��, ȥ��flash���᲻�����

	// bl1_position=1
	// uboot_position=49	// video start_armboot����7 15��

	// bl2_position=9
	// uboot_position=57

2.6.10.1��dram_init
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;		// ��¼��ǰ������ddr������Ϣ
	gd->bd->bi_dram[0].size  = PHYS_SDRAM_1_SIZE; 

2.6.10.2��display_dram_config	// print dram config info

	//	NandFlash: nand		NorFlash: flash

2.6.11.2��CONFIG_VFD��CONFIG_LCD
		uboot���Դ���LCD��ʾ��������, ������ֲ�Լ����LCD��ʾ��ش���

2.6.11.3��mem_malloc_init	// init uboot�Ķѹ�����(����ά�����ڴ��һЩ����) -- uboot heap size: 896KB

2.6.12.1����������г�ʼ����mmc��ʼ��
	(3)mmc_initialize(): ��ʼ��SoC�ڲ���SD/MMC������		// ./drivers/mmc/mmc.c
	(4)uboot��Ӳ���Ĳ�������ֲlinux�ں��е�������ʵ��		// ./drivers -- linux driver src
	(5)mmc_initialize�Ǿ���Ӳ���ܹ��޹ص�һ��MMC��ʼ������
		���е�ʹ�������׼ܹ��Ĵ��붼����������������MMC�ĳ�ʼ��
		mmc_initialize���ٵ���board_mmc_init��cpu_mmc_init����ɾ����Ӳ����MMC��������ʼ������
		// board����sd��������, usb����sd��������оƬ
		// x210CPU����sd��������, ����mmc_init����CPU����ִ��

// uboot����û�е���ʵ������
// uboot���������ʹ�������ַ, Linuxʹ�������ַ, ������uboot����ʹ��Linux�е�����
// uboot������Ҫ��Linux�ں������ܹ������˽�
// uboot������ʽ�ܸ���, ��Ϊ�����������Linux�ں�������, ��ΪLinux�ں����кܶ�ܹ�����ȷ����
// drivers/mmc ͨ��mmc���������� mmc.h�Ǻ����ļ�linux mmc mtd�����ܹ�

2.6.13.1��env_relocate		// env is embeded in text segment  -- warning: text segment will copy to ddr
		
	(2) flash����8��������������Ϊ���������洢����(4KB)
		��¼/����ϵͳʱ, ��¼(uboot��kernel��rootfs), û����¼env����
		��һ������ʱflash��env����Ϊ��, ����flash��envʧ��, uboot�����ڲ�default env

		// flash��env������������ 	-- saveenv or auto?

	-- env_relocate()	// ���������ض�λ��ddr��
	  |
	  | -- env_ptr = (env_t *)malloc (CFG_ENV_SIZE)
	  |
	  | -- env_relocate_spec()
		 |
		 | -- env_relocate_spec_movinand()
		    |
			| -- movi_read_env(virt_to_phys(env_ptr))	// assign value env_ptr
			|
			| -- if (crc32(0, env_ptr->data, ENV_SIZE) != env_ptr->crc)	// crc exe error
			   |
		       | -- use_default()
	  |
	  | -- gd->env_addr = (uint32_t)&(env_ptr->data)		// ����env -- gd->env_addr

2.6.14.1��IP��ַ��MAC��ַ��ȷ��

2.6.14.2��devices_init		// linux kernel������devices_init

	//����ִ�и���Ӳ���豸��������init����

2.6.14.3��jumptable_init	// no use

	// C�����Ƿ��������ģ�����C���Ա�д��Linux�ں�����������

2.6.15.start_armboot����13
2.6.15.1��console_init_r
(1)console_init_f�ǿ���̨�ĵ�һ�׶γ�ʼ����console_init_r�ǵڶ��׶γ�ʼ����
ʵ���ϵ�һ�׶γ�ʼ����û��ʵ���Թ������ڶ��׶γ�ʼ���Ž�����ʵ���Թ�����
(3)console_init_r����console�Ĵ�����ܹ�����ĳ�ʼ��
��˵���˾���ȥ��console��ص����ݽṹ�������Ӧ��ֵ�����������ڴ�����������͵ĳ�ʼ����
(4)uboot��consoleʵ���ϲ�û�и��������ת����������ֱ�ӵ��õĴ���ͨ�ŵĺ�����
�����ò���consoleʵ�ʲ�û��ʲô�ֱ�
����linux��console�Ϳ����ṩ������ƵȲ���console����ʵ�ֵĶ�������

2.6.15.2��enable_interrupts		// no use, uboot not use irq

2.6.15.3��loadaddr��bootfile������������
	// �������������������ں������йصģ�������linux�ں�ʱ��ο�����������������ֵ��

2.6.15.4��board_late_init	// no use

2.6.16.1��eth_initialize
(1)������Ӧ����������صĳ�ʼ�������ﲻ��SoC������оƬ����ʱSoC��ߵĳ�ʼ������������оƬ�����һЩ��ʼ��
(2)����X210��DM9000����˵����������ǿյġ�X210��������ʼ����board_init�����У�����оƬ�ĳ�ʼ����������

	// 	IDE�ӿ�Ӳ��

2.6.16.2��x210_preboot_init(LCD��logo��ʾ)	//start_armboot����14

2.6.16.3��check menu key to update from sd		// SD������

2.6.16.4��main_loop

(1)�ڶ��׶���Ҫ�ǶԿ����弶���Ӳ����������ݽṹ���г�ʼ����

	init_sequence[]
		|
		| -- cpu_init()	// if necessary: ����IRQ FIQ stack	-- msp or psp
		|
		| -- board_init()	// ����, ������, �ڴ洫�ε�ַ
		   |
		   | -- dm9000_pre_init()	// SROM controller reg init
		   | -- gd->bd->bi_arch_number
		   | -- gd->bd->bi_boot_params	// memory_base + 0x100
	    |
		| -- interrupt_init()  // init timer4 -- auto_load, 10ms, no_interrupt, turn_on
		|
		| -- env_init()
		   |
		   | -- gd->env_addr = (uint32_t)&default_environment[0]
		   | -- gd->env_valid = 1
		|
		| -- init_baudrate()
		   |
		   | -- gd->bd->bi_baudrate = gd->baudrate = CONFIG_BAUDRATE
		|
		| -- serial_init()	// nothing
		|
		| -- console_init_f()
		   |
		   | -- gd->have_console = 1
		|
		| -- display_banner()
		   |
		   | -- printf("%s\n", version_string)		// _DATE_ _TIME_
		|
		| -- print_cpuinfo()	// speed.c
		|
		| -- checkboard() 	// printf x210
		|
		| -- dram_init()	// gd struct init -- ddr init in asm_code
		   |
		   | -- gd->bd->bi_dram[0].start = PHY_SDRAM_1			// 0x3000_0000
		   | -- gd->bd->bi_dram[0].size  = PHYS_SDRAM_1_SIZE	// 0x1000_0000
		   | -- gd->bd->bi_dram[1].start = PHYS_SDRAM_2			// 0x4000_0000
		   | -- gd->bd->bi_dram[1].size  = PHYS_SDRAM_2_SIZE	// 0x1000_0000
		|
		| -- display_dram_config()	// printf ddr config_info(size)
		
	mem_malloc_init		��ʼ��uboot�Լ�ά���Ķѹ��������ڴ�
	mmc_initialize		inand/SD����SoC�������Ϳ��ĳ�ʼ��
	env_relocate		���������ض�λ
	gd->bd->bi_ip_addr	gd���ݽṹ��ֵ
	gd->bd->bi_enetaddr	gd���ݽṹ��ֵ
	devices_init		�յ�
	jumptable_init		���ù�ע��
	console_init_r		�����Ŀ���̨��ʼ��
	enable_interrupts	�յ�
	loadaddr��bootfile 	��������������ʼ��ȫ�ֱ���
	board_late_init		�յ�
	eth_initialize		�յ�
	x210_preboot_init	LCD��ʼ������ʾlogo
	check_menu_update_from_sd	����Զ�����
	main_loop			��ѭ��

2.6.17.2���������������ܽ�
(1)��һ�׶�Ϊ���׶Ρ��ڶ��׶�ΪC�׶�
(2)��һ�׶���SRAM�С��ڶ��׶���DRAM��
(3)��һ�׶�ע��SoC�ڲ����ڶ��׶�ע��SoC�ⲿBoard�ڲ�

2.6.17.3����ֲʱ��ע���
(1)x210_sd.hͷ�ļ��еĺ궨��
(2)�ض�Ӳ���ĳ�ʼ������λ�ã�Ʃ��������




















