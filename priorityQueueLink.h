#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED

template <typename T>
class priorityQueue
{
private:
	struct node						//二叉堆结点类
	{
		T data;
		node *lchild, *rchild, *parent;

		node(T d, node *l = nullptr, node *r = nullptr, node *p = nullptr) :data(d), lchild(l), rchild(r), parent(p) {};
		node() :lchild(nullptr), rchild(nullptr), parent(nullptr) {};
	};

	node * root;					//根结点
	int size;						//堆的规模

	void percolateDown(node * hole);	//向下过滤函数
	void clear(node * &p);				//清空函数
	node * &find(int x);				//定位函数
	node * &merge(node * &t1, node * &t2);


public:
	priorityQueue() { size = 0; root = nullptr; }
	~priorityQueue() { clear(root); root = nullptr; }
	void enQueue(T elem);					//入队
	T deQueue();							//出队
	T getHead() { return root->data; }		//取队首
	bool isEmpty() { return size == 0; }	//判断是否队空
	void merge(priorityQueue <T> &other)
	{
		root = merge(root, other.root);		//调用递归的merge函数完成归并
		size *= 2;							//归并后堆的规模扩大一倍
		other.root = nullptr;				//归并后，作为参数的堆不存在了
		other.size = 0;
	}

};

template <typename T>
void priorityQueue<T>::clear(node *&p)
{
	if (p == nullptr)return;
	clear(p->lchild);					//删除左子树
	clear(p->rchild);					//删除右子树
	delete p;							//删除根结点
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
	++size;												//堆的规模+1
	if (root == nullptr)
	{
		root = new node(elem);							//若为空树，新插入的结点作为根结点
		return;
	}
	node *p = find(size / 2);							//找到新插入结点的父亲
	if (size % 2)										
	{
		p->rchild = new node(elem, nullptr, nullptr, p);
		p = p->rchild;
	}
	else                                                 //插入为父亲的左儿子
	{
		p->lchild = new node(elem, nullptr, nullptr, p);
		p = p->lchild;
	}
	//向上过滤
	for (;p != root&&elem<p->parent->data;p = p->parent)
		p->data = p->parent->data;
	p->data = elem;
}

template <typename T>
T priorityQueue<T>::deQueue()
{
	T value = root->data;	//保存根结点的值
	node *p = find(size);	//p为堆中最后一个结点的地址
	root->data = p->data;	//最后一个结点的值存入根结点
	--size;					//堆的规模-1
	if (p == root)			//出队后队列为空
	{
		delete root;
		root = nullptr;
	}
	else
	{					//释放p结点的空间，并修改父亲结点的指针值，然后执行向下过滤
		(p == p->parent->rchild) ? p->parent->lchild = nullptr : p->parent->rchild = nullptr;
		delete p;
		percolateDown(root);
	}
	return value;		//返回队元素值
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
	node *p;				//存放左子堆和右子堆归并的结果
	if (t1->data < t2->data)//t1作为新堆的根
	{
		if (t1->lchild != nullptr)//t1有儿子，归并两个儿子作为t1的右子堆
		{
			p = merge(t1->lchild, t1->rchild);
			t1->rchild = p;
			p -> parent = t1;
		}
		t1->lchild = t2;			//t2作为t1的左子堆
		t2->parent = t1;		
		return t1;
	}
	else
	{								//t2作为新堆的根
		if (t2->lchild != nullptr)	//t2有儿子，归并两个儿子作为t2的右子堆
		{
			p = merge(t2->lchild, t2->rchild);
			t2->rchild = p;
			p->parent = t2;
		}
		t2->lchild = t1;			//t1作为t2的左子堆
		t1->parent = t2;
		return t2;
	}
}

#endif // PRIORITYQUEUE_H_INCLUDED
