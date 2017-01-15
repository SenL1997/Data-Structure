#include <iostream>
#include "seqBinaryTree.h"

using namespace std;

int main()
{
    char ch1[13] = "ALCBEFDPQRSU";
    seqBinaryTree<char> t1(ch1,12);
    cout<<"PreOrder: ";
    t1.preOrder();
    cout <<"\nInOrder: ";
    t1.inOrder();
    cout << "\nPostOrder: ";
    t1.postOrder();
    cout << endl;
    char ch2[10] = "AB D   HI";
    seqBinaryTree<char> t2(ch2,9);
    cout<<"PreOrder: ";
    t2.preOrder();
    cout <<"\nInOrder: ";
    t2.inOrder();
    cout << "\nPostOrder: ";
    t2.postOrder();
    cout << endl;

    cout <<"ch2: "<< ch2 << endl;
    return 0;
}
