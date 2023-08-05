#include <iostream>
#include <list>
#include <string>

using namespace std;

class Graph
{
	int V;

	list<int>* adj;
	char* parent;
	size_t** Edge;
	int* d;
	bool* visited;
	int* COLOR;

public:
	Graph(int V)
	{
		this->V = V;
		adj = new list<int>[V];
		parent = new char[V]; // მშობელი
		Edge = new size_t * [V]; // წიბოს წონა
		d = new int[V]; // სიგრძე საწყისი წვეროდან
		visited = new bool[V]; // თეთრი ან შავი (მოუნახულებელი ან მონახულებული)
		COLOR = new int[V]; // ფერი დავალებისთვის

		for (int i = 0; i < V; ++i)
		{
			Edge[i] = new size_t[V];
		}
	}

	~Graph()
	{
		// გავასუფთავოთ heap მეხსიერება
		delete[] adj;
		delete[] parent;
		delete[] d;
		delete[] visited;
		delete[] COLOR;
		for (int i = 0; i < V; ++i)
		{
			delete[] Edge[i];
		}
		delete[] Edge;
	}

	void addEdge(char v, char w, int Weight = 1) // გულისხმობით წიბოს წონა 1-ია
	{
		int a = IntoInt(v);
		int b = IntoInt(w);
		if (a < V && a >= 0 && Weight >= 0)
		{
			adj[a].push_back(b);
			Edge[a][b] = Weight;
		}
		else
		{
			cout << "Warning: Algorithm does not work for Negative weights.\n" << endl;
			cout << "Or we can't create Edge (\'" << v << "\', " << w << "\')" << endl;
		}
	}

	// ლათინური ასო გადაჰყავს რიცხვში
	int IntoInt(char k)
	{
		switch (k)
		{
		case 'a': return 0;
		case'b': return 1;
		case'c': return 2;
		case'd': return 3;
		case'e': return 4;
		case'f': return 5;
		case'g': return 6;
		case'-': return -1; // NULL
		default: return V;
		}
	}

	// რიცხვი გადაჰყავს ლათინურ ასოში
	char IntoChar(int a)
	{
		switch (a)
		{
		case 0: return 'a';
		case 1: return 'b';
		case 2: return 'c';
		case 3: return 'd';
		case 4: return 'e';
		case 5: return 'f';
		case 6: return 'g';
		case -1: return '-'; // NULL
		default: return 'Z';
		}
	}

	void BFS(char s)
	{
		int S = IntoInt(s); // გადავიყვანოთ გადმოწოდებული სიმბოლო რიცხვში რომ შემდგომ ვიმუშაოთ მასთან

		for (int i = 0; i < V; ++i)
		{
			parent[i] = '-'; // (NULL)
			d[i] = -1; // (უსასრულობა)
			visited[i] = false; // ყველა წვეროს ანიჭებს აღმოუჩენელი წვეროს სტატუსს
		}

		// რიგი, რომელსაც ვიყენებთ BFS-ში
		list<int> queue;

		// s წვეროს ვანიჭებთ აღმოჩენილის სტატუსს, სიგრძეს 0-ს და შეგვაქვს რიგში. parent[S] = '-' აღარაა საჭირო!
		visited[S] = true;
		d[S] = 0;
		queue.push_back(S);

		list<int>::iterator i;

		cout << "Vertex <-> length from \'" << s << "\' <-> parent:\n" << endl;
		while (!queue.empty())
		{
			// რიგიდან ამოიღე პირველივე ელემენტი და დაბეჭდე (FIFO)

			S = queue.front(); // შევინახოთ პირველი ელემენტი
			cout << '\'' << IntoChar(S) << "\'  <->  " << d[S] << "  <->  \'" << parent[S] << '\'' << endl; // დავბეჭდოთ
			queue.pop_front(); // და წავშალოთ queue-დან

			for (i = adj[S].begin(); i != adj[S].end(); ++i) // გადავიაროთ queue-დან ამოღებული ელემენტის მოსაზღვრე წვეროები
			{
				if (!visited[*i]) // თუ არ არის მონახულებული
				{
					visited[*i] = true; // ვაქციოთ მონახულებულად
					d[*i] = d[S] + Edge[S][*i]; // სიგრძე გავხადოთ მშობლის სიგრძეს + წონა
					parent[*i] = IntoChar(S); // მშობელი განვუსაზღვროთ
					queue.push_back(*i); // და ჩავსვათ რიგში

					// ყოველი ახლად აღმოჩენილი წვერო შევღებოთ მშობლის ფერისგან განსხვავებული ფერით! --> დავალებისთვის
					if (COLOR[S] == 1)
						COLOR[*i] = 2;
					else if (COLOR[S] == 2)
						COLOR[*i] = 1;
				}
			}
		}
		cout << endl;
	}

	// ბეჭდავს გზას start-დან current-მდე
	void P_P(char start, char current)
	{
		int S = IntoInt(start);
		int C = IntoInt(current);

		if (S == C)
		{
			cout << '\'' << start << '\'' << " ";
			return;
		}
		else if (parent[C] == '-')
		{
			cout << "There's no way!" << endl;
			exit(0); // დასრულდეს პროგრამა
		}
		else P_P(start, parent[C]); // რეკურსია

		for (int i = 0; i < Edge[IntoInt(parent[C])][C]; ++i) // წიბოს წონის მიხედვით ბეჭდავს მის სიგრძეს '-' სიმბოლოს დახმარებით
			cout << "-";
		cout << "> \'" << current << "\' ";
	}

	bool DyeInTwoColors()
	{
		// 0 - შეუღებავი(აღმოუჩენელი), 1 - თეთრი, 2 - შავი

		for (int i = 0; i < V; ++i)
		{
			COLOR[i] = 0; // ყველა წვერო გავხადოთ შეუღებავი
		}

		COLOR[IntoInt('a')] = 1; // ავირჩიოთ რომელიმე წვერო და შევღებოთ თეთრად (ავირჩიე წვერო 'a')

		BFS('a'); // გავუშვათ სიგანეში ძებნის ალგორითმი არჩეული წვეროდან

		// ახლა ყოველი აღმოუჩენელი წვეროსთვის ვამოწმებთ არის, თუ არა იგი მიერთებული ორ ან მეტ ერთსა და იმავე ფრად შეღებილ წვეროსთან

		int countwhite = 0;
		int countblack = 0;
		for (int i = 0; i < V; ++i)
		{
			if (!visited[i]) // ან COLOR[i] == 0
			{
				// ყოველი ციკლისას დავსვათ მთვლელები 0-ზე
				countwhite = 0;
				countblack = 0;

				for (auto it = adj[i].begin(); it != adj[i].end(); ++it) // ყოველი მეზობელი წვეროსთვის
				{
					if (COLOR[*it] == 1) // თუ მეზობელი წვეროს ფერი არის თეთრი
						++countwhite;
					else if (COLOR[*it] == 2) // თუ მეზობელი წვეროს ფერი არის შავი
						++countblack;
					// თუ მეზობელი წვერო საერთოდ არაა შეღებილი ანუ COLOR[*it] == 0, მაშინ უბრალოდ გავაგრძელოთ პროცესი
				}

				// ყველა მეზობელი წვეროს მონახულების შემდეგ, თუ მათგან რომელიმე ორი ან მეტი წვერო შეღებილია ერთი ფერით (შავით ან თეთრით),
				// (შეუღებლობა არ ითვლება, შესაძლოა ორი ან მეტი შეუღებელი გვყავდეს) მაშინ გრაფი არ შეიღებება ორად
				if (countwhite >= 2 || countblack >= 2)
					return false;
			}
		}

		// თუ კოდმა აქამდე მოაღწია მაშინ გრაფი შეიღებება ორად
		return true;
	}
};

int main()
{
	Graph G(6);

	G.addEdge('a', 'c');
	G.addEdge('c', 'a');
	G.addEdge('a', 'd');
	G.addEdge('d', 'a');
	G.addEdge('c', 'b');
	G.addEdge('b', 'c');
	G.addEdge('b', 'd');
	G.addEdge('d', 'b');
	G.addEdge('f', 'd');
	G.addEdge('d', 'f');

	// 1) !!! შემოვლას (BFS-ს) რომელი წვეროდანაც ვიწყებთ იქიდან აიღება თითოეული წვეროს მშობელი !!!
	// 2) !!! რომელი წვეროდანაც BFS-ი (შემოვლა) იწყება, იქიდან ვიყენებთ P_P ფუნქციასაც ყოველი სხვა წვეროსთვის,
	//		  რადგან სხვა შემთხვევაში, წვერომ მშობელი არ იცის!!!
	// 3) !!! მარყუჟის წონა შეგვიძლია მივუთითოთ, მაგრამ d-ში არ აისახება ალგორითმიდან გამომდინარე !!!

	cout << "BFS from 'a':\n" << endl;
	G.BFS('a');

	cout << "\nThe way from 'a' to 'f':\n" << endl;
	G.P_P('a', 'f');

	cout << "\n\nBFS from 'd':\n" << endl;
	G.BFS('d');
	cout << "\nThe way from 'd' to 'a':\n" << endl;
	G.P_P('d', 'a');


	cout << "\n\nBFS from 'c':\n" << endl;
	G.BFS('c');
	cout << "\nThe way from 'c' to 'd':\n" << endl;
	G.P_P('c', 'd');

											// გრაფის ორ ფრად შეღებვისთვის დამატებული კოდი
	if (G.DyeInTwoColors())
	{
		cout << "This Graph can be Dyed in two colors!" << endl;
	}
	else
	{
		cout << "This Graph can NOT be Dyed in two colors!" << endl;
	}
}
