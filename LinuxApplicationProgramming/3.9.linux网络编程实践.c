
3.9.3.TCPЭ���ѧϰ2
		-- �������ӵ�����: ������listenʱ�ͻ�����������connect
		-- �ر�������Ҫ�Ĵ�����, ���������߿ͻ��˶�������������ر�
		-- ����Э���Ѿ���װ��TCPЭ���ڲ�, socket��̽ӿ�ƽʱ���ù�
		-- �ͻ��˶˿ںſ����Զ�����

3.9.4.socket��̽ӿڽ���
	3.9.4.1����������
		(1)socket	//socket����������open, ��һ����������, �ɹ��򷵻�һ�������ļ�������(int����)
					//�Ժ��������������Ӷ�ͨ����������ļ�������
		(2)bind 	//��local ip��ַ
		(3)listen
		(4)connect
		(5)accept	����ֵ��һ��fd, ��ʾ�Ѿ���ǰ�����ӵĿͻ���֮�佨����һ��TCP����
					ͨ���������(new fd)���Ϳͻ��˽���/*��д����*/

			//ע��: socket���ص�fd��������fd, �����������ͻ��˵�, �����������κοͻ��˽��ж�д 	\
					accept���ص�fd��������fd, �����������Ƕ˵Ŀͻ��˳�����ж�д				\
					-- tcp udp��socket����ֵ����ĺ��岻ͬ
		(6)send��write
		(7)recv��read	// flag = 0

	3.9.4.4�������Ժ���
		(1)inet_addr, inet_aton, inet_ntoa			// inet_addr
		(2)inet_ntop��inet_pton						// net to point   warning: return const char *

		// in_addr_t inet_addr(const char *cp);		//
		// char *inet_ntoa(struct in_addr in);		// sockaddr_in.sin_addr

	3.9.4.5����ʾIP��ַ������ݽṹ
		(1)�������� netinet/in.h

		(3)typedef uint32_t in_addr_t;		�����ڲ�������ʾIP��ַ������

		(4)struct in_addr				// struct in_addr && struct in6_addr
		  {
			in_addr_t s_addr;			// ��װΪ��ĳһ��ε�һ����
		  };							// struct in_addr addr = 0;
										// invalid initialize ��ʼ���ṹ�������������ʼ��
		(5)struct sockaddr_in			// sockaddr_in  sockaddr_in6
		  {
			__SOCKADDR_COMMON (sin_);
			in_port_t sin_port;
			struct in_addr sin_addr;	// warning: �ֺ�

			unsigned char sin_zero[sizeof (struct sockaddr) - __SOCKADDR_COMMON_SIZE - sizeof (in_port_t) - sizeof (struct in_addr)]; // calculate pad size
		  };							// warning: �ֺ�
		
		(6)struct sockaddr{}			// ʵ�ʱ����sockaddrʹ��sockaddr_in����sockaddr_in6���

3.9.8.3��̽�֣�����÷������Ϳͻ��˺úù�ͨ
	(1)�ͻ��˺ͷ�����ԭ���϶���������ķ�����, ����ʵ����˫���������
	(2)//client��server֮���ͨ�����첽��, ���������ĸ�Դ
	(3)�������: ����Ӧ�ò�Э�������, server��client��������һϵ�е�ͨ��Լ��












