#include <iostream>

using namespace std;

template <typename T>
class set
{
    template <typename U>
	friend set<U> operator*(const set<U> &a, const set<U> &b);//交
    template <typename U>
	friend set<U> operator+(const set<U> &a, const set<U> &b);//并
    template <typename U>
	friend set<U> operator-(const set<U> &a, const set<U> &b);//差

private:
	T *elem;						//存放集合元素的数组
	int size, volume;				//当前集合元素个数与容量
	void doubleSpace();				//扩展空间函数
	bool exist(T x)const;			//查找x是否存在函数

public:
	set();
	set(const set<T> &a);
	~set(){delete []elem;}

	set &operator=(const set<T> &a);	//重载赋值运算符
	int getSize(){return size;}			//返回集合元素个数
	bool insert(T x);					//插入函数
	bool erase (T x);					//删除函数
	void display();						//输出函数
};

template <typename T>
set<T>::set()							//构造函数
{
	size = 0;
	volume = 20;
	elem = new T[volume];
}

template <typename T>
set<T>::set(const set<T> &a)			//复制构造函数
{
	size = a.size;
	volume = a.volume;
	elem = new T[volume];
	for (int i = 0; i < size; ++i)
		elem[i]=a.elem[i];
}

template <typename T>
void set<T>::doubleSpace()				//扩展空间函数
{
	volume *=2;
	T *tmp = new T[volume];
	for (int i = 0; i<size; ++i)
		tmp[i] = elem[i];
	delete []elem;
	elem = tmp;
}

template <typename T>
bool set<T>::exist(T x)const			//查找函数
{
	for (int i = 0; i<size; ++i)
		if(elem[i]==x)
			return true;
	return false;
}

template <typename T>
bool set<T>::insert(T x)				//插入函数
{
	if(exist(x))
		return false;
	if(size==volume)
		doubleSpace();
	elem[size++]=x;
	return true;
}

template <typename T>					//删除函数
bool set<T>::erase(T x)
{
	bool flag = false;
	int i;
	for (i=0; i<size; ++i)
		if(elem[i]==x)
		{
			flag = true;
			break;
		}
	if(flag)
		for (;i<size-1;++i)
			elem[i]=elem[i+1];
	return flag;
}

template <typename T>
set<T> &set<T>::operator=(const set<T> &a)	//等号重载
{
	size = a.size;
	delete []elem;
	elem = new T[size];
	for (int i=0;i<size;++i)
		elem[i]=a.elem[i];
	return *this;
}

template <typename T>
void set<T>::display()						//显示函数
{
	for (int i=0; i<size; ++i)
		cout << elem[i]<<" ";
	cout <<endl;
}

template <typename U>
set<U> operator*(const set<U> &a, const set<U> &b)	//交函数的实现
{
	set<U> c;
	for (int i=0; i<a.size;++i)						//检查a集合的每一个元素
		if(b.exist(a.elem[i]))
			c.insert(a.elem[i]);
	return c;
}

template <typename U>
set<U> operator+(const set<U> &a, const set<U> &b)	//并函数的实现
{
	set<U> c =a;
	for (int i=0;i<b.size;++i)
		c.insert(b.elem[i]);
	return c;
}

template<typename U>
set<U> operator-(const set<U> &a, const set<U> &b)	//差函数的实现
{
	set<U> c;
	for (int i=0;i<a.size;++i)
		if(!b.exist(a.elem[i]))
			c.insert(a.elem[i]);
	return c;
}

