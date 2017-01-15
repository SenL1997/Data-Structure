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
    //测试二分查找
    int pos = binarySearch(data,0,10000,key);
    if(pos != -1)
		cout<< "在数组的第"<<pos<<"个位置找到"<<key<<"\n";
	else
		cout<< "未在数组中找到元素"<<key<<endl;

    vector<double> dataset;
    for(double i = 0; i<1000000; i++)
    {
        dataset.push_back(i);
    }
    //测试第7章第5题
    pos = seqSearch(dataset, key);
    if(pos != -1)
		cout<< "在数组的第"<<pos<<"个位置找到"<<key<<"\n";
	else
		cout<< "未在数组中找到元素"<<key<<endl;
    pos = seqSearch(dataset, key-999);
    if(pos != -1)
		cout<< "在数组的第"<<pos<<"个位置找到"<<key-999<<"\n";
	else
		cout<< "未在数组中找到元素"<<key<<endl;
    pos = seqSearch(dataset, key-1000);
    if(pos != -1)
		cout<< "在数组的第"<<pos<<"个位置找到"<<key-1000<<"\n";
	else
		cout<< "未在数组中找到元素"<<key<<endl;

//    //测试第7章第3题，需使用set.h库
    set<int> s1,s2,s3;
    s1.insert(1);s1.insert(2);s1.insert(3);
    cout << "s1初始化："<<endl;
    s1.display();
    s2.insert(2);s2.insert(3);s2.insert(4);
    cout << "s2初始化："<<endl;
    s2.display();
    s3 = s1+s2;
    cout << "并：s3 = s1+s2 = ";
    s3.display();
    cout << "\n交：s3 = s1+s2 = ";
    s3 = s1*s2;
    s3.display();
    cout << "\n差：s3 = s1-s2 = ";
    s3 = s1-s2;
    s3.display();

    //测试第7章第4题，需使用setLink.h库
//    set<int> s1,s2,s3;
//    s1.insert(1);s1.insert(2);s1.insert(3);
//    cout << "s1初始化："<<s1<<endl;
//    s2.insert(2);s2.insert(3);s2.insert(4);
//    cout << "s2初始化："<< s2<<endl;
//    s3 = s1+s2;
//    cout << "并：s3 = s1+s2 = "<<s3<<endl;
//    s3 = s1*s2;
//    cout << "交：s3 = s1*s2 = "<<s3<<endl;
//    s3 = s1-s2;
//    cout << "差：s3 = s1-s2 = "<<s3<<endl;

    return 0;
}
