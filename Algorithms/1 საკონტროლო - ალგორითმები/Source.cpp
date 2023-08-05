#include <iostream>
#include <list>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

class Graph
{
	int Time; // დრო რომელიც მუდამ იზრდება

	int V; // წვეროთა მაქსიმალური რაოდენობა
	list<int>* adj; // სია წიბოებისთვის
	int* color; // ფერი
	int* d; // მონახულების მომენტი
	int* f; // შესწავლის დასრულების მომენტი

public:

	vector<pair<int, int>> key_F;
	vector<pair<int, int>> key_D;

	Graph(int V)
	{
		Time = 0;

		this->V = V;
		this->adj = new list<int>[V];
		this->color = new int[V];
		this->d = new int[V];
		this->f = new int[V];

		for (int i(0); i < V; ++i)
		{
			color[i] = 0; // თავიდან ყველა თეთრია
			d[i] = 0;
			f[i] = 0;
		}
	}

	~Graph()
	{
		// წავშალოთ heap-ში გამოყოფილი მეხსიერება
		delete[] adj;
		delete[] color;
		delete[] d;
		delete[] f;
	}

	void addEdge(int v, int u)
	{
		if (v >= 0 && v < V)
		{
			adj[v].push_back(u);
		}
		else
		{
			cout << "We cant create Edge (" << v << ", " << u << ')' << endl;
		}
	}

	void DFS()
	{
		// ყოველი წვეროსთვის
		for (int i(0); i < V; ++i)
		{
			DFS(i);
		}
	}

	void DFS(int v)
	{
		if (color[v] == 0)
		{
			DFSvisit(v);
			cout << endl;
		}
		cout << "Vertex: \'" << v << "\'    Color: " << Color(color[v])
			<< "    d[" << v << "] = " << d[v] << "    f[" << v << "] = " << f[v] << '\n' << endl;
	}

	void DFSvisit(int v)
	{
		// წვეროს მონახულება
		++Time;
		d[v] = Time;
		key_D.push_back(make_pair(v, d[v])); // !!! ამის დასორტვა აღარ გვიწევს რადგან ისედაც ზრდადობით ჩაიწერება
		color[v] = 1;
		//---------------------

		// წვეროს შესწავლა მეზობლებითა და მათი შთამომავლებითურთ
		for (auto it = adj[v].begin(); it != adj[v].end(); ++it)
		{
			if (color[*it] == 0)
			{
				DFSvisit(*it); // რეკურსია (დინამიური დაპროგრამება)
			}
		}
		//----------------------------------------------------------------

		// წვეროს შესწავლის დასრულება
		++Time;
		color[v] = 2;
		f[v] = Time;
		key_F.push_back(make_pair(v, f[v]));
		//--------------------------
	}

	string Color(int x)
	{
		switch (x)
		{
		case 0: return "White";
		case 1: return "Gray";
		case 2: return "Black";
		}

		return "Red :)";
	}

	// პირობა 2)

	Graph* G_T()
	{
		Graph* result = new Graph(this->V);

		for (int i(0); i < this->V; ++i)
		{
			for (auto it = adj[i].begin(); it != adj[i].end(); ++it)
			{
				result->addEdge(*it, i);
			}
		}

		return result;
	}


	// პირობა 4)

	bool Trees()
	{
		for (int i = 0; i < V; ++i)
		{
			color[i] = 0;
		}

		DFSVVisit(this->key_D[0].first); // d[u] ისედაც ზრდადობით არის დალაგებული

		for (int i = 0; i < V; ++i)
		{
			if (color[i] == 0)
				return false;
		}

		return true;
	}

	void DFSVVisit(int v)
	{
		// წვეროს მონახულება
		color[v] = 1;
		//---------------------

		// წვეროს შესწავლა მეზობლებითა და მათი შთამომავლებითურთ
		for (auto it = adj[v].begin(); it != adj[v].end(); ++it)
		{
			if (color[*it] == 0)
			{
				DFSVVisit(*it); // რეკურსია (დინამიური დაპროგრამება)
			}
		}
		//----------------------------------------------------------------

		// წვეროს შესწავლის დასრულება
		color[v] = 2;
		//--------------------------
	}
};

bool decrease(pair<int, int>&, pair<int, int>&);

int main()
{
	Graph Luka(7);

	Luka.addEdge(0, 5);
	Luka.addEdge(5, 4);
	Luka.addEdge(4, 3);
	Luka.addEdge(3, 6);
	Luka.addEdge(6, 1);
	Luka.addEdge(1, 2);
	Luka.addEdge(2, 0);
	Luka.addEdge(3, 6);
	Luka.addEdge(4, 5);
	Luka.addEdge(4, 1);
	Luka.addEdge(5, 1);
	Luka.addEdge(6, 2);

	Luka.DFS();

	// G_T გრაფის შექმნა
	Graph* Luka_T = Luka.G_T();

	// DFS(G_T) G-ის f[u]-ის კლებადობით
	sort(Luka.key_F.begin(), Luka.key_F.end(), decrease);

	for (int i = 0; i < Luka.key_F.size(); ++i)
	{
		Luka_T->DFS(Luka.key_F[i].first);
	}

	// მიღებული ხეები გვაძლევს ძლიერად ბმულ კომპონენტებს
	//sort(Luka.key_D.begin(), Luka.key_D.end(), encrease);
	if (Luka_T->Trees())
	{
		cout << "Grafi aris dzlierad bmuli" << endl;
	}
	else
	{
		cout << "Grafi ar aris dzlierad bmuli, mas gaachnia dzlierad bmuli komponentebi" << endl;
	}
	

	//
	delete Luka_T;
}

bool decrease(pair<int,int>& A, pair<int,int>& B)
{
	return A.second > B.second;
}