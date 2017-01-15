#ifndef StackBasedOnQUEUE_H_INCLUDED
#define StackBasedOnQUEUE_H_INCLUDED

#include "queue.h"
#include "linkQueue.h"
#include "linkQueue.cpp"

//基于队列实现栈

template<class elemType>
class StackBasedOnQueue
{
	private:
		linkQueue<elemType> q1;
		linkQueue<elemType> q2;


	public:
		bool isEmpty(){return (q1.isEmpty()&&q2.isEmpty());}
		void push(const elemType &x);
		elemType pop();
		elemType top();
};

template<class elemType>
void StackBasedOnQueue<elemType>::push(const elemType &x)
{
    //优先进入不空的队列；若都空，默认进q1
    if((q1.isEmpty()&&q2.isEmpty()))
    {
        q1.enQueue(x);
    }
    else if(!q1.isEmpty())
    {
        q1.enQueue(x);
    }
    else//q1空，q2不空时进q2
    {
         q2.enQueue(x);
    }
}

template<class elemType>
elemType StackBasedOnQueue<elemType>::pop()
{
    if(q1.isEmpty()&&q2.isEmpty())
        std::cout << "The stack is empty!"<<std::endl;
    if(!q1.isEmpty())
    {
        while(q1.size()!=1)
        {
            q2.enQueue(q1.deQueue());
        }
        elemType value1 = q1.deQueue();
        return value1;
    }
    if(!q2.isEmpty())
    {
        while(q2.size()!=1)
        {
            q1.enQueue(q2.deQueue());
        }
        elemType value2 = q2.deQueue();
        return value2;
    }
}


template<class elemType>
elemType StackBasedOnQueue<elemType>::top()
{
    if(q1.isEmpty()&&q2.isEmpty())
        std::cout << "The stack is empty!"<<std::endl;
    if(!q1.isEmpty())
    {
        while(q1.size()!=1)
        {
            q2.enQueue(q1.deQueue());
        }
        elemType value1 = q1.getHead();
        q2.enQueue(q1.deQueue());
        return value1;
    }
    if(!q2.isEmpty())
    {
        while(q2.size()!=1)
        {
            q1.enQueue(q2.deQueue());
        }
        elemType value2 = q2.getHead();
        q1.enQueue(q2.deQueue());
        return value2;
    }
}

#endif //StackBasedOnQUEUE_H_INCLUDED
