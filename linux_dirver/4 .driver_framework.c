
5.4.9.linux�ں˵�gpiolibѧϰ1
	���ڿ�ʼѧϰgpiolib����Ҫ����ѧϰ�ص���������ߣ��ͱ����ֵ�ѧϰ����������
	���ǰ��Ŀγ��ҵ���gpiolib��������ڡ�
5.4.10.linux�ں˵�gpiolibѧϰ2
	�����ص㽲��gpiolib�ж�gpio��Ϣ�ķ�װ�ṹ�壬�Լ��ں��м�¼����GPIO�ı��
	�����궨��ȡ�
5.4.11.linux�ں˵�gpiolibѧϰ3
	���ڽ��Ͻڼ�������gpiolib����Ҫ�����˼�¼оƬ��gpio bank�����ṹ�����
5.4.12.linux�ں˵�gpiolibѧϰ4
	���ڽ��Ͻڼ�������gpiolib�����ڵ���������������ʦд��Ӳ�������������֣�
	��Ҫ������GPIOΪ����ģʽ�����ģʽ��2��������
5.4.13.linux�ں˵�gpiolibѧϰ5
	���ڿ�ʼ����gpiolib��������ܲ��֣��ⲿ�����ں˿����߱�д�ġ�������Ҫ
	�������п��Ÿ�goiolibʹ���ߵĽӿ�
5.4.14.linux�ں˵�gpiolibѧϰ6	
	���ڽ��Ͻڼ�������gpiolib��������ܲ��֣����ڼ����������п��Ÿ�gpiolibʹ��
	�ߵĽӿڡ�
5.4.15.linux�ں˵�gpiolibѧϰ7	
	���ڽ��Ͻڼ�������gpiolib��������ܲ��֣���Ҫ����gpiolib�Լ������Ĳ��֣�
	�����ص��Ǹ���attribute��ʵ�ִ��롣
5.4.16.ʹ��gpiolib���led����	
	����ʹ��gpiolib������Ӳ����������������֮ǰд��led��������������õ���
	��������һ����ʵ��LED�豸�����ˡ�
5.4.17.��������ӵ��ں���
	���ڽ�����ν�һ��д�õ���������Դ����ӵ��ں��У����ҿ������ں���ȥ����
	�������ı��룬����ʵ�ʹ����к����á�



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
	(1) �ο�drivers/leds/leds-s3c24xx.c

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

5.4.10.linux�ں˵�gpiolibѧϰ2
5.4.10.1��struct s3c_gpio_chip
	(1)����ṹ����һ��GPIO�˿ڵĳ���,����ṹ���һ�������Ϳ�����ȫ������һ��IO�˿ڡ�
	(2)�˿ں�IO�����������S5PV210�кܶ��IO�ڣ�160�����ң�����ЩIO�����ȱ��ֳ�N���˿ڣ�port group����Ȼ��ÿ���˿����ְ�����M��IO�ڡ�Ʃ��GPA0��һ���˿ڣ����������8��IO�ڣ�����һ�������GPA0_0����GPA0.0����GPA0_1��
	(3)�ں���Ϊÿ��GPIO������һ����ţ������һ�����֣�Ʃ��һ����160��IOʱ��žͿ��Դ�1��160�����ֲ�������ſ����ó���ܷ����ȥʶ��ÿһ��GPIO��
5.4.10.2��s5pv210_gpio_4bit
	(1)���������һ���ṹ�����飬�����а����˺ܶ��struct s3c_gpio_chip���͵ı�����


5.4.11.linux�ں˵�gpiolibѧϰ3
5.4.11.1��S5PV210_GPA0��
(1)�����ķ���ֵ����GPA0�˿ڵ�ĳһ��IO�ڵı��ֵ�����ξ����������IO����GPA0�˿��еľֲ���š�
(2)samsung_gpiolib_add_4bit_chips����������Ǿ������gpiolib��ע��ġ�����������յĲ��������ǵ�ǰ�ļ��ж���õĽṹ������s5pv210_gpio_4bit����ʵ2�������ֱ���������������Ԫ�ظ������������������ʵ�Ͱ����˵�ǰϵͳ�����е�IO�˿ڵ���Ϣ����Щ��Ϣ�������˿ڵ����֡��˿�������GPIO�ı�š��˿ڲ����Ĵ�����������ַ����ַ���˿���IO�ڵ��������˿���������ģʽ�����ú������˿��е�IO�ڻ������Ӧ���жϺŵĺ�������


5.4.12.linux�ں˵�gpiolibѧϰ4
5.4.12.1����������
(1)�ĸ�Ŀ¼���ĸ��ļ�
(2)��������Ϊʲô�и�4bit�����ǵ�CPU��2440��CON�Ĵ�����2bit��Ӧһ��IO�ڣ���6410��210�Լ�֮���ϵ����CON�Ĵ�����4bit��Ӧ1��IO�ڡ�����gpiolib�ڲ���2440��210��CON�Ĵ���ʱ�ǲ�ͬ�ġ�
5.4.12.2���������ù�ϵ
samsung_gpiolib_add_4bit_chips
	samsung_gpiolib_add_4bit
	s3c_gpiolib_add
��������������samsung_gpiolib_add_4bit�ڲ���ʵ��û����gpiolib��ע�Ṥ�������ǻ�������䣬������ÿһ��GPIO�����ó�����ģʽ/���ģʽ�Ĳ���������


5.4.13_14.linux�ں˵�gpiolibѧϰ5_6
5.4.13.1��s3c_gpiolib_add
(1)���ȼ�Ⲣ����chip��direction_input/direction_ouput/set/get��4������
(2)Ȼ�����gpiochip_add��������������ע���������ʵ���ע����ǽ����ǵķ�װ��һ��GPIO�˿ڵ�������Ϣ��chip�ṹ������ҽӵ��ں�gpiolibģ�鶨���һ��gpio_desc�����е�ĳһ�������С�
5.4.13.2����������ܽǶ���������һ��gpiolib
(1)֮ǰ�ķ����Ѿ���һ���䣬����Ŀǰ�����Ѿ��������gpiolib�Ľ������̡�������ֻ������gpiolib������һ���֣��ǳ�����������ʦ�������һ���֣�������һ�������ں˿������ṩ��������ܵ���һ���֣��������Ǻ���Ҫȥ�����ĵ�2�����ߡ�
(2)drivers/gpio/gpiolib.c����ļ������еĺ������������ǵ�2���֣�Ҳ�����ں˿�����д��gpiolib��ܲ��֡�����ļ����ṩ�ĺ�����Ҫ�����²��֣�
gpiochip_add:	�ǿ�ܿ������Ľӿڣ���������������ʦ�ã��������ں�ע�����ǵ�gpiolib
gpio_request: 	�ǿ�ܿ������Ľӿڣ���ʹ��gpiolib����д�Լ�����������������ʦ�õģ�
				������Ҫ��ʹ��ĳһ��gpio���ͱ����ȵ���gpio_request�ӿ������ں˵�
				gpiolib�������룬�õ������ſ���ȥʹ�����gpio��
gpio_free:		��Ӧgpio_request�������ͷ�����������˵�gpio
gpio_request_one/gpio_request_array: ��������gpio_request�ı���	
gpiochip_is_requested:	�ӿ������ж�ĳһ��gpio�Ƿ��Ѿ���������
gpio_direction_input/gpio_direction_output: �ӿ���������GPIOΪ����/���ģʽ��
				ע��ú����ڲ�ʵ�ʲ�û�ж�Ӳ�����в�����ֻ��ͨ��chip�ṹ�������
				����ָ������˽���SoC���̵���������ʦд�������Ĳ���Ӳ��ʵ��gpio
				���ó����ģʽ���Ǹ�������
				
���ϵĽӿ�����һ�࣬��Щ���Ǹ�д�������������õ���gpiolib����ʹ�õ�
ʣ�µĻ�������һ�ຯ�������ຯ����gpiolib�ڲ��Լ���һЩ����ʵ�ֵĴ���
				

5.4.15.linux�ں˵�gpiolibѧϰ7
5.4.15.1��gpiolib��attribute����
(1)CONFIG_GPIO_SYSFS
(2)GPIO��attribute��ʾ
5.4.15.2����ش������
(1)

gpiolib_sysfs_init
	gpiochip_export
		sysfs_create_group


5.4.16.ʹ��gpiolib���led����
5.4.16.1�����̷���
(1)��1����ʹ��gpio_request����Ҫʹ�õ�һ��GPIO
(2)��2����gpio_direction_input/gpio_direction_output ��������/���ģʽ
(3)��3�����������ֵgpio_set_value  ��ȡIO��ֵgpio_get_value
5.4.16.2������ʵ��
(1)��led1�ϱ�д�������ͨ��
(2)��չ֧��led2��led3��led4.���Էֿ�ע��Ҳ����ʹ��gpio_request_arrayȥһ��ע��
(3)ѧϰlinux�в鿴gpioʹ������ķ���
�ں����ṩ�������ļ�ϵͳdebugfs��������һ��gpio�ļ����ṩ��gpio��ʹ����Ϣ��
ʹ�÷�����mount -t debugfs debugfs /tmp��Ȼ��cat /tmp/gpio���ɵõ�gpio��������Ϣ��
ʹ�����umount /tmpж�ص�debugfs


5.4.17.��������ӵ��ں���
5.4.17.1�������Ĵ�����ʽ
(1)Ұ���������Ƿ�����Կ����������ڿ����׶ζ�������
(2)���������ƿ������ں�����ʱmake menuconfig�����ں���ô���룬���㼯��
5.4.17.2������������һ�㲽��
(1)��ģ�����ʽ���ⲿ��д������
(2)�����Ժõ��������뼯�ɵ�kernel��
5.4.17.3��ʵ��
(1)�ؼ��㣺Kconfig��Makefile��make menuconfig
(2)�������裺
��1������д�õ�����Դ�ļ������ں�Դ������ȷ��Ŀ¼��
��2������Makefile�������Ӧ������
��3������Kconfig�������Ӧ��������
��4����make menuconfig


	
Ŀ¼���ļ��ṹ��
mach-s5pv210/gpiolib.c 		s5pv210_gpiolib_init()
mach-s5pv210/include/mach/gpio.h			#define S5PV210_GPA0(_nr)	(S5PV210_GPIO_A0_START + (_nr))
arch/arm/plat-samsung/gpiolib.c		������210/6410����4bit CON�Ĵ������͵Ĳ�������
arch/arm/plat-samsung/gpio.c		������24XX����2bit CON�Ĵ������͵Ĳ�������
drivers/gpio/gpiolib.c				�������ں˿������ṩ��gpiolib��������ܲ���



