
5.9.1.1�����õ�2�ִ�����
	(1) ���败����������һ���2�֣�һ����SoC���ô�������������һ�������õ�
		ר�Ŵ���������оƬ��ͨ��I2C�ӿں�SoCͨ��
	(2) ���ݴ�����������ֻ��һ�֣����ר�õĵ���ʽ����������оƬ��I2C�ӿں�
		SoCͨ��

		// SOC == ������IC == ������

5.9.1.2��X210ʹ�õĴ�����
	(1) X210V3ʹ�õĴ�������ft5x06
	(2) X210V3Sʹ�õĴ�������gslX680

5.9.1.3��ѧϰ�����������Ĺؼ���
	(1) input��ϵͳ���֪ʶ
	(2) �ж����°벿
	(3) I2C��ϵͳ
	(4) ������оƬ����֪ʶ

5.9.1.4������״̬��ͬ��

5.9.2.3�����������ź�����ʹ��Ҫ��
	(1) ���������ܵݹ�
	(2) ���������������ж������ģ��ź��������ԣ���Ϊ����˯�ߣ��ж������Ĳ���
		����ȣ����������ж��������л�ȡ������֮ǰҪ/*�Ƚ��ñ����ж�*/
	(3) �������ĺ���Ҫ���ǣ�ӵ���������Ĵ�����벻��˯�ߣ�Ҫһֱ����CPUֱ��
		�ͷ�������
	(4) �ź����Ͷ�д�ź����ʺ��ڱ���ʱ��ϳ�����������ǻᵼ�µ�����˯�ߣ����
		ֻ���ڽ���������ʹ�ã����������ʺ��ڱ���ʱ��ǳ��̵���������������κ�
		������ʹ�á�����������Ĺ�����Դֻ�ڽ��������ķ��ʣ�ʹ���ź��������ù�
		����Դ�ǳ����ʣ�����Թ�����Դ�ķ���ʱ��ǳ��̣�������Ҳ���ԡ��������
		�������Ĺ�����Դ��Ҫ���ж������ķ��ʣ������װ벿���жϴ������Ͷ��벿
		�����жϣ����ͱ���ʹ���������������������ڼ�����ռʧЧ�ģ����ź����Ͷ�
		д�ź��������ڼ��ǿ��Ա���ռ�ġ�������ֻ�����ں˿���ռ��SMP���ദ������
		������²�������Ҫ���ڵ�CPU�Ҳ�����ռ���ں��£������������в������ǿղ���

5.9.4.�жϵ����°벿1
5.9.4.1���жϴ����ע���
	(1) �ж������ģ����ܺ��û��ռ����ݽ��� // �磺copy_to_user() copy_from_user() �����ݽ����Ĺ����У����ܻᵼ������
	(2) ���ܽ���CPU���������ߡ�����schedule��
	(3) ISR����ʱ�価���̣ܶ�Խ����ϵͳ��Ӧ����Խ��

5.9.4.2���ж��°벿2�ֽ������
	(2) �°벿�������1��tasklet��С����
	(3) �°벿�������2��workqueue���������У�

5.9.4.3��taskletʹ��ʵս
	(1) tasklet��ؽӿڽ���		// declare_tasklet()	tasklet_schedule()

5.9.5.1��workqueueʵս��ʾ
	(1) workqueue��ͻ���ص����°벿�ύ��worker thead������°벿���ڽ�������
		�ģ����Ա����ȣ���˿���˯�ߡ�
	(2) include/linux/workqueue.h

5.9.5.2���ж����°벿����ԭ��
	(1) �����������н�������ļ���������������жϵĶ��벿�У���ʱ����������
		��ͬ���͵��жϣ������������٣����Կ���Ѹ�ٲ��ܴ��ŵش������������
	(2) ��Ҫ����ʱ����е������ļ����������tasklet�С���ʱ���������κ��ж�
		���������Լ��Ķ��벿ͬ���͵��жϣ������Բ�Ӱ�춥�벿�Խ�������Ĵ���
		ͬʱ�ֲ�������û����̵��ȣ��Ӷ���֤���Լ������������Ѹ����ɡ�
	(3) ��Ҫ�϶�ʱ���Ҳ������ȣ���������ϵͳ��������Ȩ���Ĵ����������
		workqueue�С���ʱ����ϵͳ�ᾡ�����ٴ�����������񣬵����������̫��
		�ڼ����ϵͳҲ���л�����ȱ���û��������У��Ӷ���֤������Ϊ�������
		��Ҫ����ʱ�佫�����û������޷����С�
	(4) ��������˯�ߵ��������workqueue�С���Ϊ��workqueue��˯���ǰ�ȫ�ġ���
		��Ҫ��ô������ڴ�ʱ������Ҫ��ȡ�ź���ʱ������Ҫִ������ʽ��I/O����ʱ��
		��workqueue�ܺ��ʡ�

5.9.6.2��linux�ں˵�I2C�����������
	(2) Դ����I2C��ص�������λ�ڣ�drivers/i2cĿ¼�¡�linuxϵͳ�ṩ2��I2C����
		ʵ�ַ�������һ�ֽ�i2c-dev����Ӧdrivers/i2c/i2c-dev.c�����ַ���ֻ�Ƿ�װ
		��������I2C master��һ����SoC�����õ�I2C����������I2C����������������
		Ӧ�ò��ṩ��Ӧ�Ĳ����ӿڣ�Ӧ�ò������Ҫ�Լ�ȥʵ�ֶ�slave�Ŀ��ƺͲ�����
		��������I2C�����൱��ֻ���ṩ��Ӧ�ò���Է���slaveӲ���豸�Ľӿڣ�����
		��δ��Ӳ�����κβ�����Ӧ����Ҫʵ�ֶ�Ӳ���Ĳ�������������I2C
		�����ֽ�����Ӧ�ò������������ַ�ʽ�������������������ǰѲ��컯������Ӧ��
		�У��������豸�Ƚ��Ѳ���������slave�ǷǱ�׼I2Cʱ��ʱ���ö���������ֻ��
		Ҫ�޸�Ӧ�þͿ���ʵ�ֶԸ����豸������
	(3) �ڶ���I2C���������еĴ��붼����������ʵ�֣�ֱ����Ӧ�ò��ṩ���ս����
		Ӧ�ò���������Ҫ֪����������I2C���ڣ�Ʃ�����ʽ������������ֱ����Ӧ��
		���ṩ/dev/input/event1�Ĳ����ӿڣ�Ӧ�ò��̵��˸�����֪��event1����
		������I2C

5.9.8.linux�ں˵�I2C��ϵͳ���3
5.9.8.1��I2C��ϵͳ��4���ؼ��ṹ��
	(1) struct i2c_adapter			I2C������
	(2) struct i2c_algorithm		I2C�㷨
	(3) struct i2c_client			I2C���ӻ����豸��Ϣ
	(4) struct i2c_driver			I2C���ӻ����豸����

5.9.9.linux�ں˵�I2C��ϵͳ���4
5.9.9.1��i2c-core.c��������
	(1) smbus�����Թ�
	(2) ģ����غ�ж��:bus_register(&i2c_bus_type);		// cd /sys/bus

5.9.9.2��I2C���ߵ�ƥ�����
	(1) match����
	(2) probe����
		�ܽ᣺I2C��������2����֧��i2c_client����i2c_driver�������κ�һ��
			driver����clientȥע��ʱ��I2C���߶������match����ȥ��client.name
			��driver.id_table.name����ѭ��ƥ�䡣���driver.id_table�����е�id
			��ƥ�䲻����˵��client��û���ҵ�һ����Ӧ��driver��û�ˣ����ƥ����
			�������client��driver�����õģ���ôI2C���߻���������probe������
			�����probe�����ֻ����driver���ṩ��probe������driver�е�probe��
			������豸����Ӳ����ʼ���ͺ���������

5.9.9.3�����Ĳ㿪�Ÿ��������ֵ�ע��ӿ�
	(1) i2c_add_adapter/i2c_add_numbered_adapter()		// register adapter
	(2) i2c_add_driver()								// register driver
	(3) i2c_new_device()								// register client

5.9.10.1��adapterģ���ע��	// platform����

5.9.10.2��probe��������
	(1) ���һ��i2c_adapter�ṹ�壬���ҵ��ýӿ�ȥע��֮		// i2c_add_numbered_adapter()
	(2) ��platform_device����Ӳ����Ϣ������Ҫ�Ĵ���request_mem_region & ioremap��request_irq�ȣ�
	(3) ��Ӳ������ʼ����ֱ�Ӳ���210�ڲ�I2C�������ļĴ�����

5.9.10.3��i2c_algorithm
	(1) i2c->adap.algo = &s3c24xx_i2c_algorithm;
	(2) functionality
	(3) s3c24xx_i2c_doxfer()

// i2c�Ŀ�����(adapter)��soc�ڲ����裬ʹ��platform���ߺ���

	static int i2c_adap_s3c_init(void)
	{
		return platform_driver_register(&s3c34xx_i2c_driver);
	}

	subsys_initcall(i2c_adap_s3c_init);

// i2c-s3c2410.c	i2c platform driver	 -- ƥ�����ͨ��id_table �� name�� -- platform.c platform_match()
// mach-x210.c 	���е�ƽ̨�����豸���� ������

// i2c->clk = clk_get(&pdev->dev, "i2c");		// �ں��ṩ��ʱ�ӽӿ�

// -------------------------------------------------
struct bus_type platform_bus_type = {};
bus_register(&platform_bus);

struct bus_type i2c_bus_type = {};
bus_register(&i2c_bus_type);

5.9.11_12.linux�ں˵�I2C��ϵͳ���6_7
5.9.11.1��i2c_driver��ע��
(1)��gslX680������Ϊ��
(2)��������ӵ��ں�SI��Ŀ��
(3)i2c_driver�Ļ���������name��probe		// name��������ƥ�䣬��iic bus��
											// probe��ִ�е��ݴ�����������س�ʼ��

// i2c-core.c -- static int i2c_device_match() -- ��ͨ��id_table
// driver: -- gslX680.c
// device: -- mach-x210.c

5.9.11.2��i2c_client��������
(1)ֱ����Դ��i2c_register_board_info
smdkc110_machine_init
	i2c_register_board_info

struct i2c_board_info {
	char		type[I2C_NAME_SIZE];			// �豸��
	unsigned short	flags;						// ����
	unsigned short	addr;						// �豸�ӵ�ַ
	void		*platform_data;					// �豸˽������
	struct dev_archdata	*archdata;
#ifdef CONFIG_OF
	struct device_node *of_node;
#endif
	int		irq;								// �豸ʹ�õ�IRQ�ţ���ӦCPU��EINT
};

(2) ʵ��ԭ�����
	�ں�ά��һ������ __i2c_board_list��������������ӵ���I2C�����Ϲҽӵ�����
	Ӳ���豸����Ϣ�ṹ�塣Ҳ����˵�������ά������һ��struct i2c_board_info��
	��������
	��������Ҫ��struct i2c_client�ڱ�ĵط���__i2c_board_list�����еĸ����ڵ�
	���������⹹�����ɡ�

�������ò�Σ�
i2c_add_adapter/i2c_add_numbered_adapter
	i2c_register_adapter
		i2c_scan_static_board_info
			i2c_new_device
				device_register

�ܽ᣺I2C���ߵ�i2c_client���ṩ���ں�ͨ��i2c_add_adapter/i2c_add_numbered_adapter�ӿ�
����ʱ�Զ����ɵģ����ɵ�ԭ����mach-x210.c�е�
i2c_register_board_info(1, i2c_devs1, ARRAY_SIZE(i2c_devs1));

5.9.13.gslX680��������ֲʵ��
5.9.13.1��������ֲʵ��
(1)Դ���ȡ
(2)Դ������ں���				/* һ����������������ģ�� */
(3)mach�ļ������board_info
(4)������ں�ȥ����
5.9.13.2�����ں����������CONFIG��
(1)����һ��������Ʃ��CONFIG_TOUCHSCREEN_GSLX680
(2)�ڴ�����ʹ�ú�����������
(3)��Makefile��ʹ�ú�����������
(4)��Kconfig��Ŀ����Ӻ��������
(5)make menuconfig��ѡ��Y����N


5.9.14_15.gslX680����Դ�����1_2


5.9.16.�ϰ汾������������
5.9.16.1��ft5x06������ֲʵ��
5.9.16.2��ft5x06����Դ�����

	(1) struct i2c_adapter			I2C������
	(2) struct i2c_algorithm		I2C�㷨
	(3) struct i2c_client			I2C���ӻ����豸��Ϣ
	(4) struct i2c_driver			I2C���ӻ����豸����

// i2c_adapter ע����platform bus��
	(1) i2c_adapter driver		// i2c-s3c2410.c
		�� static struct platform_driver s3c24xx_i2c_driver = {};

	(2) i2c_adapter device		// mach-x210.c -- platform device array
		�� struct platform_device s3c_device_i2c0 = {};
		�� s3c_i2c0_set_platdata(NULL);

	(3) -- s3c24xx_i2c_probe()
		 |
		 | -- s3c24xx_i2c_init()		// init i2c controller
		 |
		 | -- i2c_add_numbered_adapter()
		    |
			| -- i2c_register_adapter()		// register i2c_device

// touch screen ע����i2c bus��
	(1) touch screen i2c_driver		// gslX680.c
		�� static struct i2c_driver gsl_ts_driver = {};

	i2c_check_functionality(client->adapter, I2C_FUNC_I2C)		// client->adapter

	struct i2c_board_info i2c_devs1[] = {
		.irq = 
	}
	
	gslX680.c -- client->irq = IRQ_PORT;		// line857  ����һ�㲻����������

	// line860

	gsl_ts_init()	// input irq��ز���

ft5x06_touch_5p.c
//line627 ts->wq = create_workqueue("ft5x06_wq")		// ��̬����workqueue

i2c-dev.c

xmbuf_transfer
