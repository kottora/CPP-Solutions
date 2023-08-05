#include <iostream>
#include <list>
#include <queue>
#include <set>
#include <algorithm>

using namespace std;

# define INF 0x3f3f3f3f

typedef pair<int, int> Ipair;

class Graph
{
	int V;
	list<int>* adj;

	int* d;
	int* Parent;
	int* Child;

	int** Edges;

	list<Ipair> Q;
	set<int> S;
	set<int> P;
	set<int> T;

public:

	Graph(int V)
	{
		this->V = V;
		adj = new list<int>[V];

		d = new int[V];
		Parent = new int[V];
		Child = new int[V];

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
		delete[] Child;

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
			Edges[u][v] = w;
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

	void Sort(list<Ipair>& A)
	{
		vector<Ipair> vec;
		for (auto it = A.begin(); it != A.end(); ++it)
		{
			vec.push_back(*it);
		}
		sort(vec.begin(), vec.end(), [](Ipair a, Ipair b) { return a.first < b.first; });
		A.clear();
		for (int i = 0; i < vec.size(); ++i)
		{
			A.push_back(vec[i]);
		}
	}

	bool ThereIs_b(int x)
	{
		if (ToChar(x) == 'b')
		{
			return true;
		}
		else if (Parent[x] == x)
		{
			return false;
		}
		return ThereIs_b(Parent[x]);
	}

	void ClearChildren(int x)
	{
		if (Child[x] == x)
		{
			Parent[x] = x;
			d[x] = INF;
			for (auto it = Q.begin(); it != Q.end(); ++it)
			{
				if (it->second == x)
				{
					Q.erase(it);
					break;
				}
			}
			Q.push_back({ d[x], x });
			return;
		}

		ClearChildren(Child[x]);

		Parent[x] = x;
		d[x] = INF;
		Child[x] = x;
		for (auto it = Q.begin(); it != Q.end(); ++it)
		{
			if (it->second == x)
			{
				Q.erase(it);
				break;
			}
		}
		Q.push_back({ d[x], x });
	}

	void findroadto_(int x)
	{
		if (Parent[x] == x)
		{
			return;
		}

		findroadto_(Parent[x]);

		T.emplace(x);
	}

	void allroadsleadto_b(char U)
	{
		for (int i = 0; i < V; ++i)
		{
			d[i] = INF;
			Parent[i] = i;
			Child[i] = i;
		}
		d[ToInt(U)] = 0;

		Dijkstra_b('b');
		S.clear();

		for (int i = 0; i < V; ++i)
		{
			d[i] = INF;
			Parent[i] = i;
			Child[i] = i;
		}
		d[ToInt(U)] = 0;

		DijkstraFor_b(U);
		S.clear();

		for (int i = 0; i < V; ++i)
		{
			if (ToChar(i) == 'b')
				continue;
			d[i] = INF;
			Parent[i] = i;
			Child[i] = i;
		}
		Dijkstra(U);
	}

	void Dijkstra_b(char U)
	{
		int v = ToInt(U);

		if (v >= V)
		{
			cout << "Invalid Parameter!" << endl;
			return;
		}

		Q.push_back({ 0, v });

		Ipair A;
		while (!Q.empty())
		{
			Sort(Q);
			A = Q.front();
			Q.pop_front();

			for (auto it = adj[A.second].begin(); it != adj[A.second].end(); ++it)
			{
				if ((A.first + Edges[A.second][*it] < d[*it]) && (S.find(*it) == S.end())) // თუ d[u] + W(u,v) < d[v] და v არ ეკუთვნის S-ს (ანუ არაა შესწავლილი)
				{
					d[*it] = A.first + Edges[A.second][*it];
					Parent[*it] = A.second;
					Child[A.second] = *it;

					Q.push_back(make_pair(d[*it], *it));
				}
			}
			S.emplace(A.second);
		}

		findroadto_(ToInt('b'));
	}

	void DijkstraFor_b(char U)
	{
		int v = ToInt(U);

		if (v >= V)
		{
			cout << "Invalid Parameter!" << endl;
			return;
		}

		Q.push_back({ 0, v });

		Ipair A;
		while (!Q.empty())
		{
			Sort(Q);
			A = Q.front();
			Q.pop_front();

			for (auto it = adj[A.second].begin(); it != adj[A.second].end(); ++it)
			{
				if ((A.first + Edges[A.second][*it] < d[*it]) && (S.find(*it) == S.end())) // თუ d[u] + W(u,v) < d[v] და v არ ეკუთვნის S-ს (ანუ არაა შესწავლილი)
				{
					d[*it] = A.first + Edges[A.second][*it];
					Parent[*it] = A.second;
					Child[A.second] = *it;

					Q.push_back(make_pair(d[*it], *it));
				}
			}
			S.emplace(A.second);
		}

		for (int i = 0; i < V; ++i)
		{
			if (ThereIs_b(i))
			{
				cout << "Vertex: '" << ToChar(i) << "'; Length from '" << U << "' = d['" << ToChar(i) << "'] = " << d[i] << "; Path:\n" << endl;
				P_P(i);
				cout << endl << endl;
				P.emplace(i);
			}
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

		Q.push_back({ 0, v });
		Q.push_back({ d[ToInt('b')], ToInt('b') });

		int counter_road_to_b = 0;
		int round = 1;

		Ipair A;
		while (!Q.empty())
		{
			Sort(Q);
			A = Q.front();
			
			for (auto it = adj[A.second].begin(); it != adj[A.second].end(); ++it)
			{
				if (A.second == ToInt('b'))
				{
					counter_road_to_b++;
					if (counter_road_to_b >= V)
					{
						break;
					}
					if (T.find(*it) != T.end())
					{
						if(round == 1)
							continue;
						else
						{
							if ((A.first + Edges[A.second][*it] < d[*it]) && (S.find(*it) == S.end())) // თუ d[u] + W(u,v) < d[v] და v არ ეკუთვნის S-ს (ანუ არაა შესწავლილი)
							{
								d[*it] = A.first + Edges[A.second][*it];
								Parent[*it] = A.second;
								Child[A.second] = *it;

								int exist = 0;
								for (auto it1 = Q.begin(); it1 != Q.end(); ++it1)
								{
									if (it1->second == *it)
									{
										++exist;
									}
								}
								if (exist == 0)
								{
									Q.push_back(make_pair(d[*it], *it));
								}
							}
						}
					}
					else
					{
						if ((A.first + Edges[A.second][*it] < d[*it]) && (S.find(*it) == S.end())) // თუ d[u] + W(u,v) < d[v] და v არ ეკუთვნის S-ს (ანუ არაა შესწავლილი)
						{
							d[*it] = A.first + Edges[A.second][*it];
							Parent[*it] = A.second;
							Child[A.second] = *it;
							
							int exist = 0;
							for (auto it1 = Q.begin(); it1 != Q.end(); ++it1)
							{
								if (it1->second == *it)
								{
									++exist;
								}
							}
							if (exist == 0)
							{
								Q.push_back(make_pair(d[*it], *it));
							}
						}
					}
					
				}
				else
				{
					if ((A.first + Edges[A.second][*it] < d[*it]) && (S.find(*it) == S.end())) // თუ d[u] + W(u,v) < d[v] და v არ ეკუთვნის S-ს (ანუ არაა შესწავლილი)
					{
						d[*it] = A.first + Edges[A.second][*it];
						Parent[*it] = A.second;
						Child[A.second] = *it;

						Q.push_back(make_pair(d[*it], *it));
					}
				}
			}
			if (A.second == ToInt('b') && counter_road_to_b >= V)
			{
				d[ToInt('b')] = 11; // rigit shemdegi
				counter_road_to_b = 0;
				round++;
				if (round > 2)
				{
					Q.pop_front();
				}
			}
			else if (A.second == ToInt('b'))
			{
				continue;
			}
			else
			{
				if (ThereIs_b(A.second) || A.second == ToInt('e'))
				{
					S.emplace(A.second);
					Q.pop_front();
				}
				else
				{
					ClearChildren(A.second);
				}
			}
		}


		for (int i = 0; i < V; ++i)
		{
			if (P.find(i) == P.end())
			{
				cout << "Vertex: '" << ToChar(i) << "'; Length from '" << U << "' = d['" << ToChar(i) << "'] = " << d[i] << "; Path:\n" << endl;
				P_P(i);
				cout << endl << endl;
			}
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
	Graph G(5);

	G.add_edge('a', 'b', 3);
	G.add_edge('b', 'c', 1);
	G.add_edge('b', 'd', 2);
	G.add_edge('d', 'a', 1);
	G.add_edge('e', 'b', 11);
	G.add_edge('e', 'c', 4);
	G.add_edge('e', 'd', 3);

	G.allroadsleadto_b('e');
};