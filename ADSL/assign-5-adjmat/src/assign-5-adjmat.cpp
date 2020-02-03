//============================================================================
// Name        : assign-5-adjmat.cpp
// Author      : Mufaddal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>

#define MAX 10
using namespace std;

class AdjMat
{
	int G[MAX][MAX];
	int n;

	bool isPresent(int, int);
	int kruskals();
	int prims(int, int ar[]);
public:
		AdjMat()
		{
			for(int i = 0; i<MAX; i++)
					for(int j = 0; j<MAX; j++)
						G[i][j] = 999;
			n = 0;
		}
		void createGraph();
		void showGraphMat();
		void showGraph();
		void shortestPath(int);
};

bool AdjMat::isPresent(int dest, int src)
{
	return G[src][dest] != 999;
}

void AdjMat::createGraph()
{
	cout<<"No. of Branches : "; cin>>n;
	cout<<endl;
	for(int src = 1; src<=n; src++)
	{
		cout<<"Source Branch - "<<src<<endl<<endl;
		int dest, cost;
		do
		{
			cout<<"Destination Branch : "; cin>>dest;
			while(dest>n || dest<0)
			{
				cout<<"Branch no. out of range\n";
				cout<<"Destination Branch : "; cin>>dest;
			}
			if(dest)
			{
				cout<<"Cost from Branch "<<src<<" to Branch "<<dest<<" : "; cin>>cost;
				while(cost<=0 || cost>=999)
				{
					cout<<"Invalid cost\n";
					cout<<"Cost from Branch "<<src<<" to Branch "<<dest<<" : "; cin>>cost;
				}
				G[src][dest] = cost;

			}
			cout<<endl;
		}while(dest);
	}
}

void AdjMat::showGraphMat()
{
	for(int j = 1; j<=n; j++)
		cout<<setw(5)<<j;
	cout<<endl;
	for(int i = 1; i<=n; i++)
	{
		cout<<i;
		for(int j = 1; j<=n; j++)
			cout<<setw(5)<<G[i][j];
		cout<<endl;
	}
}

void AdjMat::showGraph()
{
	for(int i = 1; i<=n; i++)
		for(int j = 1; j<=n; j++)
			if(G[i][j] != 999)
				cout<<"'"<<i<<"' -> '"<<j<<"' : "<<G[i][j]<<endl;
}

int AdjMat::kruskals()
{
	int *arr = new int[n+1];
	for(int i = 1; i<=n; i++)
		arr[i] = 0;

}

int main()
{
	AdjMat a1;
	int op;
	do
	{
		cout<<"1. Create Graph\n";
		cout<<"2. Show Graph\n";
		cout<<"3. Find Minimum Path\n";
		cout<<"0. Exit\n";
		cout<<"  Option : "; cin>>op; cout<<endl;
		switch(op)
		{
			case 1:
				a1.createGraph();
			break;

			case 2:
				cout<<"Normal Graph : \n";
				a1.showGraph();
				cout<<"\nAdjacency Matrix : \n";
				a1.showGraphMat();
			break;

			case 3:
				cout<<"    1. Prim's \n";
				cout<<"    2. Kruskal's \n";
				cout<<"  Option : "; cin>>op; cout<<endl;
				if(op == 1 || op == 2)
					//a1.shortestPath(op);
					op = 1;
				else
					op = 1;
			break;
		}
		cout<<endl;
	}while(op);
}

/*
1
5
2
20
4
15
0
1
16
4
12
5
10
0
2
19
0
3
25
5
18
0
1
23
3
14
0
 */











