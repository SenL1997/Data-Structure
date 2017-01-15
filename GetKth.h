
template<typename T>
T getKth1(T a[], int N, int K)
{
	priorityQueue<T, greater<T>>hp(a, N);//����һ��������󻯶ѵĶ���

	T ret;

	for (int i = 0;i < K;i++)ret = hp.deQueue();//ִ��K�γ���
	return ret;
}

template<typename T>
T getKth2(T a[], int N, int K)
{
	priorityQueue<T>H(a, K);//����һ����СΪK�Ļ�����С���ѵĶ���
	for (int i = K;i < N;i++)//���ʣ��Ԫ���Ƿ���Գ���
	{
		if (H.getHead() < a[i])
		{
			H.deQueue();
			H.enQueue(a[i]);
		}
	}

	return H.getHead();//��ͷԪ���ǵ�K���Ԫ��
}
