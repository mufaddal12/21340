//============================================================================
// Name        : assign-8-avl.cpp
// Author      : Mufaddal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class AvlNode
{
	int key;
	int data;
	AvlNode *left, *right;
	int bf;
public:
	AvlNode(int k = 0, int d = 0)
	{
		key=k;
		data = d;
		left = right = NULL;
		bf = 0;
	}
	friend class AvlTree;
};

class AvlTree
{
	AvlNode root;
	AvlNode *insertNode(AvlNode *, int key, int data, bool *d);
public:
	void insert(int key, int data);
};













int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
