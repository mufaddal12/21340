//============================================================================
// Name        : assign-1-binary.cpp
// Author      : Mufaddal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

using namespace std;

class treeNode
{
	int data;
	treeNode *left, *right;
	public:
		treeNode(int val = 0)
		{
			data = val;
			left = right = NULL;
		}
		friend class tree;
};

class tree
{
	treeNode *root;

	treeNode* makeTree();

	void preOrderR(treeNode*); //root,left,right
	void inOrderR(treeNode*); //left, root, right
	void postOrderR(treeNode*); //left, right, root

	void preOrderNR(); //root,left,right
	void inOrderNR(); //left, root, right
	void postOrderNR(); //left, right, root

	void clear(treeNode*);

	void mirrorize(treeNode*);

	void leaves(treeNode*);
	void internalNodes(treeNode*);

	void copyTree(treeNode*, treeNode*);

	bool isEqual(treeNode*, treeNode*);

	public:
		tree()
		{
			root = NULL;
		}
		void create() { root = makeTree(); }
		void traverseR(int);
		void traverseNR(int);
		void clearTree() { clear(root); root = NULL; }
		void mirror();
		void allNodes(int);
		void operator =(tree &);
		void test(tree );
		bool operator ==(tree &);
};

treeNode *tree::makeTree()
{
	treeNode *ret = new treeNode;
	cout<<"Data : "; cin>>ret->data;
	cout<<"Add left child to "<<ret->data<<"? ";
	char op;
	cin>>op;
	if(op=='y' || op=='Y')
		ret->left=makeTree();
	cout<<"Add right child to "<<ret->data<<"? ";
	cin>>op;
	if(op=='y' || op=='Y')
		ret->right=makeTree();
	return ret;
}

void tree::traverseR(int op)
{
	cout<<endl;
	switch(op)
	{
		case 1 :
			preOrder(root);
			cout<<endl;
		break;

		case 2 :
			inOrder(root);
			cout<<endl;
		break;

		case 3 :
			postOrder(root);
			cout<<endl;
		break;
	}
	cout<<endl;
}

void tree::preOrderR(treeNode *disp)
{
	if(!disp)
		return;
	else
	{
		cout<<disp->data<<" - ";
		preOrderR(disp->left);
		preOrderR(disp->right);
	}
}

void tree::inOrderR(treeNode *disp)
{
	if(!disp)
		return;
	else
	{
		inOrderR(disp->left);
		cout<<disp->data<<" - ";
		inOrderR(disp->right);
	}
}

void tree::postOrderR(treeNode *disp)
{
	if(!disp)
		return;
	else
	{
		postOrderR(disp->left);
		postOrderR(disp->right);
		cout<<disp->data<<" - ";
	}
}

void tree::traverseNR(int op)
{
	cout<<endl;
	switch(op)
	{
		case 1 :
			preOrderNR();
			cout<<endl;
		break;

		case 2 :
			inOrderNR();
			cout<<endl;
		break;

		case 3 :
			postOrderNR();
			cout<<endl;
		break;
	}
	cout<<endl;
}

void tree::inOrderNR()
{
	treeNode* stack[50];
	int top = 0;
	treeNode *temp = root;
	while(1)
	{
		while(temp)
		{
			top++;
			stack[top] = temp;
			temp = temp->left;
		}
		if(top == 0)
			break;
		else
		{
			temp = stack[top];
			cout<<temp->data<<" - ";
			top--;
			temp = temp->right;
		}
	}
}

void tree::preOrderNR()
{
	treeNode* stack[50];
	int top = 0;
	treeNode *temp = root;
	while(1)
	{
		while(temp)
		{
			top++;
			cout<<temp->data<<" - ";
			stack[top] = temp->right;
			temp = temp->left;
		}
		if(top == 0)
			break;
		else
		{
			temp = stack[top];
			top--;
		}
	}
}

void tree::postOrderNR()
{
	treeNode* stack[50];
	int top = 0;
	treeNode *temp = root;
	while(1)
	{
		while(temp)
		{
			top++;
			stack[top] = temp;
			if(temp->right)
			{
				top++;
				stack[top] = temp->right;
				top++;
				stack[top] = NULL;
			}
			temp = temp->left;
		}
		while(stack[top] && top!=0)
		{
			temp = stack[top];
			cout<<temp->data<<" - ";
			top--;
		}
		if(top != 0)
			top--;
		if(top==0)
			break;
		temp = stack[top];
		top--;
	}
}

void tree::clear(treeNode* del)
{
	if(!del)
		return;
	else
	{
		clear(del->left);
		clear(del->right);
		cout<<"Node "<<del->data<<" deleted\n";
		delete del;
		del = NULL;
	}
}

void tree::mirror()
{
	if(!root)
		return;
	mirrorize(root);
}

void tree::mirrorize(treeNode *node)
{
	if(node)
	{
		mirrorize(node->left);
		mirrorize(node->right);
		treeNode *temp = node->right;
		node->right = node->left;
		node->left = temp;
	}
}

void tree::allNodes(int op)
{
	cout<<endl;
	switch(op)
	{
		case 1 :
			leaves(root);
		break;

		case 2 :
			internalNodes(root);
		break;
	}
}

void tree::leaves(treeNode* p)
{
	if(p == NULL)
		return;
	else if( p->left == NULL && p->right == NULL)
		cout<<p->data<<" - ";
	else
	{
		leaves(p->left);
		leaves(p->right);
	}
}

void tree::internalNodes(treeNode* p)
{
	if(p==root)
	{
		internalNodes(p->left);
		internalNodes(p->right);
	}
	else if(p == NULL)
		return;
	else if( p->left != NULL || p->right != NULL)
	{
		cout<<p->data<<" - ";
		internalNodes(p->left);
		internalNodes(p->right);
	}
}

void tree::operator =(tree &t)
{
	if(t.root)
	{
		root = new treeNode(t.root->data);
		copyTree(root,t.root);
	}
}

void tree::copyTree(treeNode *t1, treeNode *t2)
{
	if(t2->left)
	{
		t1->left = new treeNode(t2->left->data);
		copyTree(t1->left, t2->left);
	}
	if(t2->right)
	{
		t1->right = new treeNode(t2->right->data);
		copyTree(t1->right, t2->right);
	}
}

bool tree::operator ==(tree &t2)
{
	return isEqual(root, t2.root);
}

bool tree::isEqual(treeNode* node1, treeNode* node2)
{
	bool out;
	if(node1 && !node2)
		return false;
	if(!node1 && node2)
		return false;
	if(!node1 && !node2)
		return true;
	else
	{
		out = (node1->data == node2->data);
		out = out && isEqual(node1->left, node2->left);
		out = out && isEqual(node1->right, node2->right);
		return out;
	}

}

int main()
{
	int op, op1;
	tree t1, t2;
	do
	{
		cout<<"1. Create Tree\n";
		cout<<"2. Traverse\n";
		cout<<"2. Recursive Traverse\n";
		cout<<"3. Non-Recursive Traverse\n";
		cout<<"4. Display Types of nodes\n";
		cout<<"5. Clear Tree\n";
		cout<<"6. Tree1 = Tree2\n";
		cout<<"7. Compare Trees\n";
		cout<<"0. Exit\n";
		cout<<" Option : "; cin>>op;
		cout<<endl;
		switch(op)
		{
			case 1 :
				t1.clearTree();
				t1.create();
			break;

			case 2:
				cout<<"  1. Tree 1\n";
				cout<<"  2. Tree 2\n";
				cout<<"   Option : "; cin>>op;
				cout<<endl;
				cout<<"    1. Pre-Order Traversal\n";
				cout<<"    2. In-Order Traversal\n";
				cout<<"    3. Post-Order Traversal\n";
				cout<<"     Option : "; cin>>op1;
				switch(op)
				{
					case 1 :
						t1.traverseR(op1);
					break;

					case 2:
						t2.traverseR(op1);
					break;
				}
				op = 1;
			break;

			case 3:
				cout<<"  1. Tree 1\n";
				cout<<"  2. Tree 2\n";
				cout<<"   Option : "; cin>>op;
				cout<<endl;
				cout<<"    1. Pre-Order Traversal\n";
				cout<<"    2. In-Order Traversal\n";
				cout<<"    3. Post-Order Traversal\n";
				cout<<"     Option : "; cin>>op1;
				switch(op)
				{
					case 1 :
						t1.traverseNR(op1);
					break;

					case 2:
						t2.traverseNR(op1);
					break;
				}
				op = 1;
			break;

			case 4:
				cout<<"  1. Tree 1\n";
				cout<<"  2. Tree 2\n";
				cout<<"   Option : "; cin>>op;
				cout<<endl;
				cout<<"    1. Leaves\n";
				cout<<"    2. Internal nodes\n";
				cout<<"     Option : "; cin>>op1;
				cout<<endl;
				switch(op)
				{
					case 1 :
						t1.allNodes(op1);
					break;

					case 2:
						t2.allNodes(op1);
					break;
				}

				op = 1;
			break;


			case 5:
				cout<<"  1. Tree 1\n";
				cout<<"  2. Tree 2\n";
				cout<<"   Option : "; cin>>op;
				cout<<endl;
				switch(op)
				{

					case 1 :
						t1.clearTree();
					break;

					case 2:
						t2.clearTree();
					break;
				}
			break;

			case 6:
				t2 = t1;
			break;

			case 7:
				if(t1 == t2)
					cout<<"Trees are equal\n";
				else
					cout<<"Trees are not equal\n";
			break;
		}
		cout<<endl;
	}while(op);
	return 0;
}







