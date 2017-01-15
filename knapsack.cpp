//最少背包问题
//假设有许多盒子，每个盒子能保存的总重量为1.0。有N个项i1,i2,...,iN，它们的重量分别是w1,w2,...,wN。要求用尽可能少的盒子放入所有的项，
//任何盒子的重量不能超过它的总重量。例如，如果给出的重量为0.4，0.4，0.6，0.6，用两个盒子就能解决问题
//按如下策略解决此问题：按给定的次序扫描每一个项，把每个项放入能够容纳它而不至于溢出的最满的盒子。用优先级队列选择要装入的盒子

#include <iostream>
#include "priorityQueueSeq.h"

using namespace std;

int main()
{
	int n, num = 0;				//n:项的数量，num:所需的背包数
	double *ar;				//存放n个项的重量
	priorityQueue<double> myQueue;		//以背包剩余容量为优先级所组成的背包队列

										//初始化
	cout << "请输入一共多少项：\n";
	cin >> n;
	ar = new double[n];
	cout << "请依次输入每项的数量：\n";
	for (int i = 0; i<n; ++i)
	{
		cin >> ar[i];			//最坏情况下背包数与项数相同
		myQueue.enQueue(1.0);		//背包的初始容量都是1.0
	}
	for (int i = 0; i<n; ++i)			//逐个放入n个项
	{
		myQueue.decreaseKey(myQueue.findMin(ar[i]), ar[i]);
		while (myQueue.getHead() == 0)
		{
			++num;
			myQueue.deQueue();
		}
	}
	while (!myQueue.isEmpty())				//检查用到的背包数
		if (myQueue.deQueue()<1.0) ++num;

	cout << "按照此种给定顺序和贪婪算法，得到需要的背包总数为：" << num << endl;

	delete[]ar;

	return 0;
}
