
2.13.1.2�������·����
	x210��LCDģ����ʹ��MP3202оƬ��������, PWMTOUT0(GPD0_0)������IC��FB������			// �͵�ƽֱ�ӵ���
	SoCӦ��ͨ�����������һ��Ƶ�ʸ�����IC, ����MP3202����ĵ�����С, �Ӷ�������Ļ����
	L_DISP(DISP��SYS_OE��GPF3_5)������MP3202��EN����, �ߵ�ƽenable

2.13.1.3��X210��uboot��LCD�������		// x210_preboot_init()

2.13.2.1��LCD����mpadfb.c����
	step1: lcd init	// lcd initִ�����, дlcd framebuff�������ʾ
		(1)fb_init()		// ���info
		(2)lcd_port_init()	// port -> gpio	
		(3)lcd_reg_init()	// lcd controller reg init

	step2: write framebuff && open backlight
		(1)display_logo()
		(2)backlight_init()

	// important struct && global variable(init)
	static struct fb_info info = {
		.name		= "fb",
	}
	// fb_info.bitmap.xxx, infoȫ�ֱ�����������Ա������fb_init()�и�ֵ

	static struct fb s5pv210_fb = {
		.info		= &info,
		.map_color	= fb_ft_map_color,
	}

2.13.2.2������°濪����X210BV3S��logo��ʾ����		// lcd����, �ֱ����޸�1024*600

2.13.3.1��ʲô��fastboot		// Androidˢ��: fastboot, recovery

2.13.4.2���ؼ��㣺rx_handler
do_fastboot
	fastboot_poll
		fboot_usb_int_hndlr
			fboot_usb_pkt_receive
				fboot_usb_int_bulkout
					fastboot_interface->rx_handler������ָ�룩
						ָ��cmd_fastboot.c/rx_handler

2.13.4.3���������
(1)���ļ�download����	// usb���䵥�δ������ֻ�����޸��ֽ�(64��256)

(2)down�����Ӧ����, �������ͨ��fastboot_tx_status����������������Ӧ, ������ʾ�����Ӧ

(3)fastboot�йغ궨��
	CFG_FASTBOOT_TRANSFER_BUFFER
	CFG_FASTBOOT_TRANSFER_BUFFER_SIZE		// download max size

