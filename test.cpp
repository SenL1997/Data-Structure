#include <iostream>
#include "StackBasedOnQueue.h"
#include "linkQueue.h"
#include "queue.h"

using namespace std;

int main()
{
    int i = 0;
    StackBasedOnQueue<int> s;
    for (i=0;i<101;i++)
    {
        s.push(i);
    }
    if(!s.isEmpty())
    {
        cout << "The stack is not empty!"<<endl;
    }
    cout << "The top of the stack is "<<s.top()<<endl<<endl;
    for (i=0;i<100;i++)
    {
        cout <<s.pop() << " ";
    }
    cout <<endl;

//    s.push(1);
//    s.push(4);
//    s.push(5);
//    s.push(6);
//    s.push(7);
//    cout << s.pop() << endl;
//    cout << s.pop() << endl;
//    cout << s.pop() << endl;
//    cout << s.pop() << endl;
//    cout << s.pop() << endl;


    return 0;
}
