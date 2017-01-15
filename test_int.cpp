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
    linkedList<int> s;
    for (i=0;i<1000;i++)
    {
        s.insert(i,i);
    }
    cout << "Insert() Time (1e+03): "<<t1.elapsed_us()<<" us"<<endl;

    //STL
    t1.reset();
    list <int> v;
    for (i=0;i<1000;i++)
    {
        v.push_back(i);
    }
    cout << "Push_back() Time (1e+03): "<< t1.elapsed_us()<<" us"<<endl;
    //cout<<"The size of v is: "<<v.size()<<", the capacity of v is: "<<v.capacity()<<endl;

    t1.reset();
    linkedList<int> s2;
    for (i=0;i<10000;i++)
    {
        s2.insert(i,i);
    }
    cout << "Insert() Time (1e+04): "<<t1.elapsed_us()<<" us"<<endl;

    t1.reset();
    list <int> v2;
    for (i=0;i<10000;i++)
    {
        v2.push_back(i);
    }
    cout << "Push_back() Time (1e+04): "<< t1.elapsed_us()<<" us"<<endl;

    t1.reset();
    linkedList<int> s3;
    for (i=0;i<100000;i++)
    {
        s2.insert(i,i);
    }
    cout << "Insert() Time (1e+05): "<<t1.elapsed_us()<<" us"<<endl;

    t1.reset();
    list <int> v3;
    for (i=0;i<100000;i++)
    {
        v2.push_back(i);
    }
    cout << "Push_back() Time (1e+05): "<< t1.elapsed_us()<<" us"<<endl;



//    s.traverse();
//    s.reverse();
//    cout << "\n\nReverse(): ";
//    s.traverse();
//    cout << "\n\nThe length of linkedList is " << s.length() << endl;
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
