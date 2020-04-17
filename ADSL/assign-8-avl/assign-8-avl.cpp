//============================================================================
// Name        : assign-8-avl.cpp
// Author      : Mufaddal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stack>
using namespace std;

class AvlNode
{
	int key;
	int data;
	AvlNode *left, *right;
	int ht;

public:
	AvlNode(int k = 0, int d = 0)
	{
		key = k;
		data = d;
		left = right = NULL;
		ht = 0;
	}
	friend class AvlTree;
};

class AvlTree
{
	AvlNode *root;
	AvlNode *insertNode(AvlNode *, int key, int data, bool *d);
	void balance(AvlNode *p, stack<AvlNode *>);
	int height(AvlNode *t);
	void changeHt(stack<AvlNode *>);
	AvlNode *rotateRight(AvlNode *t);
	AvlNode *rotateLeft(AvlNode *t);

public:
	void insert(int key, int data);
	void display();
	AvlTree()
	{
		root = NULL;
	}
};

int max(int a, int b)
{
	return a > b ? a : b;
}

void AvlTree::insert(int k, int data)
{
	stack<AvlNode *> st;
	AvlNode *p = new AvlNode(k, data);
	if (root == NULL)
	{
		root = p;
		return;
	}
	else
	{
		AvlNode *t = root, *t2 = root;
		while (t)
		{
			t2 = t;
			st.push(t);
			if (k > t->key)
			{
				t = t->right;
			}
			else if (k < t->key)
			{
				t = t->left;
			}
			else
				break;
		}
		if (t)
		{
			cout << "Key Already in Dataset\n";
			return;
		}

		else
		{
			if (k > t2->key)
				t2->right = p;
			else
				t2->left = p;
		}
	}
	changeHt(st);
	balance(p, st);
}

void AvlTree::changeHt(stack<AvlNode *> st)
{
	AvlNode *child;
	while (!st.empty())
	{
		child = st.top();
		st.pop();
		child->ht = 1 + max(height(child->left), height(child->right));
	}
}

void AvlTree::balance(AvlNode *p, stack<AvlNode *> st)
{
	AvlNode *child, *parent;
	int rh, lh;
	int bf;
	child = st.top();
	st.pop();
	while (!st.empty())
	{
		parent = st.top();
		st.pop();
		rh = height(child->right);
		lh = height(child->left);
		bf = lh - rh;
		if (bf > 1)
		{
			child = rotateRight(child);
		}
		if (bf < -1)
		{
			child = rotateLeft(child);
		}
		if (child->key < parent->key)
			parent->left = child;
		if (child->key > parent->key)
			parent->right = child;
		child = parent;
	}
}

AvlNode *AvlTree::rotateRight(AvlNode *child)
{
	AvlNode *temp = child->left;
	if (height(temp->left) < height(temp->right))
	{
		temp = child->left = rotateLeft(temp);
	}
	child->left = temp->right;
	child->ht = 1 + max(height(child->left), height(child->right));
	temp->right = child;
	temp->ht = 1 + max(height(temp->left), height(temp->right));

	return temp;
}

AvlNode *AvlTree::rotateLeft(AvlNode *child)
{
	AvlNode *temp = child->right;
	if (height(temp->right) < height(temp->left))
		temp = child->right = rotateRight(temp);
	child->right = temp->left;
	child->ht = 1 + max(height(child->left), height(child->right));
	temp->left = child;
	temp->ht = 1 + max(height(temp->left), height(temp->right));

	return temp;
}

int AvlTree::height(AvlNode *p)
{
	if (p == NULL)
		return -1;
	else
		return p->ht;
}

void AvlTree::display()
{
	AvlNode *p = root;
	stack<AvlNode *> st;
	st.push(p);
	while (!st.empty())
	{
		p = st.top();
		st.pop();
		if (p)
		{
			st.push(p->right);
			st.push(p->left);
			cout << p->key << " : ";
			if (p->left)
				cout << p->left->key << " , ";
			else
				cout << "NULL , ";
			if (p->right)
				cout << p->right->key << " , ";
			else
				cout << "NULL , ";
			cout << endl;
		}
	}
}

int main()
{
	AvlTree at;
	int op;
	int key, val;
	do
	{
		cout << "1. Insert Data\n";
		cout << "2. Delete Data\n";
		cout << "3. Update Data\n";
		cout << "4. Display\n";
		cout << "0. Exit\n";
		cout << " Option : ";
		cin >> op;
		cout << endl;
		switch (op)
		{
		case 1:
			cout << "Key   : ";
			cin >> key;
			cout << "Value : ";
			cin >> val;
			at.insert(key, val);
			break;

		case 2:
			cout << "Key   : ";
			cin >> key;
			//at.deleteKey(key);
			break;

		case 3:
			cout << "Key   : ";
			cin >> key;
			cout << "Value : ";
			cin >> val;
			//at.updateVal(key, val);
			break;

		case 4:
			/*cout << "  1. Ascending Order\n";
			cout << "  2. Descending Order\n";
			cout << "   Option : ";
			cin >> op;
			cout << endl;*/
			at.display();

			op = 1;
			break;
		}
		cout << endl;
	} while (op);
	return 0;
}
