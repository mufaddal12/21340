//============================================================================
// Name        : assig-2-BST.cpp
// Author      : Mufaddal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<string>
using namespace std;

class treeNode
{
	string key;
	int data;
	treeNode *left, *right;
	public:
		treeNode(string k="", int val = 0)
		{
			key = k;
			data = val;
			left = right = NULL;
		}
		friend class Dictionary;
};

class Dictionary
{
	treeNode *root;

	void incInOrder(treeNode*);
	void decInOrder(treeNode*);

	void deleteBST(treeNode*, treeNode*);

	void copyTree(treeNode*, treeNode*);

	public:
		Dictionary(){ root = NULL; }
		void addKey(string, int);
		void deleteKey(string);
		void updateVal(string, int);
		void display(int);
		void operator =(Dictionary&);
		int isKey(string);
};

void Dictionary::addKey(string key, int value = 0)
{
	if(!root)
	{
		root = new treeNode(key, value);
	}
	else
	{
		treeNode *temp = root;
		treeNode *temp2 = root;
		while(temp)
		{
			if(key>temp->key)
			{
				temp2 = temp;
				temp = temp->right;
			}
			else if(key<temp->key)
			{
				temp2 = temp;
				temp = temp->left;
			}
			else
				break;
		}
		if(temp)
			cout<<"Key Already in Dataset\n";
		else
		{
			treeNode *node = new treeNode(key, value);
			if(key > temp2->key)
				temp2->right = node;
			else
				temp2->left = node;
		}
	}
}

void Dictionary::display(int op)
{
	if(op == 1)
		incInOrder(root);
	if(op == 2)
		decInOrder(root);
}

void Dictionary::incInOrder(treeNode *disp)
{
	if(!disp)
		return;
	else
	{
		incInOrder(disp->left);
		cout<<'"'<<disp->key<<'"'<<" : ";
		cout<<disp->data<<endl;
		incInOrder(disp->right);
	}
}

void Dictionary::decInOrder(treeNode *disp)
{
	if(!disp)
		return;
	else
	{
		decInOrder(disp->right);
		cout<<'"'<<disp->key<<'"'<<" : ";
		cout<<disp->data<<endl;
		decInOrder(disp->left);
	}
}

void Dictionary::deleteKey(string key)
{
	treeNode *child = root;
	treeNode *parent = root;
	int del = 1;
	if(root == NULL)
	{
		cout<<"Empty Dictionary\n";
		return;
	}
	while(child->key != key && child && del)
	{
		if(key>child->key)
		{
			parent = child;
			if(child->right)
				child = child->right;
			else del = 0;
		}
		else if(key<child->key)
		{
			parent = child;
			if(child->left)
				child = child->left;
			else del = 0;
		}
	}
	if(del)
		deleteBST(parent, child);
	else
		cout<<"Key "<<'"'<<key<<'"'<<" not Found\n";
}

void Dictionary::deleteBST(treeNode *parent, treeNode *child)
{
	if(child->left && child->right)
	{
		parent = child;
		treeNode *temp = child->right;
		while(temp->left)
		{
			parent = temp;
			temp = temp->left;
		}
		cout<<"key "<<'"'<<child->key<<'"'<<" Deleted\n";
		child->data = temp->data;
		child->key = temp->key;
		delete temp;
		temp = NULL;
	}
	else if(child->left == NULL && child->right == NULL)
	{
		if(parent->right == child)
			parent->right = NULL;
		else
			parent->left = NULL;
		cout<<"key "<<'"'<<child->key<<'"'<<" Deleted\n";
		delete child;
		child = NULL;
	}
	else if(child->left == NULL && child->right)
	{
		if(parent->left == child)
			parent->left = child->right;
		else
			parent->right = child->right;
		cout<<"key "<<'"'<<child->key<<'"'<<" Deleted\n";
		delete child;
		child = NULL;
	}
	else
	{
		if(parent->left == child)
			parent->left = child->left;
		else
			parent->right = child->left;
		cout<<"key "<<'"'<<child->key<<'"'<<" Deleted\n";
		delete child;
		child = NULL;
	}
}

void Dictionary::updateVal(string key, int value)
{
	treeNode *temp = root;
	while(temp && temp->key!=key)
	{
		if(key>temp->key)
		{
			temp = temp->right;
		}
		else if(key < temp->key)
		{
			temp = temp->left;
		}
	}
	if(temp)
		temp->data = value;
	else
		cout<<"Key "<<'"'<<key<<'"'<<" not Found\n";
}

void Dictionary::operator =(Dictionary &d)
{
	if(d.root)
		{
			root = new treeNode(d.root->key, d.root->data);
			copyTree(root,d.root);
		}
}

void Dictionary::copyTree(treeNode *t1, treeNode *t2)
{
	if(t2->left)
		{
			t1->left = new treeNode(t2->left->key, t2->left->data);
			copyTree(t1->left, t2->left);
		}
		if(t2->right)
		{
			t1->right = new treeNode(t2->right->key, t2->right->data);
			copyTree(t1->right, t2->right);
		}
}

int Dictionary::isKey(string key)
{
	int count = 1;
	treeNode *temp = root;
	while(temp && temp->key!=key)
	{
		if(key>temp->key)
			temp = temp->right;
		else
			temp = temp->left;
		count++;
	}
	if(temp)
		return count;
	else
		return -1;
}

int main()
{
	Dictionary d1, d2;
	string key; int val;
	int c;
	int op, op1;
	do
    {
		cout<<"1. Insert Data\n";
		cout<<"2. Delete Data\n";
		cout<<"3. Update Data\n";
		cout<<"4. Search a key\n";
		cout<<"5. Equate 2 trees\n";
		cout<<"6. Display\n";
		cout<<" Option : "; cin>>op;
		cout<<endl;
		switch(op)
		{
			case 1 :
				cout<<"Key   : "; cin>>key;
				cout<<"Value : "; cin>>val;
				d1.addKey(key,val);
			break;

			case 2 :
				cout<<"Key   : "; cin>>key;
				d1.deleteKey(key);
			break;

			case 3 :
				cout<<"Key   : "; cin>>key;
				cout<<"Value : "; cin>>val;
				d1.updateVal(key, val);
			break;

			case 4:
				cout<<"Enter key :"; cin>>key;
				c = d1.isKey(key);
				if(c!=-1)
					cout<<"Key '"<<key<<"' found in "<<c<<" comparisons\n";
				else
					cout<<"Key '"<<key<<"' not found\n";
			break;

			case 5 :
				d2 = d1;
			break;

			case 6 :
				cout<<"  1. Dictionary 1\n";
				cout<<"  2. Dictionary 2\n";
				cout<<"   Option : "; cin>>op;
				cout<<endl;
				if(op==1 || op==2)
				{
					cout<<"    1. Ascending Order\n";
					cout<<"    2. Descending Order\n";
					cout<<"     Option : "; cin>>op1;
					cout<<endl;
				}
				switch(op)
				{
					case 1 :
						d1.display(op1);
					break;

					case 2 :
						d2.display(op1);
					break;
				}
				op = 1;
			break;
		}
		cout<<endl;
	}while(op);
	return 0;
}
