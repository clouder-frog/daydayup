
5.7.1.1��ʲô��framebuffer			// fb
	(5) fb��һ�����͵��ַ��豸�����Ҵ�����һ����/sys/class/graphics

5.7.1.2��framebuffer��ʹ��
	(1) �豸�ļ� /dev/fb0
	(2) ��ȡ�豸��Ϣ #include <linux/fb.h>	// ioctl(fd, FBIOGET_VSCREENINFO, &var_info);
	(3) mmap��ӳ��
	(4) ���framebuffer

5.7.5.1��������ܲ���
	(1) drivers/video/fbmem.c		// �������
	(2) drivers/video/fbsys.c		// fb��/sysĿ¼�µ������ļ�
	(3) drivers/video/modedb.c		// ��ʾģʽ����
	(4) drivers/video/fb_notify.c

5.7.5.2����������
	(1) drivers/video/samsung/s3cfb.c		// ��������
	(2) drivers/video/samsung/s3cfb_fimd6x.c	// lcdӲ����������
	(2) arch/arm/mach-s5pv210/mach-x210.c	// �ṩplatform_device
	(3) arch/arm/plat-s5p/devs.c	// �ṩdevice�����Ϣ

5.7.8.2��ע��ǼǸ�fb�豸
	(1) registered_fb[i] = fb_info;		// ���ݵ���䡢���ݡ�ʹ��

5.7.9.1��s3cfb.c
	(2) static struct platform_driver s3cfb_driver = {};

5.7.9.2��s3c_device_fb
	(1) struct platform_device s3c_device_fb = {};

5.7.10.1��probe��������
	(1) struct s3c_platform_fb
	(2) struct s3cfb_global		// ����s3cfb.c��s3cfb_fimd6x.c�����ļ���������

5.7.11.1��struct s3cfb_lcd			//  lcd param

5.7.11.4��resource�Ĵ���
	(1) platform_device���ṩresource�ṹ������
	(2) probe��platform_get_resourceȡ��resource���Ұ�FLAG��ͷ����

// free fbdev
// line921 fbdev

5.7.12.1��lcd�Ĵ������Ӳ������
	(1) s3cfb_set_vsync_interrupt()
	(2) s3cfb_set_global_interrupt()
	(3) s3cfb_init_global()

5.7.12.3������ע���fb�豸
	(1) s3cfb_alloc_framebuffer()
	(2) s3cfb_register_framebuffer()

5.7.13.framebuffer��������4
5.7.13.1��һЩӲ������
	(1) s3cfb_set_clock
	(2) s3cfb_set_window
	(3) s3cfb_display_on

5.7.13.2�������д����ж�
	(1) platform_get_irq()
	(2) request_irq()		// �ں˹����¼���е��ж�

5.7.13.3��logo��ʾ
	(1) drivers/video/logo/xxx.ppm
	// �ں˽�ppm�ļ�ת��Ϊstruct logo{}����ֵ

	s3cfb_probe
		fb_prepare_logo
			fb_find_logo
		fb_show_logo
			fb_show_logo_line
				fb_do_show_logo
					info->fbops->fb_imageblit	// file_operation

5.7.14.Ӧ�ò�Ϊ�β������÷ֱ���
5.7.14.1����������
	(1) ��4��ʱ��ͼ��Ӧ�ò����÷ֱ���ʧ���ˣ�ԭ����ڣ�
	(2) ��λ���⣺�϶����������¶�
	(3) ��һ�������ж�λ��ioctl���ֵ��¶�

5.7.14.2��fb��ioctl����
	(1) fb�ǵ��͵��ַ��豸����
	(2) ioctl��Ϊ2���֣���������ܲ��ֺ��������ָ���һ��

5.7.15.�����ں˵�����logo
5.7.15.1����logo��ʾ����Ļ����
5.7.15.2���Զ����ں�����logo

	// logo_x210_clut224.ppm
	
	// logo/Makefile
	
	// logo�ṹ�� �� ppm�ĵڶ���

