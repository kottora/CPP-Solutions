#include <iostream>
#include "MyList.h"

using namespace std;

int main()
{
	cout << "Hello world" << endl;
	MyList<int> L1;
	for (int i(0); i < 100; ++i)
	{
		L1.push(i);
	}
	cout << L1 << endl;
	L1[49] = 12345;
	cout << L1 << endl;

	L1.erase(12345);
	cout << L1 << endl;

	L1.erase(0);
	cout << L1 << endl;

	L1.operator=(L1);
	MyList<int> L2;
	L2 = L1;
	cout << "L2" << endl;
	cout << L2 << endl;

	cout << "Luka" << endl;
	MyList<int> luka(L2);
	cout << luka << endl;

	luka.push(0000000000);
	cout << luka << endl;

	if (luka.search(9999999))
	{
		cout << 9999999 << " is in the List" << endl;
	}
	else
	{
		cout << 9999999 << " is not in the List" << endl;
	}

	if (luka.search(0))
	{
		cout << 0 << " is in the List" << endl;
	}
	else
	{
		cout << 0 << " is not in the List" << endl;
	}

	MyList<int>* misho = new MyList<int>;
	misho->push(1999);
	misho->display(cout);
	delete misho;
	misho = nullptr;
	cout << "Well Done!" << endl;
}