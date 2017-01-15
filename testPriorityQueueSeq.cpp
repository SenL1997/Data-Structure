#include <iostream>
#include "priorityQueueSeq.h"

using namespace std;

int main()
{
	int a[16] = { 3,6,7,12,8,21,14,15,37,18,24,23,33,18,17,26 };
	priorityQueue<int> q(a, 16);
	cout << "At the beginning, the head of priorityQueue is " << q.getHead() << endl;

	int b = q.findMin(9);
	cout << "\n优先级大于等于指定元素9的最小值下标是：" << b << endl;

	b = q.findMin(15);
	cout << "优先级大于等于指定元素15的最小值下标是：" << b << endl;

	b = q.findMin(20);
	cout << "优先级大于等于指定元素20的最小值下标是：" << b << endl;

	b = q.findMin(25);
	cout << "优先级大于等于指定元素25的最小值下标是：" << b << endl;

	q.decreaseKey(3,5);
	cout << "\nAfter decreaseKey(3,2), the head of priorityQueue is " << q.getHead() <<endl;

	q.deQueue();
	cout << "\nAfter deQueue(), the head of priorityQueue is " << q.getHead() << endl;

	q.deQueue();
	cout << "After deQueue(), the head of priorityQueue is " << q.getHead() << endl;

	q.deQueue();
	cout << "After deQueue(), the head of priorityQueue is " << q.getHead() << endl;

	q.deQueue();
	cout << "After deQueue(), the head of priorityQueue is " << q.getHead() << endl;

	q.enQueue(1);
	cout << "\nAfter enQueue(1), the head of priorityQueue is " << q.getHead() << endl;

	return 0;
}
