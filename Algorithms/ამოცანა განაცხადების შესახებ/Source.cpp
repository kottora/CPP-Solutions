#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Applications
{
	int განაცხადების_მაქსიმალური_რაოდენობა;
	vector<pair<double, double>> Durations;

public:
	Applications(int განაცხადების_მაქსიმალური_რაოდენობა)
	{
		this->განაცხადების_მაქსიმალური_რაოდენობა = განაცხადების_მაქსიმალური_რაოდენობა;
	}

	void Add_Application(double S_i, double f_i)
	{
		if (Durations.size() == განაცხადების_მაქსიმალური_რაოდენობა)
		{
			cout << "You can't add Applications anymore..." << endl;
			return;
		}
		if (f_i >= S_i && S_i >= 0.0)
		{
			Durations.push_back({ S_i, f_i });
		}
		else
		{
			cout << "Ilegal Arguments!" << endl;
		}
	}

	void Greedy_Activation_Select()
	{
		cout << "All Applications:\n" << endl;
		for (size_t i(0); i < Durations.size(); ++i)
		{
			cout << i + 1 << ") (S_i, f_i) -> " << "(" << Durations[i].first << ", " << Durations[i].second << ")\n";
		}
		cout << endl;


		// Sort by f_i
		sort(Durations.begin(), Durations.end(),
			[](const pair<double, double> a, const pair<double, double> b)
			{
				return a.second < b.second;
			}
		);

		int size = Durations.size();
		vector<pair<double, double>> Result;

		Result.push_back(Durations[0]); // შედეგში ჩავწეროთ პირველივე განაცხადი

		for (size_t i = 1, j = 0; i < size; ++i)
		{
			// თუ წინა განაცხადის დასრულების დრო ნაკლებია ან ტოლია მოცემული განაცხადის დაწყების დროზე მაშინ ეს განაცხადი ჩავწეროთ სიაში
			if (Durations[i].first >= Durations[j].second)
			{
				Result.push_back(Durations[i]);
				j = i;
			}
		}

		cout << "Maximum possible number of Compatible applications: " << Result.size() << "\n" << endl;
		for (size_t i(0); i < Result.size(); ++i)
		{
			cout << i + 1 << ") (S_i, f_i) -> " << "(" << Result[i].first << ", " << Result[i].second << ")\n";
		}
		cout << endl;
	}
};

int main()
{
	Applications App1(5); // განაცხადების მაქსიმალური რაოდენობა

	App1.Add_Application(1, 2); // (დაწყების დრო, დასრულების დრო)
	App1.Add_Application(2.1, 14);
	App1.Add_Application(13, 14);
	App1.Add_Application(5, 13);
	App1.Add_Application(14, 23);

	App1.Greedy_Activation_Select(); // ხარბი ალგორითმი
}