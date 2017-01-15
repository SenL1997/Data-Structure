void trans(int a[], int size)
{
	int vacant;//额外单元
	int left = 0;//标记当前搜索到的左端
	int right = size - 1;//右端

	while (left < right)
	{
		while (left < right&&a[left] < 0)++left;
		while (left < right&&a[right]>0)--right;
		if (left < right)
		{
			vacant = a[left];
			a[left] = a[right];
			a[right] = vacant;
		}
	}
}
