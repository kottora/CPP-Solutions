#include <iostream>

using namespace std;

#define size 25

int main()
{
	char *x = new char[size];
	char *y = new char[size];

	char* a = x;
	char* b = y;

	cout << "Enter first word: ";
	cin >> x;
	cout << "Enter second word: ";
	cin >> y;

	while (*(++a)); // there is '\0' at the end

	while (*(a++) = *(b++));

	cout << "After concatenate: " << x << endl;

	delete[] x;
	delete[] y;
}