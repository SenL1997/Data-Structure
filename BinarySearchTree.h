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
		BinarySearchTree(BinaryNode *t = NULL){root = t;}
		~BinarySearchTree(){makeEmpty(root);}
		bool find(const Type &x) const;
		void insert(const Type &x);
		void remove(const Type &x);
		bool check() const;
		void delLess(const Type x);
		void delGreat(const Type x);
		void delRange(const Type x, const Type y);
		int findLevel(const Type &x)const{return findLevel(x, root);}
	private:
		BinaryNode *root;
		void insert(const Type &x, BinaryNode *&t);
        void remove(const Type &x, BinaryNode *&t);
		bool find(const Type &x, BinaryNode *t) const ;
		void makeEmpty(BinaryNode *&t);
		bool check(BinaryNode *t, Type &min, Type &max)const;
		void delLess(Type x, BinaryNode *&t);
		void delGreat(Type x, BinaryNode *&t);
		void delRange(Type x, Type y, BinaryNode *&t);
		int findLevel(const Type &x, BinaryNode *t)const;
};

template <typename Type>
bool BinarySearchTree<Type>::find(const Type &x) const
{
	return find(x,root);
}

template <typename Type>
bool BinarySearchTree<Type>::find(const Type &x, BinaryNode *t)const
{
	if(t==NULL)
		return false;
	else if(x<t->data)
		return find(x,t->left);//继续查找左子树
	else if(x>t->data)
		return find(x,t->right);//继续查找右子树
	else
	       	return true;//找到被查结点，返回
}

template <typename Type>
void BinarySearchTree<Type>::insert(const Type &x)
{
	insert(x,root);
}
template <typename Type>
void BinarySearchTree<Type>::insert(const Type &x, BinaryNode *&t)
{
	if(t==NULL)
		t=new BinaryNode(x, NULL, NULL);
	else if(x<t->data)
		insert(x, t->left);
	else if(x>t->data)
		insert(x, t->right);
}

template <typename Type>
void BinarySearchTree<Type>::remove(const Type &x)
{
	remove(x,root);
}
template <typename Type>
void BinarySearchTree<Type>::remove(const Type &x, BinaryNode *&t)
{
	if(t==NULL)
	       	return;
	if(x<t->data)
		remove(x, t->left);
	else if(x>t->data)
		remove(x, t->right);
	else if(t->left!=NULL && t->right != NULL)//有两个儿子
	{
		BinaryNode *tmp = t->right;
		while(tmp->left!=NULL)
			tmp = tmp->left;
		t->data = tmp ->data;
		remove(t->data, t->right);
	}
	else //被删结点是叶结点或只有一个儿子
	{
		BinaryNode *oldNode = t;
		t = (t->left!=NULL)?t->left:t->right;
		delete oldNode;
	}
}

template <typename Type>
void BinarySearchTree<Type>::makeEmpty(BinaryNode *&t)
{
	if(t!=NULL)
	{
        makeEmpty(t->left);
        makeEmpty(t->right);
		if(t->left==NULL&&t->right==NULL)
		{
			delete(t);
			t = NULL;
		}
	}
}

template <typename Type>
bool BinarySearchTree<Type>::check()const
{
    Type min, max;
    bool flag;

    if(root == NULL)
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

	if(t->left)
	{
		flag = check(t->left, min, maxt);
		if(!flag||maxt>t->data)
			return false;
	}
	else min = t->data;

	if(t->right)
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
	if(t==NULL)
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
	if(t==NULL)
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
	if(t==NULL)
		return ;
	if(t->data<x)
		delRange(x,y,t->right);//被删元素在右子树上
	else if(t->data>y)
		delRange(x,y,t->left);//被删元素在左子树上
	else//根节点需要删除
	{
		remove(t->data,t);
		delRange(x, y, t);
	}
}

template <typename Type>
int BinarySearchTree<Type>::findLevel(const Type &x,BinaryNode *t)const
{
	if (t == nullptr)//x不存在
		return -1;
	if (t->data == x)//x等于根结点
		return 1;

	int level;
	if (x < t->data)
		level = findLevel(x, t->left);
	else
		level = findLevel(x, t->right);

	return (level == -1 ? -1 : level + 1);//x的深度为子树上的深度加1
}

