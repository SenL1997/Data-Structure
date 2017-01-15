
template<typename Type>
class closeHash//Table :public hashTable<Type>
{
private:
	struct node//ɢ�б�Ľ����
	{
		Type data;
		int state;//0:�յ�Ԫ 1:��ЧԪ�� 2:��ɾ��

		node() { state = 0; }
	};
	node *array;
	int size;

	int load;//ɢ�б��е�Ԫ�ظ���
	int dead;//�ѱ�ɾ����Ԫ�ظ���
	int deadline;//��ɾ��Ԫ�ظ���������
	int(*key)(const int &x);//ȡ��Ԫ��x�ļ�����ת��������
	static int defaultKey(const int &k) { return k; }//ȱʡ��ת������

	void rehash();//����ɢ�б�
	void doubleSpace();
	bool isPrime(int n);
	int nextPrime(int n);

public:
	closeHash(int length = MAXN, int die = MAXN / 2, int(*f)(const Type &x) = defaultKey) :load(0), deadline(die), dead(0)
	{
		size = nextPrime(length);//ѡ����ڻ����length����С������Ϊ��
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
				rehash();//����ָ����ֵ������ɢ��
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
		if (array[pos].state != 1)//�ҵ�λ�ã����Ԫ��
		{
			array[pos].data = x;
			array[pos].state = 1;
			++load;//��ЧԪ����+1
			if (load * 2 >= size)//�������Ӵﵽ0.5������ռ�
			{
				doubleSpace();
			}
			return true;
		}
		if (array[pos].state == 1 && array[pos].data == x)//�ظ�����
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
