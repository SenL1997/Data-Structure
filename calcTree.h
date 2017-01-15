#ifndef CALCTREE_H_INCLUDED
#define CALCTREE_H_INCLUDED

#include <iostream>
#include <cmath>

using namespace std;

class calc
{
	enum Type { DATA, ADD, SUB, MULTI, DIV, EXP, OPAREN, CPAREN, EOL };

	struct node
	{
		Type type;
		int data;
		node *lchild, *rchild;

		node(Type t, int d = 0, node * lc = NULL, node * rc = NULL)
		{
			type = t;
			data = d;
			lchild = lc;
			rchild = rc;
		}
	};
	node *root;

	node *create(char * &s);
	Type getToken(char * &s, int &value);
	int result(node *t);
	bool check(node *t);

public:
	calc(char *s) { root = create(s); }
	int result()
	{
		if (root == NULL) return 0;
		return result(root);
	}
	bool check(){return check(root);}
};

calc::node *calc::create(char * &s)
{
	calc::node*p, *root = NULL,	*tmp;
	Type returnType=Type(), flag = DATA;

	int value;

	while (*s)
	{
		flag = returnType;
		returnType = calc::getToken(s, value);

		switch (returnType)
		{
		case calc::DATA:
			p = new calc::node(DATA, value);
			if(root!=nullptr)
			{
				tmp = root;
				while (tmp->rchild != NULL)
					tmp = tmp->rchild;
				tmp->rchild = p;
			}
			break;
		case calc::OPAREN:
			p = create(s);
			if (root != nullptr)
			{
				tmp = root;
				while (tmp->rchild != NULL)
					tmp = tmp->rchild;
				tmp->rchild = p;
			}
			else
			{
				root = p;
			}
			break;
		case calc::ADD:
		case calc::SUB:
			if (root == NULL)root = new node(returnType, 0, p);
			else root = new node(returnType, 0, root);
			break;
		case calc::MULTI:
		case calc::DIV:
			if (root == NULL) root = new node(returnType, 0, p);
			else if (root->type == MULTI || root->type == DIV || root->type == DATA || flag == OPAREN)
				root = new node(returnType, 0, root);
			else root->rchild = new node(returnType, 0, root->rchild);
			break;
		case EXP:
			if (root == nullptr)
				root = new node(returnType, 0, p);
			else if (root->type == DATA||root->type==OPAREN||root->type==EXP)
				root = new node(returnType, 0, root);
			else if (root->rchild != nullptr)
			{
				if (root->rchild->type == MULTI || root->rchild->type == DIV)
					tmp = root->rchild;

				else tmp = root;
				//为了实现乘方运算的左结合，以下2行注释掉
				//while (tmp->rchild->type==EXP)
				//	tmp = tmp->rchild;
				tmp->rchild = new node(returnType, 0, tmp->rchild);

			}
			break;
		case calc::CPAREN:case calc::EOL:
			return root;
		}
	}
	return root;
}

calc::Type calc::getToken(char *&s, int &data)
{
	char type;
	while (*s == ' ') ++s;
	if (*s >= '0'&&*s <= '9')
	{
		data = 0;
		while (*s >= '0'&&*s <= '9') { data = data * 10 + *s - '0'; ++s; }
		return DATA;
	}
	if (*s == '\0')return EOL;

	type = *s; ++s;
	switch (type)
	{
	case'+':return ADD;
	case'-':return SUB;
	case'*':return MULTI;
	case'/':return DIV;
	case'(':return OPAREN;
	case')':return CPAREN;
	case'^':return EXP;
	default:
		return EOL;
	}
}

int calc::result(node *t)
{
	int num1, num2;
	if (t->type == DATA)
	{
		//cout << t->data << " ";
		return t->data;
	}

	num1 = result(t->lchild);//计算左子表达式
	num2 = result(t->rchild);//计算右子表达式
	switch (t->type)
	{
	case ADD:t->data = num1 + num2;break;
	case SUB:t->data = num1 - num2;break;
	case MULTI:t->data = num1 * num2;break;
	case DIV:t->data = num1 / num2;break;
	case EXP:t->data = pow(num1, num2);break;
	}
	//cout << t->data << " ";
	return t->data;
}

bool calc::check(node *t)
{
    if(t->lchild == NULL && t->rchild==NULL&&t->type==DATA)return true;//若结点是叶结点，它的类型一定是数据
    if(t->lchild==NULL&&t->rchild==NULL&&t->type!=DATA)return false;
    if((t->lchild==NULL)||(t->rchild==NULL))return false;//所有结点的度要么为0，要么为2
    if(t->type == DATA)return false;//所有度为2的结点，类型一定是运算符

    return check(t->lchild)&&check(t->rchild);
}


#endif // CALCTREE_H_INCLUDED
