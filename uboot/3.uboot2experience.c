
2.3.2.2������
	(1)uboot��linux kernel�ȸ�����Ŀ, ������ֱ�ӱ���, ��Ҫ�����ò��ܱ���
	(2)uboot���÷���: ��ubootԴ���Ŀ¼ִ��: make x210_sd_config
		ִ�����������: Configuring for x210_sd board... // config ok

2.3.2.3������õ�uboot.bin
	(1)��鵱ǰ���뻷������û�а�װ���ʵ�arm-linux-gcc	//arm-2009q3 ���ǹٷ� Cross_compile_toolchain
	(2)��鵱ǰĿ¼��(uboot��Ŀ¼)��Makefile�б������������Ƿ���ȷ
		// �ڹ��̵���Makefile�л����ý�����빤������·��������
		// make or make -j4

2.3.3.2�����ļ�����
	(1) .gitignore
	(2) arm_config.mk 	// .mk -> Makefile�ļ�, ����Makefile�л�ȥ������
	(4)	config.mk		// makefile�ļ�
	(5) COPYINGuboot	// uboot��GPL���֤
	(7) image_split		// �ű�. //for split boot.bin to BL1
	(9) MAKEALL			// �ű�, ��������uboot
	(10)Makefile		// for all uboot src compile management
	(11)mk				// shell script: clean -> config -> compile
	(12)mkconfig		// uboot���ý׶ε���Ҫ���ýű�, uboot����ֲ�Ե���Ҫ����, uboot���ñ�����̵�ʵ��
	(13)mkmovi			// script for iNand/SD boot 
	(15)rules.mk		// uboot��Makefileʹ�õĹ���

	// important file:	\
					  (1)mkconfig: uboot�������	\
					  (2)Makefile: uboot�������

2.3.4.uboot��Դ��Ŀ¼����2
	(1) api			Ӳ���޹صĹ��ܺ���API, uboot����ʹ�õ�API, ��ֲʱ����Ҫ����
	(3) board		����һ: ˼��uboot���֧�ֶ��׿����壬��ξ��п���ֲ�� -- //ÿ����������boardĿ¼������
					�����: board������ô���ļ��У��������ȷ������ʹ�õ�����һ�� -- // ����ǰ���õ�Ŀ��
					������: boardĿ¼����vendor����, board/samsung/x210 -- ����ʱ��Ҫע��·��, 
					//warning: uboot�����ý׶�(mkconfig�ű���Makefile�������йصĲ���)	\
						��Ҫ���������: ȷ������ʱԴ�ļ�·�� -- �ڿ���ֲ���ϵ�֧��
	(4) common		ƽ̨�޹ش���, (1)ubootϵͳ����--cmd (2)ʵ�ֻ�������--env 
	(5) cpu			SOC��س�ʼ���Ϳ��ƴ���, Ʃ��CPU���жϡ����ڵ�SoC�ڲ������, ����/*��ʼ����*/start.S
					//warning: Ӳ��ƽ̨���, ��ֲʱһ�������޸�
	(6) disk
	(7) doc
	(8) drivers		drivers from Linux devices driver // eth inand/sd nand...
					uboot�е�������ʵ����linux�е�����, uboot��һ���̶�����ֲ��linux���������Լ���
					����linux�ǲ���ϵͳ��ubootֻ�Ǹ��������, ���������ֲ���в�ͬ
					//uboot�е�������ʵ��linux�е�������һ����
	(9)examples
	(10)fs			from linux src, ��������Flash����Դ��
	(11)include		uboot��linux kernel�ڹ���ͷ�ļ�ʱ, �����е�ͷ�ļ�ȫ�����д����includeĿ¼��
	(12)lib_*		���͵�lib_arm(arm�ܹ�)��lib_generic�ܹ�(�����ܹ�ͨ��) 
	(13)libfdt		�豸�����, linux kernel 3.4 ����������ʱ���εĻ���, �����豸���������������Σ�����Ӳ����Ϣ������
	(14)nand_spl	nand��� //no use
	(15)net			�������, Ʃ��uboot�е�tftp nfs pingʵ��
	(16)onenand
	(17)post
	(18)sd_fusing	����ʵ������¼uboot����SD�� //important
	(19)tools		������һЩ������Ĵ���, Ʃ��mkimage��

	// important file:	\
		board common cpu drivers include lib_arm lib_generic sd_fusing






















