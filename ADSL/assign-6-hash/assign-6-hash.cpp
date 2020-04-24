//============================================================================
// Name        : assign-6-hash.cpp
// Author      : Mufaddal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iomanip>
#define MAX 10
using namespace std;
class Data
{
	int key;
	int value;
	public:
	Data(int st=0, int val = 0)
	{
		key = st;
		value = val;
	}
	friend class HashMap;
};
class HashMap
{
	Data table[MAX];
	int n;
	int hashFunc(int key);
	public:
		HashMap(int k = 10)
		{
			n = k;
			Data d;
			for(int i =0; i<n; i++)
				table[i] = d;
		}
		void insertWithoutRep(int key, int val);
		void insertWithRep(int key, int val);
		void deleteKey(int key);
		int find(int key);
		void display();
		float averageCost();
};

int HashMap::hashFunc(int key)
{
	return key%n;
}

void HashMap::insertWithoutRep(int key, int val)
{
	int ind = hashFunc(key);
	int i = ind;
	bool firstHit = true;
	while(table[i].key != 0)
	{
		i++;
		i = i%n;
		if(i == ind) break;
		firstHit = false;
	}
	if(i != ind || firstHit)
	{
		Data d(key, val);
		table[i] = d;
	}
	else
		cout<<"Overflow\n";
}

void HashMap::insertWithRep(int key, int val)
{
	int ind = hashFunc(key);
	if(table[ind].key == 0)
	{
		Data d(key, val);
		table[ind] = d;
		return;
	}
	else
	{
		Data newd = table[ind];
		Data d(key, val);
		if(ind == hashFunc(newd.key))
			insertWithoutRep(key, val);
		else
		{
			Data d(key, val);
			table[ind] = d;
			insertWithoutRep(newd.key, newd.value);
		}
		return;
	}
}

void HashMap::display()
{
	cout<<setw(7)<<"Index"<<setw(5)<<"Key"<<setw(7)<<"Value"<<endl;
	for(int i = 0; i<n; i++)
	{
		cout<<setw(7)<<i<<setw(5)<<table[i].key<<setw(7)<<table[i].value<<endl;
	}
}

float HashMap::averageCost()
{
	int totalcost = 0;
	int count = 0;
	for(int i = 0; i< n; i++)
	{
		Data d = table[i];
		if(d.key != 0)
		{
			int ind = hashFunc(d.key);
			count ++;
			totalcost++;
			while(table[ind].key != d.key)
			{
				totalcost++;
				ind++;
				ind = ind%n;
			}
		}
	}
	float avg = totalcost/float(count);
	return avg;
}

int HashMap::find(int key)
{
	int ind = hashFunc(key);
	if(table[ind].key == 0)
	{
		cout<<"Key '"<<key<<"' not found";
		return -1;
	}
	else
	{
		int i = ind;
		while(table[i].key != key)
		{
			i++;
			i = i%n;
			if(i==ind)
			{
				i = -1;
				break;
			}
		}
		if(i != -1)
		{
			cout<<"Key   : "<<key<<" ";
			cout<<"Value : "<<table[i].value;
		}
		else
			cout<<"Key '"<<key<<"' not found";

		return i;
	}

}

void HashMap::deleteKey(int key)
{
	int ind = find(key);
	if(ind != -1)
	{
		cout<<" deleted\n";
		table[ind].key = 0;
		table[ind].value = 0;
	}
}

int main() {
	int op;
	HashMap h;
	int key, val;
	cout<<"1. Hashing With Replacement\n";
	cout<<"2. Hashing without replacement\n";
	int withrep;
	cout<<"  Option : "; cin>>withrep;
	cout<<endl;
	do
	{
		cout<<"1. Insert\n";
		cout<<"2. Find\n";
		cout<<"3. Delete\n";
		cout<<"4. Average cost\n";
		cout<<"5. Display Hash Table\n";
		cout<<"0. Exit\n";
		cout<<"  Option : "; cin>>op;
		cout<<endl;
		switch(op)
		{
			case 1:
				cout<<"Key   : "; cin>>key;
				cout<<"Value : "; cin>>val;
				switch(withrep)
				{
					case 1:
						h.insertWithRep(key, val);
					break ;

					case 2:
						h.insertWithoutRep(key, val);
					break ;
				}
			break;

			case 2:
				cout<<"Key : "; cin>>key;
				key = h.find(key);
				cout<<endl;
			break;

			case 3:
				cout<<"Key : "; cin>>key;
				h.deleteKey(key);
			break;

			case 4:
				cout<<"Average search cost is "<<h.averageCost()<<endl;

			break;

			case 5:
				h.display();
			break;
		}
		cout<<endl;
	}while(op);
	return 0;
}













