//���ٱ�������
//�����������ӣ�ÿ�������ܱ����������Ϊ1.0����N����i1,i2,...,iN�����ǵ������ֱ���w1,w2,...,wN��Ҫ���þ������ٵĺ��ӷ������е��
//�κκ��ӵ��������ܳ������������������磬�������������Ϊ0.4��0.4��0.6��0.6�����������Ӿ��ܽ������
//�����²��Խ�������⣺�������Ĵ���ɨ��ÿһ�����ÿ��������ܹ�������������������������ĺ��ӡ������ȼ�����ѡ��Ҫװ��ĺ���

#include <iostream>
#include "priorityQueueSeq.h"

using namespace std;

int main()
{
	int n, num = 0;				//n:���������num:����ı�����
	double *ar;				//���n���������
	priorityQueue<double> myQueue;		//�Ա���ʣ������Ϊ���ȼ�����ɵı�������

										//��ʼ��
	cout << "������һ�������\n";
	cin >> n;
	ar = new double[n];
	cout << "����������ÿ���������\n";
	for (int i = 0; i<n; ++i)
	{
		cin >> ar[i];			//�����±�������������ͬ
		myQueue.enQueue(1.0);		//�����ĳ�ʼ��������1.0
	}
	for (int i = 0; i<n; ++i)			//�������n����
	{
		myQueue.decreaseKey(myQueue.findMin(ar[i]), ar[i]);
		while (myQueue.getHead() == 0)
		{
			++num;
			myQueue.deQueue();
		}
	}
	while (!myQueue.isEmpty())				//����õ��ı�����
		if (myQueue.deQueue()<1.0) ++num;

	cout << "���մ��ָ���˳���̰���㷨���õ���Ҫ�ı�������Ϊ��" << num << endl;

	delete[]ar;

	return 0;
}
