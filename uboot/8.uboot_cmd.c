
2.8.1.1��ʹ��uboot����
	(1)uboot��������������л�����, ���Ͻ����ַ�, �յ�enter, ��ʼ�����ַ���, Ȼ��ִ�� 
		-- �����յ�backspace, �ַ����Ĵ������Դ���

2.8.1.3��ÿ�������Ӧһ������		// do_xxx() -- ����ִ�к���

2.8.1.4�����������argc��argv���������
(1)����ִ�к������յĲ����б�����argc��argv, Ȼ��������ϵ���ִ������ʱ������+����
	// md 30000000 10	 -- argc = 3, argv[0]=md, argv[1]=30000000, argv[2]=10���ݸ�����ִ�к���

2.8.2.3��run_commond()
	(1)�����ȡ
	(2)�������		// parse_line()
	(3)��������		// find_cmd(argv[0])
	(4)ִ������		// ����ṹ���к���ָ��

	// uboot��������ϵ����(ע�ᡢ�洢����������)

2.8.3.1�����ܵĹ���ʽ
	(1)����	-- �ṹ������ // �ṹ���Ա������װ�����������Ϣ
	(2)���� -- ÿ��node��Ӧһ������

	// ubootʹ���Զ���εķ�ʽ���洢��������

2.8.3.2������ṹ��cmd_tbl_t
	struct cmd_tbl_s	// ��װ���������е������Ϣ
	{
		char	*name;
		int		maxargs;	// �����Լ� -- error: version  111
		int		repeatable;
		int		(*cmd)(struct cmd_tbl_s *, int, int, char *[]); /* Implementation function */
		char	*usage;
		char	*help
	};		// warnging: �����ط���';' 

	// һ�������Ӧһ��cmd_tbl_tʵ��

2.8.3.3��ubootʵ���������
	(1) ���һ��cmd_tbl_tʵ������һ������	// cmd_tbl_tʵ�������Զ��������(�û��Զ����) -- for link

	(2) uboot�ض�λʱ���ö�������ص�ddr��	// �����ڽṹ������    -- warning: ������ default_environment[]

	(3) ����ʼ��ַ�ͽ�����ַ		// ���ڱ�����

2.8.4.1��U_BOOT_CMD��

	#define Struct_Section  __attribute__ ((unused,section (".u_boot_cmd")))

	#define U_BOOT_CMD(name, maxargs, rep, cmd, usage, help) \
		cmd_tbl_t __u_boot_cmd_##name Struct_Section = {#name, maxargs, rep, cmd, usage, help}	 // gcc��չ�﷨: ##name #name

	U_BOOT_CMD(
		version,	1,		1,	do_version,		// version not "version"
		"version - print monitor version\n",
		NULL
	);

	// uboot/common/command.h -- search�� ��һ����ͷ�ļ���
	// gcc test.c -E -o test	-- ֻԤ����
	// ##name������������������

2.8.4.2��find_cmd����
	(1)find_cmd()�ӵ�ǰuboot������в����Ƿ���ĳ������, ����ҵ��򷵻��������ṹ���ָ��, ���δ�ҵ�����NULL

	// cmd_tbl_t *cmdtp_tmp = &__u_uboot_cmd_start;
	// len = ((p = strchr(cmd, '.')) == NULL) ? strlen(cmd) : (p - cmd);	// -- md.b md.w md.l
	// cmdtp_tmp++ 	// ָ���++, Ҫ����ָ�����������

2.8.5.1�������е�c�ļ���ֱ���������
	(1)��uboot/common/command.c���������, ʹ��U_BOOT_CMD����cmd_tbl_tʵ��, �ṩdo_xxx()��Ӧ����ִ�к���

2.8.5.2���Խ�һ��c�ļ����������
	(1)��uboot/commonĿ¼���½�cmd_xxx.c
		// �����Ӧͷ�ļ�
		// uboot/common/Makefile���cmd_xxx.o


// �������� -- kernel�г���
	COBJS-y += main.o
	COBJS-$(CONFIG_CMD_BDI) += cmd_bdinfo.o

// ubootʹ��/*���Ӷ�����*/�ķ�ʽ������	-- kernel�г���






