
template<typename Type>
class closeHash//Table :public hashTable<Type>
{
private:
	struct node//散列表的结点类
	{
		Type data;
		int state;//0:空单元 1:有效元素 2:已删除

		node() { state = 0; }
	};
	node *array;
	int size;

	int load;//散列表中的元素个数
	int dead;//已被删除的元素个数
	int deadline;//被删除元素个数的上限
	int(*key)(const int &x);//取出元素x的键，并转换成整型
	static int defaultKey(const int &k) { return k; }//缺省的转换函数

	void rehash();//整理散列表
	void doubleSpace();
	bool isPrime(int n);
	int nextPrime(int n);

public:
	closeHash(int length = MAXN, int die = MAXN / 2, int(*f)(const Type &x) = defaultKey) :load(0), deadline(die), dead(0)
	{
		size = nextPrime(length);//选择大于或等于length的最小素数作为表长
		array = new node[size];
		key = f;
	}
	~closeHash() { delete[]array; }
	bool find(const Type &x)const;
	bool insert(const Type &x);
	bool remove(const Type &x);

};

template <typename Type>
bool closeHash<Type>::remove(const Type &x)
{
	int initPos, pos;
	initPos = pos = key(x) % size;

	do {
		if (array[pos].state == 0)return false;
		if (array[pos].state == 1 && array[pos].data == x)
		{
			array[pos].state = 2;
			--load;
			++dead;
			if (dead > deadline)
				rehash();//超过指定的值，重新散列
			return true;
		}
		pos = (pos + 1) % size;
	} while (pos != initPos);

	return false;
}

template <typename Type>
bool closeHash<Type>::insert(const Type &x)
{
	int initPos, pos;
	initPos = pos = key(x) % size;
	do
	{
		if (array[pos].state != 1)//找到位置，添加元素
		{
			array[pos].data = x;
			array[pos].state = 1;
			++load;//有效元素数+1
			if (load * 2 >= size)//负载因子达到0.5，扩大空间
			{
				doubleSpace();
			}
			return true;
		}
		if (array[pos].state == 1 && array[pos].data == x)//重复插入
			return true;
		pos = (pos + 1) % size;
	} while (pos != initPos);
	return false;
}

template <typename Type>
bool closeHash<Type>::find(const Type &x)const
{
	int initPos, pos;
	initPos = pos = key(x) % size;
	do {
		if (array[pos].state == 0)return false;
		if (array[pos].state == 1 && array[pos].data == x)return true;
		pos = (pos + 1) % size;
	} while (pos != initPos);

	return false;
}

template <typename Type>
void closeHash<Type>::rehash()
{
	dead = 0;
	node *tmp = array;
	array = new node[size];

	for (int i = 0;i < size;++i)
	{
		if (tmp[i].state == 1)
			insert(tmp[i].data);
	}

	delete[]tmp;
}

template <typename Type>
void closeHash<Type>::doubleSpace()
{
	node *tmp = array;
	int oldsize = size;

	size = nextPrime(oldsize * 2);
	deadline *= 2;
	load = 0;
	array = new node[size];
	for (int i = 0;i < oldsize;i++)
		if (tmp[i].state == 1)
			insert(tmp[i].data);
	delete[]tmp;
}

template <typename T>
bool closeHashTable<T>::isPrime(int n)//判断n是否为素数
{
	if (n == 2 || n == 3)
		return true;
	if (n == 1 || n % 2 == 0)
		return false;
	for (int i = 3;i*i <= n;i += 2)
		if (n%i == 0)
			return false;
	return true;
}

template <typename T>
int closeHashTable<T>::nextPrime(int n)//寻找大于或等于n的最小素数
{
	if (n % 2 == 0)
		++n;
	while (!isPrime(n))
		n += 2;
	return n;
}
