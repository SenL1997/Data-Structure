#include <iostream>
#include <string>
#include "hfTree.h"

using namespace std;

int main()
{
//	char ch[] = { "aeistdn" };
//	int w[] = { 10, 15, 12, 3, 4, 13, 1 };
//	hfTree<char> tree(ch, w, 7);
//	hfTree<char>::hfCode result[7];
//
//	tree.getCode(result);
//	cout << "The Huffman Coding is " << endl;
//	for (int i = 0;i < 7;++i)
//	{
//		cout << result[i].data << " " << result[i].code << endl;
//	}
//	cout << "The Huffman Coding is " << endl;
	char ch2[] = { "abcdefghijklmnopqrstuvwxyz" };
	int w2[] = { 78, 21, 72, 3, 55, 23, 47, 21, 12, 55, 35, 52, 31, 27, 97, 21, 30, 68, 8, 6, 44, 20, 73, 68, 19, 2 };
	hfTree<char> tree2(ch2, w2, 26);
	hfTree<char>::hfCode result2[26];

	tree2.getCode(result2);

	for (int i = 0;i < 26;++i)
		cout << result2[i].data << " " << result2[i].code << endl;
	cout << "The cost of Huffman Coding is " << tree2.cost(result2) << endl;
	cout << "The cost of Huffman Coding / The cost of Fixed-length Coding = " << tree2.rate(result2) << "%" << endl;

	return 0;
}

