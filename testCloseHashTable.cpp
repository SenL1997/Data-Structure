#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "closeHashTable.h"

using namespace std;

int main()
{
	closeHashTable<int> ht(25013);//25013是最接近25000的素数
	int count;//记录每次探测次数
	double avgCountSer = 0;//记录平均探测次数
	int list[10000];//记录随机生成的数据

	srand(time(nullptr));
	for (int i = 0;i < 10000;i++)//生成10000个随机整数并插入散列表
	{
		list[i] = rand();
		ht.insert(list[i], count);
		avgCountSer += count;
	}
	avgCountSer /= 10000;
	cout << "平均探测次数：" << avgCountSer << endl;
	return 0;
}
