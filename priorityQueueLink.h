#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED

template <typename T>
class priorityQueue
{
private:
	struct node						//����ѽ����
	{
		T data;
		node *lchild, *rchild, *parent;

		node(T d, node *l = nullptr, node *r = nullptr, node *p = nullptr) :data(d), lchild(l), rchild(r), parent(p) {};
		node() :lchild(nullptr), rchild(nullptr), parent(nullptr) {};
	};

	node * root;					//�����
	int size;						//�ѵĹ�ģ

	void percolateDown(node * hole);	//���¹��˺���
	void clear(node * &p);				//��պ���
	node * &find(int x);				//��λ����
	node * &merge(node * &t1, node * &t2);


public:
	priorityQueue() { size = 0; root = nullptr; }
	~priorityQueue() { clear(root); root = nullptr; }
	void enQueue(T elem);					//���
	T deQueue();							//����
	T getHead() { return root->data; }		//ȡ����
	bool isEmpty() { return size == 0; }	//�ж��Ƿ�ӿ�
	void merge(priorityQueue <T> &other)
	{
		root = merge(root, other.root);		//���õݹ��merge������ɹ鲢
		size *= 2;							//�鲢��ѵĹ�ģ����һ��
		other.root = nullptr;				//�鲢����Ϊ�����ĶѲ�������
		other.size = 0;
	}

};

template <typename T>
void priorityQueue<T>::clear(node *&p)
{
	if (p == nullptr)return;
	clear(p->lchild);					//ɾ��������
	clear(p->rchild);					//ɾ��������
	delete p;							//ɾ�������
}

template <typename T>
typename priorityQueue<T>::node *&priorityQueue<T>::find(int x)
{
	if (x == 1)return root;
	if (x % 2) return find(x / 2)->rchild;
	else return find(x / 2)->lchild;
}

template <typename T>
void priorityQueue<T>::enQueue(const T elem)
{
	++size;												//�ѵĹ�ģ+1
	if (root == nullptr)
	{
		root = new node(elem);							//��Ϊ�������²���Ľ����Ϊ�����
		return;
	}
	node *p = find(size / 2);							//�ҵ��²�����ĸ���
	if (size % 2)										
	{
		p->rchild = new node(elem, nullptr, nullptr, p);
		p = p->rchild;
	}
	else                                                 //����Ϊ���׵������
	{
		p->lchild = new node(elem, nullptr, nullptr, p);
		p = p->lchild;
	}
	//���Ϲ���
	for (;p != root&&elem<p->parent->data;p = p->parent)
		p->data = p->parent->data;
	p->data = elem;
}

template <typename T>
T priorityQueue<T>::deQueue()
{
	T value = root->data;	//���������ֵ
	node *p = find(size);	//pΪ�������һ�����ĵ�ַ
	root->data = p->data;	//���һ������ֵ��������
	--size;					//�ѵĹ�ģ-1
	if (p == root)			//���Ӻ����Ϊ��
	{
		delete root;
		root = nullptr;
	}
	else
	{					//�ͷ�p���Ŀռ䣬���޸ĸ��׽���ָ��ֵ��Ȼ��ִ�����¹���
		(p == p->parent->rchild) ? p->parent->lchild = nullptr : p->parent->rchild = nullptr;
		delete p;
		percolateDown(root);
	}
	return value;		//���ض�Ԫ��ֵ
}

template <typename T>
void priorityQueue<T>::percolateDown(node * hole)
{
	T tmp = hole->data;
	node *child;
	for (;hole->lchild != nullptr;hole = child)
	{
		child = hole->lchild;
		if (hole->rchild != nullptr&&hole->rchild->data<child->data)
			child = hole->rchild;
		if (child->data<tmp)
			hole->data = child->data;
		else
			break;
	}
	hole->data = tmp;
}

template <class T>
typename priorityQueue<T>::node * &priorityQueue<T>::merge(node * &t1, node * &t2)
{
	node *p;				//������ӶѺ����Ӷѹ鲢�Ľ��
	if (t1->data < t2->data)//t1��Ϊ�¶ѵĸ�
	{
		if (t1->lchild != nullptr)//t1�ж��ӣ��鲢����������Ϊt1�����Ӷ�
		{
			p = merge(t1->lchild, t1->rchild);
			t1->rchild = p;
			p -> parent = t1;
		}
		t1->lchild = t2;			//t2��Ϊt1�����Ӷ�
		t2->parent = t1;		
		return t1;
	}
	else
	{								//t2��Ϊ�¶ѵĸ�
		if (t2->lchild != nullptr)	//t2�ж��ӣ��鲢����������Ϊt2�����Ӷ�
		{
			p = merge(t2->lchild, t2->rchild);
			t2->rchild = p;
			p->parent = t2;
		}
		t2->lchild = t1;			//t1��Ϊt2�����Ӷ�
		t1->parent = t2;
		return t2;
	}
}

#endif // PRIORITYQUEUE_H_INCLUDED
