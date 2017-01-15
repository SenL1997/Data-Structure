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


    seqList<int> s;
    s.create(1);
    for (i=0;i<10000001;i++)
    {
        s.insert(i,i);
    }
    cout << "seqList: \n";
    t1.reset();
    for (i=10000000;i>9500000;i--)
    {
        s.remove(i);
    }
    cout << "Remove( ) Time (5e+05): "<<t1.elapsed_us()<<" us"<<endl;
    cout << "Size: "<<s.length()<<endl;
    t1.reset();
    for (i=9500000;i>8500000;i--)
    {
        s.remove(i);
    }
    cout << "Remove() Time (1e+06): "<<t1.elapsed_us()<<" us"<<endl;
    cout << "Size: "<<s.length()<<endl;


    vector <int> v;
    for (i=0;i<10000000;i++)
    {
        v.push_back(i);
    }
    t1.reset();
    for (i=0;i<500000;i++)
    {
        v.pop_back();
    }
    cout << "Vector: \n";
    cout << "Pop_back() Time (5e+05): "<<t1.elapsed_us()<<" us"<<endl;
    for (i=0;i<1000000;i++)
    {
        v.pop_back();
    }
    cout << "Pop_back() Time (1e+06): "<<t1.elapsed_us()<<" us"<<endl;

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
