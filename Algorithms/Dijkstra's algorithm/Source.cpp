#include <iostream>
#include <list>
#include <queue>
#include <set>

using namespace std;

# define INF 0x3f3f3f3f

typedef pair<int, int> Ipair;

class Graph
{
	int V;
	list<int>* adj;

	int* d;
	int* Parent;

	int** Edges;

public:

	Graph(int V)
	{
		this->V = V;
		adj = new list<int>[V];

		d = new int[V];
		Parent = new int[V];

		Edges = new int* [V];
		for (int i = 0; i < V; ++i)
		{
			Edges[i] = new int[V];
		}
	}

	~Graph()
	{
		delete[] adj;

		delete[] d;
		delete[] Parent;

		for (int i = 0; i < V; ++i)
		{
			delete[] Edges[i];
		}
		delete Edges;
	}

	void add_edge(char U, char V, int w)
	{
		int u = ToInt(U), v = ToInt(V);

		if ((u >= 0 && u < V) && (v >= 0 && v < V) && (w >= 0)) //  
		{
			adj[u].push_back(v);
			//adj[v].push_back(u);
			Edges[u][v] = w;
			Edges[v][u] = w;
		}
		else if (w < 0)
		{
			cout << "Edge: '" << U << "' --[" << w << "]--> '" << V << "' will not be added!\nDijkstra's algorithm does not work with negative weights!\n" << endl;
		}
		else
		{
			cout << "Invalid vertexes!" << endl;
		}
	}

	void Dijkstra(char U)
	{
		int v = ToInt(U);

		if (v >= V)
		{
			cout << "Invalid Parameter!" << endl;
			return;
		}

		priority_queue<Ipair, vector<Ipair>, greater<Ipair>> Q;
		Q.emplace(0, v);

		set<int> S;

		for (int i = 0; i < V; ++i)
		{
			d[i] = INF;
			Parent[i] = i;
		}
		d[v] = 0;

		Ipair A;
		while (!Q.empty())
		{
			A = Q.top();
			Q.pop();

			for (auto it = adj[A.second].begin(); it != adj[A.second].end(); ++it)
			{
				if ((A.first + Edges[A.second][*it] < d[*it]) && (S.find(*it) == S.end())) //  // თუ d[u] + W(u,v) < d[v] და v არ ეკუთვნის S-ს (ანუ არაა შესწავლილი)
				{
					d[*it] = A.first + Edges[A.second][*it];
					Parent[*it] = A.second;

					Q.push(make_pair(d[*it], *it));
				}
			}
			S.emplace(A.second);
		}

		
		for (int i = 0; i < V; ++i)
		{
			cout << "Vertex: '" << ToChar(i) << "'; Length from '" << U << "' = d['" << ToChar(i) << "'] = " << d[i] << "; Path:\n" << endl;
			P_P(i);
			cout << endl << endl;
		}
	}

	void P_P(int v)
	{
		if (Parent[v] == v)
		{
			cout << '\'' << ToChar(v) << "' ";
			return;
		}
		
		P_P(Parent[v]);
		for (int i = 0; i < Edges[Parent[v]][v]; ++i)
		{
			cout << "-";
		}
		cout << "> '" << ToChar(v) << "' ";
	}

	int ToInt(char a)
	{
		switch (a)
		{
		case 'a': return 0;
		case 'b': return 1;
		case 'c': return 2;
		case 'd': return 3;
		case 'e': return 4;
		case 'f': return 5;
		case 'g': return 6;
		case 'h': return 7;
		case 'i': return 8;
		default: return -100; // :)
		}
	}

	char ToChar(int a)
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
		case 7: return 'h';
		case 8: return 'i';
		default: return 'Z'; // :)
		}
	}
};

int main()
{
	Graph G(4);

	G.add_edge('a', 'b', 1);
	G.add_edge('b', 'c', 1);
	G.add_edge('a', 'd', 3);
	G.add_edge('d', 'c', -4);

	G.Dijkstra('a');
};