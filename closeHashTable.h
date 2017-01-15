template<typename Type>
class closeHashTable
{
private:
	struct node//ɢ�б�Ľ����
	{
		Type data;
		int state;

		node() { state = 0; }
	};
	node *array;
	int size;
	int(*key)(const Type &x);//ȡ��Ԫ��x�ļ�����ת��������
	static int defaultKey(const int &k) { return k; }//ȱʡ��ת������

public:
	closeHashTable(int length = 101, int(*f)(const Type &x) = defaultKey);
	~closeHashTable() { delete[]array; }
	bool find(const Type &x)const;
	bool insert(const Type &x, int & count);
	bool remove(const Type &x);

	void rehash();//����ɢ�б�
};
template <typename Type>
closeHashTable<Type>::closeHashTable(int length, int(*f)(const Type &x))
{
	size = length;
	array = new node[size];
	key = f;
}

template <typename Type>
bool closeHashTable<Type>::remove(const Type &x)
{
	int initPos, pos;
	initPos = pos = key(x) % size;

	do {
		if (array[pos].state == 0)return false;
		if (array[pos].state == 1 && array[pos].data == x)
		{
			array[pos].state = 2;
			return true;
		}
		pos = (pos + 1) % size;
	} while (pos != initPos);

	return false;
}

template <typename Type>
bool closeHashTable<Type>::insert(const Type &x, int & count)
{
	count = 0;//��������ʼ��
	int initPos, pos;//��ʼλ�ã���ǰλ��
	initPos = pos = key(x) % size;
	do
	{
		++count;//̽�������1
		if (array[pos].state != 1)//�ҵ�λ�ã����Ԫ��
		{
			array[pos].data = x;
			array[pos].state = 1;
			return true;
		}
		if (array[pos].state == 1 && array[pos].data == x)//�ظ�����
			return true;
		pos = (pos + 1) % size;
	} while (pos != initPos);
	return false;
}

template <typename Type>
bool closeHashTable<Type>::find(const Type &x)const
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
void closeHashTable<Type>::rehash()
{
	node *tmp = array;
	array = new node[size];
	for (int i = 0;i < size;++i)
	{
		if (tmp[i].state == 1)
			insert(tmp[i].data);
	}
	delete[]tmp;
}
