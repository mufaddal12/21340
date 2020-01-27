//============================================================================
// Name        : assign-3-tbt.cpp
// Author      : Mufaddal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <queue>
using namespace std;

class treeNode
{
	treeNode *left; bool lbit;
	int data;
	treeNode *right; bool rbit;
	public:
		treeNode(int val = 0)
		{
			data = val;
			lbit = rbit = true;
			left = right = NULL;
		}
		friend class TBT;
};

class TBT
{
	treeNode *head;

	void insertLeft(treeNode*, treeNode*);

	void insertRight(treeNode*, treeNode*);

	treeNode* inSuc(treeNode*);

	void dispInOrder(treeNode*);

	public:
		TBT()
		{
			head = new treeNode();
			head->lbit = 0;
			head->left = head;
			head->rbit = 1;
			head->right = head;
		}

		void createTree();

		void inOrder();

		void preOrder();

};

void TBT::createTree()
{
	queue<treeNode*> q;
	q.push(head);
	while(!q.empty())
	{
		treeNode* temp = q.front();
		q.pop();
		int val;
		cout<<"Add to left of "<<temp->data<<" : "; cin>>val;
		if(val)
		{
			treeNode *l = new treeNode(val);
			insertLeft(temp, l);
			q.push(l);
		}
		if(temp != head)
		{
			cout<<"Add to right of "<<temp->data<<" : "; cin>>val;
			if(val)
			{
				treeNode *r = new treeNode(val);
				insertRight(temp, r);
				q.push(r);
			}
		}
	}
}

void TBT::insertLeft(treeNode* parent, treeNode* child)
{
	child->lbit = parent->lbit;
	child->left = parent->left;
	child->right = parent;
	child->rbit = 0;
	parent->left = child;
	parent->lbit = 1;
}

void TBT::insertRight(treeNode* parent, treeNode* child)
{
	child->right = parent->right;
	child->rbit = parent->rbit;
	child->left = parent;
	child->lbit = 0;
	parent->right = child;
	parent->rbit = 1;
}

void TBT::inOrder()
{
	dispInOrder(head);
	cout<<endl;
}

treeNode* TBT::inSuc(treeNode* t)
{
	treeNode* s = t->right;
	if(t->rbit)
		while(s->lbit)
			s = s->left;
	return s;
}

void TBT::dispInOrder(treeNode *T)
{
	while(1)
	{
		T = inSuc(T);
		if(T==head)
			return;
		cout<<T->data<<"-";
	}
}

void TBT::preOrder()
{
	int flag = 1;
	treeNode *p = head->left;
	while(p!=head)
	{
		while(flag)
		{
			cout<<p->data<<"-";
			if(p->lbit)
				p=p->left;
			else
				break;
		}
		flag = p->rbit;
		p = p->right;
	}
	cout<<endl;
}

int main()
{
	TBT t;
	int op;
	do
	{
		cout<<"1. Create Tree\n";
		cout<<"2. In-Order Traveersal\n";
		cout<<"3. Pre-Order Traversal\n";
		cout<<"0. Exit\n";
		cout<<" Option : "; cin>>op;
		cout<<endl;
		switch(op)
		{
			case 1:
				t.createTree();
			break;

			case 2:
				t.inOrder();
			break;

			case 3:
				t.preOrder();
			break;
		}
		cout<<endl;
	}while(op);
	t.createTree();
	return 0;
}










