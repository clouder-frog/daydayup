
6.3.H264��NAL��Ԫ���1
	���ڽ���SODB��RBSP��NALU��h264����Ҫ���ͬʱ���ⳣ�õ�h264�������������������Ӻ���Ͻ���H264����һЩ����
6.4.H264��NAL��Ԫ���2
	�����ص㽲��H264��sequence��sps��pps��sei��NALU�ȣ����ص���NALU��λ����ͽ�����������Щ�����Ǻ�������h264��rtsp����Ĺؼ��㡣
6.5.H264��NAL��Ԫ���3
	�����ص㽲��sps��pps��sei���ڲ�֡�ṹ���Լ�h264��profile��level����Ҫ���
6.6.H264��NAL��Ԫ���4
	���ڶ�h264��NAL���ֽ����ܽᣬ���״�ͨǰ������ô�Ҷ�h264�������������ݺͽ��������б��ʵ����ա�
6.7.rtsp����Դ�����1
	���ڿ�ʼ����rtsp����Դ�룬��Ҫ�Ǵ�������ܹ��ķ�����
6.8.rtsp����Դ�����2
	���ڽ��ŷ���rtspԴ�룬��Ҫ��RtspServerListen��صĲ��֡�
6.9.rtsp����Դ�����3
	���ڽ��ŷ���rtspԴ�룬��Ҫ�������򲿷֣��Լ���rtsp����
6.10.rtsp����Դ�����4
	���ڽ��ŷ���rtspԴ�룬��Ҫ��client��server֮����������Ӧ���Լ�rtspͨ�Ž����Ĺ��̣��ؼ��ֵ�parser�ȡ�
6.11.rtsp����ʵս����
	���ڴ�ʵս�Ƕȷ���rtsp������룬��ʵ����֤�ķ�ʽ�������ǽ�һ������rtsp�������Ĺ������̡�
6.12.ֱ�ӷ����뻷״buffer����
	���ڽ���2��rtp�����Ͳ��ԣ�ֱ�ӷ��ͺͻ�״buffer���ͣ���2�ַ�ʽ�����ṩ��Դ���ж�������ʾ��
6.13.rtsp�ְ�����h264��Դ�����	
	���ڽ���h264�ְ���rtp���Ͳ��ִ��룬�����Ƿְ�����fu_indicator��fu_header���nalu�Ĳ��֣��Լ���ص�һЩ��־λ�ȡ�



6.2.H264����ԭ���ͻ�������
6.2.1��h.264����ԭ��
	(1) ͼ��������Ϣ���ռ����ࡢʱ������
	(2) ��Ƶ����ؼ��㣺ѹ���ȡ��㷨���Ӷȡ���ԭ��
	(3) H.264��2����ɲ��֣�VCL��NAL
	
6.2.2��h.264������ص�һЩ����
	(1) ��� MB  macroblock
	(2) Ƭ slice
	(3) ֡ frame
	(4) I֡��B֡��P֡
	(5) ֡�� fps
	(6) ����->���->Ƭ->֡->����->����

6.3.H264��NAL��Ԫ���1
6.3.1��VCL��NAL�Ĺ�ϵ
	(1) VCLֻ���ı��벿�֣��ص����ڱ����㷨�Լ����ض�Ӳ��ƽ̨��ʵ�֣�VCL�����
		�Ǳ����Ĵ���Ƶ����Ϣ��û���κ�����ͷ��Ϣ
	(2) NAL���ĵ���VCL���������Ƶ����α�����ͷ�����������紫��
	(3) SODB��String Of Data Bits 
	(4) RBSP��Raw Byte Sequence Payload		
	(5) NALU��Network Abstraction Layer Units
	(6) ��ϵ��
			SODB  + RBSP trailing bits    = RBSP
			NAL header(1 byte) + RBSP     = NALU
	(7) �ܽ᣺�����������˹��ĵ���VCL���֣�����Ƶ����ͽ��벥�ŵ��˹��ĵ���NAL����

6.3.2��H.264��Ƶ����������
	(1) ������Ʒ��SpecialVH264.exe
	(2) ���⹤�ߣ�Elecard StreamEye Tools
	(3) �����ƹ��ߣ�winhex
	(4) ����ץ�����ߣ�wireshark
	(5) ��������vlc

6.3.3��h264��Ƶ���������
	(1) h264��׼�ж���汾�����ܻ��в��죬������첻��
	(2) ���Ͽ���������ʱ�������г�ͻ�������޷���֤�Ĳ���
	(3) ���ǵĿγ̶����Ժ�˼ƽ̨Ϊ����Ϊ׼��Ϊ���������ܱ�֤����ƽ̨Ҳ��ȫһ��
	(4) ��˼ƽ̨���������H.264��������һ�����а�����1sps+1pps+1sei+1I֡+����p֡

6.4.H264��NAL��Ԫ���2
6.4.1����ظ���
	(1) ���� sequence
	(2) �ָ���
	(3) sps
	(4) pps
	(5) sei
	(6) NALU

6.4.2��NALU���
	https://blog.csdn.net/jefry_xdz/article/details/8461343

6.5_6.H264��NAL��Ԫ���3_4
6.5.1��sps��pps���
	https://www.cnblogs.com/wainiwann/p/7477794.html

6.5.2��H264��profile��level
	https://blog.csdn.net/xiaojun111111/article/details/52090185

6.5.3��sequence
	(1) һ��h.264��������ʵ���Ƕ��sequence��ɵ�
	(2) ÿ��sequence���й̶��ṹ��1sps+1pps+1sei+1I֡+����p֡
	(3) sps��pps��sei������sequence��ͼ����Ϣ����Щ��Ϣ���������紫������
	(4) I֡�ǹؼ�������I֡����sequence�ͷ��ˣ�ÿ��sequence����ֻ��1��I֡
	(5) p֡�ĸ�������fps-1
	(6) I֡Խ����P֡����ԽС����֮I֡ԽС��P֡��Խ��
	(7) I֡�Ĵ�Сȡ����ͼ�������ݣ���ѹ���㷨�Ŀռ�ѹ������
	(8) P֡�Ĵ�Сȡ����ͼ��仯�ľ��ҳ̶�
	(9) CBR��VBR��P֡�Ĵ�С���Ի᲻ͬ��CBRʱP֡��С�����㶨��VBRʱ�仯��ȽϾ���

6.7.rtsp����Դ�����1
	// ������init -- ����һ���߳�����listen
	// �ͻ���connect -- ������accept  --  �������߳�������������
	
	// venc�����ڲ�����һ���߳������б���
	// ������ɷ���VB��buff��				-- VB������һ������
	// step6 -- SAMPLE_COMM_VENC_StartGetStream() -- �����̣߳�ȡbuff
	
	// line -- 1409
	// /* Set Venc Fd */
	// VencFd[i] = HI_MPI_VENC_GetFd(i)		// ��ȡ�ڲ������߳� fd

6.8.rtsp����Դ�����2

6.9.rtsp����Դ�����3

6.10.rtsp����Դ�����4
	// ��ORTPʵ�鲻ͬ --   û���ṩsdp��Ϣ��ֱ��������
	// sample�ṩ��sdp��Ϣ

6.11.rtsp����ʵս����

6.12.ֱ�ӷ����뻷״buffer����

6.13.rtsp�ְ�����h264��Դ�����

rtp_timestamp��
	https://blog.csdn.net/jasonhwang/article/details/7316128

fu_indicator��
	https://www.cnblogs.com/yjg2014/p/6144977.html


�������ÿ�ܣ�
main
	RtspServer_init
		RtspServerListen
			RtspClientMsg
				ParseRequestString
		vdRTPSendThread
			VENC_Sent
	SAMPLE_VENC_720P_CLASSIC
		SAMPLE_COMM_VENC_Sentjin




ENC_Sent


RTSP_Session_Info

