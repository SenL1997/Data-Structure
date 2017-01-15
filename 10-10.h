#include "quickSort.h"

void sqrN(int a[], int size, int k)
{
	for (int i = 0;i < size - 1;++i)
		for (int j = i + 1;j < size;++j)
			if (a[i] + a[j] = k)
				cout << a[i] << "+" << a[j] << "=" << k << endl;
}

void nLogN(int a[], int size, int k)
{
	quickSort(a, size);
	int j = size - 1, i = 0;
	while (i < j)
	{
		if (a[i] + a[j]>k)--j;
		else if (a[i] + a[j] == k)
			cout << a[i++] << "+" << a[j--] << "=" << k << endl;
		else
			++i;
	}
}