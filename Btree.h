template <typename T, int idxSize, int dataBlkSize>
class Btree
{
	struct idxNode//索引块结构
	{
		int type;//0：下一层是索引结点，1：下一层是数据结点
		T key[idxSize - 1];//关键字数组
		void * idx[idxSize];//指针数组
		int len;//有效的儿子数
		idxNode() :len(1) {}
	};

	struct dataNode //数据块结构
	{
		int len;//有效记录数
		T record[dataBlkSize];//存放记录的数组
		dataNode() :len(1) {}
	};

	idxNode *root;//指向根结点的指针
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
	if (root == nullptr)//空树的插入
	{
		root = new idxNode;//设置根结点
		root->type = 1;
		root->dix[0] = new dataNode;
		dataNode *p = (dataNode *)root->idx[0];//设置数据块
		p->record[0] = x;
		return;
	}
	idxNode *p = insert(x, root);//对根结点调用私有的insert
	if (p != nullptr)//原根结点被分裂了，处理树增高
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
		dataNode *d = (dataNode *)p->idx[0];//寻找第二块的最小值
		root->key[0] = d->record[0];
	}
}
template <typename T,int idxSize, int dataBlkSize>
Btree<T, idxSize, dataBlkSize>::idxNode *Btree <T, idxSize, dataBlkSize>::insert(const T &x, idxNode *t)
{
	void *newNode;

	for (int i = 0;i < t->len - 1;++i)//查找x所在的子树
		if (x < t->key[i])break;

	if (t->type == 0)
		newNode = insert(x, (idxNode *)t->idx[i]);
	else
		newNode = insert(x, (dataNode *)t->idx[i]);

	if (newNode == nullptr)
		return nullptr;
	else//添加索引项
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
	//分裂当前块
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
	if (t->len < idxSize)//当前块没有满,直接插入
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
	//分裂结点
	idxNode * newIdx = new idxNode;
	newIdx->type = 1;
	int max = idxSize / 2;
	newIdx->len = max + 1;

	if (newNode->record[0] > t->key[idxSize - 2])//新增加的数据块是最大的
	{
		newIdx->key[max - 1] = newNode->record[0];
		newIdx->idx[max] = newNode;
	}
	else//将原索引块的最大项移到新的索引块，新增加的数据块插入原索引块
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
	//将一半索引项移到新索引块
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
	//找新插入块的最小值存入min
	while (p->type==0)
	{
		p = (idxNode *)p->idx[0];
	}
	dataNode *d = (dataNode *)p->idx[0];
	T min = d->record[0];

	if (t->len < idxSize)//索引块没有满，直接加入
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
	//分裂当前结点
	idxNode *newIdx = new idxNode;//申请一个新索引结点
	newIdx->type = 0;
	int max = idxSize / 2;
	newIdx->len = max + 1;
	
	if (min > t->key[idxSize - 2])//新插入项是最大的，移到新索引块
	{
		newIdx->key[max - 1] = min;
		newIdx->idx[max] = newNode;
	}
	else//将原索引块的最大项移到新的索引块，新增加的数据块插入原索引块
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
	//分裂一半索引项到新增索引结点
	for (i = max - 1, j = idxSize - 1;i > 0;--i, --j)
	{
		newIdx->idx[i] = t->idx[j];
		newIdx->key[i - 1] = t->key[j - 1];
	}
	newIdx->idx[0] = t->idx[j];

	t->len = idxSize - max;
	return newIdx;
}