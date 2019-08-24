
5.8.1.3��input��ϵͳ���
	(2) input��ϵͳ��4�����֣�Ӧ�ò� + input event + input core + Ӳ������

5.8.2.1��ȷ���豸�ļ���
	(1) Ӧ�ò�������������ַ�����/devĿ¼�µ��豸�ļ���/sysĿ¼�µ������ļ�	// /dev/input/eventn

5.8.2.2����׼�ӿڴ򿪲���ȡ�ļ�
	(3) struct input_event				// #include <linux/input.h>

5.8.4.1��input��ϵͳ��Ϊ����
	(1) �ϲ㣺	�¼�������		// evdev.c��mousedev.c��joydev.c
	(2) �м�㣺���Ĳ�			// input.c
	(3) �²㣺	�豸������		// drivers/input/xxx

5.8.4.2��input���豸������������
	(1) �¼������㡢���Ĳ㲻��Ҫ��д��
	(2) ���ú��Ĳ㶨��Ľӿڣ�����豸������

5.8.6.������Ĳ�Դ�����1
5.8.6.1������ģ��ע��input_init()
	(1) class_register()			// �����ļ���ʵ��device_register()
	(2) input_proc_init()
	(3) register_chrdev()

	// class_create()	class_register()

5.8.6.2�����Ĳ�Ϊ�豸�������ṩ�Ľӿں���	// ���Ĳ�Ϊ�¼��������ṩ�Ľӿں���
	(1) input_allocate_device()
	(2) input_set_capability()
	(3) input_register_device(struct input_dev *dev)

	// register -- ����Ӳ����ؽṹ���������䣬������Ӧ�ӿں���(���ʵ��)ע��

5.8.7.������Ĳ�Դ�����2
5.8.7.1��handler��device��ƥ��
 -- input_for_each_entry(handler, &input_handler_list, node)	// ��������
  |
  | -- input_attach_handler(dev, handler);
	 |
	 | -- input_match_device()		// ƥ��device��handler
	 |
	 | -- handler->connect(handler, dev, id)	// ƥ���Ϻ󣬹ҽ�device��handler

//  handler�������ϲ�(�����¼�������)
//  handler���ã�ΪӦ�ò��ṩ�ӿ�(/dev/input/eventX)����������

//  �ں�������������handler������handler��device(usb��serial)ƥ��	\
	ע��һ�����豸ʱ�����豸��4��handler����ƥ��					\
	�󶨺���Ӧ�ò�������Ӧ���豸�ļ���ΪӦ�ò��ṩ���ʽӿ�			\
	�󶨺��豸���������¼����ϱ�����Ӧhandler						\
	handler�����ݰ���һ����ʽ���뻺������������read������app

// Handlers: Keyboard Handlers��Mouse Handlers��Joystick Handler��Event Handler(����)

5.8.7.2�����Ĳ�Ϊ�¼��������ṩ�Ľӿں���
	(1) input_register_handler(&mousedev_handler)		// mousedev.c
	(2) input_register_handler(&evdev_handler)			// evdev.c

	static const struct input_device_id evdev_ids[] = 
	{
		{ .driver_info = 1, },		// match all devices
	}

5.8.8.�¼�������Դ�����
	(1) struct input_handler
		{
			void *private;			// for special data
			void (*event)(...);		// ����ײ��ϱ������ݣ�����struct input_event�ṹ�������appʹ��
			void (*match)(...);		// û��ʹ�ã�ʹ�ú��Ĳ��ṩ��match()
			int (*connect)(...);	// ��handler��deviceƥ��󣬵���connect
			
			const struct file_operations *fops;		// ӳ��app���fops
		}

	(2) -- evdev_read()
		 |
		 | -- if (count < input_event_size())	// read(fd, &buf, sizeof(struct input_event));
		 |
		 | -- retval = wait_event_interruptible();		// block
		 |
		 | -- input_event_to_user();		// copy_to_user()

	(3) -- evdev_connect()
		 |
		 | -- device_initialize(&evdev->dev)
		 |
		 | -- device_add(&evdev->dev)		// device_register() -- /dev/input/eventxxx

	(3) -- evdev_event()
		 |
		 | -- struct input_event event;
		 |
		 | -- event.xxx = xxx; 	// event���
		 |
		 | -- evdev_pass_event()
		    |
			| -- client->buffer[client->head++] = *event	// event���뻺����
			|
			| -- kill_fasync(&client->fasync, SIGIO, POLL_IN)	// ֪ͨӦ�ò�

5.8.9.1�����ҵ�bsp�а�������Դ��
	(1) cat /dev/input/event0		// ���°������ж��Ƿ��з�Ӧ���ж������Ƿ����
	(2) /driver/input/keyboard		// ��Makefile�ж���Щ�ļ������룬��ֱ��ȥԴ�����¼��
	(3) cat /sys/input/eventx/name 	// ͨ���豸name�����ļ�����Դ������������ļ�

5.8.9.3��Դ��ϸ��ʵ�ַ���
	(1) gpio_request()
	(2) input_allocate_device()
	(3) input_register_device()
	(4) timer()

5.8.11.1��ģ��	// input_programming.txt

5.8.12.�жϷ�ʽ��������ʵս2
// mach-s5pv210/include/mach/irqs.h		-- OS���жϵ�ͳһ���
// kernel/include/linux/interrupt.h
// proc/interrupts

// Ӧ�ò�û��syc��ӡ -- ������û��set_bit(EV_SYNC, input->evbit)

// timer.expires = jiffies + (HZ/100)
// ʱ��� �� ʱ���
// jiffies ��ǰʱ���
