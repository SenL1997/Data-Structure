#include <iostream>

using namespace std;

template <typename T>
class set
{
    template <typename U>
	friend set<U> operator*(const set<U> &a, const set<U> &b);//集合交
    template <typename U>
	friend set<U> operator+(const set<U> &a, const set<U> &b);//集合并
    template <typename U>
	friend set<U> operator-(const set<U> &a, const set<U> &b);//集合差
    template <typename U>
	friend ostream &operator<< (ostream &os, const set<U> &s);//输出集合

private:
	struct node												//结点类
	{
		T data;
		node * next;
		node (node *ne = nullptr):next(ne){}
	};
	node *arr;												//头指针
	bool exist(const T &t)const;
	void clear();

public:
	set(){arr = new node;}
	set(const set &s);
	~set(){clear();	delete arr;};							//析构函数

	set &operator=(const set &s);
	void insert(const T &x);
	void erase (const T &x);
};

template <typename T>
set<T>::set(const set<T> &s)								//复制构造函数
{
	arr = new node;
	node *n = s.arr->next;
	while(n!=nullptr)
	{
		insert(n->data);
		n=n->next;
	}
}

template <typename T>									//清空集合，只保留头结点
void set<T>::clear()
{
	node *tmp;
	while (arr!=nullptr)
	{
		tmp = arr;
		arr = arr->next;
		delete tmp;
	}
	arr = new node;
}

template <typename T>
bool set<T>::exist(const T &t)const							//检查t是否在集合中
{
	node * now = arr->next;
	while(now != nullptr && now->data!=t)
		now =now ->next;
	if(now != nullptr)
		return true;
	else
		return false;
}

template <typename T>
void set<T>::insert(const T &t)								//向集合插入元素函数
{
	node *q = new node(arr->next);
	q->data = t;
	arr->next = q;
}

template <typename T>										//删除函数，从集合删除t
void set<T>::erase(const T &t)
{
	node * now = arr;
	node *p;
	while (now -> next!=nullptr && now->next ->data!=t)
		now = now ->next;
	if(now ->next !=nullptr)
	{
		p=now ->next;
		now -> next = p->next;
		delete p;
	}
}

template <typename T>
set<T> &set<T>::operator=(const set<T> &s)					//赋值运算符重载函数
{
	clear();
	arr = new node;
	node *n = s.arr->next;
	while(n!=nullptr)
	{
		insert (n->data);
		n=n->next;
	}
	return *this;
}

template <typename U>
set<U> operator*(const set<U> &s1, const set<U> &s2)		//交函数实现
{
	set<U> ans;
	typename set<U>::node *s = s1.arr->next;
	while(s!=nullptr)
	{
		if(s2.exist(s->data))
			ans.insert(s->data);
		s=s->next;
	}
	return ans;
}

template <typename U>
set<U> operator+(const set<U> &s1, const set<U> &s2)		//并函数实现
{
	set<U> ans = s1;
	typename set<U>::node *s = s2.arr->next;
	while(s!=nullptr)
	{
		if(!s1.exist(s->data))
			ans.insert(s->data);
		s=s->next;
	}
	return ans;
}

template<typename U>
set<U> operator-(const set<U> &s1, const set<U> &s2)		//差函数实现
{
	set<U> ans;
	typename set<U>::node *s = s1.arr->next;
	while(s!=nullptr)
	{
		if(!s2.exist(s->data))
			ans.insert(s->data);
		s=s->next;
	}
	return ans;
}

template <typename U>
ostream & operator <<(ostream &os, const set<U> &s)			//输出集合元素
{
	typename set<U>::node *n = s.arr->next;
	while(n!=nullptr)
	{
		cout << n->data<<" ";
		n=n->next;
	}
	cout << endl;
	return os;
}
