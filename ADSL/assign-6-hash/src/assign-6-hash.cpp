//============================================================================
// Name        : assign-6-hash.cpp
// Author      : Mufaddal
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>
#define MAX 10
using namespace std;
class Data
{
	string key;
	int value;
	public:
	Data(string st="", int val = 0)
	{
		key = st;
		value = val;
	}
	friend class HashMap;
};
class HashMap
{
	Data table[MAX];

	public:
		HashMap()
		{

		}
};

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
