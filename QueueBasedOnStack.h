#ifndef QUEUEBASEDONSTACK_H_INCLUDED
#define QUEUEBASEDONSTACK_H_INCLUDED

#include <iostream>
#include "linkStack.h"
//��ջʵ�ֶ���

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

		//��stack2���أ���push stack1
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
		head = stack2.pop();//ֱ�ӷ���stack2��ջ�����Ƕ�ͷ
		return head;
	}
	else
	{
		while(!(stack1.isEmpty()))
		//��stack1����Ԫ��ʱ����stack1��Ԫ��ȫ���Ƶ�stack2
		{
			stack2.push(stack1.pop());
			//stack1.pop();
		}
		head = stack2.pop();//��ȡstack1��ʣ������һ��Ԫ�ز����أ����Ƕ��еĶ�ͷ
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
		//��stack1��ȫ��Ԫ���Ƶ�stack2��Ȼ�󷵻�stack2 ջ��Ԫ��
		while(!stack1.isEmpty())
		{
			stack2.push(stack1.pop());
		}
		head = stack2.top();
		return head;
	}
}


#endif //QUEUEBASEDONSTACK_H_INCLUDED




