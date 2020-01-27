//============================================================================
// Name        : linked.cpp
// Author      : Mufaddal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

class node
{
	int data;
	node *next;
	public:
		friend class LL;
		node(int k = 0)
		{
			data=k;
			next = NULL;
		}
};

class LL
{
	node *head;
	int length;
	public:
		LL(){head = NULL; length = 0;}
		void insert(int,int);
		void deletenode(int);
		void reverse();

		void display()
		{
			node *p = head;
			while(p)
			{
				cout<<p->data<<" ";
				p = p->next;
			}
			cout<<endl;
		}
		int size()
		{
			return length;
		}
};

void LL::insert(int val, int pos)
{
	if(!head)
	{
		head = new node;
		head->data = val;
		length = 1;
	}
	else
	{
		int c=1;
		node *p = head;
		while(c<pos-1 && p->next)
		{
			p=p->next;
			c++;
		}
		node *t = new node(val);
		if(pos==1)
		{
			t->next=head;
			head = t;
		}
		else
		{
			t->next = p->next;
			p->next=t;
		}
		length++;
	}
}
void LL::deletenode(int pos)
{
	if(!head)
		cout<<"Empty list\n";
	else
	{
		int c=1;
		node *p = head;
		while(c<pos-1 && p->next)
		{
			c++;
			p=p->next;
		}
		node *t = p->next;
		if(pos==1)
		{
			t = head;
			head = head->next;
			cout<<t->data<<" deleted\n";
		}
		else
		{
			t = p->next;
			p->next = p->next->next;
			cout<<t->data<<" deleted\n";
		}
		delete t;
		t = NULL;
		length--;
	}
}

void LL::reverse()
{
	if(head)
	{
		node *p1 = head;
		node *p2 = head->next;
		p1->next=NULL;
		node *p3;
		while(p2)
		{
			p3 = p2->next;
			p2->next=p1;
			p1 = p2;
			p2 = p3;
		}
		head = p1;
	}
}


int main()
{
	LL list;
	int op;
	do
	{
		cout<<"1. Insert at \n";
		cout<<"2. Delete from \n";
		cout<<"3. Reverse\n";
		cout<<"4. Display\n";
		cout<<"0. Exit\n";
		cout<<" Option  : "; cin>>op;
		switch(op)
		{
			case 1 :
				cout<<"  1. Beginning\n";
				cout<<"  2. Position\n";
				cout<<"  3. End\n";
				cout<<"   Option : "; cin>>op;
				int val;

				switch(op)
				{
					case 1 :
						cout<<"Value : "; cin>>val;
						list.insert(val,1);
					break;

					case 2 :
						cout<<"Value : "; cin>>val;
						int pos;
						cout<<"Position : "; cin>>pos;
						if(pos>=0 && pos<=list.size())
							list.insert(val,pos);
						else
							cout<<"Position out of range\n";
					break;

					case 3 :
						cout<<"Value : "; cin>>val;
						list.insert(val,list.size()+1);
					break;
				}
				op = 1;
			break;

			case 2 :
				cout<<"  1. Beginning\n";
				cout<<"  2. Position\n";
				cout<<"  3. End\n";
				cout<<"   Option : "; cin>>op;
				switch(op)
				{
					case 1 :
						list.deletenode(1);
					break;

					case 2 :
						int pos;
						cout<<"Position : "; cin>>pos;
						if(pos>=0 && pos<=list.size())
							list.deletenode(pos);
						else
							cout<<"Position out of range\n";
					break;

					case 3 :
						list.deletenode(list.size());
					break;
				}
				op=1;
			break;

			case 3:
				list.reverse();
			break;

			case 4 :
				list.display();
			break;
		}
		cout<<endl;
	}while(op);
	return 0;
}















