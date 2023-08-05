#include<iostream>
#include<list>

using namespace std;

class Graph {
	int V;

	int time;
	int* d;
	int* f;
	list<int>* adj;
	int* visited;

public:

	Graph(int V);
	~Graph();
	void addEdge(int x, int y);
	void dfsviz(int v);
	void DFS(int);
	Graph* createG_T();
	bool colored(Graph&);
};

Graph::Graph(int V) {
	this->V = V;
	visited = new int[V];
	d = new int[V];
	f = new int[V];
	adj = new list<int>[V];
	time = 0;
}

Graph::~Graph()
{
	delete[] visited;
	delete[] d;
	delete[] f;
	delete[] adj;
}

void Graph::addEdge(int x, int y) 
{
	adj[x].push_back(y);
}

void Graph::dfsviz(int v)
{
	visited[v] = 1;
	time++;
	d[v] = time;
	for (auto i = adj[v].begin(); i != adj[v].end(); i++) {
		if (visited[*i] == 0) {
			dfsviz(*i);
		}
	}
	visited[v] = 1;
	time++;
	f[v] = time;
}

void Graph::DFS(int v) 
{
	for (int i = 0; i < V; i++)
	{
		visited[i] = 0;
		d[i] = -1;
		f[i] = -1;
	}
		
	time = 0;

	dfsviz(v);

	for (int i = 0; i < V; i++) {
		cout << " " << i << " wvero ";
		cout << " d[" << i << "]=" << d[i] << " f[" << i << "]=" << f[i] << " " << endl;
	}
	cout << endl;
}

Graph* Graph::createG_T()
{
	Graph* g_T = new Graph(V);
	for (int i = 0; i < V; ++i)
	{
		for (auto j = adj[i].begin(); j != adj[i].end(); ++j)
		{
			g_T->addEdge(*j, i);
		}
	}
	return g_T;
}

bool Graph::colored(Graph& A)
{
	DFS(1);
	for (int i = 0; i < V; ++i)
	{
		if (visited[i] == 0)
			return false;
	}
	A.DFS(1);
	for (int i = 0; i < V; ++i)
	{
		if (A.visited[i] == 0)
			return false;
	}

	return true;
}

int main() 
{
	Graph g(6);

	g.addEdge(1, 0);
	g.addEdge(0, 2); 
	g.addEdge(2, 3);
	g.addEdge(3, 4);
	g.addEdge(4, 5);
	//g.addEdge(5, 1);

	// creating transposed graph
	Graph* G_T = g.createG_T();
	if (g.colored(*G_T))
	{
		cout << "\nGraph can be colored in 2 colors" << endl;
	}
	else
	{
		cout << "\nGraph can NOT be colored in 2 colors" << endl;
	}
	delete G_T;
}
