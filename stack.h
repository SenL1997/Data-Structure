#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>

//Õ»µÄ³éÏóÀà


template <class elemType>
class stack
{
	public:
		virtual bool isEmpty() const = 0;
		virtual void push(const elemType &x) = 0;
        virtual elemType pop() = 0;
		virtual elemType top() const = 0;
		virtual ~stack(){};
};

#endif //STACK_H_INCLUDED
