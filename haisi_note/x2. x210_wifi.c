
3.1�������������ȷ��
	(1) mount -t nfs -o nolock 192.168.1.77:/home/aston/src/rootfs/rootfs /opt
	(2) DPO_MT7601U_LinuxSTA_3.0.0.4_20130913.tar.bz2	// Դ���
	(3) lsusb�鿴������VID��PID
		Bus 001 Device 003: ID 148f:7601

4.����Դ���޸ļ�����
	(1) ����Դ��� make clean
	(2) ȷ��USB��VID��PID	// usb_dev_id.c	 -- driver��dev���
	(3) ȷ�ϸ�Դ���Ƿ�֧�ָ��豸id	// USB_DEVICE_ID rtusb_dev_id[];

4.2���޸�Makefile
	(1) PLATFORM 		=	SMDK
	(2) LINUX_SRC 		= 	linux-src-tree
	(3) CROSS_COMPILE	= 	arm-linux-

	// �޸�Makefile����Դ�룺ARCH CROSS_COMPILE
	// �������� -- Դ����Ŀ¼

4.3���޸���������(��ѡ)
	(1) ���������������ƣ�rax��wlanx
	(2) �޸�include/rtmp_def.h�ļ�
		#define INF_MAIN_DEV_NAME "ra"
		#define INF_MBSSID_DEV_NAME "ra"

4.4�����wpa_supplicant֧��
	ȷ��config.mk�ļ���WPA_SUPPLICANT=y		// ��driverԴ���Ŀ¼ find -name "config.mk"

4.5��������������ģ��	// os/linux/mt7601Usta.ko
	// modinfo xxx.ko
	// �Ա��ں��ϵ��ӡ�� vermagic

5.1������Դ�����
	// �����ҵ�Դ�����  -- ����driver�������� module_init()

	// �ڹ���Դ������������
	// �������Makefile�����ýű��ж���

	// �� make clean
	// �� grep "MT7601U" * -nR

	 -- os/linux/config.mk:674
	 WFLAG += -DMT7601U

	// ���ù����У�ͨ��-D���ݷ���

6.1��iwconfig���߼��Ľ��ܺ�ʹ����ʾ		 // busybox�Ѿ����ɸ�����
	(1) linux��ר�����������������һЩ���
	(2) ��Ϊiwconfig������һ�����ƣ�ֻ֧��һ���ļ��ܸ�ʽ

	/* һ���������������Թ�����sta��APģʽ */

7.1��wpa_supplicant�����ļ�		// ����WiFi
	(2) /etc/Wireless/RT2870STA/RT2870STA.dat
	(3) /etc/wpa_supplicant.conf	// wpa���������ļ�

7.2������������������
	insmod mt7601Usta.ko

	ifconfig ra0 up 	//������������ -- ��Ҫxxx.dat�����ļ�

	wpa_supplicant -B -c /etc/Wireless/RT2870STA/wpa_supplicant.conf -i ra0
	wpa_cli -i ra0 status

	ifconfig ra0 192.168.0.166
	ping 192.168.0.1

	route add default gw 192.168.0.1 dev ra0
	ping 8.8.8.8

	vi /etc/resolv.conf
	nameserver 192.168.0.1

	ping www.baidu.com   

8.2��ʹ��dhcp��̬����IP		// udhcpc -i ra0

9.���Լ����Ƶ�rootfs����ֲ����
9.1��ȷ���Լ�������rootfs������
	(1)busybox�������
	(2)������ֱ��nfs��ʽ�����ļ�����ʽ��rootfs������ok�������ɾ�����¼
	(3)���ز���bootargs��setenv bootargs root=/dev/nfs nfsroot=192.168.1.141:/root/rootfs ip=192.168.1.10:192.168.1.141:192.168.1.1:255.255.255.0::eth0:off  init=/linuxrc console=ttySAC2,115200 

	set bootcmd 'tftp 30008000 zImage; bootm 30008000'
	
	// tftp����������
	
9.2����Ҫ�Ĺ��߼�ȷ��
	(1) iwconfig���߼���������ֲ�ģ�����busybox�е�
	(2) dhcp���߼�(udhcpc)����busybox�м��ɵģ�ȷ��busybox��menuconfig������֧�������
	(3) wpa_supplicant���߼���������ֲ�ģ�����busybox�е�

9.3���������iwconfig
	(1)Դ������
	(2)����
	(3)�������
	(4)����װ 	// file iwconfig -- dynamic linked  -- ��װ�� /lib/libiw.so
	(5)����
	
	PREFIX = /home/aston/src/rootfs/rootfs
	INSTALL_DIR=$(PREFIX)/sbin/
	
	// make
	// make install


10_11.��ֲwpa_supplicant����������1_2
10.1���������wpa_supplicant
(1)����wpa_supplicantԴ�벢���ñ��롣�ο�http://blog.csdn.net/hktkfly6/article/details/48949863
(2)�������װ汾��openssl�����ñ���
(3)ȥ������NL��ص�ѡ��ʡȥ��ֲlibnl���ο���http://www.cnblogs.com/helloworldtoyou/p/6145995.html
10.2����nfs�в���wpa_supplicantʹ��
10.3������ext2����ˢ������

����/etc/wpa_supplicant.conf�ļ����ݣ�
ctrl_interface=/var/run/wpa_supplicant

network={
        key_mgmt=WPA-PSK			// error
        ssid="zhulaoshi"
        psk="www.zhulaoshi.org"
}

// chmod -R 777 /var/

insmod /wifi_driver/mt7601Usta.ko
ifconfig ra0 up
wpa_supplicant -Dwext -ira0 -c/etc/Wireless/RT2870STA/wpa_supplicant.conf &
wpa_cli -i ra0 status








