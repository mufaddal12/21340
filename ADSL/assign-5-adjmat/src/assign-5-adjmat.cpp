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
	int prims(int);
	void getallmins(int arr[]);
	void displayFather(int arr[]);
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
		int minSpanTree(int);
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
			while(dest>n || (dest<src && dest!=0))
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
				G[dest][src] = cost;
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
			if(G[i][j] != 999)
				cout<<setw(5)<<G[i][j];
			else
				cout<<setw(5)<<"INF";
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

void AdjMat::getallmins(int arr[])
{
	for(int i = 1; i<=n; i++)
	{
		arr[i] = 1;
		for(int j = 0;j<n; j++)
		{
			if(G[i][j] < G[i][arr[i]])
				arr[i] = j;
		}
	}
}

void AdjMat::displayFather(int arr[])
{
	for(int i = 1; i<=n;i++)
	{
		if(arr[i] != 0)
			cout<<i<<" -> "<<arr[i]<<endl;
	}
}

int AdjMat::kruskals()
{
	int min = 1000, temp, temp1;
	int wt_tree = 0, count = 0;
	int root_temp, root_temp1;
	int father[MAX]= {0}, result[MAX][MAX] = {{0}};
	int g[MAX][MAX];
	for(int i = 0; i<=n; i++)
		for(int j = 0; j<=n; j++)
			g[i][j] = G[i][j];
	while(count<n-1)
	{
		min = 1000;
		for(int v1 = 1; v1<=n; v1++)
		{
			for(int v2 = 1; v2<=n; v2++)
			{
				if(g[v1][v2] != 0 && min>g[v1][v2])
				{
					min = g[v1][v2];
					temp = v1;
					temp1 = v2;
				}
			}
		}
		int t = temp, t1 = temp1;
		g[temp][temp1] = g[temp1][temp] = 0;
		while(temp>0)
		{
			root_temp = temp;
			temp = father[temp];
		}
		while(temp1>0)
		{
			root_temp1 = temp1;
			temp1 = father[temp1];
		}
		if(root_temp != root_temp1)
		{
			result[t][t1] = result[t1][t] = min;
			wt_tree += min;
			father[root_temp1] = root_temp;
			//count++;

		}
		count++;
	}
	displayFather(father);
	return wt_tree;
}

int AdjMat::prims(int v1)
{
	int count1 = 1, count = 0;
	int arr[MAX];
	arr[count1] = v1;
	count1++;
	int min = 999;
	int temp = 0, temp1 = 0;
	int g[MAX][MAX];
	int wt_tree = 0;
	for(int i = 0; i<=n; i++)
		for(int j = 0; j<=n; j++)
			g[i][j] = G[i][j];
	int father[MAX]= {0}, result[MAX][MAX] = {{0}};

	while(count<n-1)
	{
		min = 999;
		for(v1 = 1; v1<count1; v1++)
		{
			for(int v2 = 1; v2<=n; v2++)
			{
				if(g[arr[v1]][v2] != 0)
				{
					if(g[arr[v1]][v2] < min)
					{
						min = g[arr[v1]][v2];
						temp = arr[v1];
						temp1 = v2;
					}
				}
			}
		}
		int t = temp, t1 = temp1;
		g[t][t1] = g[t1][t] = 0;
		int root_temp=0, root_temp1=0;
		while(temp>0)
		{
			root_temp = temp;
			temp = father[temp];
		}
		while(temp1>0)
		{
			root_temp1 = temp1;
			temp1 = father[temp1];
		}
		if(root_temp != root_temp1)
		{
			result[t][t1] = result[t1][t] = min;
			wt_tree += min;
			father[root_temp1] = root_temp;
			//count++;
		}count++;
	}
	displayFather(father);
	return wt_tree;
}

int AdjMat::minSpanTree(int op)
{
	int st;
	switch(op)
	{
		case 1:
			cout<<"Starting vertex : "; cin>>st;
			if(st>n || st<1)
				return -1;
			return prims(st);

		break;

		case 2:
			return kruskals();
		break;
	}
	return -1;
}

int main()
{
	AdjMat a1;
	int op;
	int weight;
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
				{
					weight = a1.minSpanTree(op);
					cout<<"Weight of Minimum Spanning tree : "<<weight<<endl;
					op = 1;
				}
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
19
0
3
16
5
20
0
5
18
0
0
0
*/











