#ifndef HFTREE_H_INCLUDED
#define HFTREE_H_INCLUDED

//哈夫曼树的头文件

#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

template <class Type>
class hfTree
{
private:
	struct Node//数组中的元素类型
	{
		Type data;//结点值
		int weight;//结点的权值
		int parent, left, right;//父结点及左右儿子的下标地址
	};

	Node *elem;
	int length;

public:
	struct hfCode//保存哈夫曼编码的类型
	{
		Type data;//待编码的字符
		string code;//对应的哈夫曼编码
	};

	hfTree(const Type *x, const int *w, int size);
	void getCode(hfCode result[]);//从哈夫曼树生成哈夫曼编码
	int cost(const hfCode result[]);
	double rate(const hfCode result[]);
	~hfTree() { delete[] elem; }
};

template<class Type>
hfTree<Type>::hfTree(const Type * v, const int * w, int size)
{
	const int MAX_INT = 32767;
	int min1, min2;//最小树，次最小树的权值
	int x, y;//最小树，次最小树的下标

			 //置初值
	length = 2 * size;
	elem = new Node[length];

	for (int i = size; i < length; ++i)
	{
		elem[i].weight = w[i - size];
		elem[i].data = v[i - size];
		elem[i].parent = elem[i].left = elem[i].right = 0;
	}
	//归并森林中的树
	for (int i = size - 1;i>0;--i)
	{
		min1 = min2 = MAX_INT;
		x = y = 0;
		for (int j = i + 1; j < length; ++j)
		{
			if (elem[j].parent == 0)
			{
				if (elem[j].weight < min1)
				{
					min2 = min1;
					min1 = elem[j].weight;
					x = y;
					y = j;
				}
				else if (elem[j].weight < min2)
				{
					min2 = elem[j].weight;
					x = j;
				}
			}
		}
		elem[i].weight = min1 + min2;
		elem[i].left = x;
		elem[i].right = y;
		elem[i].parent = 0;
		elem[x].parent = i;
		elem[y].parent = i;
	}
}

template<class Type>
void hfTree<Type>::getCode(hfCode result[])
{
	int size = length / 2;
	int p, s;//s为追溯过程中正在处理节点的下标，p是s的父结点下标
	for (int i = size; i < length; ++i)//对每个带编码的符号
	{
		result[i - size].data = elem[i].data;
		p = elem[i].parent;
		s = i;
		while (p)
		{
			if (elem[p].left == s)
				result[i - size].code = '0' + result[i - size].code;
			else
				result[i - size].code = '1' + result[i - size].code;
			s = p;
			p = elem[p].parent;
		}
	}
}

//计算代码代价
template <typename Type>
int hfTree<Type>::cost(const hfCode result[])
{
	int s=0;
	for (int i = 0; i<length/2; i++)
	{
		s = s + (result[i].code.length())*(elem[length/2 + i].weight);
	}
	return s;
}
//与等长编码相比，编码代价降低的程度
template <typename Type>
double hfTree<Type>::rate(const hfCode result[])
{
	double s1 = 0, s2 = 0, t = ceil(log(length / 2) / log(2));
	for (int i = 0; i<length / 2; i++)
	{
		s1 = s1 + (result[i].code.length())*(elem[length / 2 + i].weight);
		s2 = s2 + (t*(elem[length / 2 + i].weight));
	}

	return (100 - s1 / s2 * 100);
}

#endif // HFTREE_H_INCLUDED
