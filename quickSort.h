template<typename T>
void quickSort(T a[], int low, int high)
{
	int mid;

	if (low >= high)//待分段的元素只有一个或0个，递归终止
		return;
	mid = divide(a, low, high);
	quickSort(a, low, mid - 1);//排序左一半
	quickSort(a, mid + 1, high);//排序右一半
}

//快排的包裹函数
template <typename T>
void quickSort(T a[], int size)
{
	quickSort(a, 0, size - 1);
}

template <typename T>
int divide(T a[], int low, int high)
{
	T k = a[low];

	do
	{
		while (low < high&&a[high] >= k)--high;
		if (low < high)
		{
			a[low] = a[high];
			++low;
		}
		while (low < high&&a[low] <= k)++low;
		if (low < high)
		{
			a[high] = a[low];
			--high;
		}
	} while (low != high);
	a[low] = k;
	return low;
}