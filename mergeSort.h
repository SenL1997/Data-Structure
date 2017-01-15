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

	//����h�ֳ������ӱ�,h��h2
	n1 = n / 2;n2 = n - n1;//n1��h�ĳ��ȣ�n2��h2�ĳ���
	for (i = 0, p = h;i < n1 - 1;++i)p = p->next;
	h2 = p->next;
	p->next = nullptr;//��һ���ӱ�͵ڶ����ӱ�Ͽ�
	h1 = merge(h, n1);//�����һ���ӱ�
	h2 = merge(h2, n2);//����ڶ����ӱ�

	//�鲢���������
	if (h1->data < h2->data)//���ñ�ͷ
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
	while (h1 != nullptr&&h2 != nullptr)//���ӱ�1���ӱ�2���ǿ�
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