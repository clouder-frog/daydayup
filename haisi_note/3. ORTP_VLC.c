
3.1.2����Ƶ���紫���2�ַ�ʽ
	(1) �������أ�http or ftp
	(2) ����ʵʱ��RTP/RTSP/RTCP

3.1.3��ORTP�Ľ���		// ����RTP��RTCPЭ��ʵ��
	(1) openRTP����Cʵ�ֵ�һ��RTP��	// C++��Javaʵ��
	(2) ʵ����һ����Ƶ������������ʱ�ͻ��˺ͷ�����ʵʱ������Ƶ����
	(3) һ����ΪRTP�����ڴ���㣬������ʵRTP��TCP/UDP��һ�����

3.2.1��׼��Դ��		// https://github.com/dmonakhov/ortp

3.2.2��Դ���޸�
	(1) ����H.264��payload֧��
		��src/avprofile.c��357����ӣ�
		rtp_profile_set_payload(profile,96,&payload_type_h264);

3.2.3�����úͱ��롢��װ
	(1) ����ortpĿ¼ִ��./autogen.sh
	(2) error��./autogen.sh: line 44: libtoolize: command not found
	    �����sudo apt-get install libtool*		// not libtoolize
	(2) error��libtoolize:   error: Please install GNU M4, or 'export M4=/path/to/gnu/m4'.
	    �����sudo apt-get install m4
	(3) error��Automake - aclocal: command not found 
	    �����sudo apt-get install automake

	(4) ����ִ��./configure --prefix=/tmp/ortp --host=arm-hisiv300-linux

	(5) make && make install

3.2.4����/tmp/ortpĿ¼�²鿴��ֲ�õĿ��ͷ�ļ�

3.3.1���ڹٷ�SDK��sample�����rtp�������
	(1) venc/sample_venc.c				// channel num
	(2) common/sample_common_venc.c		// handle video stream

3.3.2�����±���sample
	(1) ���ortpͷ�ļ�		// warning: ��������, error: ���Ͷ���
	(2) �޸�venc/Makefile		// -lortp -L /home/aston/src/ortp/ortp_lib/lib

3.3.3���������в������в���
	(1) ����libortp.so����������/usr/libĿ¼��
	(2) ��鿪������ԭ�������Ƿ���ȷ��Ʃ��sensor�Ƿ��Ӧʵ��
	(3) ��nfs�������µ�sample����
	(4) vlc�д����úõ�sdp�ļ�

//  makefile -- -lpthread -lm -lortp ָ����  -L /tmp/ortp/lib ָ����·�� 	-I ͷ�ļ�
3.4_5.ORTP���Դ�����1_2
3.4.1��ORTP�����
	(1) �Ȿ��û��main��ֻ�ṩ���ܺ���������srcĿ¼��
	(2) ���ʹ�ø��˰�������main����src/testsĿ¼��
	(3) ������ݽṹ��ͷ�ļ���include/ortpĿ¼��
	(4) ortpʵ����rtp��rtcpЭ�飬ǰ�߸����䣬���߸�����ƺ�ͬ��Э��

3.4.2��ORTP���ʹ�ð���
	(1) src/tests/rtpsend.c
	(2) ortp_init��av_profile_init
	(3) ortp_scheduler_init��ORTP��������һ����������ɶ���Ự�ķ��ͺͽ��գ�
		������select
	(4) rtp_session_new��rtp�ĻỰ����

3.4.3��rtp��session
	(1) rtpͨ���Ự���������ݷ��ͺͽ��գ��Ự�ı�����һ���ṹ�壬����ܶ���Ϣ
	(2) �����Ự��rtp_session_new
	(3) rtp������rtp_session_send_with_ts
	(4) �ײ������ɻ�Ļ���socket�ӿ���һ�ף��ο�rtpsession_inet.c

3.4.4��ORTP��һЩСϸ��
	(1) port.c�ж�OS�ĳ��û��ƣ����񴴽������١����̹�����ź����ȣ������˷�
		װ�����ڽ�ortp��ֲ����ͬƽ̨��
	(2) utils.c��ʵ����һ��˫������
	(3) str_util.c��ʵ����һ�����й���
	(4) rtpparse.c��rtcpparse.c�ļ�ʵ���˽����յ���rtp���ݰ��Ĳ���
	(5) jitterctl.c��ʵ����jitter buffer��������jitter buffer������ip ����Ƶͨ����
		��ԱȽϸ߼������⣬jitter bufferģ��û�ͨ���Ǻ���һ��voip�ͻ���/��������
		���ļ�����֮һ�������������綶���Ƚ����أ���3g, wifi���������ݰ���rttֵ����
		�������ᵼ���������٣����ֵ�����jitter buffer ģ��ͨ������һ�����ݰ�����
		���ݰ����ţ������ȵ��͸����Ŷˣ�һ���õ�jitter bufferʵ��ͨ���Ƕ�̬��������
		��С�ģ��������ӳٴ󣬶�������ʱ�ᶯ̬���ӻ����С��������ָ�ʱ��̬��С��
		���С�Լ��ٶ˵��˵Ĳ����ӳ١�

3.4.6_7.RTP����ʵ��Դ�����1_2
3.4.6.1��ortp����ӦAPI
3.4.6.2�����ͺ������ص㽲��
3.4.6.3�����ܵ���չ����
	(1) �ü�sample�����
	(2) �޸�һЩ������ʵ�飨Ʃ��ÿ���ֽ�����IP��ַ���˿ںŵȣ�

3.4.8.VLC��sdp�ļ������Ϳγ��ܽ�
3.4.8.1��SDP�ļ���ʽ		// ��sdp�ļ����� ��һ�����紮��
3.4.8.2���������ܽ�

 -- rtp_session_init()
 
 -- rtp_session_set_scheduling_mode()
 
 -- rtp_session_set_blocking_mode()
 
 -- rtp_session_signal_connect()
 
 -- rtp_session_set_local_addr()

 -- rtp_session_set_remote_addr()
 
 -- rtp_session_set_send_payload_type()
 
 -- rtp_session_send_with_ts()
 
 -- rtp_session_recv_with_ts()
 
 -- rtp_session_destroy()
