#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void Welcome();
void Readfile(vector<string>&, string);
void Userinput(const vector<string>&);
void printlist(const vector<string>&, char = 'u'); // default 'u' - unsorted
void findname(const vector<string>&);
void includestr(const vector<string>&);
void backup(const vector<string>&);

int main()
{
	Welcome();
	vector<string> Names;
	Readfile(Names, "name.txt");

	Userinput(Names);
}

void Welcome()
{
	cout << "Hello, You can use these commands:\n\n"
		<< "a) \"l\" list all names from the file.\n"
		<< "b) \"s\" list all names sorted A - Z.\n"
		<< "c) \"k\" find name. You need to input the name you are looking for, e.g. \"David\".\n"
		<< "d) \"f\" filter. If you type \"f\", You'll need to input a string.\n"
		<< "e) \"b\" backup. The program will create a backup copy of the input file.\n"
		<< "f) \"e\" Exit. The program will end.\n"
		<< "g) \"i\" instructions.\n" << endl;
}

void Readfile(vector<string>& Names, string filename)
{
	ifstream fin(filename);
	string word;
	while (fin >> word)
	{
		Names.push_back(word);
	}
}

void Userinput(const vector<string>& Names)
{
	string command;
	while (true)
	{
		cout << "\nEnter command: ";
		cin >> command;
		if (command.size() > 1)
		{
			cout << "Wrong command!" << endl;
			continue;
		}
		else if (command[0] == 'e')
		{
			cout << "Good bye!" << endl;
			break;
		}

		switch (command[0])
		{
		case'i': Welcome(); break;
		case'l': printlist(Names); break;
		case's': printlist(Names, 's'); break;
		case'k': findname(Names); break;
		case'f': includestr(Names); break;
		case'b': backup(Names); break;
		default: cout << "Wrong command!" << endl; break;
		}
	}
}

void printlist(const vector<string>& Names, char condition)
{
	int size = Names.size();
	if (condition == 's')
	{
		vector<string> tmp; // lets make a copy of our list
		for (int i = 0; i < size; ++i)
		{
			tmp.push_back(Names[i]);
		}
		sort(tmp.begin(), tmp.end()); // standard sort algorithm
		for (size_t i(0); i < size; ++i)
		{
			if (i % 7 == 0)
				cout << endl;
			cout << left << setw(14) << tmp[i] + ", ";
		}
	}
	else
	{
		for (size_t i(0); i < size; ++i)
		{
			if (i % 7 == 0)
				cout << endl;
			cout << left << setw(14) << Names[i] + ", ";
		}
	}
	cout << endl;
}

void findname(const vector<string>& Names)
{
	string example;
	cout << "Enter name you are looking for: ";
	cin >> example;

	int counter = 0;
	for (int i = 0, size = Names.size(); i < size; ++i)
	{
		if (Names[i] == example)
			++counter;
	}
	cout << "Word \"" << example << "\" was found " << counter << " times" << endl;
}

void includestr(const vector<string>& Names)
{
	string partof;
	cout << "Enter SubString: ";
	cin >> partof;

	int counter, quantity = 0;

	for (int i = 0, size = Names.size(); i < size; ++i) // go for all our names
	{
		counter = 0;
		for (int j = 0, k = 0; j < Names[i].size(); ++j) // go for all characters of each name
		{
			if (Names[i][j] == partof[k]) // if first characters are same ++counter
			{
				++counter;
				if (counter == partof.size()) // if counter equals string's length then we found it
				{
					if (quantity % 7 == 0)
						cout << endl;
					cout << left << setw(14) << Names[i] + ", ";
					++quantity;
					break;
				}
				++k;
			}
			else if (Names[i].size() - (j + 1) < partof.size()) // if there are less characters than we need for a word then we cant find it
			{
				break;
			}
			else // if none of those happen then we should stay on first character and counter should return to 0
			{
				k = 0;
				counter = 0;
			}
		}
	}
	if (quantity == 0)
		cout << "None of these Names include \"" << partof << "\"." << endl;
	else
		cout << endl;
}

void backup(const vector<string>& Names)
{
	static int exists = 0; // static, otherwise we cant know if copy already exists

	if (exists > 0)
	{
		string answer;
		while (true)
		{
			cout << "Such copy of file already exists, would you like to override it? (y or n) ";
			cin >> answer;
			if (answer.size() > 1)
			{
				cout << "Wrong input!" << endl;
				continue;
			}
			if (answer[0] == 'y')
			{
				cout << "Copy is overrided!" << endl;
				break;
			}
			else if (answer[0] == 'n')
			{
				cout << "New Copy is created!" << endl;
				++exists;
				break;
			}
			else
				cout << "Wrong input!" << endl;
		}
	}
	else
	{
		cout << "File Copy is created!" << endl;
		++exists;
	}
	string filename = "Copy_Names" + to_string(exists) + ".txt";
	ofstream fout(filename);
	for (int i = 0, size = Names.size(); i < size; ++i)
		fout << Names[i] << endl;

	// if program ends, we can't know if there was a copy, because static variable will be gone!!!
}