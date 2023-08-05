#include <iostream>
#include <vector>

using namespace std;

class ქურდი_და_ზურგჩანთა
{
	int Weight;
	int stuffnumber;
	int** V;
	vector<pair<int, int>> Jewelry;

public:

	ქურდი_და_ზურგჩანთა(int ზურგჩანთის_წონა, int ნივთების_რაოდენობა)
	{
		Weight = ზურგჩანთის_წონა;
		stuffnumber = ნივთების_რაოდენობა;

		V = new int* [stuffnumber + 1];
		for (int i = 0; i <= stuffnumber; ++i)
		{
			V[i] = new int[Weight + 1];
		}

		// ნულოვანი სვეტისა და სტრიქონის ინიციალიზაცია ნულებით, რადგან თუ არაფერს ჩავდებთ ჩანთაში ფასი 0 გამოდის და ასევე თუ ჩანთა არ გვაქვს მასში ვერაფერს ჩავდებთ
		for (int i = 0; i <= stuffnumber; ++i)
		{
			V[i][0] = 0;
		}
		for (int j = 0; j <= Weight; ++j)
		{
			V[0][j] = 0;
		}
	}

	~ქურდი_და_ზურგჩანთა()
	{
		for (int i = 0; i <= stuffnumber; ++i)
		{
			delete[] V[i];
		}
		delete[] V;
	}

	void Add_Jewel(int Value, int Weight)
	{
		if (Jewelry.size() == stuffnumber)
		{
			cout << "You can't add stuff anymore..." << endl;
		}
		else if (Value > 0 && Weight > 0)
		{
			Jewelry.push_back({ Value, Weight });
		}
		else
		{
			cout << "Invalid arguments!" << endl;
		}
	}

	int MAX(int a, int b)
	{
		return (a >= b) ? a : b;
	}

	// დინამიკური პროგრამირება - რეკურსია
	int VALUE(int i, int j)
	{
		if (i == 0 || j == 0)
		{
			return 0;
		}

		if (j >= Jewelry[i - 1].second)
		{
			return MAX(VALUE(i - 1, j), (Jewelry[i - 1].first + VALUE(i - 1, j - Jewelry[i - 1].second)));
		}

		return VALUE(i - 1, j);
	}

	void მაქსიმალური_მოგება_ქურდობისას()
	{
		cout << "All Jewelry:\n" << endl;
		for (size_t i(0); i < Jewelry.size(); ++i)
		{
			cout << i + 1 << ") (Value, Weight) -> (" << Jewelry[i].first << " Gel, " << Jewelry[i].second << " kg)\n";
		}
		cout << endl;
		//-------------------------------------------------

		for (int i = 1; i <= stuffnumber; ++i)
		{
			for (int j = 1; j <= Weight; ++j)
			{
				V[i][j] = VALUE(i, j); // რეკურსიული ფუნქცია
			}
		}

		vector<pair<int, int>> Result;
		for (int i = stuffnumber, j = Weight; i > 0 && j > 0; --i) // დავიწყოთ ბოლო ნივთიდან და ჩავიდეთ პირველამდე, გავიგოთ შევა თუ არა თითოეული შედეგში
		{
			if (V[i][j] > V[i - 1][j])
			{
				Result.push_back(Jewelry[i - 1]);
				j -= Jewelry[i - 1].second;
			}
		}
		
		// ------------------------------------------------
		cout << "Maximal Value of Stolen Jewelry: " << V[stuffnumber][Weight] << " Gel" << endl;
		cout << "BackPack, containing all of these Jewelry:\n" << endl;
		for (size_t i(0); i < Result.size(); ++i)
		{
			cout << i + 1 << ") (Value, Weight) -> (" << Result[i].first << " Gel, " << Result[i].second << " kg)\n";
		}
		cout << endl << endl;
	}
};

int main()
{
	ქურდი_და_ზურგჩანთა ციხე(10, 4); // ჩანთის ტევადობა - 10კგ და ნივთების რაოდენობა - 4

	ციხე.Add_Jewel(12, 3); // (ნივთის ფასი - ₾, ნივთის წონა - კგ)
	ციხე.Add_Jewel(25, 4);
	ციხე.Add_Jewel(30, 7);
	ციხე.Add_Jewel(14, 2);

	ციხე.მაქსიმალური_მოგება_ქურდობისას();


	// ეს მაგალითი უკვე გავარჩიეთ უნივერსიტეტში და ბარემ ეწეროს

	ქურდი_და_ზურგჩანთა ლუკა(5, 4); // ჩანთის ტევადობა - 5კგ და ნივთების რაოდენობა - 4

	ლუკა.Add_Jewel(12, 2); // (ნივთის ფასი - ₾, ნივთის წონა - კგ)
	ლუკა.Add_Jewel(10, 1);
	ლუკა.Add_Jewel(20, 3);
	ლუკა.Add_Jewel(15, 2);

	ლუკა.მაქსიმალური_მოგება_ქურდობისას();
}