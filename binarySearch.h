//二分查找的递归实现
template <typename T>
int binarySearch(T *data, int low, int high, T x)
{
	if(low > high)										//没有找到
		return -1;

	int mid=(low+high)/2;
	if(data[mid]==x)
		return mid;										//找到了，返回位置
	if(data[mid]<x)
		return binarySearch(data, mid+1, high, x);		//查找后一半
	else
		return binarySearch(data, low, mid-1, x);		//查找前一半
}

