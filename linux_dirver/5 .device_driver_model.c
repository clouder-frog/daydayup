
5.5.1.linux�豸����ģ�ͼ��
	(1) ��class������bus���豸device������driver
	(2) kobject�Ͷ�����������
	(3) sysfs
	(4) udev

5.5.1.2��Ϊʲô��Ҫ�豸����ģ��
	(3) 2.6 �汾����ʽ�����豸����ģ�ͣ��豸����ģ�͸���ͳһʵ�ֺ�ά��һЩ
		���ԣ����磺��Դ�����Ȳ�Ρ������������ڡ��û��ռ�������ռ�Ľ�
		����	// ͳһ������������������д

5.5.1.3������������2����
	(1) �������ܱ�д -- Ӳ����ز���
	(2) ������μ��� -- �����ز���

5.5.2.�豸����ģ�͵ĵײ�ܹ�
5.5.2.1��kobject
	(1) ������linux/kobject.h��
	(2) ���ֶ����������Ԫ���ṩһЩ�����ͷ����磺�������ü�����ά��������
		���������������û��ռ�ı�ʾ
	(3) �豸����ģ���еĸ��ֶ������ڲ��������һ��kobject
	(4) ��λ�൱�����������ϵ�ܹ��е��ܻ���
5.5.2.2��kobj_type
	(1) �ܶ����м��Ϊktype��ÿһ��kobject����Ҫ��һ��ktype���ṩ��Ӧ����
	(2) �ؼ���1��sysfs_ops���ṩ�ö�����sysfs�еĲ���������show��store��
	(2) �ؼ���2��attribute���ṩ��sysfs�����ļ���ʽ���ڵ����ԣ���ʵ����Ӧ�ýӿ�
5.5.2.3��kset
	(1) kset����Ҫ������������kobject��������
	(2) kset����ҪĿ���ǽ�����kobject�������Ÿ���������֯��Ŀ¼��μܹ�
	(3) ������Ϊkset����Ϊ����sysfs��Ū��Ŀ¼���Ӷ����豸����ģ���еĶ��
		�����ܹ��в�����߼��Ե���֯��һ��

5.5.3.����ʽ�豸������֯��ʽ
5.5.3.1������
	(2) ��������е�����ʽ���
	(3) bus_type�ṹ�壬�ؼ���match������uevent����

5.5.3.2���豸
	(1) struct device��Ӳ���豸���ں���������еĳ���struct usb_device��
		struct device������
	(2) device_register()�������ں��������ע��һ���豸

5.5.3.3������
	(1) struct device_driver�������������ں���������еĳ���
	(2) �ؼ�Ԫ��1��name���������豸ƥ������
	(3) �ؼ�Ԫ��2��probe�����������̽�⺯�����������һ���豸�Ƿ���Ա�������������
		// ����ʽ�������ʹ��probe����
		// �����൱��module_init()�Զ�ִ�еĺ���
		// ������probe()�����������ʶ������豸�����豸���԰�װ������

5.5.3.4����
	(1) ��ؽṹ�壺struct class �� struct class_device
	(2) udev��ʹ���벻��class
	(3) class����������������Ϊͬ����һ��class�Ķ���豸��������
		Ҳ����˵��class��һ��������Ŀ�ľ���Ϊ�˶Ը����豸���з������
		��Ȼ��class�ڷ����ͬʱ����ÿ����������һЩ����ǩ������Ҳ���豸����
		ģ��Ϊ����д�����ṩ�Ļ�����ʩ

5.5.4.platformƽ̨���߹���ԭ��1
5.5.4.1����Ϊƽ̨����
	(1) �����usb��pci��i2c������������˵��platform����������ġ����������
	(2) CPU������ͨ�ŵ�2�ַ�ʽ����ַ����ʽ���Ӻ�ר�ýӿ�ʽ���ӡ�ƽ̨���߶�Ӧ
		��ַ����ʽ�����豸��Ҳ����SoC�ڲ����ɵĸ����ڲ�����

	// Ϊʲô��Ҫ���� -- ���ڹ����������豸???
	// ������cpu���ӵķ�ʽ����ַ����(����)��ר�ýӿ�(�磺nand)

5.5.4.2��ƽ̨�����¹����2Ա��		// drivers/base/platform.c
	(2) �����ṹ�壺platform_device��platform_driver
	(3) �����ӿں�����platform_device_register()��platform_driver_register()

	// platform_device����device

struct platform_device
{
	const char	* name;
	int		id;
	struct device	dev;
	u32		num_resources;
	struct resource	* resource;		// ��Դ�����׵�ַ
	const struct platform_device_id	*id_entry;
	struct pdev_archdata	archdata;	// specific data
};

5.5.5.platformƽ̨���߹���ԭ��2
5.5.5.1��ƽ̨������ϵ�Ĺ�������
	(1)��һ����ϵͳ����ʱ��busϵͳ��ע��platform			// sys/bus -- �ں�bus��ϵͳ
	(2)�ڶ������ں���ֲ���˸����ṩ��ע��platform_device	// mach-x210.c
	(3)��������д�������˸����ṩ��ע��platform_driver
	(4)���Ĳ���platform��match��������driver��deviceƥ��󣬵���driver��probe
			   ��������������ĳ�ʼ���Ͱ�װ��Ȼ���豸�͹���������

	// �ڶ�����mach-x210.c�������Ӧ�� struct platform_device xxx_device

	// 1��4���Զ���ɡ���Ҫ���2��3�����ṩplatform_device��platform_driver

5.5.5.2�����������platform����ע��
	(1) ÿ�����ߣ�������platform��usb��i2c��ЩҲ�ǣ������һ��match����
		match���������������µ�device��driver����ƥ�䡣������ÿ�����ߵ�
		ƥ���㷨�ǲ�ͬ�ģ�����ʵ����һ�㶼�ǿ�name�ġ�
	(2) platform_match��������ƽ̨���ߵ�ƥ�䷽�����ú����Ĺ��������ǣ�
		�����id_table��˵����������֧�ֶ���豸��������ʱ��Ҫȥ�Ա�
		id_table�����е�name��ֻҪ�ҵ�һ����ͬ�ľ�ƥ�����˲������ˣ�
		�������id_table����û�ҵ���˵��ÿƥ���ϣ����û��id_table��
		��ÿƥ���ϣ��Ǿ�ֱ�ӶԱ�device��driver��name�����ƥ���Ͼ�ƥ
		�����ˣ������ûƥ�����Ǿ�ƥ��ʧ�ܡ�

struct bus_type
{
	const char *name;
	
	int (*match)(struct device *dev, struct device_driver *drv);	// not usb_device or platform_device
}

static int platform_match(struct device *dev, struct device_driver *drv)
{
	struct platform_device *pdev = to_platform_device(dev);
	struct platform_driver *pdrv = to_platform_driver(drv);
}


// ����device�ṹ�壬���ýӿ�ע��
static struct platform device smdk_backlight_device =
{
	.name = "pwm-backlight",
	.id  = -1,
};

ret = platform_device_register(&smdk_backlight_device);

// ͨ��name������Ӧdriver
drivers/video/backlight
static int __init pwm_backlight_init(void)
{
	return platform_driver_register(&pwm_backlight_driver );
} 

//device.h
//mach-mini2440.c
5.5.6.platformƽ̨���߹���ԭ��3
5.5.6.1����leds-s3c24xx.cΪ��������platform�豸��������ע�����
	(1) platform_driver_register
	(2) platform_device_register

5.5.6.2��platdata��ô��			// ������resource�ṹ��
	(1) platdata��ʵ�����豸ע��ʱ/*�ṩ���豸�йص�һЩ����*/
		��Ʃ���豸��Ӧ��gpio��ʹ�õ����жϺš��豸���ơ���������
	(2) ��Щ�������豸������match֮�󣬻����豸��ת���������������õ���Щ���ݺ�
		ͨ����Щ���ݵ�֪�豸�ľ�����Ϣ��Ȼ���������豸��
	(3) �������ĺô��ǣ�����Դ���в�Я�����ݣ�ֻ�����㷨����Ӳ���Ĳ�����������
		�ִ����������������㷨�����ݷ��룬�������̶ȱ��������Ķ����Ժ���Ӧ��

5.5.6.3��match�����ĵ��ù켣
5.5.6.4��probe�����Ĺ��ܺ�����

// ����˼�룺���ݺ������Ƿ���ġ�leds-s3c24xx.c���������������豸������Ľṹ��
// devices��driver��nameƥ���Ϻ󣬻��Զ�ִ��probe��������ִ��led_classdev_register()������Ӧ���豸�ļ��ڵ�

// ��ǰ����������ɲٿ�led1תΪ����led2����Ҫ�޸Ĵ���û�У�

5.5.7.ƽ̨����ʵ������1
5.5.7.1���ع�
5.5.7.2���ȳ����������platform_driver
(1)��1�������޸�ԭ���Ĵ��뵽ֻ��led1
(2)��2����
5.5.7.3��ʵ���������


5.5.8.ƽ̨����ʵ������2
5.5.8.1�����mach-x210.c���Ƿ���led��ص�platform_device
5.5.8.2���ο�mach-mini2440.c�����led��platform_device����
5.5.8.3������ֻ��platform_deviceû��platform_driverʱ��������


5.5.9.ƽ̨����ʵ������3
5.5.9.1������platform_device��platform_driver����ʱ������
5.5.9.2��probe����
	(1) probe����Ӧ����ʲô
	(2) probe���������ݴ�������
	(3) ���ʵ��

5.5.10.ƽ̨����ʵ������4

x210-led.c	

// linux/device.h

struct device_attribute
{
	struct attribute	attr;
	ssize_t (*show)(struct device *dev, struct device_attribute *attr, char *buf);
	ssize_t (*store)(struct device *dev, struct device_attribute *attr, const char *buf, size_t count);
};

#define DEVICE_ATTR(_name, _mode, _show, _store) \
struct device_attribute dev_attr_##_name = __ATTR(_name, _mode, _show, _store)

#define __ATTR(_name,_mode,_show,_store) { \
	.attr = {.name = __stringify(_name), .mode = _mode },	\
	.show	= _show,					\
	.store	= _store,					\
}

// x210-led.c
static DEVICE_ATTR(led1, 0666, x210_led_read, x210_led_write);

struct device_attribute dev_attr_led1 =
{
	.attr =
	{
		.name = led1,
		.mode = 0666,
	},
	.show = x210_led_read,
	.store = x210_led_write,
}


