
5.3.1.1���½ӿ����Ͻӿ�
	(1) �Ͻӿڣ�register_chrdev		// �豸��(ֻ�����豸�ţ��޴��豸��)	fops
	(2) �½ӿڣ�register_chrdev_region/alloc_chrdev_region + cdev	// struct cdev

		// ע���豸�ź������Ƿֿ���

5.3.1.2��cdev����
	(2) ��غ�����cdev_alloc()��cdev_init()��cdev_add()��cdev_del()

5.3.1.4�����ʵ��
	(1) register_chrdev_region(), cdev_init(), cdev_add(), unregister_chrdev_region()

// 200 0 1 2 3

// from MKDEV(200, 0)
// count 4

5.3.2.1��alloc_chrdev_region()�Զ������豸��

5.3.2.2���õ���������豸�źʹ��豸��	// MKDEV(), MAJOR(), MINOR()
	*/note: dev_t device_dec; unsigned int device_major;

5.3.2.3����;����ĵ�Ӱʽ��������	// note: goto��� ��Դ�ͷ�

5.3.4.1��ʹ��cdev_alloc

5.3.4.2��cdev_init�����
	// cdev->owner = THIS_MODULE;
	// cdev->ops = &fops;

5.3.5.�ַ��豸����ע��������1
5.3.5.1���Ͻӿڷ���
 -- register_chrdev()
  |
  | -- __register_chrdev()
  |
  | -- __register_chrdev_region()
  |
  | -- cdev_alloc()
  |
  | -- cdev_add()

5.3.5.2���½ӿڷ���
 -- register_chrdev_region()
  |
  | -- __register_chrdev_region()

 -- alloc_chrdev_region()
  |
  | -- __register_chrdev_region()

  // ��Ƶ6 17�� kzalloc()����
  
  kernel/drivers/base/map.c -- kobj_map()		// baseĿ¼��Ϊ�����ܹ�

5.3.7.2��udev��Ƕ��ʽ���õ���mdev��
	(2) �ں�������/*Ӧ�ò�udev*/֮����һ����Ϣ������ƣ�netlinkЭ�飩
	(3) Ӧ�ò�����udev���ں�������ʹ����Ӧ�ӿڣ�����ע���ע��ʱ��Ϣ�ᱻ
		����udev����udev��Ӧ�ò�����豸�ļ��Ĵ�����ɾ��
		// uevent -> udev

5.3.7.3���ں������豸����غ���
	(1) class_create()
	(2) device_create()
	(3) device_destory()
	(4) class_destroy()

	// lrwxrwxrwx 1 0 0 0 Jan  1 13:43 led_device_test -> ../../devices/virtual/led_class_test/led_device_test

5.3.8.1��sys�ļ�ϵͳ���
	(1) sys�ļ�ϵͳ�����˼��
	(2) �豸��ĸ���
	(3) /sys/class/xxx/�е��ļ�������

5.3.10.��̬ӳ��������̷���
	(1) ӳ���PA��VA��صĺ궨��
	(2) ӳ���������mach-smdkc110.c/smdkc110_map_io()

 -- smdkc110_map_io()
  |
  | -- s5p_init_io()
     |
	 | -- iotable_init(s5p_iodesc, ARRAY_SIZE(s5p_iodesc))

//	��������������ģ���ַ�ռ䣬�����ַ�ľ�̬ӳ�䡣 -- �ֶ�����s5p_iodesc

(3) ����ʱ����ӳ���������
 -- setup_arch()
  |
  | -- paging_init()
     |
	 | -- devicemaps_init()
	    |
		| -- if (mdesc->map_io)
		   |
		   | -- mdesc->map_io();

5.3.12.2���ں��ṩ�ļĴ�����д�ӿ�
	(1) writel()��readl()
	(2) iowrite32()��ioread32()
