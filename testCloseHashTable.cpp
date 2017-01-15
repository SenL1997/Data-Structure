#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "closeHashTable.h"

using namespace std;

int main()
{
	closeHashTable<int> ht(25013);//25013����ӽ�25000������
	int count;//��¼ÿ��̽�����
	double avgCountSer = 0;//��¼ƽ��̽�����
	int list[10000];//��¼������ɵ�����

	srand(time(nullptr));
	for (int i = 0;i < 10000;i++)//����10000���������������ɢ�б�
	{
		list[i] = rand();
		ht.insert(list[i], count);
		avgCountSer += count;
	}
	avgCountSer /= 10000;
	cout << "ƽ��̽�������" << avgCountSer << endl;
	return 0;
}
