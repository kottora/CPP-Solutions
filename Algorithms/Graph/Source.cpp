#include <iostream>
#include <list>

using namespace std;

class Graph
{
	int V;

	list<int>* adj;

public:
	Graph(int V)
	{
		this->V = V;
		adj = new list<int>[V];
	}
	void addEdge(int v, int W)
	{
		if (v < V)
		{
			adj[v].push_back(W);
		}
		else
		{
			cerr << "NO such vertex in Graph" << endl;
		}
	}
	void print() const
	{
		for (size_t i(0); i < V; ++i)
		{
			for (auto it = adj[i].begin(); it != adj[i].end(); ++it)
			{
				cout << i << " ---> " << *it << ", ";
				
			}
			if (!adj[i].empty())
			{
				cout << endl;
			}
		}
	}
};

int main()
{
	Graph G = 5;

	G.addEdge(1, 2);
	G.addEdge(1, 3);
	G.addEdge(1, 4);
	G.addEdge(3, 2);
	G.addEdge(3, 0);
	G.addEdge(7, 7);
	G.addEdge(7, 9);
	G.addEdge(0, 1);

	G.print();
}