#ifndef LINKQUEUE_H_INCLUDED
#define LINKQUEUE_H_INCLUDED

#include "queue.h"

//队列的链接定义

template<class elemType>
class linkQueue:public queue<elemType>
{
	private:
		struct node {
			elemType data;
			node *next;
			node (const elemType &x, node *N = NULL)
			{ data = x; next = N;}
			node():next(NULL){}
			~node(){}
		};

		node *front, *rear;

	public:
		linkQueue(){front = rear = NULL;}
		~linkQueue();
		bool isEmpty(){return front == NULL;}
		void enQueue(const elemType &x);
		elemType deQueue();
		elemType getHead(){return front->data;}
		int size();
};

#endif //LINKQUEUE_H_INCLUDED
