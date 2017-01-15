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
    for (i=0;i<100000;i++)
    {
        s.insert(i,i);
    }
    cout<<"linkedList created!"<<endl;
    t1.reset();
    for (i=1000;i<11000;i++)
    {
        s.remove(i);
    }
    cout << "linkedList: \n";
    cout << "Remove() Time(10000): "<<t1.elapsed_us()<<" us"<<endl;
    t1.reset();
    for (i=1000;i<4000;i++)
    {
        s.remove(i);
    }
    cout << "Remove() Time(3000): "<<t1.elapsed_us()<<" us"<<endl;


    list <int> v;
    for (i=0;i<100000;i++)
    {
        v.push_back(i);
    }
    cout<<"seqList created!"<<endl;
    t1.reset();
    for (i=1000;i<11000;i++)
    {
        v.remove(i);
    }
    cout << "List: \n";
    cout << "Remove() Time(10000): "<<t1.elapsed_us()<<" us"<<endl;
    t1.reset();
    for (i=1000;i<4000;i++)
    {
        v.remove(i);
    }
    cout << "Remove() Time(3000): "<<t1.elapsed_us()<<" us"<<endl;

//    cout << "linkedList: ";
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
