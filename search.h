//本文件中包含顺序查找、二分查找、分块查找和插值查找

#include <iostream>
#include <vector>

using namespace std;
//顺序查找
template<typename T>
int seqSearch(vector <T> &data, const T &x)
{
	int i;
	for (i = data.size()-1;(i>=0)&&(x!=data[i]);--i);
	if(i<0)
        return -1;
	else
        return i;
}

//二分查找
template <typename Type>
int binarySearch(const vector<Type> &data, const Type &x)
{
	int low = 1, high = data.size()+1,mid;
	while (low <= high)//查找区间存在
	{
		mid = (low + high) /2;
		if(x==data[mid])
			return mid;
		if(x<data[mid])
			high = mid -1;
		else
			low = mid +1 ;
	}
	return -1;
}

//分块查找
template <typename T>
class indexList
{
	int blockSize;      //块的大小
	int listSize;       //表中的元素个数
	vector<T> data;            //数据区
	vector<T> index;           //索引区

	public:
	indexList(int bs, vector<T> d) //bs:块长， ls:元素数， d:元素值
	{
		int i;
        int ls = d.size();
		blockSize = bs;
		listSize = ls;
		for (i = 0;i<ls;++i)
			data.push_back(d[i]);
		for (i=0;i<(ls-1)/bs;++i)
			index.push_back(data[(i+1)*bs-1]);
		index.push_back(data[ls-1]);
	}
	~indexList(){data.clear();index.clear();}
	int find(T x)const;
};

//find函数实现
template <typename T>
int indexList<T>::find(T x)const
{
	int indexLength = listSize==0?0:(listSize-1)/blockSize + 1;
	int i;
	for(i = 0;i<indexLength;++i)        //查找索引区
		if(x<=index[i])
			break;
	if(i==indexLength)                  //找不到相应的数据块
		return -1;

	int start, end;
	if(i==0)
		start = 0;
	else
		start = i*blockSize;            //计算数据块的起始位置
	end = blockSize*(i+1)-1;            //计算数据块的终止位置
	end = (end<listSize?end:listSize);

	for(i = start;i<=end;++i)
		if(x==data[i])
			return i;                   //查找数据块
	return -1;
}

//插值查找
template <typename T>
int interpolationSearch(const vector<T> &data, const T &key)
{
	int low,high,mid;
	low = 0;
	high = data.size() - 1;
	while(low <= high)
	{
		mid = low + (high - low) * (key - data[low]) / (data[high] - data[low]); //此处于二分查找不同,套用插值公式
		if(data[mid] > key)			                                //如果key比插值小,把高位调整为插值下标的下一位
			high = mid - 1;
		else if(data[mid] < key)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}
