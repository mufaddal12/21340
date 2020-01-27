//============================================================================
// Name        : assign-3-adlist.cpp
// Author      : Mufaddal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <queue>
#define MAX 10
using namespace std;

class GraphNode
{
	string city;
	int time;
	GraphNode *next;
	public:
		GraphNode(string name = "", int t = 0)
		{
			city = name;
			next = NULL;
			time = t;
		}
		friend class AL;
};

class AL
{
	GraphNode **head;
	int n;

	bool cityExist(string);
	bool isPresent(string, GraphNode*);
	int getIndex(string);
	void DFS(string, int*);
	void BFS(string, int*);
	public:
		AL()
		{
			head = new GraphNode*[MAX];
			n = 0;
		}
		void createGraph();
		void showGraph();
		void insertRoute(string, string, int);
		void removeRoute(string, string);
		void insertCity(string);
		void removeCity(string);
		int inDegree(string);
		int outDegree(string);
		void traverse(int, string);
};

int AL::getIndex(string city)
{
	for(int i = 0; i<n; i++)
	{
		if(city == head[i]->city)
			return i;
	}
	return -1;
}

bool AL::isPresent(string dest, GraphNode *src)
{
	GraphNode *p = src->next;
	while(p)
	{
		if(p->city == dest)
			return true;
		p = p->next;
	}
	return false;
}

void AL::createGraph()
{
	cout<<"No. of Cities : "; cin>>n; cout<<endl;
	head = new GraphNode*[n];
	cout<<"Insert all Cities : \n";
	string src;
	for(int i = 0; i<n; i++)
	{
		cout<<"City "<<i+1<<" : "; cin>>src;
		head[i] = new GraphNode(src);
	}
	cout<<endl;
	for(int i = 0; i<n; i++)
	{
		string src = head[i]->city;
		GraphNode *p = head[i];
		int count = 1;
		string dest;
		cout<<"Source City - "<<src<<endl<<endl;
		do
		{
			cout<<"Destination "<<count<<" : "; cin>>dest;
			while((getIndex(dest) == -1 && dest != "none") || isPresent(dest, head[i]))
			{
				cout<<"City '"<<dest<<"' not in Database or re-input of same city\n";
				cout<<"Destination "<<count<<" : "; cin>>dest;
			}
			if(dest != "none")
			{
				int time;
				cout<<"Time from "<<src<<" to "<<dest<<" : "; cin>>time;
				while(time <= 0 && src != dest )
				{
					cout<<"Time cannot be <=0\n";
					cout<<"Time from "<<src<<" to "<<dest<<" : "; cin>>time;
				}
				GraphNode *temp = new GraphNode(dest, time);
				p->next = temp;
				p = temp;
				count++;
			}
			cout<<endl;
		}while(dest!="none");
		cout<<endl;
	}
}

void AL::showGraph()
{
		cout<<"Source-"<<"Destination : "<<"Time\n";
		for(int i = 0;i < n; i++)
		{
			string src = head[i]->city;
			GraphNode *p = head[i]->next;
			while(p)
			{
				string dest = p->city;
				int time = p->time;
				cout<<"'"<<src<<"'->'"<<dest<<"' : "<<time<<endl;
				p = p->next;
			}
		}
}

void AL::insertRoute(string src, string dest, int val)
{
	int s = getIndex(src);
	int d = getIndex(dest);
	if(val)
	{
		if(s!=-1)
		{
			if(d!=-1)
			{
				GraphNode *temp = head[s];
				char op = 'n';
				bool present = isPresent(dest, temp);
				if(present)
				{
					cout<<"Already a route from '"<<src<<"' to '"<<dest<<"' is present. Rewrite it? "; cin>>op;
				}
				if(!present)
				{
					while(temp->next)
						temp = temp->next;
					GraphNode *p = new GraphNode(dest, val);
					temp->next = p;
					cout<<"Route from '"<<src<<"' to '"<<dest<<"' is added.\n";
				}
				else if(op=='y')
				{
					while(temp->city != dest)
						temp = temp->next;
					temp->time = val;
					cout<<"Route from '"<<src<<"' to '"<<dest<<"' is added.\n";
				}
			}
			else
				cout<<"City '"<<dest<<"' not in database\n";
		}
		else
			cout<<"City '"<<src<<"' not in database\n";
	}
	else
		cout<<"Time cannot be <=0\n";
}

void AL::removeRoute(string src, string dest)
{
	int s = getIndex(src);
	if(s != -1)
	{
		if(getIndex(dest) != -1)
		{
			GraphNode *temp = head[s];
			while(temp->next)
			{
				if(temp->next->city == dest)
					break;
				temp = temp->next;
			}
			if(temp->next)
			{
				GraphNode *p = temp->next;
				temp->next = p->next;
				cout<<"Route '"<<src<<"' -> '"<<dest<<"' deleted\n";
				delete p;
			}
			else
				cout<<"No route '"<<src<<"' -> '"<<dest<<"' found\n";
		}
		else
			cout<<"City '"<<dest<<"' not in database\n";
	}
	else
		cout<<"City '"<<src<<"' not in database\n";
}

void AL::insertCity(string city)
{
	if(getIndex(city) == -1)
	{
		if(n!=MAX)
		{
			head[n] = new GraphNode(city);
			n++;
		}
		else
		{
			cout<<"Cannot enter new city\n";
		}
	}
	else
		cout<<"City '"<<city<<"' already in database\n";
}

void AL::removeCity(string city)
{
	int index = getIndex(city);
	if(index != -1)
	{
		GraphNode *del = head[index];
		for(int i = index; i<n-1; i++)
			head[i] = head[i+1];
		n--;
		GraphNode *p = del;
		GraphNode *p1 = p->next;
		while(p1)
		{
			cout<<"Route '"<<city<<"' -> '"<<p1->city<<"' deleted\n";
			p = p1;
			p1 = p1->next;
			delete p;
		}
		delete del;

		for(int i = 0; i<n; i++)
		{
			GraphNode *temp = head[i];
			del = temp;
			while(del->next)
			{
				if(del->next->city == city)
					break;
				del = del->next;
			}
			if(del->next)
			{
				temp = del->next;
				del->next = temp->next;
				cout<<"Route '"<<head[i]->city<<"' -> '"<<temp->city<<"' deleted\n";
				delete temp;
			}
		}

	}
	else
		cout<<"City '"<<city<<"' not in database\n";

}

int AL::inDegree(string dest)
{
	int index = getIndex(dest);
	if(index != -1)
	{
		int count = 0;
		for(int i = 0; i<n; i++)
		{
			GraphNode *temp = head[i];
			if(i != index)
			{
				while(temp)
				{
					if(temp->city == dest)
					{
						count++;
						break;
					}
					temp = temp->next;
				}
			}
		}
		return count;
	}
	else
	{
		cout<<"City '"<<dest<<"' not in database\n";
		return -1;
	}
}

int AL::outDegree(string src)
{
	int index = getIndex(src);
	if(index != -1)
	{
		int count = 0;
		GraphNode *temp = head[index]->next;
		while(temp)
		{
			count++;
			temp = temp->next;
		}
		return count;
	}
	else
	{
		cout<<"City '"<<src<<"' not in database\n";
		return -1;
	}
}

void AL::traverse(int n, string city)
{
	int *arr = new int[n];
	for(int i = 0; i<n; i++)
		arr[i] = 0;
	cout<<endl;
	switch(n)
	{
		case 1:
			DFS(city, arr);
		break;

		case 2:
			BFS(city, arr);
		break;
	}
	cout<<endl;
}

void AL::DFS(string curr, int arr[])
{
	int ind = getIndex(curr);
	if(arr[ind] == 0)
	{
		cout<<curr<<" - ";
		arr[ind] = 1;
		GraphNode *temp = head[ind]->next;
		while(temp)
		{
			DFS(temp->city, arr);
			temp = temp->next;
		}
	}
}

void AL::BFS(string curr, int arr[])
{
	queue<GraphNode*> q;
	int ind = getIndex(curr);
	GraphNode *temp;
	arr[ind] = 1;
	q.push(head[ind]);
	cout<<curr<<" - ";
	while(!q.empty())
	{
		temp = q.front(); q.pop();
		temp = temp->next;
		while(temp)
		{
			ind = getIndex(temp->city);
			if(arr[ind] == 0)
			{
				q.push(head[ind]);
				cout<<temp->city<<" - ";
				arr[ind] = 1;
			}
			temp = temp->next;
		}
	}
}

int main()
{
	AL g1;
	string src, dest;
	int val;
	int n;
	int op;
	do
	{
		cout<<"1. Create graph\n";
		cout<<"2. Insert new city\n";
		cout<<"3. Delete city\n";
		cout<<"4. Insert new route\n";
		cout<<"5. Delete route\n";
		cout<<"6. In-degree of a city\n";
		cout<<"7. Out-degree of a city\n";
		cout<<"8. Display\n";
		cout<<"9. Traverse\n";
		cout<<"0. Exit\n";
		cout<<"  Option : "; cin>>op;
		cout<<endl;
		switch(op)
		{
			case 1:
				g1.createGraph();
			break;

			case 2:
				cout<<"Enter city Name : "; cin>>src;
				g1.insertCity(src);
			break;

			case 3:
				cout<<"Enter city Name : "; cin>>src;
				g1.removeCity(src);
			break;

			case 4:
				cout<<"Enter source      : "; cin>>src;
				cout<<"Enter destination : "; cin>>dest;
				cout<<"Time from '"<<src<<"' to '"<<dest<<"' : "; cin>>val;
				g1.insertRoute(src, dest, val);

			break;

			case 5:
				cout<<"Enter source      : "; cin>>src;
				cout<<"Enter destination : "; cin>>dest;
				g1.removeRoute(src, dest);
			break;

			case 6:
				cout<<"City : "; cin>>dest;
				n = g1.inDegree(dest);
				if(n!=-1)
					cout<<"In-Degree of city '"<<dest<<"' is "<<n<<endl;
			break;

			case 7:
				cout<<"City : "; cin>>src;
				n = g1.outDegree(src);
				if(n!=-1)
					cout<<"Out-Degree of city '"<<src<<"' is "<<n<<endl;
			break;

			case 8:
					g1.showGraph();
			break;

			case 9:
				cout<<"    1. Depth First Search\n";
				cout<<"    2. Breadth First Search\n";
				cout<<"      Option : "; cin>>op; cout<<endl;
				if (op == 1 || op ==2)
				{
					cout<<"City to start Traversal from : "; cin>>src;
					g1.traverse(op, src);
				}
				op = 1;
			break;
		}
		cout<<endl;
	}while(op);
	return 0;
}











