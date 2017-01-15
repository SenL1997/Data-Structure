template <typename T, int idxSize, int dataBlkSize>
class Btree
{
	struct idxNode//������ṹ
	{
		int type;//0����һ����������㣬1����һ�������ݽ��
		T key[idxSize - 1];//�ؼ�������
		void * idx[idxSize];//ָ������
		int len;//��Ч�Ķ�����
		idxNode() :len(1) {}
	};

	struct dataNode //���ݿ�ṹ
	{
		int len;//��Ч��¼��
		T record[dataBlkSize];//��ż�¼������
		dataNode() :len(1) {}
	};

	idxNode *root;//ָ�������ָ��
public:
	Btree() :root(NULL) {};
	~Btree() { makeEmpty(root); }
	bool find(const T &x)const { return find(x, root); }
	void insert(const T &x);
	void remove(const T &x);

private:
	void makeEmpty(idxNode *t);
	idxNode *insert(const T &x, idxNode *t);
	dataNode *insertData(const T &x, dataNode *t);
	idxNode *addIdxBlk(idxNode *n, idxNode *t);
	idxNode *addDataBlk(dataNode *n, idxNode *t);
};

template <typename T, int idxSize, int dataBlkSize>
void Btree<T, idxSize, dataBlkSize>::insert(const T &x)
{
	if (root == nullptr)//�����Ĳ���
	{
		root = new idxNode;//���ø����
		root->type = 1;
		root->dix[0] = new dataNode;
		dataNode *p = (dataNode *)root->idx[0];//�������ݿ�
		p->record[0] = x;
		return;
	}
	idxNode *p = insert(x, root);//�Ը�������˽�е�insert
	if (p != nullptr)//ԭ����㱻�����ˣ�����������
	{
		idxNode *t = root;
		root = new idxNode;
		root->type = 0;
		root->len = 2;
		root->idx[0] = t;
		root->idx[1] = p;
		while (p->type==0)
		{
			p = (idxNode *)p->idx[0];
		}
		dataNode *d = (dataNode *)p->idx[0];//Ѱ�ҵڶ������Сֵ
		root->key[0] = d->record[0];
	}
}
template <typename T,int idxSize, int dataBlkSize>
Btree<T, idxSize, dataBlkSize>::idxNode *Btree <T, idxSize, dataBlkSize>::insert(const T &x, idxNode *t)
{
	void *newNode;

	for (int i = 0;i < t->len - 1;++i)//����x���ڵ�����
		if (x < t->key[i])break;

	if (t->type == 0)
		newNode = insert(x, (idxNode *)t->idx[i]);
	else
		newNode = insert(x, (dataNode *)t->idx[i]);

	if (newNode == nullptr)
		return nullptr;
	else//���������
	{
		if (t->type == 0)
			return addIdxBlk((idxNode *)newNode, t);
		else
			return addDataBlk((dataNode *)newNode, t);
	}

}

template <typename T,int idxSize, int dataBlkSize>
Btree<T, idxSize, dataBlkSize>::dataNode *Btree<T, idxSize, dataBlkSize>::insertData(const T &x, dataNode *t)
{
	int i;
	if (t->len < dataBlkSize)
	{
		for (i = t->len;i > 0 && x < t->record[i - 1];--i)
			t->record[i] = t->record[i - 1];
		t->record[i] = x;
		++(t->len);
		retunr nullptr;
	}
	//���ѵ�ǰ��
	dataNode *newNode = new dataNode;
	int i, j;
	int max = dataBlkSize / 2;
	newNode->len = max + 1;
	for (i = max, j = dataBlkSize - 1;i >= 0 && t->record[j]>x;--i)
		newNode->record[i] = t->record[j--];
	if (i >= 0)
		newNode->record[i--] = x;
	for (;i >= 0;--i)
		newNode->record[i] = t->record[j--];

	t->len = dataBlkSize - max;
	if (j < t->len - 1)
	{
		for (;j >= 0 && x < t->record[j];--j)
			t->record[j + 1] = t->record[j];
		t->record[j + 1] = x;
	}
	return newNode;
}

template <typename T, int idxSize, int dataBlkSize>
Btree<T, idxSize, dataBlkSize>::idxNode *Btree<T, idxSize, dataBlkSize>::addDataBlk(dataNode *newNode, idxNode *t)
{
	int i, j;
	if (t->len < idxSize)//��ǰ��û����,ֱ�Ӳ���
	{
		for (i = t->len - 1;i > 0 && newNode->record[0] < t->key[i - 1];--i)
		{
			t->key[i] = t->key[i - 1];
			t->idx[i + 1] = t->idx[i];
		}
		t->key[i] = newNode->record[0];
		t->idx[i + 1] = newNode;
		++(t->len);
		return nullptr;
	}
	//���ѽ��
	idxNode * newIdx = new idxNode;
	newIdx->type = 1;
	int max = idxSize / 2;
	newIdx->len = max + 1;

	if (newNode->record[0] > t->key[idxSize - 2])//�����ӵ����ݿ�������
	{
		newIdx->key[max - 1] = newNode->record[0];
		newIdx->idx[max] = newNode;
	}
	else//��ԭ�������������Ƶ��µ������飬�����ӵ����ݿ����ԭ������
	{
		newIdx->key[max - 1] = t->key[idxSize - 2];
		newIdx->idx[max] = t->idx[idxSize - 1];
		for (i = t->len - 2;i > 0 && newNode->record[0] < t->key[i - 1];--i)
		{
			t->key[i] = t->key[i - 1];
			t->idx[i + 1] = t->idx[i];
		}
		t->key[i] = newNode->record[0];
		t->idx[i + 1] = newNode;
	}	qqa
	//��һ���������Ƶ���������
	for (i = max - 1, j = idxSize - 1;i > 0;--i, --j)
	{
		newIdx->idx[i] = t->idx[j];
		newIdx->key[i - 1] = t->key[j - 1];
	}
	newIdx->idx[0] = t->idx[j];

	t->len = idxSize - max;
	return newIdx;
}

template<typename T, int idxSize, int dataBlkSize>
Btree<T, idxSize, dataBlkSize>::idxNode *Btree<T, idxSize, dataBlkSize>::addIdxBlk(idxNode *newNode, idxNode *t)
{
	int i, j;
	idxNode *p = newNode;
	//���²�������Сֵ����min
	while (p->type==0)
	{
		p = (idxNode *)p->idx[0];
	}
	dataNode *d = (dataNode *)p->idx[0];
	T min = d->record[0];

	if (t->len < idxSize)//������û������ֱ�Ӽ���
	{
		for (i = t->len - 1;i > 0 && min < t->key[i - 1];--i)
		{
			t->key[i] = t->key[i - 1];
			t->idx[i + 1] = t->idx[i];
		}
		t->idx[i + 1] = newNode;
		t->key[i] = min;
		++(t->len);
		return nullptr;
	}
	//���ѵ�ǰ���
	idxNode *newIdx = new idxNode;//����һ�����������
	newIdx->type = 0;
	int max = idxSize / 2;
	newIdx->len = max + 1;
	
	if (min > t->key[idxSize - 2])//�²����������ģ��Ƶ���������
	{
		newIdx->key[max - 1] = min;
		newIdx->idx[max] = newNode;
	}
	else//��ԭ�������������Ƶ��µ������飬�����ӵ����ݿ����ԭ������
	{
		newIdx->key[max - 1] = t->key[idxSize - 2];
		newIdx->idx[max] = t->idx[idxSize - 1];
		for (int i = t->len - 2;i > 0 && min < t->key[i - 1];--i)
		{
			t->key[i] = t->key[i - 1];
			t->idx[i - 1] = t->idx[i];
		}
		t->key[i] = min;
		t->idx[i + 1] = newNode;
	}
	//����һ������������������
	for (i = max - 1, j = idxSize - 1;i > 0;--i, --j)
	{
		newIdx->idx[i] = t->idx[j];
		newIdx->key[i - 1] = t->key[j - 1];
	}
	newIdx->idx[0] = t->idx[j];

	t->len = idxSize - max;
	return newIdx;
}