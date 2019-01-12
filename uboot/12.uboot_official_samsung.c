
2.12.1.3���°�uboot������ϵ�ĸı�
	(1) ����linux kernel��������ϵ(Kbuild��Kconfig��menuconfig), ������ͼ�ν�����, �������ں�һ������uboot

2.12.2.1���ļ��нṹ���
	// �ͼܹ��йص�ͷ�ļ�����arch/arm/includeĿ¼��

2.12.2.3����Makefile�����boards.cfg�ļ�
	(1)uboot������ط���board.cfg�ļ���		// make xxx_config

	cpu:	u-boot-2013.10\arch\arm\cpu\armv7
	board:	u-boot-2013.10\board\samsung\goni

2.12.3.mkconfig�ű�����
	(1)uboot config -- make s5p_goni_config

	(2)�°汾��Makefile��:
		%_config::	unconfig
			@$(MKCONFIG) -A $(@:_config=)	// ����mkconfig ����: -A s5p_goni

	(3)�°汾mkconfig�ű���:
		��24��35����ʹ��awk������ʽ/*�ַ���ƥ��*/��boards.cfg����$(s5p_goni)ƥ�����һ�н�ȡ������ֵ������line
		Ȼ��line�������Կո�Ϊ����ֿ�, �ֱ�ֵ��$1��$2������$8

	(4)ע���ڽ�����boards.cfg֮��$1��$8�������µ�ֵ
		$1 = Active
		$2 = arm
		$3 = armv7
		$4 = s5pc1xx
		$5 = samsung
		$6 = goni
		$7 = s5p_goni
		$8 = -

2.12.3.2���������κ��京��		// ��Ҫ��ͨ���⼸������, ������������, ���ӵ���Ӧ���ļ�
	(1)��������Ҫ�ı���
		arch=arm
		cpu=armv7
		vendor=samsung
		soc=s5pc1xx

2.12.3.3����������
	(1)include/asm  -> arch/arm/include/asm
	(2)include/asm/arch -> include/asm/arch-s5pc1xx
	(3)include/asm/proc -> include/asm/proc-armv

	��󴴽���include/config.h�ļ�

2.12.3.4��Makefile����ӽ�����빤����	// ���ȼ��tool chain����
	(1)û�ж���CROSS_COMPILE	// Ĭ��gcc���������inter CPU��ʹ��, ���ǽ������

2.12.3.5�����ñ������
	(1)	������̣�
		make distclean			// make clean -- error
		make s5p_goni_config
		make
	
	(2) �������
	
	// arch/arm/cpu/u-boot.lds
	
	ifneq ($(CONFIG_SYS_TEXT_BASE),)
		LDFLAGS_u-boot += -Ttext $(CONFIG_SYS_TEXT_BASE)
	endif

2.12.4.2��������Ϊʲô��¼���в���ȷ��	// ����SD checksum Error
	// ��¼��������: ͬ������
	// code����:  -- sd checksum���㷽ʽ, sd checksum�����ɷ�ʽ

2.12.6.2���޸�u-boot.lds��lowlevel_init.S�ŵ�ǰ��
	// u-boot.map�ж�lowlevel_init.S�Ƿ���ǰ8K
	// �ж�ĳ���ļ��Ƿ񱻱������� -- Makefile

2.12.6.3���޸�board/samsung/goni/Makefile������������	// -- redefinition
	(3)�ο���ǰ�汾��uboot��start.S�ļ��Ĵ�����	// all:

2.12.7�����SDRAM��ʼ��
2.12.9�����uboot�ڶ��׶��ض�λ����bss��
2.12.10���Ƴ�oneNand�����mmc��ʼ��
	// grep "R_ARM_RELATIVE" -nR *

2.12.11.CPUʱ����Ϣ��ʾ��ֲ1
// cpu.h
	#define IS_SAMSUNG_TYPE(type, id)	\
		static inline int cpu_is_##type(void)
		{
			return s5p_cpu_id == id ? 1 : 0;
		}

	IS_SAMSUNG_TYPE(s5pc100, 0xc100)
	IS_SAMSUNG_TYPE(s5pc110, 0xc110)

	// ����ĳɺ���, ��һ�׶ε�Ԥ�����ܽ���
	// �궨����Ԥ����׶ν���

2.12.14.6������MACH_TYPE�Ķ�������
	// MACH_TYPE���ж�����һ���ļ�arch/arm/include/asm/mach-types.h -- ������linux kernel

2.12.15.board_init_r��ֲ
	// ȥ��oneNand֧��, ���sd/mmc֧��

	// cmd_mmc.c mmc��д���ʵ��

2.12.20.������������ֲ		// 0x4000, 16KB, 32sector	-- blk #17

2.12.21.���������Ĳ��Ժ�������ֲ

2.12.22.������������ֲ1

	// CONGIF_CMD_NET
	// CONFIG_CMD_PING
	// drivers/net/dm9000x.c -- dm9000_initialize() init eth_devices




