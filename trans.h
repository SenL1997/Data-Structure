void trans(int a[], int size)
{
	int vacant;//���ⵥԪ
	int left = 0;//��ǵ�ǰ�����������
	int right = size - 1;//�Ҷ�

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
