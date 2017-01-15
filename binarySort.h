template <typename T>
void binarySort(T a[], int size)
{
	int i, j, k, mid;
	T tmp;

	for (k = 1;k < size;++k)//逐个插入第1~size-1号元素
	{
		i = 0;
		j = k - 1;
		while (i <= j)//寻找插入位置
		{
			mid = (i + j) / 2;
			if (a[k] == a[mid])return;
			if (a[k] < a[mid])j = mid - 1;
			else i = mid + 1;
		}

		if (a[k] < a[mid])i = j;//i为插入位置

		//插入a[k]
		tmp = a[k];
		for (;k > i;--k)
			a[k] = a[k - 1];
		a[i] = tmp;
	}
}
