//============================================================================
// Name        : assign-8-avl.cpp
// Author      : Mufaddal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>

#define MAX 100

using namespace std;

class AvlNode;
class AvlTree;
class stack;

class stack
{
	AvlNode *arr[MAX];
	int t;

public:
	stack()
	{
		t = -1;
	}

	void push(AvlNode *data)
	{
		t++;
		arr[t] = data;
	}
	void pop()
	{
		t--;
	}
	AvlNode *top()
	{
		return arr[t];
	}
	bool empty() { return t == -1; }
};

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
	void balance(stack);
	int height(AvlNode *t);
	void changeHt(stack);
	AvlNode *rotateRight(AvlNode *t);
	AvlNode *rotateLeft(AvlNode *t);
	stack find(int);
	void inOrderAsc(AvlNode *);
	void inOrderDesc(AvlNode *);

public:
	void insert(int key, int data);
	void display(int);
	void deleteKey(int val);
	void updateVal(int key, int data);
	void search(int key);
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
	stack st;
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
	balance(st);
}

void AvlTree::changeHt(stack st)
{
	AvlNode *child;
	while (!st.empty())
	{
		child = st.top();
		st.pop();
		child->ht = 1 + max(height(child->left), height(child->right));
	}
}

void AvlTree::balance(stack st)
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
		child->ht = 1 + max(height(child->right), height(child->left));
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

void AvlTree::display(int op)
{
	cout << setw(8) << "KEY" << setw(8) << "DATA" << setw(8) << "HEIGHT" << endl;
	switch (op)
	{
	case 1:
		inOrderAsc(root);
		break;
	case 2:
		inOrderDesc(root);
		break;
	}
	/*
	AvlNode *p = root;
	stack st;
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
				cout << p->right->key << " ---- ";
			else
				cout << "NULL ---- ";
			cout << p->ht;
			cout << endl;
		}
	}*/
}

void AvlTree::inOrderAsc(AvlNode *p)
{
	if (p == NULL)
		return;
	inOrderAsc(p->left);
	cout << setw(8) << p->key << setw(8) << p->data << setw(8) << p->ht << endl;
	inOrderAsc(p->right);
}
void AvlTree::inOrderDesc(AvlNode *p)
{
	if (p == NULL)
		return;

	inOrderDesc(p->right);
	cout << setw(8) << p->key << setw(8) << p->data << setw(8) << p->ht << endl;
	inOrderDesc(p->left);
}

stack AvlTree::find(int key)
{
	stack st;
	AvlNode *p = root;
	//st.push(p);
	while (p)
	{
		if (key > p->key)
		{
			st.push(p);
			p = p->right;
		}
		else if (key < p->key)
		{
			st.push(p);
			p = p->left;
		}
		else
			break;
	}
	st.push(p);
	return st;
}

void AvlTree::deleteKey(int key)
{
	stack st1 = find(key);

	if (st1.top() == NULL)
	{
		cout << "Key '" << key << "' not found\n";
		return;
	}
	AvlNode *delKey = st1.top();
	st1.pop();
	AvlNode *delKeyParent;

	if (delKey->left == NULL && delKey->right == NULL) //means the delete node is leaf
	{
		if (!st1.empty())
		{
			delKeyParent = st1.top();
			if (delKeyParent->right == delKey)
			{
				delKeyParent->right = NULL;
			}
			else
			{
				delKeyParent->left = NULL;
			}

			delete delKey;
			changeHt(st1);
			balance(st1);
		}
		else
		{
			root = NULL;
			delete delKey;
		}
	}
	else if (delKey->left && delKey->right == NULL) //means delete node has left subtree only
	{
		if (!st1.empty())
		{
			delKeyParent = st1.top();
			if (delKey == delKeyParent->left)
			{
				delKeyParent->left = delKey->left;
			}
			else
			{
				delKeyParent->right = delKey->left;
			}
		}
		else
		{
			root = root->left;
			st1.push(root);
		}
		delete delKey;
		changeHt(st1);
		balance(st1);
	}
	else if (delKey->left == NULL && delKey->right) //means delete node has right subtree only
	{
		if (!st1.empty())
		{
			delKeyParent = st1.top();
			if (delKey == delKeyParent->left)
			{
				delKeyParent->left = delKey->right;
			}
			else
			{
				delKeyParent->right = delKey->right;
			}
		}
		else
		{
			root = root->right;
			st1.push(root);
		}
		delete delKey;
		changeHt(st1);
		balance(st1);
	}
	else
	{
		stack st2;
		AvlNode *repKeyParent;
		AvlNode *repKey;

		if (delKey->left->right)
		{
			if (st1.empty())
				delKeyParent = root;
			else
				delKeyParent = st1.top();

			AvlNode *k = delKey->left;
			repKey = k;
			repKeyParent = k;
			while (k)
			{
				repKeyParent = repKey;
				st2.push(repKeyParent);
				repKey = k;
				k = k->right;
			}
			repKeyParent->right = NULL;
			repKey->left = delKey->left;
			repKey->right = delKey->right;
			if (delKeyParent->left == delKey)
			{
				delKeyParent->left = repKey;
			}
			else if (delKeyParent->right == delKey)
			{
				delKeyParent->right = repKey;
			}
			else
			{
				root = repKey;
			}
			st1.push(repKey);
			delete delKey;
			changeHt(st2);
			balance(st2);
			changeHt(st1);
			balance(st1);
		}
		else
		{
			if (st1.empty())
				delKeyParent = root;
			else
				delKeyParent = st1.top();

			if (delKey == delKeyParent->left)
			{
				delKeyParent->left = delKey->left;
			}
			else if (delKey == delKeyParent->right)
			{
				delKeyParent->right = delKey->left;
			}
			else
			{
				root = delKey->left;
				st1.push(root);
			}

			delete delKey;
			changeHt(st1);
			balance(st1);
		}
	}

	/*
	if (p->left)
	{
		//st2.push(p);
		p = p->left;
		st2.push(p);
		int f = 0;
		while (p->right)
		{
			f = 1;
			repKeyParent = p;
			p = p->right;
			st2.push(p);
		}
		repKey = p;
		if (!f)
		{
			delKey->left = repKey->left;
		}
		else
		{
			repKeyParent->right = NULL;
		}
	}
	else if (p->right)
	{
		//st2.push(p);
		p = p->right;
		st2.push(p);
		int f = 0;
		while (p->left)
		{
			f = 1;
			repKeyParent = p;
			st2.push(p);
			p = p->left;
		}
		repKey = p;
		if (!f)
		{
			delKey->right = repKey->right;
		}
		else
		{
			repKeyParent->left = NULL;
		}
	}
	else
	{
		if (key > delKeyParent->key)
		{
			delete delKey;
			delKeyParent->right = NULL;
		}
		else if (key < delKeyParent->key)
		{
			delete delKey;
			delKeyParent->left = NULL;
		}
		else
		{
			//this means only root node in tree
		}

		st1.pop();
		changeHt(st1);
		balance(st1);
		return;
	}

	if (key > delKeyParent->key)
	{
		delKeyParent->right = repKey;
		repKey->left = delKey->left;
		repKey->right = delKey->right;
		delete delKey;
	}
	else if (key < delKeyParent->key)
	{
		delKeyParent->left = repKey;
		repKey->left = delKey->left;
		repKey->right = delKey->right;
		delete delKey;
	}
	else
	{
		root = repKey;
		repKey->left = delKey->left;
		repKey->right = delKey->right;
		delete delKey;
		//st2.pop();
	}

	//st2.push(repKeyParent);

	changeHt(st2);
	balance(st2);
	st1.pop();
	st1.push(repKey);
	changeHt(st1);
	balance(st1);*/
}

void AvlTree::updateVal(int key, int data)
{
	AvlNode *p = find(key).top();
	if (p == NULL)
		cout << "Key '" << key << "' not found\n";
	else
	{
		p->data = data;
		cout << "Data of key '" << key << "' updated successfully\n";
	}
}

void AvlTree::search(int key)
{
	AvlNode *p = find(key).top();
	if (p == NULL)
		cout << "Key '" << key << "' not found\n";
	else
	{
		cout << "Key    : " << key << endl;
		cout << "Data   : " << p->data << endl;
		cout << "Height : " << p->ht << endl;
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
		cout << "4. Search key\n";
		cout << "5. Display\n";
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
			at.deleteKey(key);
			break;

		case 3:
			cout << "Key   : ";
			cin >> key;
			cout << "Value : ";
			cin >> val;
			cout << endl;
			at.updateVal(key, val);
			break;
		case 4:
			cout << "Search Key   : ";
			cin >> key;
			cout << endl;
			at.search(key);
			op = 1;
			break;
		case 5:
			cout << "  1. Ascending order \n";
			cout << "  2. Descending order \n";
			cout << "   Option : ";
			cin >> op;
			cout << endl;
			at.display(op);
			op = 1;
			break;
		}
		cout << endl;
	} while (op);
	return 0;
}
