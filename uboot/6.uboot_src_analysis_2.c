
2.6.1.start_armboot		// ��������������uboot�����ĵڶ��׶�
2.6.1.3����۷�����uboot�ڶ��׶�Ӧ����ʲô
	(1)uboot step1: ��Ҫ��ʼ����SoC�ڲ���һЩ����(���Ź���ʱ��), Ȼ���ʼ��ddr��������ض�λ
	(2)uboot step2: init SoC�弶Ӳ��(iNand������оƬ��), uboot�����һЩ����(uboot���������������)
					���ճ�ʼ����ɺ����uboot��������׼����������

2.6.1.4��˼����uboot�ڶ��׶�����ںδ�
	(2)����û�û�и������ִ��bootcmd�����Զ������ں�����, ubootִ�����
	(3)uboot����������һ����ѭ��, ѭ�����ڲ����ظ�: ��������, ��������, ִ������

2.6.2.1��init_fnc_t
	(1)typedef int (init_fnc_t) (void)		// ��������  -- init_fnc_t *init_sequence[] = {}
	(2)init_fnc_t **init_fnc_ptr			// ����ָ��  -> ָ������ 
											// �ɵ�һ�� * -- init_fnc_t *init_sequence[]
		// ���غ���ָ��: ��ָ��һ��ָ��, ��ָ��ָ������
		// һ�㽫����ָ�����Ϊָ������

2.6.2.2��DECLARE_GLOBAL_DATA_PTR   			// �ṹ��ָ��᲻���ظ�����? -- ����һ��declare
	(1)#define DECLARE_GLOBAL_DATA_PTR     register volatile gd_t *gd asm ("r8")	//gd: global data

2.6.3.2���ڴ��Ų�
	(1)uboot code	// | 0xC3E0_0000
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

2.6.4.1��ִ��init_sequence
	(1)init_fnc_t *init_sequence[]	//����ָ������ -- init_fnc_t *
	(3)init_fnc_t **init_fnc_ptr	//���غ���ָ�� -- init_fnc_t **		init_fnc_ptr ָ�� init_sequence	

	// array_name not &array_name
	// init_fnc_ptr++ (+4) 		-- ����ָ����������

2.6.4.2��board_init
	(1)eth init: config controller's gpio, controller control regs
	(2)gd->bd->bi_arch_number		// board������ -- �ں�����ǰ����uboot�����еĻ�����, �ж��Ƿ�����
	(3)gd->bd->bi_boot_params		// uboot���ں�����ʱ�Ĵ��ε�ַ(�ַ����׵�ַ0x3000_0100), bootargs

	// pc���豸 ��׼��
	// Ƕ��ʽ�豸 ���ƻ� ��Ӳ���ɲü�
	// ǿ������ת�����ڴ��ַ��ֵ  	ָ�� -> ����(�ڴ�)
	// ʵ����: 		 				�� -> ����
	// ����̨�ǻ��ڴ���, ����̨����ʵ�ֱ�׼�������
	// hang()/*����*/

2.6.4.x��dram_init	//	ddr������
	(1)Ӳ����ʼ��: ddr������������	// lowlevel_init

	(2)�����ʼ��: ����ܹ���һЩddr��ص���������, ��ַ����
		// uboot&&linux��λ�ȡ��ǰϵͳ�ڴ������Ϣ, ��: �ڴ�����, �ڴ�������, ��ʼ��ַ��
		��: x210_sd.h���ú궨��ָ��, Ȼ��ubootֱ��ʹ����Щ��Ϣ
		��: ������PC��biosͨ����ȡӲ����Ϣ��ȷ��

2.6.4.3��interrupt_init
		(1)TIM4 init
			read_reg -> r,m,p,s -> get_pllclk() -> get_hclk -> get_pclk() -> timer_load_val

2.6.6.2��env_init
	(1)uboot֧�ָ��ֲ�ͬ����������(norflash��nandflash��inand��sd��...), ����ж��env_init()
	(2)�������ֻ�Ƕ�/*�ڴ�*/��ά������һ��uboot��env���˻����ĳ�ʼ��	// judge valid or not
	   ��ǰenvû�д�SD����DDR�е�relocate/*only relocate firmware*/	    // -- current env invalid
	(4)��start_armboot������(line776)����env_relocate(), ����env��SD���е�DDR�е��ض�λ
		�ض�λ֮����Ҫ��������ʱ�ſ��Դ�DDR��ȥȡ, �ض�λ֮ǰ���Ҫʹ�û�������ֻ�ܴ�SD����ȥ��ȡ -- // ?

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

	// �ĵ����ݲ��漰��Makefile ���漰�� x210_sd.h ��ֱ��make����

2.6.10.1��dram_init
	gd->bd->bi_dram[0].start = PHYS_SDRAM_1;		// ��¼��ǰ������ddr������Ϣ
	gd->bd->bi_dram[0].size  = PHYS_SDRAM_1_SIZE; 

2.6.10.2��display_dram_config	// print dram config info

2.6.10.3��init_sequence�ܽ�
	(1) �弶Ӳ���ĳ�ʼ��
		eth init(gpio)��Timer4 init(10ms)
	(2) gd��Ա������ʼ��
		gd->bd->bi_arch_number	// machine code
		gd->bd->bi_boot_params	// �ں˴����׵�ַ
		gd->bd->bi_baudrate��gd->baudrate	// baudrate
		gd->have_console����Ϊ1		// console step1 init
		gd->bd->bi_dram	// ddr config info init
	(3) ������ӡ��Ϣ

2.6.11.1��CFG_NO_FLASH	// test macro in board.c
	(1)NandFlash: nand;		NorFlash: flash
	(2)flash_init: norflash init
	   display_flash_config: print norflash config info		// Flash: 8MB

2.6.11.2��CONFIG_VFD��CONFIG_LCD
		uboot���Դ���LCD��ʾ��������, ������ֲ�Լ����LCD��ʾ��ش���

2.6.11.3��mem_malloc_init	// init uboot�Ķѹ�����(����ά�����ڴ��һЩ����) -- uboot heap size: 896KB

2.6.12.1����������г�ʼ����mmc��ʼ��
	(3)mmc_initialize(): ��ʼ��SoC�ڲ���SD/MMC������		// ./drivers/mmc/mmc.c
	(4)uboot��Ӳ���Ĳ�������ֲlinux�ں��е�������ʵ��		// ./drivers -- linux driver src
	(5)mmc_initialize�Ǿ���Ӳ���ܹ��޹ص�һ��MMC��ʼ������
		���е�ʹ�������׼ܹ��Ĵ��붼����������������MMC�ĳ�ʼ����
		mmc_initialize���ٵ���board_mmc_init��cpu_mmc_init����ɾ����Ӳ����MMC��������ʼ������
		// board����sd��������, usb����sd��������оƬ
		// 210CPU����sd��������, ����mmc_init����CPU����ִ��
	(6)cpu_mmc_init��uboot/cpu/s5pc11x/cpu.c
		�������ּ�ӵĵ�����drivers/mmc/s3c_mmcxxx.c�е�������������ʼ��Ӳ��MMC������
		������ֲ�ܶ࣬�ֲ��˼��һ��Ҫ�У�������ȫ�ͺ�Ϳ��
		// uboot/soc/s5pc11x/cpu.c

// uboot����û�е���ʵ������
// uboot���������ʹ�������ַ, Linuxʹ�������ַ, ������uboot����ʹ��Linux�е�����
// uboot������Ҫ��Linux�ں������ܹ������˽�
// uboot������ʽ�ܸ���, ��Ϊ�����������Linux�ں�������, ��ΪLinux�ں����кܶ�ܹ�����ȷ����
// drivers/mmc ͨ��mmc���������� mmc.h�Ǻ����ļ�linux mmc mtd�����ܹ�

2.6.13.1��env_relocate		// env is embeded in text segment  -- warning: text segment will copy to ddr
	(1)env_relocate: ���������ض�λ //������������SD����ȡ��DDR��
	(2)���������洢λ��:
		SD������8��������������Ϊ���������洢����4KB��
		��¼/����ϵͳʱ, ��¼(uboot��kernel��rootfs), û����¼env����
		��¼/������ϵͳ��һ������ʱENV�����ǿյ�
		��һ�δ�SD�����ػ�������(��Ȼ)ʧ��, uboot�����ڲ�default env(in text segment)
		����uboot������ʱ�����ص�ddr��, ��ʱdefault envҲ��ddr��
		Ȼ��д��(������saveenvʱд��, Ҳ�����ǵ�һ�ζ�ȡĬ�ϻ���������ͱ�д�뵽SD����ENV����)
		�Ժ��ϵ��ʼ��ʱ��ȡ��OK
	(3)�����Ĵ�SD����DDR���ض�λENV�Ĵ�������env_relocate_spec�ڲ���movi_read_env��ɵ�

	// set_default_env()	// default_environment in config_sd.h  -- �Ѿ�����һ���޸ĸ��ļ�û��Ч��
	// env_movi.c

	// dataflash

2.6.14.1��IP��ַ��MAC��ַ��ȷ��
	(1) �豸��ip��ַ��gd->bd->bi_ip_addr��ά��, ��Դ�ڻ�������ipaddr
		getenv��ȡip��ַ�ַ�����ʽ, string_to_ipת��Ϊ���ʮ����(�����ַ���)	// ����ASCII����ʽ
		// x210_sd.h�����õ���Ĭ�ϻ�������

2.6.14.2��devices_init
	(1)devices_init�����־����豸�ĳ�ʼ����������豸ָ�ľ��ǿ������ϵ�Ӳ���豸��
		���������ʼ�����豸���������豸����������������Ǵ�������������������ġ�
		uboot�кܶ��豸��������ֱ����ֲlinux�ں˵ģ�Ʃ��������SD������
		linux�ں��е�����������Ӧ���豸��ʼ��������
		linux�ں������������о���һ��devices_init(���ֲ�һ����ȫ�ԣ����ǲ��)��
		���þ��Ǽ���ִ�и���Ӳ��������init������
	(2)uboot�����������ʵ���Ǵ�linux�ں�����ֲ�����ģ�
		��������Ҳ��ȥִ�����еĴ�linux�ں��м̳�������ЩӲ�������ĳ�ʼ��������

2.6.14.3��jumptable_init
	(1)jumptable��ת��������һ������ָ�����飬�����¼�˺ܶຯ���ĺ�������
		����������Ҫʵ��һ������ָ�뵽���庯����ӳ���ϵ��
		����ͨ����ת���еĺ���ָ��Ϳ���ִ�о���ĺ�����
		�����ʵ��������C����ʵ����������̡���linux�ں����кܶ����ּ��ɡ�
	(2)ͨ������������ת��ֻ�Ǳ���ֵ��δ�����ã������ת����uboot�и�����ûʹ�á�
	
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

2.6.15.2��enable_interrupts
(1)������Ӧ�����жϳ�ʼ�����롣����ָ����CPSR�����жϱ�־λ��ʹ�ܡ�
(2)��Ϊ����uboot��û��ʹ���жϣ����û�ж���CONFIG_USE_IRQ�꣬�������������������Ǹ��տ��ӡ�
(3)uboot�о�������һ��������Ǹ���һ�����Ƿ�������������������Ƿ����һ�������ڲ��Ĵ��롣
uboot����2�ֽ���������������������
����һ���ڵ��ú�����ʹ���������룬Ȼ������ʵ����ȫ�ṩ���롣
���������ڵ��ú�����ֱ�ӵ��ã�Ȼ���ں����崦�ṩ2�������壬һ������ʵ���һ���ǿտ��ӣ�
�ú궨����������������ʵ�ʱ���ʱ�����ĸ�������ȥ��

2.6.15.3��loadaddr��bootfile������������
(1)�������������������ں������йصģ�������linux�ں�ʱ��ο�����������������ֵ��

2.6.15.4��board_late_init
(1)����������������ǿ����弶���һЩ��ʼ����Ƚ�����ˣ��������ڳ�ʼ����
�������ھ���ǰ��ó�ʼ���Ķ���ʼ�����ˣ�ʣ�µ�һЩ������ں����ʼ���ľ��������ˡ�
����˵���˿����弶���Ӳ�������ʼ����һ�����ˡ�
(2)����X210��˵����������ǿյġ�

2.6.16.start_armboot����14
2.6.16.1��eth_initialize
(1)������Ӧ����������صĳ�ʼ�������ﲻ��SoC������оƬ����ʱSoC��ߵĳ�ʼ������������оƬ�����һЩ��ʼ����
(2)����X210��DM9000����˵����������ǿյġ�X210��������ʼ����board_init�����У�����оƬ�ĳ�ʼ���������С�

2.6.16.2��x210_preboot_init��LCD��logo��ʾ��
(1)x210����������������֮ǰ��һЩ��ʼ�����Լ�LCD��Ļ�ϵ�logo��ʾ��

2.6.16.3��check menukey to update from sd
(1)uboot���������׶������һ���Զ����µĹ��ܡ����ǣ����ǿ��Խ�Ҫ�����ľ���ŵ�SD���Ĺ̶�Ŀ¼�У�Ȼ�󿪻�ʱ��uboot���������׶μ��������־����һ�������������б�־Ϊ"LEFT"���Ǹ������������������������ʾupdate mode���������ʱδ�������ʾboot mode�����������update mode��uboot���Զ���SD���ж�ȡ�����ļ�Ȼ����¼��iNand�У��������boot mode��uboot��ִ��update��ֱ�������������С�
(2)���ֻ����ܹ��������ǿ�����¼ϵͳ������������ʱ��SD������ϵͳ��¼����

2.6.16.4����ѭ��
(1)������
(2)���������Զ�ִ��
(3)���ȫ


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
		   | -- gd->env_addr = default_environment
		   | -- gd->env_valid = 0
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
		| -- display_dram_config()	// printf ddr config_info
		
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




















