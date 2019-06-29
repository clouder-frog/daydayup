
5.2.2.1�����õ�ģ���������
	(1) lsmod
	(2) insmod		// insmod xxx.ko
	(3) modinfo		// modinfo xxx.ko
	(4) rmmod
	(5) modprobe��depmod

	// ����һ��ʵ��Ϊģ��ķ�ʽ
	// �ں�Դ�����±��������������ں�Makefile		\
							 ������װʱ�汾У�鲻����� -- ����vermagicһ��

5.2.2.2��ģ��İ�װ��ж��
	(2)	module_init(chrdev_init)		// insmod xxx.koʱ�Զ�����chrdev_init()
	(3) module_exit(chrdev_exit)		// rmmod xxxʱ�Զ�����chrdev_exit()

5.2.3.2��ģ���г��ú�
	(1) MODULE_LICENSE
	(2) MODULE_AUTHOR
	(3) MODULE_DESCRIPTION
	(4) MODULE_ALIAS

5.2.3.3���������η�
	(1) __init		// #define __init	__section(.init.text) __cold notrace
		�ں�����ʱͳһ����.init.text���е�ģ�鰲װ�������������ͻ�������
		���ͷŵ��Խ�ʡ�ڴ�

	(2) inline
		Ч��
		��ֹͷ�ļ�����ĺ���������ʱ�ظ�����
		// ͷ�ļ��ж���������ṹ�屣�����ܷ�ֹ����error�����ӿ���error

5.2.4.1��printk�������			// for kernel not app
		cat /proc/sys/kernel/printk		// ��һ�����֣�����ԽС����Խ��
		// ubuntu��dmesg�鿴printk��ӡ��Ϣ

	(5) ubuntu�����printk�Ĵ�ӡ�������û��ʵ����ubuntu�в�����Ѽ�����ô
		���ö�����ֱ�Ӵ�ӡ����������dmesg����ȥ�鿴

5.2.4.2����������ģ���е�ͷ�ļ�
	(1) ����Դ�����а�����ͷ�ļ���ԭ��Ӧ�ñ�̳����а�����ͷ�ļ�����һ����

		Ӧ�ñ���а�����ͷ�ļ���Ӧ�ò��ͷ�ļ�����Ӧ�ó���ı�����(gcc)�ṩ
		gcc��ͷ�ļ�·��/usr/include���Ͳ���ϵͳ�޹�

		����Դ�������ں�Դ���һ���֣�����Դ���е�ͷ�ļ���ʵ�����ں�Դ����Ŀ¼
		�µ�includeĿ¼�µ�ͷ�ļ�

5.2.4.3�����������Makefile����
	(1) KERN_DIR��������ֵ�������������������ģ����ں�Դ������Ŀ¼
	(2) obj-m += module_test.o					// obj-m
	(3) make -C $(KERN_DIR) M=`pwd` modules		// make modules

		make -C���뵽ָ�����ں�Դ����Ŀ¼��
		Ȼ����Դ��Ŀ¼����/*����*/�ں�Դ���ж����ģ��������ȥ�������ģ��
		������ɺ�����ɵ��ļ�����������ǰĿ¼��	// ͨ��M=`pwd`ʵ��

5.2.5.�ÿ�����������ģ��
	// uname				Linux
	// uname -r				3.13.0-32-generic
	// Ubuntu�ں�Դ����		/lib/modules/3.13.0-32-generic/build

5.2.6.1��ϵͳ���幤��ԭ��
	(1) Ӧ�ò�->API->�豸����->Ӳ��
	(2) API��open��read��write��close��
	(3) ����Դ�����ṩ������open��read��write��close�Ⱥ���ʵ��

5.2.6.2��file_operations	/* kernel/include/linux/fs.h */
	(1) Ԫ����Ҫ�Ǻ���ָ�룬�����ҽ�ʵ����������
	(2) ÿ���豸��������Ҫһ���ýṹ�����͵ı���
	(3) �豸�������ں�ע��ʱ���ṩ�ýṹ�����͵ı���

5.2.7.1��register_chrdev	/* fs.h */

5.2.7.2���ں���ι����ַ��豸����
	(1) �ں��ýṹ������洢ע����ַ��豸����
	(3) cat /proc/devices�鿴�ں����Ѿ�ע���char devices��block devices
	(4) ���豸��(major)�����豸��ţ�Ҳ���豸�������±�

5.2.8.�ַ��豸��������ʵ��1		// ���岢���file_operations��ע������
	// make && make cp

5.2.10.1�������豸�ļ��Ĵ���
	(2) �豸�ļ��Ĺؼ���Ϣ�������豸�ţ�ʹ��ls -lȥ�鿴�豸�ļ�
		�Ϳ��Եõ�����豸�ļ���Ӧ�������豸��
	(3) ʹ��mknod�����豸�ļ���mknod /dev/xxx c ���豸�� ���豸��

	// vi /dev/led_test			-- �豸�ļ�һ�㲻��vi��
	// ls -l /dev/led_test

5.2.11.��Ӷ�д�ӿ�
	(1) copy_from_user()
		���������ݴ��û��ռ临�Ƶ��ں˿ռ�
		�ɹ������򷵻�0��������ɹ������򷵻���δ�ɹ�����ʣ�µ��ֽ���

	(2) copy_to_user()

	// ע�����ָ��ƺ�mmap��ӳ��

5.2.13.��������βٿ�Ӳ���������
	(1) �Ĵ�����ַ��ͬ�������ַתΪ�����ַ
	(2) ��̷�����ͬ�������ֱ���ú���ָ�������kernel�÷�װ�õ�io��д��������
		�߿���ֲ��

5.2.14.2�����ǰ汾�ں��еľ�̬ӳ���
	(1) ��ӳ���λ�ڣ�arch/arm/plat-s5p/include/plat/map-s5p.h
	(2) �����ַ����ַ�����ڣ�arch/arm/plat-samsung/include/plat/map-base.h
	(3) GPIO��ص���ӳ���λ�ڣ�arch/arm/mach-s5pv210/include/mach/regs-gpio.h
	(4) GPIO�ľ���Ĵ�������λ�ڣ�arch/arm/mach-s5pv210/include/mach/gpio-bank.h

5.2.17.1����̬ӳ�佨��������
	(1) request_mem_region() ���ں����루���棩��Ҫӳ����ڴ���Դ
	(2) ioremap() ���������ַ�����������ַ
	(3) iounmap()
	(4) release_mem_region()		// ע���Ⱥ�˳��


