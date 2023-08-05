#include <iostream>
#include <list>

using namespace std;

#define INF 0x3f3f3f3f

class Graph
{
	int V;
	list<int>* adj;
	int* d;
	int* Parent;
	int** Edges;

	bool Bellman_Ford(int v)
	{
		for (int i = 0; i < V; ++i)
		{
			Parent[i] = i;
			d[i] = INF;
		}
		d[v] = 0;

		for (int i = 1; i < V; ++i) // ყველა წვეროს რელაქსაცია მოვახდინოთ (V-1)-ჯერ რადგან ხეში V-1 წიბო გვაქვს
		{
			for (int j = 0; j < V; ++j)
			{
				for (auto it = adj[j].begin(); it != adj[j].end(); ++it)
				{
					RELAX(j, *it);
				}
			}
		}

		// რელაქსაცია მოვახდინოთ ბოლოჯერ და თუ რამე შეიცვალა ესეიგი უარყოფითი ციკლი გვაქვს ანუ არ არსებობს უმცირესი გზა
		for (int j = 0; j < V; ++j)
		{
			for (auto it = adj[j].begin(); it != adj[j].end(); ++it)
			{
				if (d[j] + Edges[j][*it] < d[*it])
				{
					return false;
				}
			}
		}

		return true;
	}

	void RELAX(int u, int v)
	{
		if (d[u] + Edges[u][v] < d[v])
		{
			d[v] = d[u] + Edges[u][v];
			Parent[v] = u;
		}
	}

public:

	Graph(int V)
	{
		this->V = V;
		adj = new list<int>[V];
		d = new int[V];
		Parent = new int[V];
		Edges = new int* [V];
		for (int i(0); i < V; ++i)
		{
			Edges[i] = new int[V];
		}
	}

	~Graph()
	{
		delete[] adj;
		delete[] d;
		delete[] Parent;
		for (int i(0); i < V; ++i)
		{
			delete[] Edges[i];
		}
		delete[] Edges;
	}

	void add_edge(char U, char V, int w)
	{
		int u = ToInt(U), v = ToInt(V);

		if ((u >= 0 && u < V) && (v >= 0 && v < V))
		{
			adj[u].push_back(v);
			Edges[u][v] = w;
		}
		else
		{
			cout << "Invalid Vertexes!" << endl;
		}
	}

	void Bellman_Ford_result(char U)
	{
		int v = ToInt(U);

		if (Bellman_Ford(v))
		{
			for (int i = 0; i < V; ++i)
			{
				cout << "Vertex: '" << ToChar(i) << "'; Length from '" << U << "' = d['" << ToChar(i) << "'] = " << d[i] << "; Path:\n" << endl;
				P_P(i, v);
				cout << endl << endl;
			}
		}
		else
		{
			cout << "There is a negative cycle in the Graph, we can't find shortest path from '" << v << "' to any other vertex" << endl;
		}
	}

	void P_P(int v, int s)
	{
		if (Parent[v] == v && v != s)
		{
			// აქ რეკურსია არ იქნება, რადგან ან ეყოლება მშობელი, ან საერთოდ არა!
			cout << "There is no way from 'start' to '" << ToChar(v) << "'" << endl;
			return;

		}
		else if (Parent[v] == v)
		{
			cout << '\'' << ToChar(v) << "' ";
			return;
		}
		else
		{
			P_P(Parent[v], s);
			for (int i = 0; i < abs(Edges[Parent[v]][v]); ++i)
			{
				if (Edges[Parent[v]][v] > 0)
					cout << "-";
				else
					cout << "~";
			}
			cout << " '" << ToChar(v) << "' ";
		}
	}

	int ToInt(char a)
	{
		if(a >= 97 && a < 123)
			return a - 97;

		return -100; // :)
	}

	char ToChar(int a)
	{
		if (a >= 0 && a < 27)
			return a + 97;

		return 'Z'; // :)
	}
};

int main()
{
	Graph G(4);

	G.add_edge('a', 'b', 1);
	G.add_edge('b', 'c', 1);
	G.add_edge('a', 'd', 3);
	G.add_edge('d', 'c', -100);

	G.Bellman_Ford_result('a');
}