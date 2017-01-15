template <typename T>
void sort(node<T> *&head)
{
	int n = 0;
	node <T> *p = head;

	while (p)
	{
		++n;
		p = p->next;
	}
	head = merge(head, n);
}

template<typename T>
node<T> *merge(node<T>*h, int n)
{
	if (n <= 1)return h;
	int n1, n2, t1, t2, i;
	node <T> *h1, *h2, *newh, *last, *p;

	//将表h分成两个子表,h和h2
	n1 = n / 2;n2 = n - n1;//n1是h的长度，n2是h2的长度
	for (i = 0, p = h;i < n1 - 1;++i)p = p->next;
	h2 = p->next;
	p->next = nullptr;//第一个子表和第二个子表断开
	h1 = merge(h, n1);//排序第一个子表
	h2 = merge(h2, n2);//排序第二个子表

	//归并两个有序表
	if (h1->data < h2->data)//设置表头
	{
		newh = h1;
		h1 = h1->next;
	}
	else
	{
		newh = h2;
		h2 = h2->next;
	}
	last = newh;
	while (h1 != nullptr&&h2 != nullptr)//当子表1和子表2均非空
	{
		if (h1->data < h2->data)
		{
			last->next = h1;
			h1 = h1->next;
		}
		else
		{
			last->next = h2;
			h2 = h2->next;
		}
		last = last->next;
	}
	if (h1 == nullptr)
		last->next = h2;
	else
		last->next = h1;
	return newh;
}