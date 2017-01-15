#include <iostream>
#include "matrixEntry.h"
#include "closeHashTable.h"
#include <time.h>
#include <stdlib.h>
using namespace std;

int main()
{
	closeHashTable<matrixEntry<int>>myhash(131, getKey);
	int chance, value, count = 0, i, j;

	srand(time(nullptr));
	for (i = 0;i < 100;++i)//��1%�������ɷ���Ԫ��
		for (j = 0;j < 100;++j)
		{
			chance = rand() * 100 / (RAND_MAX + 1);//���ɷ�0����
			if (chance != 0)//��Ӧ��Ԫ��ֵΪ0
				continue;
			value = rand() * 1000 / (RAND_MAX + 1) + 1;//���ɾ���Ԫ��ֵ
			matrixEntry<int> p(i, j, value);
			myhash.insert(p);
			++count;
		}
	cout << count << endl;

	return 0;
}
