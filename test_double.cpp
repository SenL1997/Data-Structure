#include <iostream>
#include <vector>
#include "seqList.h"
#include "seqList.cpp"
#include "timer.h"

using namespace std;

int main()
{
    //自己的类
    int i=0;
    Timer t1;
    seqList<double> s;
    s.create(1);
    for (i=0;i<100000;i++)
    {
        s.insert(i,i);
    }
    cout << "Insert() Time (1e+05): "<<t1.elapsed_us()<<" us"<<endl;

    //STL
    t1.reset();
    vector <double> v;
    for (i=0;i<100000;i++)
    {
        v.push_back(i);
    }
    cout << "Push_back() Time (1e+05): "<< t1.elapsed_us()<<" us"<<endl;
    //cout<<"The size of v is: "<<v.size()<<", the capacity of v is: "<<v.capacity()<<endl;

    t1.reset();
    seqList<double> s2;
    s2.create(1);
    for (i=0;i<1000000;i++)
    {
        s2.insert(i,i);
    }
    cout << "Insert() Time (1e+06): "<<t1.elapsed_us()<<" us"<<endl;

    t1.reset();
    vector <double> v2;
    for (i=0;i<1000000;i++)
    {
        v2.push_back(i);
    }
    cout << "Push_back() Time (1e+06): "<< t1.elapsed_us()<<" us"<<endl;

    t1.reset();
    seqList<double> s3;
    s3.create(1);
    for (i=0;i<10000000;i++)
    {
        s3.insert(i,i);
    }
    cout << "Insert() Time (1e+07): "<<t1.elapsed_us()<<" us"<<endl;

    t1.reset();
    vector <double> v3;
    for (i=0;i<10000000;i++)
    {
        v3.push_back(i);
    }
    cout << "Push_back() Time (1e+07): "<< t1.elapsed_us()<<" us"<<endl;

//    cout << "seqList: ";
//    s.traverse();
//    s.reverse();
//    cout << "\n\nReverse(): ";
//    s.traverse();
//    cout << "\n\nThe length of seqList is " << s.length() << endl;
//
//    s.insert(3,'c');
//    cout <<"\nAfter insert(3,'c'): ";
//    s.traverse();
//    s.remove(2);
//    cout <<"\n\nAfter remove(2): ";
//    s.traverse();
//    cout<<"\n\nLinkedList[1]: "<<s.visit(1)<<endl;
//    cout << "\nSearch('b'): " <<s.search('b')<<endl;
//    s.clear();
//    cout << "\nAfter clear(): " <<s.length()<<endl;
    return 0;
}
