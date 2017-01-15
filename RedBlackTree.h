template<typename Type>
class RedBlackTree
{
	struct RedBlackNode//红黑树的结点类
	{
		Type data;
		RedBlackNode *left;
		RedBlackNode *right;
		int colour;//0--Red,1--Black;

		RedBlackNode(const Type &element, RedBlackNode *lt, RedBlackNode *rt, int h = 0) :data(element), left(lt), right(rt), colour(h) {}
	};

	RedBlackNode *root;

public:
	RedBlackTree(RedBlackNode *t = nullptr) { root = t; }
	~RedBlackTree() { makeEmpty(root); }
	bool find(const Type &x)const;
	void insert(const Type &x);
	void remove(const Type &x);
private:
	enum Rotate{RED, BLACK, L, R};
	void makeEmpty(RedBlackNode *&t);
	void LL(RedBlackNode *&t);
	void LR(RedBlackNode *&t);
	void RL(RedBlackNode *&t);
	void RR(RedBlackNode *&t);
	void reColour(RedBlackNode *t);
	Rotate insert(const Type &x, RedBlackNode *&t);
	Rotate remove(const Type &x, RedBlackNode *&t);
};

template<typename Type>
void RedBlackTree<Type>::insert(const Type &x)
{
	if (root == nullptr)//空树上插入
	{
		root = new RedBlackNode(x, nullptr, nullptr, 1);
		return;
	}

	Rotate result = insert(x, root);
	root->colour = 1;
}

template<typename Type>
RedBlackTree<Type>::Rotate RedBlackTree<Type>::insert(const Type &x, RedBlackNode *&t)
{
	Rotate result, child;
	if (t == nullptr)//插入为根结点，并设为红色
	{
		t = new RedBlackNode(x, nullptr, nullptr, 0);
		return RED;
	}
	if (x < t->data)//在左子树插入
	{
		result = insert(x, t->left);
		switch (result)
		{
		case BLACK:return BLACK;
		case RED:
			if (t->colour == 0)
				return L;
			else
				return BLACK;
		case L:
			if (t->right == nullptr || t->right->colour == 1)
			{
				LL(t);
				t->colour = 1;
				t->right->colour = 0;
				return BLACK;
			}
			else
			{
				reColour(t);
				return RED;
			}
		case R:
			if (t->right == nullptr || t->right->colour == 1)
			{
				LR(t);
				t->colour = 1;
				t->right->colour = 0;
				return BLACK;
			}
			else
			{
				reColour(t);
				return RED;
			}
		}
	}
	else//往右子树上插入
	{
		result = insert(x, t->right);
		switch (result)
		{
		case BLACK:return BLACK;
		case RED:
			if (t->colour == 0)
				return R;
			else
				return BLACK;
		case L:
			if (t->left == nullptr || t->left->colour == 1)
			{
				RL(t);
				t->colour = 1;
				t->left->colour = 0;
				return BLACK;
			}
			else
			{
				reColour(t);
				return RED;
			}
		case R:
			if (t->left == nullptr || t->left->colour == 1)
			{
				RR(t);
				t->colour = 1;
				t->left->colour = 0;
				return BLACK;
			}
			else
			{
				reColour(t);
				return RED;
			}
		}
	}
}

template <typename Type>
void RedBlackTree<Type>::makeEmpty(RedBlackNode *&t)
{
	if (t != nullptr)
	{
		makeEmpty(t->left);
		makeEmpty(t->right);
		delete t;
	}
	t = nullptr;
}

template<typename Type>
bool RedBlackTree<Type>::find(const Type &x)const
{
	RedBlackNode *t = root;
	while (t != nullptr&&t->data != x)
		if (t->data > x)
			t = t->left;
		else
			t = t->right;
	if (t == nullptr)
		return false;
	else
		return true;
}

template<typename Type>
void RedBlackTree<Type>::LL(RedBlackNode *&t)
{
	RedBlackNode *t1 = t->left;
	t->left = t1->right;
	t1->right = t;
	t = t1;
}

template<typename Type>
void RedBlackTree<Type>::RR(RedBlackNode *&t)
{
	RedBlackNode *t1 = t->right;
	t->right = t1->left;
	t1->left = t;
	t = t1;
}

template<typename Type>
void RedBlackTree<Type>::LR(RedBlackNode *&t)
{
	RR(t->left);
	LL(t);

}

template <typename Type>
void RedBlackTree<Type>::RL(RedBlackNode *&t)
{
	LL(t->right);
	RR(t);
}

//template<typename Type>
//void RedBlackTree<Type>::remove(const Type &x)
//{
//	if (root == nullptr)//空树上删除
//		return;
//
//	Rotate result = remove(x, root);
//	root->colour = 1;
//}

//template<typename Type>
//RedBlackTree<Type>::Rotate RedBlackTree<Type>::remove(const Type &x, RedBlackNode *&t)
//{
//	Rotate result, child;
//	if (t == nullptr)//插入为根结点，并设为红色
//	{
//		t = new RedBlackNode(x, nullptr, nullptr, 0);
//		return RED;
//	}
//	if (x < t->data)//在左子树插入
//	{
//		result = insert(x, t->left);
//		switch (result)
//		{
//		case BLACK:return BLACK;
//		case RED:
//			if (t->colour == 0)
//				return L;
//			else
//				return BLACK;
//		case L:
//			if (t->right == nullptr || t->right->colour == 1)
//			{
//				LL(t);
//				t->colour = 1;
//				t->right->colour = 0;
//				return BLACK;
//			}
//			else
//			{
//				reColour(t);
//				return RED;
//			}
//		case R:
//			if (t->right == nullptr || t->right->colour == 1)
//			{
//				LR(t);
//				t->colour = 1;
//				t->right->colour = 0;
//				return BLACK;
//			}
//			else
//			{
//				reColour(t);
//				return RED;
//			}
//		}
//	}
//	else//往右子树上插入
//	{
//		result = insert(x, t->right);
//		switch (result)
//		{
//		case BLACK:return BLACK;
//		case RED:
//			if (t->colour == 0)
//				return R;
//			else
//				return BLACK;
//		case L:
//			if (t->left == nullptr || t->left->colour == 1)
//			{
//				RL(t);
//				t->colour = 1;
//				t->left->colour = 0;
//				return BLACK;
//			}
//			else
//			{
//				reColour(t);
//				return RED;
//			}
//		case R:
//			if (t->left == nullptr || t->left->colour == 1)
//			{
//				RR(t);
//				t->colour = 1;
//				t->left->colour = 0;
//				return BLACK;
//			}
//			else
//			{
//				reColour(t);
//				return RED;
//			}
//		}
//	}
//}