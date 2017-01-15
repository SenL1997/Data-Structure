#include <iostream>
#include "binaryTree.h"

using namespace std;

int main()
{
    BinaryTree<char> tree, tree1('M'),tree2;
    tree.createTree('@');

    cout << "\nHeight: "<<tree.height()<<endl;
    cout << "Size: "<<tree.size()<<endl;

    tree.swap();//test binaryTree<Type>::swap(),SUCCESSFUL;

    tree.preOrder();
    tree.midOrder();
    tree.postOrder();

    cout <<endl<<endl;
    tree.BFS();//test binaryTree<Type>::BFS(),SUCCESSFUL;

    cout<<"The number of node of degree 2: "<<tree.countDegreeTwo()<<endl;//test BinaryTree<Type>::count2(), SUCCESSFUL;

    int a = tree.isCompleteBinaryTree();
    if (a==1)
        cout << "\nThis is a complete binary tree!" <<endl;
    else
        cout << "\nThis is not a complete binary tree!" <<endl;

    tree2.makeTree('Y',tree,tree1);
    cout <<endl;
    cout << "\nHeight: "<<tree2.height()<<endl;
    cout <<"Size: "<<tree2.size()<<endl;
    tree2.preOrder();
    tree2.midOrder();
    tree2.postOrder();

    cout <<endl<<endl;
     cout<<"The number of node of degree 2: "<<tree2.countDegreeTwo()<<endl;

    if (tree==tree2)//test operator==, SUCCESSFUL!
        cout << "\nThey are same!" <<endl;
    else
        cout << "\nThey are different!" <<endl;

    return 0;

}
