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
			parent[i] = '-'; // (NULL)
			d[i] = -1; // (უსასრულობა)
			visited[i] = false; // ყველა წვეროს ანიჭებს აღმოუჩენელი წვეროს სტატუსს
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

	bool DyeInTwoColors()
	{
		// 0 - შეუღებავი(აღმოუჩენელი), 1 - თეთრი, 2 - შავი

		for (int i = 0; i < V; ++i)
		{
			COLOR[i] = 0; // ყველა წვერო გავხადოთ შეუღებავი
		}

		COLOR[0] = 1; // დავიწყოთ პირველი წვეროთი და გავხადოთ იგი თეთრი
		bool result = BFS(IntoChar(0)); // გამოვიძახოთ პირველი წვეროსთვის ალგორითმი, ის დაადგენს შექმნილი კლასტერი შეიძლება თუ არა შეიღებოს ორ ფრად


		for (int i = 1; i < V && result; ++i) // ყოველი შემდგომი კლასტერისთვის იგივე გავიმეოროთ
		{
			if (!visited[i])
			{
				COLOR[i] = 1;
				result = BFS(IntoChar(i));
			}
		}

		return result; // დავაბრუნოთ true თუ ყველა კლასტერმა ჩააბარა პირობა, თუ არადა false
	}

	bool BFS(char s)
	{
		int S = IntoInt(s); // გადავიყვანოთ გადმოწოდებული სიმბოლო რიცხვში რომ შემდგომ ვიმუშაოთ მასთან

		// რიგი, რომელსაც ვიყენებთ BFS-ში
		list<int> queue;

		// s წვეროს ვანიჭებთ აღმოჩენილის სტატუსს, სიგრძეს 0-ს, მშობელს '-' და შეგვაქვს რიგში
		parent[S] = '-';
		visited[S] = true;
		d[S] = 0;
		queue.push_back(S);

		cout << "Vertex <-> length from \'" << s << "\' <-> parent <-> COLOR:\n" << endl;
		while (!queue.empty())
		{
			// რიგიდან ამოიღე პირველივე ელემენტი და დაბეჭდე (FIFO)

			S = queue.front(); // შევინახოთ პირველი ელემენტი
			cout << '\'' << IntoChar(S) << "\'  <->  " << d[S] << "  <->  \'" << parent[S] << "\' <-> " << Get_Color(COLOR[S]) << endl; // დავბეჭდოთ
			queue.pop_front(); // და წავშალოთ queue-დან

			for (auto i = adj[S].begin(); i != adj[S].end(); ++i) // გადავიაროთ queue-დან ამოღებული ელემენტის მოსაზღვრე წვეროები
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
				else if (COLOR[*i] == COLOR[S]) // თუ მოსაზღვრე წვერო უკვე მონახულებულია, მაშინ შევამოწმოთ იგივე ფერი აქვს თუ არა მასაც
				{
					return false; // თუ იგივე ფერი აქვს, მაშინ ეს პირობას ეწინააღმდეგება და ორ ფრად ვერ შეიღებება გრაფი
				}
			}
		}
		cout << endl;
		return true; // თუ კოდი აქამდე მოვიდა ესეიგი გრაფის მოცემული კლასტერი ორ ფრად შეიღებება
	}

	// აბრუნებს სტრიქონს(ფერს) ციფრის მიხედვით
	string Get_Color(int x)
	{
		switch (x)
		{
		case 0: return "NO_COLOR";
		case 1: return "White";
		case 2: return "Black";
		default: return "Red :)";
		}
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

	// გრაფის ორ ფრად შეღებვისთვის დამატებული კოდი

	if (G.DyeInTwoColors())
	{
		cout << "\nThis Graph can be Dyed in two colors!" << endl;
	}
	else
	{
		cout << "\nThis Graph can NOT be Dyed in two colors!" << endl;
	}
}
