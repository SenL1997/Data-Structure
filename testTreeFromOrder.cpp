#include "binaryTree.h"
#include <iostream>
#include <vector>

using namespace std;

int main()
{
    //接收前序遍历和中序遍历序列
    vector <char> preSeq,midSeq;
    char ch;
    cout << "Please input the preSequence(end with '@'): "<<endl;
    while((ch=cin.get())&&(ch!='@'))
    {
        preSeq.push_back(ch);
    }
    cin.get();//过滤掉换行符
    cout << "Please input the midSequence(end with '@'): "<<endl;
    while((ch=cin.get())&&(ch!='@'))
    {
        midSeq.push_back(ch);
    }
    cin.get();//过滤掉换行符
    //根据前序遍历和中序遍历建树

    BinaryTree<char> tree;
    tree.makeTreeFromPreMidOrder(preSeq, midSeq);
    std::cout << "Create Completed!"<<std::endl;

    tree.preOrder();
    tree.midOrder();
    tree.postOrder();
    cout <<endl<<endl;

    //接收后序遍历和中序遍历序列
    vector <char> postSeq,midSeq2;
    cout << "Please input the postSequence(end with '@'): "<<endl;
    while((ch=cin.get())&&(ch!='@'))
    {
        postSeq.push_back(ch);
    }
    cin.get();//过滤掉换行符
    cout << "Please input the midSequence(end with '@'): "<<endl;
    while((ch=cin.get())&&(ch!='@'))
    {
        midSeq2.push_back(ch);
    }
     cin.get();//过滤掉换行符

    BinaryTree<char> tree2;
    tree2.makeTreeFromPostMidOrder(postSeq, midSeq2);
    std::cout << "Create Completed!"<<std::endl;

    tree2.preOrder();
    tree2.midOrder();
    tree2.postOrder();
    cout<<endl;

}
