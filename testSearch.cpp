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
    //���Զ��ֲ���
    cout<<"���ֲ��ҽ����"<<endl;
    Timer t;
    while (key<1000000)
    {
        pos = binarySearch(data, key);
        key++;
    }
//    pos = binarySearch(data, key);
    cout << "Time for Binary Search is "<<t.elapsed_ns()<<" ns "<<endl;
//    if(pos != -1)
//		cout<< "������ĵ�"<<pos<<"��λ���ҵ�"<<key<<"\n";
//	else
//		cout<< "δ���������ҵ�Ԫ��"<<key<<endl;

    key=1.0;
    cout << endl;
    //���Բ�ֵ����
    cout<<"��ֵ���ҽ����"<<endl;
    t.reset();
    while (key<1000000)
    {
        pos = binarySearch(data, key);
        key++;
    }
//	pos = interpolationSearch(data,key);
	cout << "Time for Binary Search is "<<t.elapsed_ns()<<" ns "<<endl;
//	if(pos != -1)
//		cout<< "������ĵ�"<<pos<<"��λ���ҵ�"<<key<<"\n";
//	else
//		cout<< "δ���������ҵ�Ԫ��"<<key<<endl;

    cout <<endl;
    //���Էֿ����
    key=1.0;
    cout<<"�ֿ���ҽ����"<<endl;
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
//		cout<< "������ĵ�"<<pos<<"��λ���ҵ�"<<key<<"\n";
//	else
//		cout<< "δ���������ҵ�Ԫ��"<<key<<endl;

    return 0;
}
