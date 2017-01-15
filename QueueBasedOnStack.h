#ifndef QUEUEBASEDONSTACK_H_INCLUDED
#define QUEUEBASEDONSTACK_H_INCLUDED

#include <iostream>
#include "linkStack.h"
//用栈实现队列

template <class elemType>
class QueueBasedOnStack
{
	private:
		linkStack<elemType> stack1;
		linkStack<elemType> stack2;

	public:

		void enQueue(const elemType &x);
		elemType deQueue();
		bool isEmpty() const {return stack1.isEmpty()&&stack2.isEmpty();}
		elemType getHead();
};

template <class elemType>
void QueueBasedOnStack<elemType>::enQueue(const elemType &x)
{
	if(stack1.isEmpty())
		stack1.push(x);
	else
	{

		//将stack2倒回，再push stack1
		while(!stack2.isEmpty())
		{
			stack1.push(stack2.pop());
		}
		stack1.push(x);
	}
}
template <class elemType>
elemType QueueBasedOnStack<elemType>::deQueue()
{
    elemType head;
	if(stack1.isEmpty()&&stack2.isEmpty())
	{
		std::cout << "The queue is empty!"<<std::endl;
	}
	else if(!stack2.isEmpty())
	{
		head = stack2.pop();//直接返回stack2的栈顶就是队头
		return head;
	}
	else
	{
		while(!(stack1.isEmpty()))
		//当stack1中有元素时，将stack1中元素全部移到stack2
		{
			stack2.push(stack1.pop());
			//stack1.pop();
		}
		head = stack2.pop();//获取stack1中剩余的最后一个元素并返回，就是队列的队头
		return head;
	}
}
template <class elemType>
elemType QueueBasedOnStack<elemType>::getHead()
{
    elemType head;
    if(stack1.isEmpty()&&stack2.isEmpty())
	{
		std::cout << "The queue is empty!"<<std::endl;
	}
	if(!stack2.isEmpty())
	{
		head = stack2.top();
		return head;
	}
	else
	{
		//将stack1中全部元素移到stack2，然后返回stack2 栈顶元素
		while(!stack1.isEmpty())
		{
			stack2.push(stack1.pop());
		}
		head = stack2.top();
		return head;
	}
}


#endif //QUEUEBASEDONSTACK_H_INCLUDED




