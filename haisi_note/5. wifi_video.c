
�ڶ����֡��½ڽ���
5.1.��˼ƽ̨��USB WIFI��ֲ����
	���ڽ��Ȿ���γ̵�������ǰ��صĿγ̣��ô�Ҷ�USB WIFI��ֲ�и��ƻ���
5.2.APģʽUSB WIFI������ֲ
	���ڴ�����ְ�����ֲUSB WIFI��APģʽ�µ�����Դ�롣
5.3.APģʽUSB WIFI������Ƶʵս
	�����ְ��ִ���Ҳ���USB WIFI�������������ã�ʹ��Windows���ӿ���������Ƶ���䡣
5.4.USB WIFI��staģʽ��������ֲ�Ͳ���
	���ڴ�����ְ�����ֲUSB WIFI��staģʽ�µ�����Դ�롣
5.5.��ֲwpa_supplicant
	���ڴ�����ְ�����ֲwpa_supplicant�Լ�openssl�������linux�¹���wifi��������
5.6.USB WIFI��staģʽ��ORTP��Ƶ����ʵ��
	�����ְ��ִ���Ҳ���staģʽ��USB WIFI����������·������ʹ��Windows���ӿ���������Ƶ���䡣
5.7.��WIFI���ߵ��Ի����Ĵ
	���ڽ������ubuntuҲ��������ʵ�ֿ����塢windows�������ubuntu������Ϊsta����·�����������������ã������Զ����ߵ��ԡ�
	
	// ͼ��ģ��

5.1.2����ֲ�����
(1)�� ���γ̣�
(2)����USB WIFI�����ٷ���ֲƥ������������ֲ
(3)���ں�˼SDK���Ѿ���������ں�Դ��������������
5.1.3�������γ̰���
(1)HI3518E+WIFI��AP��PC��sta��ʵ�־�������ortp��Ƶ����
(2)HI2518E+WIFI��sta��PC��sta���ⲿ·������AP��ʵ�־�������ortp��Ƶ����
(3)HI2518E+WIFI��sta��PC��sta���ⲿ·������AP��ʵ��ȫ�����ߵ��ԣ����ײ�������������


5.2.APģʽUSB WIFI������ֲ
5.2.1��Դ��
(1)���Ƶ�ubuntu��ʵ��Ŀ¼
(2)��ѹ����
5.2.2���޸���ֲ
(1)include/rtmp_def.h��1627�����ң��޸�������ʼ��Ϊ��wlan
(2)ʹ���ṩ��Makefile�滻��ԭ����Makefile
(3)./os/linux/config.mk������EXTRA_FLAGS
(4)�޸�Makefile�����ֹ�����xx.ko��/home/aston/rootfs��


5.3.APģʽUSB WIFI������Ƶʵս
5.3.1������USB WIFI����ʹ֮����ΪAP
(1)��lsusb��Ȼ�����USB WIFIģ�飬��lsusb��ȷ��ģ�鱻ʶ����
(2)�ڿ������в��� /etc/Wireless/RT2870AP/RT2870AP.dat�����޸����¼���������
	SSID=MT7601AP_WPA���������������pc���Ͽ���������ssid����
	AuthMode=WPA2PSK�����ܷ�ʽ��
	EncrypType=TKIP;AES
	WPAPSK=1234567890����������룩
(3)insmod xx.ko��װUSB WIFI����ģ��
(4)ifconfig -a���Ƿ���wlan0
(5)ifconfig wlan0 up, ifconfig wlan0 192.168.0.100
(6)ifconfig�鿴��ȷ��wlan0��������
(7)��PC���ֻ���WIFI������һ�£��Ƿ���һ����Ϊ��MT7601AP_WPA�������ˣ����˾ͳɹ���
(8)��PCǿ�Ʒ��侲̬IP
5.3.2����������׼��
(1)ORTP�汾��sample��common/sample_common_venc.c�У��޸�LOCAL_HOST_IPΪ192.168.0.30
(2)make clean��make
(3)���Ƶõ���sample_venc��/home/aston/rootfs��
5.3.3������ʵ��
(1)������ˣ�cp /mnt/sample_venc /home/	Ȼ��cd /home
(2)�ε����ߣ���ʱҲ���������¿������Գ�������ǰ���Ӱ�죩
(3)PC��WIFI���� MT7601AP_WPA���������� 1234567890
(4)PC��������������ľ�̬IP��ַΪ��192.168.0.30
(5)PC��cmdȥping 192.168.0.100�����߷������������ping PC������IP
(6)�������ִ�� ./sample_venc
(7)PC�˴�vlc��������ʹ�õ�3���е�sdp���ã�ע��c=IN IP4 192.168.0.100�����ܲ����ˡ�
ע��
���ߣ�
windows��	192.168.0.30
AP��		192.168.0.100
ubuntu��	192.168.0.50	��ubuntu��IP���ڿ��Բ��ܣ�

���ߣ�
windows��	192.168.1.20
�����壺	192.168.1.10
ubuntu��	192.168.1.141


5.4.USB WIFI��staģʽ��������ֲ�Ͳ���
5.4.1��Դ���޸�
(1)��sta�汾��driver�����Լ򵥿�һ������
(2)�޸�makefile���ο�APģʽ�µ��޸ĵ��޸�
(3)config.mk���޸ģ��ο�APģʽ�µ��޸ĵ��޸�
(4)�޸���������Ϊwlan
(5)make clean && make
5.4.2����������
(1)����/etc/Wireless/RT2870STA/RT2870STA.dat 
(2)����ko


5.5.��ֲwpa_supplicant
5.5.1��Դ������
(1)wpa_supplicant	 http://hostap.epitest.fi/wpa_supplicant/
(2)openssl			 ftp://ftp.openssl.org/source/old/0.9.x/
����openssl-0.9.8za.tar.gz
�ֱ�tar -zxvf��ѹwpa_supplicant-2.5.tar.gz��openssl-0.9.8za.tar.gz��
5.5.2����ֲopenssl
(1)��openssl�򲹶�����wpa_supplicant-2.5�����patches�ļ����µ�openssl-0.9.8za-tls-extensions.patch�ļ�������openssl-0.9.8zaĿ¼�£����У�patch -p1 < openssl-0.9.8za-tls-extensions.patch
(2)�޸�Makefile
CC=arm-hisiv300-linux-gcc
AR=arm-hisiv300-linux-ar $(ARFLAGS) 
RANLIB=arm-hisiv300-linux-ranlib

INSTALLTOP = /tmp/openssl
OPENSSLDIR = /tmp/openssl
(3)make && make install
(4)�������
****Expected text after =item, not a number
****Expected text after =item, not a number
****Expected text after =item, not a number
****Expected text after =item, not a number
ԭ��OpenSSL �� perl�汾������
���������rm -f /usr/bin/pod2man 
5.5.3����ֲwpa_supplicant
(1)��ѹ��������Ŀ¼
(2)cp /wpa_supplicant/defconfig .config
(3)�޸�.config�������������ݣ�
CC=arm-hisiv300-linux-gcc -L/tmp/openssl/lib
CFLAGS+=-I /tmp/openssl/include
LIBS+=-L/tmp/openssl/lib
(4)make		���������
driver_nl80211.c:17:31: fatal error: netlink/genl/genl.h
����wpa_supplicantĿ¼��.config 
��CONFIG_DRIVER_NL80211=y ע�͵�����
(5)����make������wpa_supplicant��wpa_cli��������ֲ�ɹ����


5.6.USB WIFI��staģʽ��ORTP��Ƶ����ʵ��
5.6.1������wpa_supplicant
(1)��wpa_supplicant��wpa_cli����������/usr/local/binĿ¼��
(2)���������ļ�/etc/wap_supplicant.conf���������£�
	ctrl_interface=/var/run/wpa_supplicant

	network={
	ssid="ZLSWLW-2"
	scan_ssid=1
	key_mgmt= WPA-EAP WPA-PSK IEEE8021X NONE
	pairwise=TKIP CCMP
	group=CCMP TKIP WEP104 WEP40
	psk="justdoit1234"
	}
5.6.2��staģʽ��USB WIFI����
(1)��װ���� insmod mt7601Usta.ko
(2)���þ�̬IP��ַ
ifconfig wlan0 up, ifconfig wlan0 192.168.0.233
(3)������sta����AP	��-dd�򿪵�����Ϣ��
wpa_supplicant -Dwext -iwlan0 -c/etc/wpa_supplicant.conf -dd &
(4)�鿴����״̬
wpa_cli -i wlan0 status      
(5)��������Ч��
ping 192.168.0.1		������AP��
route add default gw 192.168.0.1 dev wlan0
ping 8.8.8.8			��google��dnw server��
ping www.zhulaoshi.org
5.6.3��ORTP��Ƶ�������
(1)�޸�LOCAL_HOST_IP Ϊ192.168.0.100�����ҵ�Widnows��WIFI�Զ������IPһ����
(2)����õ�sample��������������
(3)�޸�sdp��c=IN IP4 192.168.0.232,��sdp����
ע��
AP��		192.168.0.1
PC��		192.168.0.100
�����壺	192.168.0.233
ubuntu��	192.168.0.244


5.7.��WIFI���ߵ��Ի����Ĵ
5.7.1��ԭ��
(1)UBUNTU��Windows�Žӣ�����ubuntu��windows�����������߶���sta����ͬһ��AP
(2)������������ֲ�����USB WIFI������wpa_supplicant��
(3)������/etc/profile����ƺ�����WIFI����������AP����̬IP��
(4)������/etc/profile�������ÿ�����ͨ������mount�����
5.7.2��ʵս
(1)��ȷ�Ͽ����岿���USB WIFI������wpa_supplicant����
(2)sample�ŵ������ubuntu�Ĺ����ļ�����
(3)������/etc/profile�����ø�������
(4)����ubuntu�Žӵ�windows����������������ubuntu���þ�̬IP��ַ
(5)��������������Ч��

#ifconfig eth0 192.168.1.10
#mount -t nfs -o nolock 192.168.0.103:/home/aston/rootfs /mnt
cd /ko            
./load3518e -i -sensor ar0130 -osmem 32 -total 64
                                           
insmod /home/mt7601Usta.ko                       
ifconfig wlan0 up                          
ifconfig wlan0 192.168.0.233               
wpa_supplicant -Dwext -iwlan0 -c/etc/wpa_supplicant.conf &
route add default gw 192.168.0.1 dev wlan0                   
                                                             
mount -t nfs -o nolock 192.168.0.244:/home/aston/rootfs /mnt
cd /mnt    


// Makefile -- LINUX

// make xxx xxx xxx moudles