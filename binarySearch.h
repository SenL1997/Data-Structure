//���ֲ��ҵĵݹ�ʵ��
template <typename T>
int binarySearch(T *data, int low, int high, T x)
{
	if(low > high)										//û���ҵ�
		return -1;

	int mid=(low+high)/2;
	if(data[mid]==x)
		return mid;										//�ҵ��ˣ�����λ��
	if(data[mid]<x)
		return binarySearch(data, mid+1, high, x);		//���Һ�һ��
	else
		return binarySearch(data, low, mid-1, x);		//����ǰһ��
}

