#include <iostream>
#include <list>
#include "linkedList.h"
#include "linkedList.cpp"
#include "timer.h"
#include "string.h"

using namespace std;

int main()
{
    struct dateT
    {
        int month;
        int day;
        int year;
    };
    struct studentT
    {
        int no;
        char name[4];
        dateT birthday;
        int score;
    };

    studentT student[50000];

    int j=0;
    for (int j=0;j<50000;j++);
    {
        student[j].no=j;
        strcpy(student[j].name, "Who");
        student[j].birthday.month=1;
        student[j].birthday.day=2;
        student[j].birthday.year=2016;
        student[j].score=100;
    }

    int i=0;
    Timer t1;
    //自己的类

    t1.reset();
    linkedList<studentT> s1;
    for (i=0;i<1000;i++)
    {
        s1.insert(i,student[i]);
    }
    cout << "Insert() Time (1e+03): "<<t1.elapsed_ns()<<" ns"<<endl;

    //STL
    t1.reset();
    list <studentT> v1;
    for (i=0;i<1000;i++)
    {
        v1.push_back(student[i]);
    }
    cout << "Push_back() Time (1e+03): "<< t1.elapsed_ns()<<" ns"<<endl;

    t1.reset();
    linkedList<studentT> s2;
    for (i=0;i<10000;i++)
    {
        s2.insert(i,student[i]);
    }
    cout << "Insert() Time (1e+04): "<<t1.elapsed_ns()<<" ns"<<endl;

    t1.reset();
    list <studentT> v2;
    for (i=0;i<10000;i++)
    {
        v2.push_back(student[i]);
    }
    cout << "Push_back() Time (1e+04): "<< t1.elapsed_ns()<<" ns"<<endl;

    t1.reset();
    linkedList<studentT> s3;
    for (i=0;i<50000;i++)
    {
        s3.insert(i,student[i]);
    }
    cout << "Insert() Time (5e+04): "<<t1.elapsed_ns()<<" ns"<<endl;

    t1.reset();
    list <studentT> v3;
    for (i=0;i<50000;i++)
    {
        v3.push_back(student[i]);
    }
    cout << "Push_back() Time (5e+04): "<< t1.elapsed_ns()<<" ns"<<endl;

    return 0;
}
