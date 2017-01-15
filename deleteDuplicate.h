#include "quickSort.h"

template<typename T>
int deleteDuplicate(T a[], int size)
{
	int i, j;

	quickSort(a, size);
	for (i = 1, j = 0;i < size;++i)
		if (a[i] != a[j])
			a[++j] = a[i];
	return j + 1;
}

