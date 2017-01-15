//这是二叉树的顺序实现头文件
#ifndef SEQBINARYTREE_H_INCLUDED
#define SEQBINARYTREE_H_INCLUDED

#include <iostream>

using namespace std;

template <class T>
class seqBinaryTree
{
    T *array;//保存节点值的数组
    int size;//树的规模

public:
    seqBinaryTree(T a[], int n)//构造函数
    {
        array = new T[n+1];
        size = n;
        for (int i=0;i<n;++i)
        {
            array[i+1]=a[i];//将根结点存储在1号单元
        }
    }
    void preOrder(){preOrder(1);}
    void inOrder(){inOrder(1);}
    void postOrder(){postOrder(1);}

    ~seqBinaryTree(){delete [] array;}

private:
    void preOrder(int root)
    {
        if(root>size) return ;
        cout << array[root];//访问根结点
        preOrder(root*2);//前序遍历左子树
        preOrder(root*2+1);//前序遍历右子树
    }
    void inOrder(int root)
    {
        if(root>size)return ;
        inOrder(root*2);//中序遍历左子树
        cout << array[root];//访问根结点
        inOrder(root * 2 + 1);//中序遍历右子树
    }
    void postOrder(int root)
    {
        if(root>size)return ;
        postOrder(root * 2);//后序遍历左子树
        postOrder(root*2 + 1);//后序遍历右子树
        cout << array[root];//访问根结点
    }
};

#endif // SEQBINARYTREE_H_INCLUDED
