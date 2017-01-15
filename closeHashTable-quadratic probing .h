template <typename T>
class closeHashTable
{
public:
	closeHashTable(int length = 101, int(*f)(const T &x) = defaultKey)
	{
		size = nextPrime(length);
		array = new node[size];
		key = f;
		load = 0;
	}
	~closeHashTable() { delete[] array; }
	bool find(const T &x)const;
	bool insert(const T &x);
	bool remove(const T &x);
	void rehash();

private:
	struct node
	{
		T data;
		int state;//0 -- empty 1 -- active 2 -- deleted

		node() { state = 0; }
	};
	node *array;
	int size, load;//size�������ģ, load:��ЧԪ����
	int(*key)(const T &x);
	static int defaultKey(const int &k) { return k; }

	void doubleSpace();
	bool isPrime(int n);
	int nextPrime(int n);
};

template <typename T>
bool closeHashTable<T>::find(const T &x)const
{
	int initPos, pos;
	int collisionNum = 0;//��ײ����

	initPos = pos = key(x) % size;
	do
	{
		if (array[pos].state == 0)
			return false;
		if (array[pos].state == 1 && array[pos].data == x)
			return true;
		pos = (pos + 2 * (++collisionNum) - 1) % size;//����һ̽���ַ
	} while (pos != initPos);
	return false;
}

template <typename T>
bool closeHashTable<T>::insert(const T &x)
{
	int initPos, pos;
	int collisionNum = 0;//��ײ����

	if (load * 2 >= size)
		doubleSpace();//����������������ռ�
	initPos = pos = key(x) % size;
	do
	{
		if (array[pos].state != 1)
		{
			array[pos].data = x;
			array[pos].state = 1;
			++load;//�²���һ��Ԫ�أ���������++
			return true;
		}
		if (array[pos].state == 1 && array[pos].data == x)//�Ѵ���
			return true;
		pos = (pos + 2 * (++collisionNum) - 1) % size;//����һ̽��λ��
	} while (pos != initPos);
	return false;
}

template <typename T>
bool closeHashTable<T>::remove(const T &x)
{
	int initPos, pos;
	int collisionNum = 0;

	initPos = pos = key(x) % size;
	do
	{
		if (array[pos].state == 0)
			return false;
		if (array[pos].state == 1 && array[pos].data == x)
		{
			array[pos].state = 2;
			--load;//Ԫ�ر�ɾ������������--
			return true;
		}
		pos = (pos + 2 * (++collisionNum) - 1) % size;
	} while (pos != initPos);
	return false;
}

template <typename T>
void closeHashTable<T>::doubleSpace()
{
	node *tmp = array;
	int oldsize = size;

	size = nextPrime(oldsize * 2);
	load = 0;

	array = new node[size];
	for (int i = 0;i < oldsize;i++)
		if (tmp[i].state == 1)
			insert(tmp[i].data);
	delete[]tmp;
}

template <typename T>
void closeHashTable<T>::rehash()
{
	node *tmp = array;
	array = new node[size];
	load = 0;
	for (int i = 0;i < size;i++)
		if (tmp[i].state = 1)
			insert(tmp[i].data);
	delete[]tmp;
}

template <typename T>
bool closeHashTable<T>::isPrime(int n)//�ж�n�Ƿ�Ϊ����
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
int closeHashTable<T>::nextPrime(int n)//Ѱ�Ҵ��ڻ����n����С����
{
	if (n % 2 == 0)
		++n;
	while (!isPrime(n))
		n += 2;
	return n;
}
