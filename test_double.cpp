#include <iostream>
#include <list>
#include "linkedList.h"
#include "linkedList.cpp"
#include "timer.h"

using namespace std;

int main()
{
    //自己的类
    int i=0;
    Timer t1;
    linkedList<double> s;
    for (i=0;i<1000;i++)
    {
        s.insert(i,i);
    }
    cout << "Insert() Time (1e+03): "<<t1.elapsed_us()<<" us"<<endl;

    //STL
    t1.reset();
    list <double> v;
    for (i=0;i<1000;i++)
    {
        v.push_back(i);
    }
    cout << "Push_back() Time (1e+03): "<< t1.elapsed_us()<<" us"<<endl;
    //cout<<"The size of v is: "<<v.size()<<", the capacity of v is: "<<v.capacity()<<endl;

    t1.reset();
    linkedList<double> s2;
    for (i=0;i<10000;i++)
    {
        s2.insert(i,i);
    }
    cout << "Insert() Time (1e+04): "<<t1.elapsed_us()<<" us"<<endl;

    t1.reset();
    list <double> v2;
    for (i=0;i<10000;i++)
    {
        v2.push_back(i);
    }
    cout << "Push_back() Time (1e+04): "<< t1.elapsed_us()<<" us"<<endl;

    t1.reset();
    linkedList<double> s3;
    for (i=0;i<100000;i++)
    {
        s2.insert(i,i);
    }
    cout << "Insert() Time (1e+05): "<<t1.elapsed_us()<<" us"<<endl;

    t1.reset();
    list <double> v3;
    for (i=0;i<100000;i++)
    {
        v2.push_back(i);
    }
    cout << "Push_back() Time (1e+05): "<< t1.elapsed_us()<<" us"<<endl;

    t1.reset();
    list <double> v4;
    for (i=0;i<1000000;i++)
    {
        v4.push_back(i);
    }
    cout << "Push_back() Time (1e+06): "<< t1.elapsed_us()<<" us"<<endl;

    t1.reset();
    list <double> v5;
    for (i=0;i<10000000;i++)
    {
        v5.push_back(i);
    }
    cout << "Push_back() Time (1e+07): "<< t1.elapsed_us()<<" us"<<endl;
    //STL中list大概O(n)
    return 0;
}
