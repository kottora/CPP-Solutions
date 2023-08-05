#include <iostream>
#include <string>

#include "MyVector.h"

using namespace std;

int main()
{
	MyVector<int> Luka;
	Luka.Push_back(100);
	Luka.Push_back(199);
	Luka.Push_back(122);
	Luka.Push_back(23);
	Luka.Push_back(7);
	Luka.Push_back(1);
	cout << Luka << endl;

	Luka.erase(100);
	cout << Luka << endl;

	Luka.insert(100, 0);
	Luka.insert(200, 5);
	Luka.erase(200);
	cout << Luka << endl;

	MyVector<string> misho;
	misho.Push_back("Luka");
	//misho[0] = "Misho";
	cout << misho << endl;

	MyVector<int> nana;
	for (size_t i(0); i < 100; ++i)
	{
		nana.Push_back(i);
	}
	cout << nana << endl;

	Luka = nana;

	cout << Luka << endl;

	Luka.Shrink_to_size();

	MyVector<int>* vec = new MyVector<int>(Luka);
	cout << *vec << endl;
	delete vec;
}