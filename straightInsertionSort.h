template <typename T>
struct node
{
	T data;
	node *next;

	node() { next = nullptr; }
	node(T data) :data(data) { next = nullptr; }

};

template <typename T>
void sort(node<T> *p)
{
	node <T> *insert, *pos, *tmp;

	if (p->next = nullptr || p->next->next == nullptr)
		return;
	insert = p->next;
	while (insert->next != nullptr)//依次插入每个结点
	{
		for (pos = p;pos != insert&&pos->next->data < insert->next->data;pos = pos->next);
		if (pos == insert) { insert = insert->next;continue; }
		tmp = insert->next;
		insert->next = tmp->next;
		tmp->next = pos->next;
		pos->next = tmp;
	}
}