#include "binarySearch.h"
#include "set.h"
//#include "setLink.h"
#include "seqSearch.h"
#include <iostream>

using namespace std;

int main()
{
    double data[10000];
    int i = 0;
    double key = 999;
    for (i = 0; i<10000; i++)
    {
        data[i] = i;
    }
    //���Զ��ֲ���
    int pos = binarySearch(data,0,10000,key);
    if(pos != -1)
		cout<< "������ĵ�"<<pos<<"��λ���ҵ�"<<key<<"\n";
	else
		cout<< "δ���������ҵ�Ԫ��"<<key<<endl;

    vector<double> dataset;
    for(double i = 0; i<1000000; i++)
    {
        dataset.push_back(i);
    }
    //���Ե�7�µ�5��
    pos = seqSearch(dataset, key);
    if(pos != -1)
		cout<< "������ĵ�"<<pos<<"��λ���ҵ�"<<key<<"\n";
	else
		cout<< "δ���������ҵ�Ԫ��"<<key<<endl;
    pos = seqSearch(dataset, key-999);
    if(pos != -1)
		cout<< "������ĵ�"<<pos<<"��λ���ҵ�"<<key-999<<"\n";
	else
		cout<< "δ���������ҵ�Ԫ��"<<key<<endl;
    pos = seqSearch(dataset, key-1000);
    if(pos != -1)
		cout<< "������ĵ�"<<pos<<"��λ���ҵ�"<<key-1000<<"\n";
	else
		cout<< "δ���������ҵ�Ԫ��"<<key<<endl;

//    //���Ե�7�µ�3�⣬��ʹ��set.h��
    set<int> s1,s2,s3;
    s1.insert(1);s1.insert(2);s1.insert(3);
    cout << "s1��ʼ����"<<endl;
    s1.display();
    s2.insert(2);s2.insert(3);s2.insert(4);
    cout << "s2��ʼ����"<<endl;
    s2.display();
    s3 = s1+s2;
    cout << "����s3 = s1+s2 = ";
    s3.display();
    cout << "\n����s3 = s1+s2 = ";
    s3 = s1*s2;
    s3.display();
    cout << "\n�s3 = s1-s2 = ";
    s3 = s1-s2;
    s3.display();

    //���Ե�7�µ�4�⣬��ʹ��setLink.h��
//    set<int> s1,s2,s3;
//    s1.insert(1);s1.insert(2);s1.insert(3);
//    cout << "s1��ʼ����"<<s1<<endl;
//    s2.insert(2);s2.insert(3);s2.insert(4);
//    cout << "s2��ʼ����"<< s2<<endl;
//    s3 = s1+s2;
//    cout << "����s3 = s1+s2 = "<<s3<<endl;
//    s3 = s1*s2;
//    cout << "����s3 = s1*s2 = "<<s3<<endl;
//    s3 = s1-s2;
//    cout << "�s3 = s1-s2 = "<<s3<<endl;

    return 0;
}
