#include <iostream>
#include "priorityQueueLink.h"

using namespace std;

int main()
{
	priorityQueue<int> q;
	q.enQueue(29);
	cout << "At the beginning, the head of priorityQueue is " << q.getHead() << endl;
	q.enQueue(60);
	cout << "After enQueue(60), the head of priorityQueue is " << q.getHead() << endl;
	q.enQueue(5);
	cout << "After enQueue(5), the head of priorityQueue is " << q.getHead() << endl;
	q.enQueue(7);
	cout << "After enQueue(7), the head of priorityQueue is " << q.getHead() << endl;
	q.enQueue(10);
	cout << "After enQueue(10), the head of priorityQueue is " << q.getHead() << endl;
	q.enQueue(23);
	cout << "After enQueue(23), the head of priorityQueue is " << q.getHead() << endl;
	q.enQueue(3);
	cout << "After enQueue(3), the head of priorityQueue is " << q.getHead() << endl;
	q.enQueue(4);
	cout << "After enQueue(4), the head of priorityQueue is " << q.getHead() << endl;
	q.enQueue(2);
	cout << "After enQueue(2), the head of priorityQueue is " << q.getHead() << endl;
	q.deQueue();
	cout << "After deQueue(), the head of priorityQueue is " << q.getHead() << endl;
	q.enQueue(1);
	cout << "After enQueue(1), the head of priorityQueue is " << q.getHead() << endl;

	priorityQueue<int> p;
	p.enQueue(1);
	p.enQueue(0);
	p.enQueue(2);
	p.enQueue(3);
	p.enQueue(5);
	p.enQueue(7);
	p.enQueue(11);
	p.enQueue(13);
	p.enQueue(17);
	p.enQueue(19);
	q.merge(p);//p和q为等高的树
	cout << "\nAfter merge(p), the head of priorityQueue is " << q.getHead() << endl;

	return 0;
}
