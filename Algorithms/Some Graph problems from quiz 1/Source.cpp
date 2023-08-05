#include <iostream>
#include <list>
#include <string>

using namespace std;

class Graph
{
	int V;

	list<int>* adj;
	string* parent;
	size_t** Edge;
	int* length;

public:
	Graph(int V)
	{
		this->V = V;
		adj = new list<int>[V];
		parent = new string[V]; // მშობელი (NULL)
		Edge = new size_t * [V];
		length = new int[V]; // უსასრულობა
		for (int i = 0; i < V; ++i)
		{
			Edge[i] = new size_t[V];
			parent[i] = "NULL";
			length[i] = -1; // სიგრძე საწყისი წვეროდან 
		}
	}

	~Graph()
	{
		delete[] adj;
		delete[] parent;
		delete[] length;
		for (int i = 0; i < V; ++i)
		{
			delete[] Edge[i];
		}
		delete[] Edge;
	}

	void addEdge(int v, int w, int Weight = 1)
	{
		if (v < V && v >= 0 && Weight >= 0)
		{
			adj[v].push_back(w);
			Edge[v][w] = Weight;
		}
		else
		{
			cout << "Algorithm does not work for Negative weights.\n" << endl;
		}
	}

	void BFS(int s)
	{
		bool* visited = new bool[V]; // თეთრი ან შავი (მოუნახულებელი ან მონახულებული)


		// ყველა წვეროს ანიჭებს აღმოუჩენელი წვეროს სტატუსს, სიგრძეს მშობლიდან: უსასრულობას(-1)
		for (int i = 0; i < V; ++i)
		{
			visited[i] = false; // თეთრი
		}


		// რიგი, რომელსაც ვიყენებთ BFS-ში
		list<int> queue;

		// s წვეროს ვანიჭებთ აღმოჩენილის სტატუსს, სიგრძეს 0-ს და შეგვაქვს რიგში
		visited[s] = true;
		length[s] = 0;
		queue.push_back(s);

		list<int>::iterator i;

		cout << "Vertex <-> length from " << s << " <-> parent:\n" << endl;
		while (!queue.empty())
		{
			// რიგიდან ამოიღე პირველივე ელემენტი და დაბეჭდე (FIFO)

			s = queue.front(); // შევინახოთ პირველი ელემენტი
			cout << '\'' << s << "\'  <->  " << length[s] << "  <->  \'" << parent[s] << '\'' << endl; // დავბეჭდო
			queue.pop_front(); // და წავშალოთ queue-დან

			for (i = adj[s].begin(); i != adj[s].end(); ++i) // გადავიაროთ queue-დან ამოღებული ელემენტის მოსაზღვრე წვეროები
			{
				if (!visited[*i]) // თუ არ არის მონახულებული
				{
					visited[*i] = true; // ვაქციოთ მონახულებულად
					length[*i] = length[s] + Edge[s][*i]; // სიგრძე გავხადოთ მშობლის სიგრძეს + წონა
					parent[*i] = to_string(s); // მშობელი განვუსაზღვროთ
					queue.push_back(*i); // და ჩავსვათ რიგში
				}
			}
		}
		cout << endl;

		delete[] visited;
	}

	void P_P(int start, int current)
	{
		if (start == current)
		{
			cout << '\'' << start << '\'' << " ";
			return;
		}
		else if (parent[current] == "NULL")
		{
			cout << "There's no way!" << endl;
			exit(0);
		}
		else P_P(start, stoi(parent[current]));

		for (int i = 0; i < Edge[stoi(parent[current])][current]; ++i)
			cout << "-";
		cout << "> \'" << current << "\' ";
	}
};

int main()
{
	Graph G(7);

	G.addEdge(0, 1);
	G.addEdge(0, 2);
	G.addEdge(2, 3, 16);
	G.addEdge(3, 3, 100);
	G.addEdge(1, 0, 3);
	G.addEdge(3, 1);
	G.addEdge(4, 5, 12);
	G.addEdge(4, 4);
	G.addEdge(1, 5);
	G.addEdge(5, 0, -23);
	G.addEdge(0, 6, 7);
	G.addEdge(6, 4);

	// 1) !!! შემოვლას (BFS-ს) საიდანაც გააკეთებ იქიდან აიღება თითოეული წვეროს მშობელი !!!
	// 2) !!! საიდანაც BFS-ი (შემოვლა) კეთდება იქიდან ვიყენებთ P_P ფუნქციასაც ყოველი წვეროსთვის, რადგან სხვა შემთხვევაში, წვერომ მშობელი არ იცის!!!
	// 3) !!! მარყუჟის წონა შეგვიძლია მივუთითოთ, მაგრამ length-ში არ აისახება ალგორითმიდან გამომდინარე !!!

	cout << "BFS from 2:\n" << endl;
	G.BFS(2);

	cout << "\nThe way from 2 to 4:\n" << endl;
	G.P_P(2, 4);

	cout << "\nBFS from 0:\n" << endl;
	G.BFS(0);
	cout << "\nThe way from 0 to 4:\n" << endl;
	G.P_P(0, 4);


	cout << "\nBFS from 6:\n" << endl;
	G.BFS(6);
	cout << "\nThe way from 6 to 5:\n" << endl;
	G.P_P(6, 5);
}
