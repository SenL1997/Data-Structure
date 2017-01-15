
template<typename T>
T getKth1(T a[], int N, int K)
{
	priorityQueue<T, greater<T>>hp(a, N);//定义一个基于最大化堆的队列

	T ret;

	for (int i = 0;i < K;i++)ret = hp.deQueue();//执行K次出队
	return ret;
}

template<typename T>
T getKth2(T a[], int N, int K)
{
	priorityQueue<T>H(a, K);//定义一个大小为K的基于最小化堆的队列
	for (int i = K;i < N;i++)//检查剩余元素是否可以出队
	{
		if (H.getHead() < a[i])
		{
			H.deQueue();
			H.enQueue(a[i]);
		}
	}

	return H.getHead();//队头元素是第K大的元素
}
