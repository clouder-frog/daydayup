
3.7.1.3�����̼���������
	(1) ���̼��л�������
	(2) ���̼�ͨ���鷳����Ч�ʵ�

3.7.2.2��linux�е��̼߳��
	(1) һ������������
	(2) һ�������п����ж���̣߳��߳��ǲ����ں˵��ȵ���С��Ԫ
	(3) ͬһ���̵Ķ���߳�֮������׸�Ч��ͨ��
	(4) �ڶ����CPU(�Գƶദ�����ܹ�SMP)�ܹ���Ч�����

// gcc xxx -lpthread

3.7.3.�̳߳�������
3.7.3.1���̴߳��������
	(1) pthread_create()
	(2) pthread_join()			���̵߳ȴ����������������߳�	// pthread_exit()���θ�pthread_join()
	(3) pthread_detach()		���̷߳������̣߳���������̲߳�����ȥ�������߳�

// �߳�Ҫô���գ�Ҫô���롣������Ҫ�ȵ�������ֹ�ſ��Ի�����Դ

3.7.3.2���߳�ȡ��
	(1) pthread_cancel()			һ�㶼�����̵߳��øú���ȥȡ�����߳�
	(2) pthread_setcancelstate()	���߳������Ƿ�����ȡ��
	(3) pthread_setcanceltype()

3.7.3.3���̺߳����˳����
	(1) pthread_exit()��return�˳�
	(2) pthread_cleanup_push(func, args)	// ���̱߳�cancel�󣬻��Զ�����func() -- �ͷ���
	(3) pthread_cleanup_pop()	// pthread_cleanup_pop(0) ȡ��func() ��ִ��

3.7.3.4����ȡ�߳�id
	(1) pthread_self()

3.7.4.3���ź����Ľ��ܺ�ʹ��
	// sem_t sem;
	// sem_init(&sem, 0, 0);	// ������cnt����ʼ��Ϊ0		-- sem_destroy(&sem);

	// sem_post(&sem);		// ����sem

	// sem_wait(&sem);

3.7.6.1��������

	(2) ��غ�����pthread_mutex_init() pthread_mutex_destroy()
				  pthread_mutex_lock() pthread_mutex_unlock()
	(3) ���������ź����Ĺ�ϵ��������Ϊ��������һ��������ź���
	(4) ��������Ҫ����ʵ�ֹؼ��α���

	// man 3 pthread_mutex_init -- ��Ҫ��װ��Ӧ��man�ֲ� sudo apt-get install manpages-posix-dev

3.7.7.�߳�ͬ��֮��������
		pthread_cond_init()		pthread_cond_destroy()
		pthread_cond_wait()		pthread_cond_signal/pthread_cond_broadcast()


// posix��׼thread  -- pthread


