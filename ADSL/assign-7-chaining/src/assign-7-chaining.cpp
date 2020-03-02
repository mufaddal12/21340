//============================================================================
// Name        : assign-7-chaining.cpp
// Author      : Mufaddal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#include <iomanip>
#define MAX 100
using namespace std;

class Data
{
	string name;
	int value;
	int next;
	public:
		Data(string key ="", int val = 0, int nextind = -1)
		{
			name = key;
			value = val;
			next = nextind;
		}
		friend class HashMap;
};

class HashMap
{
	Data table[MAX];
	int n;
	int hashFunc(string key);
	int getIndex(string key);
	public:
		HashMap(int k = 26)
		{
			n = k;
			Data d;
			for(int i =0; i<n; i++)
				table[i] = d;
		}
		void insertWithoutRep(string key, int val);
		void insertWithRep(string key, int val);
		void deleteKey(string key);
		int find(string key);
		void display();
		float averageCost();
};

int HashMap::hashFunc(string key)
{
	return (key[0]-'a')%26;
}

int HashMap::getIndex(string key)
{
	int i = hashFunc(key);
	while(i!=-1)
	{
		if(table[i].name == key) break;
		i = table[i].next;
	}
	return i;
}

void HashMap::insertWithoutRep(string key, int val)
{
	int ind = hashFunc(key);
	int i = ind;
	bool firsthit = true;
	while(i != -1)
	{
		ind = i;
		i = table[ind].next;
	}
	int k = ind;
	while(table[k].name != "")
	{
		firsthit = false;
		k = (k+1)%n;
		if(k == ind)
		{
			k = -1;
			break;
		}
	}
	if(k==-1)
		cout<<"Overflow\n";
	else
	{
		Data d(key, val);
		table[k] = d;
		if(!firsthit)
			table[ind].next = k;
	}
}

void HashMap::insertWithRep(string key, int val)
{
	int ind = hashFunc(key);
	if(table[ind].name == "")
	{
		Data d(key, val);
		table[ind] = d;
		return;
	}
	else
	{
		Data newd = table[ind];
		int newind = hashFunc(newd.name);
		if(newind==ind)
			insertWithoutRep(key, val);
		else
		{
			Data d(key, val);
			//table[ind] = d;
			int prev = newind;
			int nextind = table[ind].next;
			while(newind != ind)
			{
				prev = newind;
				newind = table[newind].next;
			}
			table[prev].next = nextind;
			table[ind] = d;
			insertWithoutRep(newd.name, newd.value);
		}

	}
}

int HashMap::find(string key)
{
	int i = getIndex(key);
	if(i!=-1)
		return table[i].value;
	return i;
}

void HashMap::deleteKey(string key)
{
	int ind = getIndex(key);
	if(ind == -1)
		cout<<"Key not Found\n";
	else
	{
		int newind = hashFunc(key);
		int prev = newind;
		int next = table[ind].next;
		while(newind != ind)
		{
			prev = newind;
			newind = table[newind].next;
		}
		table[prev].next = next;
		Data dold = table[ind];
		Data d;
		table[ind] = d;
		cout<<"Data for key '"<<key<<"' deleted\n";
	}

}

void HashMap::display()
{
	cout<<setw(7)<<"Index"<<setw(5)<<"Char"<<setw(5)<<"Key"<<setw(7)<<"Value"<<setw(6)<<"Next"<<endl;
	for(int i = 0; i<n; i++)
	{
		cout<<setw(7)<<i<<setw(5)<<char(i+'a')<<setw(5)<<table[i].name<<setw(7)<<table[i].value<<setw(6)<<table[i].next<<endl;
	}
}

float HashMap::averageCost()
{
	int allCount = 0;
	int total = 0;
	for(int i = 0; i<n; i++)
	{
		string key = table[i].name;
		if(key!="")
		{
			int j = hashFunc(key);
			allCount++;
			while(j!=-1)
			{
				if(table[j].name == key) break;
				j = table[j].next;
				allCount++;
			}
			total++;
		}
	}
	if(total==0) return 0;
	return float(allCount)/float(total);
}

int main() {
	int op;
	HashMap h;
	string key;
	int val;
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
				val = h.find(key);
				if(val==-1)
					cout<<"Key '"<<key<<"' not found\n";
				else
					cout<<"Value : "<<val<<endl;
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
