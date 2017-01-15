template <typename T>
void binarySort(T a[], int size)
{
	int i, j, k, mid;
	T tmp;

	for (k = 1;k < size;++k)//��������1~size-1��Ԫ��
	{
		i = 0;
		j = k - 1;
		while (i <= j)//Ѱ�Ҳ���λ��
		{
			mid = (i + j) / 2;
			if (a[k] == a[mid])return;
			if (a[k] < a[mid])j = mid - 1;
			else i = mid + 1;
		}

		if (a[k] < a[mid])i = j;//iΪ����λ��

		//����a[k]
		tmp = a[k];
		for (;k > i;--k)
			a[k] = a[k - 1];
		a[i] = tmp;
	}
}
