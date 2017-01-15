#include <vector>

template<typename T>
int seqSearch(vector <T> &data, const T &x)
{
	int i;
	for (i = data.size()-1;(i>=0)&&(x!=data[i]);--i);
	if(i<0)
        return -1;
	if(i!=data.size()-1)				//交换i和i+1中的元素
	{
		data[i] = data[i+1];
		data[i+1] = x;
		++i;
	}
	return i;
}
