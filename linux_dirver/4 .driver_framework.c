
5.4.1.3������ʲô���������
	(1) ������ܣ��ں�����ά������Ը�������������д���͵�����ʵ�֣��Ѳ�ͬ��
		�ҵ�ͬ��Ӳ����������ͬ�Ĳ��ֳ����ʵ�֣��ٰѲ�ͬ���������ӿڸ������
		������������ʦʵ��
	(2) �ں˶�ϵͳ��Դ����ͳһ�ܿ�(GPIO���жϺ�)��������Ҫ��������ͷ�

	// ������ں˿������ṩ��ʲô�������������Լ�Ҫ�ṩʲô

5.4.2.1���ں����������LED����ļ�
	(1) drivers/leds/led-class.c��led-core.c

5.4.2.2���Ŷ���ֲ���ں���led����		// drivers/char/led/x210-led.c

5.4.3.2��subsys_initcall()		// linux/init.h
	(1) #define subsys_initcall(fn)		__define_initcall("4", fn, 4)
	(2) #define module_init(fn)			__define_initcall("6", fn, 6)

	// kernel����ʱ�Զ�ִ�У�����Ҫinsmod����ģ��ֻ������ΪY��N���������ó�M
	// module_init��Ҫ�ֶ�insmod

5.4.3.3��led_class_attrs		// __ATTR()
	(1) ��Ӧ/sys/class/leds/Ŀ¼������ݣ�һ�����ļ����ļ���
	(2) Ӧ�ó���ͨ��/sys/class/leds/Ŀ¼�µ������ļ�������������������Ӳ����
		����������/dev/Ŀ¼�µ��豸�ļ�
	(3) attribute����һ������ʵ�֣�������file_operations

	// sysfs��������app������һ���ӿ�

5.4.3.4��led_classdev_register()
	(1) ����һ������leds������һ���豸/*ע��һ���豸*/��led��������ṩע��
		�����Ľӿڡ�����������register_chardev()ͨ��file_operation��ʽע��

5.4.5.2�����led�������֧��
	(1) make menuconfig -> devices driver -> led support ->
		-> CONFIG_LEDS_CLASS -> drivers/leds/Makefile ->
		-> obj-$(CONFIG_LEDS_CLASS)		+= led-class.o ->
		-> sys/class/led

	// ��ʱֻ�пյ�class���ڲ�û��device
	// class_create()��sys/class����һ���յ���
	// device_create()���������������豸

	// make menuconfigĿ¼�����Դ��Ŀ¼������

5.4.6.�����������дled����1
	(1) �ο� drivers/leds/leds-s3c24xx.c

	(2) �ؼ��㣺led_classdev_register()
		// ���ȼ�������Ƿ�ע��ɹ����ϰ�/proc/devices �°�/sys/class/leds/

		// ���������leds_init()�Ѿ�����class_create()������class��
		// �Լ�����led_classdev_register() -> device_create()�������Ӧ���豸

5.4.8.3��gpiolib����
	(3) gpiolib����������ܵ�һ���֣��ں�����ͳһ����ϵͳ������GPIO

5.4.9.1��gpiolibѧϰ�ص�
	(1) gpiolib�Ľ�������
	(2) gpiolib��ʹ�÷��������롢ʹ�á��ͷ�
	(3) gpiolib�ļܹ����漰��ЩĿ¼����Щ�ļ�

	// mach-s5pv210/gpiolib.c
	// plat-samsung/gpiolib.c
	// plat-samsung/gpio.c

	// drivers/gpio/gpiolib.c

5.4.10.1��struct s3c_gpio_chip
	(3) �ں���Ϊÿ��GPIO������һ����ţ��ں˷��㴦��	// chip.base

5.4.16.ʹ��gpiolib���led����
	(1) gpio_request_one()��__gpio_set_value()��gpio_free()

	(2) linux�в鿴gpioʹ�������
		mount -t debugfs debugfs /tmp
		cat /tmp/gpio
		umount /tmp

5.4.17.2������������һ�㲽��
	(1) ��ģ�����ʽ���ⲿ��д������
	(2) �����Ժõ��������뼯�ɵ�kernel��

5.4.17.3��ʵ��
	(1) �ؼ��㣺Kconfig��Makefile��make menuconfig
	(2)	�������裺
		��1������д�õ�����Դ�ļ������ں�Դ������ȷ��Ŀ¼��
		��2������Makefile�������Ӧ������
		��3������Kconfig�������Ӧ��������
		��4����make menuconfig


