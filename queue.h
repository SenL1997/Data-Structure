#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <iostream>

template<class elemType>
class queue
{
	public:
		virtual bool isEmpty() = 0;
		virtual void enQueue(const elemType &x) = 0;
		virtual elemType deQueue() = 0;
		virtual elemType getHead() = 0;
		virtual ~queue(){}
};

#endif //QUEUE_H_INCLUDED
