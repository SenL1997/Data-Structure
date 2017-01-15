#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <iostream>
#include <string>
#include <queue>
#include <vector>
using namespace std;

template <typename Type>
class BinaryTree
{
	private:
		struct Node
	       	{
			Node *left, *right;
			Type data;

			Node():left(NULL),right(NULL){}
			Node(Type item, Node *L = NULL, Node *R = NULL):
				data(item), left(L), right(R){}
			~Node(){}
		};

        struct elem
        {
            Node *p;
            int num;
        };

		Node *root;

	public:
		BinaryTree():root(NULL){}
		BinaryTree(const Type &value){root = new Node(value);}
		BinaryTree(const Node *P){root = P;}
		~BinaryTree(){clear();}

		Type getRoot() const {return root ->data;}
		Type getLeft() const {return root->left->data;}
		Type getRight() const {return root->right->data;}

		void makeTree(const Type &x, BinaryTree &lt, BinaryTree &rt)
		{
			root = new Node(x, lt.root, rt.root);
			lt.root = NULL;
			rt.root = NULL;
		}

		void delLeft()
		{
			BinaryTree tmp = root -> left;
			root -> left = NULL;
			tmp.clear();
		}

		void delRight()
		{
			BinaryTree tmp = root -> right;
			root -> right = NULL;
			tmp.clear();
		}

		bool isEmpty() const {return root == NULL;}
		void clear()
		{
			if (root != NULL)
				clear(root);
		       	root = NULL;
		}
		int size() const {return size(root);}
		int height() const {return height(root);}

		void preOrder() const
		{
			if(root != NULL)
			{
				std::cout <<"\nPreorder Traversal: ";
				preOrder(root);
			}
		}
		void postOrder() const
		{
			if(root!=NULL)
			{
				std::cout << "\nPostorder Traversal: ";
				postOrder(root);
			}
		}

		void midOrder() const
		{
			if (root != NULL)
			{
				std::cout << "\nInorder Traversal: ";
				midOrder(root);
			}
		}
		void createTree(Type flag);

		int findId(Type ch, vector<Type> &inorder)
        {
            for (int i = 0;i < inorder.size();i++){
                if (inorder[i] == ch) return i;
            }
        }
        Node * bst(vector<Type> &preorder, int &mid, vector<Type> &inorder, int st, int ed, Node * r);
        void makeTreeFromPreMidOrder(vector<Type> &preorder, vector<Type> &inorder);
        Node * pmo(vector<Type> &postorder, int &mid, vector<Type> &inorder, int st, int ed, Node * r);
        void makeTreeFromPostMidOrder(vector<Type> &postorder, vector<Type> &inorder);

		int countDegreeTwo(){return countDegreeTwo(root);}
		void BFS();//层次遍历，类似广义优先搜索。
        void swap(){swap(root);}
        bool isCompleteBinaryTree();

        friend bool operator==(const BinaryTree<Type> &t1, const BinaryTree<Type> &t2)
        {
            return checkEqual(t1.root, t2.root);
        }
        friend bool checkEqual(BinaryTree<Type>::Node *t1, BinaryTree<Type>::Node *t2)
        {
            if(t1 == NULL &&t2 == NULL)return 1;
            if(t1 ==NULL || t2 == NULL) return 0;
            if(t1->data!=t2->data) return 0;
            return checkEqual(t1->left, t2->left)&& checkEqual(t1->right, t2->right);
        }

	private:
		int height(Node*t) const
		{
			if (t==NULL) return 0;
			else
		       	{
				int lt = height(t->left), rt = height(t->right);
				return 1+((lt>rt)?lt:rt);
			}
		}
		void clear(Node*t)
		{
			if(t->left!=NULL) clear(t->left);
			if(t->right!=NULL) clear(t->right);
			delete t;
		}

		int size(Node*t)const
		{
			if (t==NULL) return 0;
			return 1+size(t->left)+size(t->right);
		}

		void preOrder(Node *t) const
		{
			if(t!=NULL)
			{
				std::cout << t->data << ' ';
				preOrder(t->left);
				preOrder(t->right);
			}
		}

		void postOrder(Node *t)const
		{
			if (t!=NULL)
			{
				postOrder(t->left);
				postOrder(t->right);
				std::cout << t->data<<' ';
			}
		}

		void midOrder(Node *t) const
		{
			if (t!=NULL)
			{
				midOrder(t->left);
				std::cout <<t->data<<' ';
				midOrder(t->right);
			}
		}
        int countDegreeTwo(Node *n)
        {
            if(n==NULL)
                return 0;
            if(n->left&&n->right)
                return 1+countDegreeTwo(n->left)+countDegreeTwo(n->right);
            else
                return countDegreeTwo(n->left)+countDegreeTwo(n->right);
        }
        void swap(Node *t);
};

template <typename Type>
void BinaryTree<Type>::createTree(Type flag)
{
	std::queue <Node *> que;
	Node *tmp;
	Type x, ldata, rdata;

	std::cout <<"Please enter the value of root node: ";
	std::cin >> x;

	if(x!=flag)
	{
        root = new Node(x);
        que.push(root);
	}

	while (!que.empty())
	{
		tmp = que.front();
		que.pop();
		std::cout <<"\nPlease enter two child nodes of "<<tmp->data<<"("<<flag<<" stand for blank node):";
		std::cin >> ldata >> rdata;
		if (ldata!=flag) que.push(tmp->left = new Node(ldata));
		if (rdata!=flag) que.push(tmp->right = new Node (rdata));
	}
	std::cout << "Create completed!"<<std::endl;
}

template <typename T>
void BinaryTree<T>::BFS()
{
    queue<Node *> que;
    Node *cur;

    cout << "Levelorder Traversal: ";
    if (root==NULL)return ;

    que.push(root);
    while(!que.empty())
    {
        cur = que.front();
        que.pop();
        if(cur->left!=NULL)que.push(cur->left);
        if(cur->right!=NULL)que.push(cur->right);
        cout << cur->data <<" ";
    }
    cout <<endl;
}


template <typename T>
bool BinaryTree<T>::isCompleteBinaryTree()
{
	queue <elem> que;
	elem cur,child;					//cur当前处理的结点，child:cur的儿子
	int count = 1;					//count:访问到的结点
	int last = 1;					//last:最后一个结点的编号

	if(root==NULL) return 1;
	cur.p = root;
	cur.num = 1;
	que.push(cur);				//根结点入队
	while (!que.empty())
	{
		cur = que.front();
		que.pop();
		if(cur.p->left!=NULL)			//处理当前结点的左儿子
		{
			++count;			        //结点数+1
			child.p = cur.p->left;
			last = child.num = cur.num*2;	//设置左儿子的编号
			que.push(child);		//左儿子入队
		}
		if(cur.p->right != NULL)		//处理当前结点的右儿子
		{
			++count;			//结点数+1
			child.p = cur.p->right;
			last = child.num = cur.num*2+1;	//设置右儿子的编号
			que.push(child);           //右儿子入队
		}
	}
	return count == last;                        	//返回结点数是否等于最后一个结点的编号
}

template <typename Type>
void BinaryTree<Type>::swap(Node *n)
{
	Node *p;
	if(n->left)
		swap(n->left);
	if(n->right)
		swap(n->right);

	p=n->left;
	n->left = n->right;
	n->right = p;
}
template <typename Type>
typename BinaryTree<Type>::Node *BinaryTree<Type>::bst(vector<Type> &preorder, int &mid, vector<Type> &inorder, int st, int ed, Node * r)
{
       if (st>ed || preorder.size()==mid){return NULL;}
       r = new Node (preorder[mid]);
       int idx = findId(preorder[mid], inorder);
       mid++;
       r->left = bst(preorder, mid, inorder, st, idx-1,r->left);
       r->right = bst(preorder, mid, inorder, idx+1, ed, r->right);
       return r;
}
template <typename Type>
void BinaryTree<Type>::makeTreeFromPreMidOrder(vector<Type> &preorder, vector<Type> &inorder)
{
       int mid = 0;
       root = bst(preorder, mid, inorder, 0, inorder.size(),root);
}
template <typename Type>
typename BinaryTree<Type>::Node *BinaryTree<Type>:: pmo(vector<Type> &postorder, int &mid, vector<Type> &inorder, int st, int ed, Node*r)
        {
        // Base case
        if (st > ed)
            return NULL;

        // Pick current node from Preorder traversal using postIndex and decrement postIndex
        r = new Node(postorder[mid]);
        mid--;

        // If this node has no children then return
        if (st == ed)
        return r;

        // Else find the index of this node in Inorder traversal
        int idx = findId(r->data, inorder);
        // Using index in Inorder traversal, construct left and right subtress
        r->right= pmo(postorder, mid, inorder, idx+1, ed,r->right);
       	r->left = pmo(postorder, mid, inorder, st, idx-1,r->left);

	return r;
}

template <typename Type>
void BinaryTree<Type>::makeTreeFromPostMidOrder(vector<Type> &postorder, vector<Type> &inorder)
{
    int mid = inorder.size()-1;
    if(mid==0)
        root = NULL;
    else
        root = pmo(postorder, mid, inorder, 0, inorder.size()-1,root);
}

#endif // BINARYTREE_H

