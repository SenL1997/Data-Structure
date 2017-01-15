#include "linkQueue.h"

//队列的链接实现

template <class elemType>
linkQueue <elemType>::~linkQueue(){
	node *tmp;
	while (front != NULL)
	{
		tmp = front;
		front = front -> next;
		delete tmp;
	}
}

template <class elemType>
void linkQueue<elemType>::enQueue(const elemType &x)
{
	if(rear == NULL)
		front = rear = new node(x);
	else
	{
		rear -> next = new node(x);
		rear = rear -> next;
	}
}

template <class elemType>
elemType linkQueue<elemType>::deQueue()
{
	node *tmp = front;
	elemType value = front ->data;
	front = front -> next;
	if (front == NULL) rear = NULL;
	delete tmp;
	return value;
}

template <class elemType>
int linkQueue<elemType>::size()
{
    int i = 0;
    node *tmp = front;
    while (tmp != NULL)
    {
        tmp=tmp->next;
        ++i;
    }
    delete tmp;
    return i;
}
