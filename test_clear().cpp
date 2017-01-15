#include <iostream>
#include <list>
#include "linkedList.h"
#include "linkedList.cpp"
#include "timer.h"

using namespace std;

int main()
{
    //�Լ�����
    int i=0;
    Timer t1;


    linkedList<double> s;
    for (i=0;i<100000;i++)
    {
        s.insert(i,i);
    }
    cout<<"linkedList Created"<<endl;
    t1.reset();
    s.clear();
    cout << "linkedList clear() Time(100000): "<<t1.elapsed_us()<<" us"<<endl;
    t1.reset();

    list <double> v;
    for (i=0;i<100000;i++)
    {
        v.push_back(i);
    }
    cout<<"List Created"<<endl;
    t1.reset();
    v.clear();
    cout << "List clear() Time(100000): "<<t1.elapsed_us()<<" us"<<endl;
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
