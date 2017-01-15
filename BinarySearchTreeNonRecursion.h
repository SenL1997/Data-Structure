template <typename Type>
class BinarySearchTree
{
	private:
		struct BinaryNode
		{
			Type data;
			BinaryNode * left;
			BinaryNode * right;

			BinaryNode(const Type &thedata, BinaryNode *lt, BinaryNode *rt):data(thedata), left(lt), right(rt){}
		};
	public:
		BinarySearchTree(BinaryNode *t = nullptr){root = t;}
		~BinarySearchTree(){makeEmpty(root);}
		bool find(const Type &x) const;
		void insert(const Type &x);
		void remove(const Type &x);
		bool check() const;
		void delLess(const Type x);
		void delGreat(const Type x);
		void delRange(const Type x, const Type y);
	private:
		BinaryNode *root;
		void makeEmpty(BinaryNode *&t);
		bool check(BinaryNode *t, Type &min, Type &max)const;
		void delLess(Type x, BinaryNode *&t);
		void delGreat(Type x, BinaryNode *&t);
		void delRange(Type x, Type y, BinaryNode *&t);
};

template <typename Type>
bool BinarySearchTree<Type>::find(const Type &x) const
{
	BinaryNode * now = root;
	while(now!=nullptr)
	{
		if(x>now->data)
			now = now->right;
		else if(x<now->data)
			now = now->left;
		else
			return true;
	}
	return false;
}

template <typename Type>
void BinarySearchTree<Type>::insert(const Type &x)
{
	BinaryNode * nd = new BinaryNode(x,nullptr, nullptr);//为插入元素申请结点
	if(root == nullptr)//在空树上插入
	{
		root = nd;
		return;
	}
	BinaryNode *now=root;//寻找插入位置并插入
	while(true)
	{
		if(x>now->data)
		{
			if(now->right==nullptr)
			{
				now->right=nd;
				break;
			}
			now=now->right;
		}
		else if(now->left==nullptr)
		{
			now->left=nd;
			break;
		}
		else
			now=now->left;
	}
}

template <typename Type>
void BinarySearchTree<Type>::remove(const Type &x)
{
	BinaryNode *now=root;//当前正在检查的结点
	BinaryNode *parent;//now的父亲
	int leftOrRight;//now是父亲的左儿子为1，右儿子为2

	while(now!=nullptr)//寻找被删节点
	{
		if(x > now->data)
		{
			leftOrRight = 2;
			parent = now;
			now = now->right;
		}
		else if(x < now->data)
		{
			leftOrRight = 1;
			parent = now;
			now = now->left;
		}
		else
			break;
	}

	//删除now
	if (now->left!=nullptr && now->right!=nullptr)//有两个儿子
	{
		BinaryNode * tmp = now->right;
		if(tmp->left == nullptr)//右儿子作为替身
        {
            now -> data = tmp->data;
            now -> right = tmp->right;
            delete tmp;
            return;
        }
        while(tmp->left->left!=nullptr)
            tmp=tmp->left;//找右子树的最小值
        BinaryNode * deleted = tmp->left;
        now -> data = deleted->data;
        tmp -> left = deleted->right;
        delete deleted;
        return;
	}
	if(now == root)//删除根节点
	{
		if(root->left==nullptr)
			root=root->right;
		else root = root->left;
		return;
	}
	if(leftOrRight ==1)//删除只有一个或没有儿子的结点
		parent -> left=(now->left==nullptr?now->right:now->left);
	else
		parent -> right = (now->left==nullptr?now->right:now->left);
	delete now;
	return;

}

template <typename Type>
void BinarySearchTree<Type>::makeEmpty(BinaryNode *&t)
{
	if(t!=nullptr)
	{
        makeEmpty(t->left);
        makeEmpty(t->right);
		if(t->left==nullptr&&t->right==nullptr)
		{
			delete(t);
			t = nullptr;
		}
	}
}

template <typename Type>
bool BinarySearchTree<Type>::check()const
{
    Type min, max;
    bool flag;

    if(root == nullptr)
        return true;//空树是二叉查找树
    if(root -> left)//有左子树
    {
        flag = check(root->left, min, max);//检查左子树是否为二叉查找树
        if(!flag||max>root->data)
            return false;
    }
    if(root -> right)//有右子树
    {
        flag = check(root->right, min, max);
        if(!flag || min <root->data)
            return false;
    }

    return true;
}

template <typename Type>
bool BinarySearchTree<Type>::check(BinaryNode *t, Type &min, Type &max)const
{
	Type mint, maxt;
	bool flag;

	if(t->left!=nullptr)
	{
		flag = check(t->left, min, maxt);
		if(!flag||maxt>t->data)
			return false;
	}
	else min = t->data;

	if(t->right!=nullptr)
	{
		flag = check(t->right, mint, max);
		if(!flag||mint<t->data)
			return false;
	}
	else max = t->data;
	return true;
}

template <typename Type>
void BinarySearchTree<Type>::delLess(const Type x)
{
	delLess(x,root);
}
template <typename Type>
void BinarySearchTree<Type>::delLess(const Type x, BinaryNode *&t)
{
	if(t==nullptr)
		return;
	if(x>t->data)//删除根节点及左子树
	{
		BinaryNode *tmp = t;
		t=t->right;
		makeEmpty(tmp->left);
		delete tmp;
		delLess(x,t);
	}
	else
		delLess(x, t->left);//在左子树上删除所有小于x的元素
}

template <typename Type>
void BinarySearchTree<Type>::delGreat(const Type x)
{
	delGreat(x, root);
}
template <typename Type>
void BinarySearchTree<Type>::delGreat(const Type x, BinaryNode *&t)
{
	if(t==nullptr)
		return;
	if(t->data>x)//删除根结点及右子树
	{
		BinaryNode *tmp = t;
		t= t->left;;
		makeEmpty(tmp->right);
		delete tmp;
		delGreat(x,t);
	}
	else
		delGreat(x, t->right);//在右子树上删除所有大于x的元素
}

template <typename Type>
void BinarySearchTree<Type>::delRange(Type x, Type y)
{
	if(x<=y)
		delRange(x, y, root);
}
template <typename Type>
void BinarySearchTree<Type>::delRange(Type x, Type y, BinaryNode *&t)
{
	if(t==nullptr)
		return ;
	if(t->data<x)
		delRange(x,y,t->right);//被删元素在右子树上
	else if(t->data>y)
		delRange(x,y,t->left);//被删元素在左子树上
	else//根节点需要删除
	{
		remove(t->data);
		delRange(x, y, t);
	}
}
