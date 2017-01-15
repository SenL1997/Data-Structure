#ifndef HFTREE_H_INCLUDED
#define HFTREE_H_INCLUDED

//����������ͷ�ļ�

#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

template <class Type>
class hfTree
{
private:
	struct Node//�����е�Ԫ������
	{
		Type data;//���ֵ
		int weight;//����Ȩֵ
		int parent, left, right;//����㼰���Ҷ��ӵ��±��ַ
	};

	Node *elem;
	int length;

public:
	struct hfCode//������������������
	{
		Type data;//��������ַ�
		string code;//��Ӧ�Ĺ���������
	};

	hfTree(const Type *x, const int *w, int size);
	void getCode(hfCode result[]);//�ӹ����������ɹ���������
	int cost(const hfCode result[]);
	double rate(const hfCode result[]);
	~hfTree() { delete[] elem; }
};

template<class Type>
hfTree<Type>::hfTree(const Type * v, const int * w, int size)
{
	const int MAX_INT = 32767;
	int min1, min2;//��С��������С����Ȩֵ
	int x, y;//��С��������С�����±�

			 //�ó�ֵ
	length = 2 * size;
	elem = new Node[length];

	for (int i = size; i < length; ++i)
	{
		elem[i].weight = w[i - size];
		elem[i].data = v[i - size];
		elem[i].parent = elem[i].left = elem[i].right = 0;
	}
	//�鲢ɭ���е���
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
	int p, s;//sΪ׷�ݹ��������ڴ���ڵ���±꣬p��s�ĸ�����±�
	for (int i = size; i < length; ++i)//��ÿ��������ķ���
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

//����������
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
//��ȳ�������ȣ�������۽��͵ĳ̶�
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
