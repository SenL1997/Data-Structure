template <typename T>
void sort(node <T> *p)
{
	node<T>*last, *pos, *minp, *tmp;
	T min;

	if (p->next == nullptr || p->next->next == nullptr)return;
	for (last = p;last->next != nullptr;last = last->next)
	{
		minp = last;
		min = minp->next->data;
		for (pos = last->next;pos->next != nullptr;pos=pos->next)
			if (pos->next->data < min)
			{
				minp = pos;
				min = pos->next->data;
			}
		if (minp == last)continue;
		tmp = minp->next;
		minp->next = tmp->next;
		tmp->next = last->next;
		last->next = tmp;
	}
}