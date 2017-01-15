#include <iostream>

using namespace std;

template <typename T>
class set
{
    template <typename U>
	friend set<U> operator*(const set<U> &a, const set<U> &b);//���Ͻ�
    template <typename U>
	friend set<U> operator+(const set<U> &a, const set<U> &b);//���ϲ�
    template <typename U>
	friend set<U> operator-(const set<U> &a, const set<U> &b);//���ϲ�
    template <typename U>
	friend ostream &operator<< (ostream &os, const set<U> &s);//�������

private:
	struct node												//�����
	{
		T data;
		node * next;
		node (node *ne = nullptr):next(ne){}
	};
	node *arr;												//ͷָ��
	bool exist(const T &t)const;
	void clear();

public:
	set(){arr = new node;}
	set(const set &s);
	~set(){clear();	delete arr;};							//��������

	set &operator=(const set &s);
	void insert(const T &x);
	void erase (const T &x);
};

template <typename T>
set<T>::set(const set<T> &s)								//���ƹ��캯��
{
	arr = new node;
	node *n = s.arr->next;
	while(n!=nullptr)
	{
		insert(n->data);
		n=n->next;
	}
}

template <typename T>									//��ռ��ϣ�ֻ����ͷ���
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
bool set<T>::exist(const T &t)const							//���t�Ƿ��ڼ�����
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
void set<T>::insert(const T &t)								//�򼯺ϲ���Ԫ�غ���
{
	node *q = new node(arr->next);
	q->data = t;
	arr->next = q;
}

template <typename T>										//ɾ���������Ӽ���ɾ��t
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
set<T> &set<T>::operator=(const set<T> &s)					//��ֵ��������غ���
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
set<U> operator*(const set<U> &s1, const set<U> &s2)		//������ʵ��
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
set<U> operator+(const set<U> &s1, const set<U> &s2)		//������ʵ��
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
set<U> operator-(const set<U> &s1, const set<U> &s2)		//���ʵ��
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
ostream & operator <<(ostream &os, const set<U> &s)			//�������Ԫ��
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
