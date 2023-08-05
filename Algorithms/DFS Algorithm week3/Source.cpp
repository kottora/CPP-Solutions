#include <iostream>
#include <list>
#include <string>

using namespace std;

int Back = 0, Tree = 0, CrossORdirecT = 0; // სხვადასხვა სახის წიბოები

class Graph
{
	static int Time; // დრო რომელიც მუდამ იზრდება

	int V; // წვეროთა მაქსიმალური რაოდენობა
	list<int>* adj; // სია წიბოებისთვის
	int* color; // ფერი
	int* d; // მონახულების მომენტი
	int* f; // შესწავლის დასრულების მომენტი

public:

	Graph(int V)
	{
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
			// თუ წვერო თეთრია მაშინ მოვინახულოთ
			if (color[i] == 0)
			{
				DFSvisit(i);
				cout << endl;
			}
			cout << "Vertex: \'" << i << "\'    Color: " << Color(color[i])
				<< "    d[" << i << "] = " << d[i] << "    f[" << i << "] = " << f[i] << '\n' << endl;
		}
	}

	void DFSvisit(int v)
	{
		// წვეროს მონახულება
		++Time;
		d[v] = Time;
		color[v] = 1;
		//---------------------

		// წვეროს შესწავლა მეზობლებითა და მათი შთამომავლებითურთ
		for (auto it = adj[v].begin(); it != adj[v].end(); ++it)
		{
			if (color[*it] == 0)
			{
				++Tree;
				cout << "Tree Edge: " << v << " --> " << *it << endl;
				DFSvisit(*it); // რეკურსია (დინამიური დაპროგრამება)
			}
			else if (color[*it] == 1)
			{
				++Back;
				cout << "Back Edge: " << v << " --> " << *it << endl;
			}
			else if (color[*it] == 2)
			{
				++CrossORdirecT;
				cout<< "Cross or Direct Edge: " << v << " --> " << *it << endl;
			}
		}
		//----------------------------------------------------------------

		// წვეროს შესწავლის დასრულება
		++Time;
		color[v] = 2;
		f[v] = Time;
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
};

int Graph::Time = 0;

int main()
{
	Graph Luka(7);
	
	Luka.addEdge(0, 5);
	Luka.addEdge(1, 4);
	Luka.addEdge(1, 3);
	Luka.addEdge(2, 6);
	Luka.addEdge(3, 4);
	Luka.addEdge(3, 6);
	Luka.addEdge(4, 5);
	Luka.addEdge(4, 1);
	Luka.addEdge(5, 1);
	Luka.addEdge(6, 2);

	Luka.DFS();

	if (Back > 0)
	{
		cout << "We have " << Back << " Back Edges in Graph!" << endl
			<< "This Oriented Graph is Cyclic!\n" << endl;
	}
	else
	{
		cout << "This Oriented Graph has not any Back Edge, so there is no Cycle in it!\n" << endl;
	}

	if (Tree > 0)
	{
		cout << "We have " << Tree << " Tree Edges in Graph!\n" << endl;
	}
	else
	{
		cout << "This Oriented Graph has not any Tree Edges\n" << endl;
	}

	if (Back > 0)
	{
		cout << "We have " << CrossORdirecT << " (Cross + Direct) Edges in Graph!\n" << endl;
	}
	else
	{
		cout << "This Oriented Graph has not any Cross or Direct Edges!\n" << endl;
	}
}