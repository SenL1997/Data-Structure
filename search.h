//���ļ��а���˳����ҡ����ֲ��ҡ��ֿ���ҺͲ�ֵ����

#include <iostream>
#include <vector>

using namespace std;
//˳�����
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

//���ֲ���
template <typename Type>
int binarySearch(const vector<Type> &data, const Type &x)
{
	int low = 1, high = data.size()+1,mid;
	while (low <= high)//�����������
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

//�ֿ����
template <typename T>
class indexList
{
	int blockSize;      //��Ĵ�С
	int listSize;       //���е�Ԫ�ظ���
	vector<T> data;            //������
	vector<T> index;           //������

	public:
	indexList(int bs, vector<T> d) //bs:�鳤�� ls:Ԫ������ d:Ԫ��ֵ
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

//find����ʵ��
template <typename T>
int indexList<T>::find(T x)const
{
	int indexLength = listSize==0?0:(listSize-1)/blockSize + 1;
	int i;
	for(i = 0;i<indexLength;++i)        //����������
		if(x<=index[i])
			break;
	if(i==indexLength)                  //�Ҳ�����Ӧ�����ݿ�
		return -1;

	int start, end;
	if(i==0)
		start = 0;
	else
		start = i*blockSize;            //�������ݿ����ʼλ��
	end = blockSize*(i+1)-1;            //�������ݿ����ֹλ��
	end = (end<listSize?end:listSize);

	for(i = start;i<=end;++i)
		if(x==data[i])
			return i;                   //�������ݿ�
	return -1;
}

//��ֵ����
template <typename T>
int interpolationSearch(const vector<T> &data, const T &key)
{
	int low,high,mid;
	low = 0;
	high = data.size() - 1;
	while(low <= high)
	{
		mid = low + (high - low) * (key - data[low]) / (data[high] - data[low]); //�˴��ڶ��ֲ��Ҳ�ͬ,���ò�ֵ��ʽ
		if(data[mid] > key)			                                //���key�Ȳ�ֵС,�Ѹ�λ����Ϊ��ֵ�±����һλ
			high = mid - 1;
		else if(data[mid] < key)
			low = mid + 1;
		else
			return mid;
	}
	return -1;
}
