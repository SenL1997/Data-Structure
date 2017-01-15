#include "search.h"
#include "timer.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    vector<double> data;
    for(double i = 0; i<1000000; i++)
    {
        data.push_back(i);
    }

    int pos;
    double key = 1.0;
    //测试二分查找
    cout<<"二分查找结果："<<endl;
    Timer t;
    while (key<1000000)
    {
        pos = binarySearch(data, key);
        key++;
    }
//    pos = binarySearch(data, key);
    cout << "Time for Binary Search is "<<t.elapsed_ns()<<" ns "<<endl;
//    if(pos != -1)
//		cout<< "在数组的第"<<pos<<"个位置找到"<<key<<"\n";
//	else
//		cout<< "未在数组中找到元素"<<key<<endl;

    key=1.0;
    cout << endl;
    //测试插值查找
    cout<<"插值查找结果："<<endl;
    t.reset();
    while (key<1000000)
    {
        pos = binarySearch(data, key);
        key++;
    }
//	pos = interpolationSearch(data,key);
	cout << "Time for Binary Search is "<<t.elapsed_ns()<<" ns "<<endl;
//	if(pos != -1)
//		cout<< "在数组的第"<<pos<<"个位置找到"<<key<<"\n";
//	else
//		cout<< "未在数组中找到元素"<<key<<endl;

    cout <<endl;
    //测试分块查找
    key=1.0;
    cout<<"分块查找结果："<<endl;
    int a = 1;
    int b = 1000000/a;
    indexList<double> dataset(a, data);
    t.reset();
    while (key<1000000)
    {
        pos = binarySearch(data, key);
        key++;
    }
//	pos = dataset.find(key);
	cout << "The indexList is devided into "<< b << " blocks. Time for Binary Search is "<<t.elapsed_ns()<<" ns "<<endl;
//	if(pos != -1)
//		cout<< "在数组的第"<<pos<<"个位置找到"<<key<<"\n";
//	else
//		cout<< "未在数组中找到元素"<<key<<endl;

    return 0;
}
