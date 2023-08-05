// C++ program for Kruskal's algorithm to find Minimum Spanning Tree
// of a given connected, undirected and weighted graph
// Kruskal C++ პროგრამა რომელიც მოცემული ბმული არაორიენტირებული შეწონილი გრაფისთვის
// პოულობს მინიმალურ დამფარავ ხეს კრასკალის ალგორითმით
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

// ლუკა კოტორაშვილი

using namespace std;

// Creating shortcut for an integer pair
// ქმნის სახელს რომელიც აღწერს მთელების წყვილს
typedef pair<int, int> iPair;

struct Graph
{
	int V, E;
	bool* electricity;
	list<int>* sets;
	vector < pair<int, iPair> > edges;

	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
		this->electricity = new bool[V]; // ელექტროენერგიისთვის
		sets = new list<int>[V]; // უდენო წვეროებისთვის

		for (int i = 0; i < V; ++i)
		{
			electricity[i] = false;
		}
	}
	void addEdge(int u, int v, int w)
	{
		// არაორიენტირებული გრაფია
		edges.push_back({ w,{ u - 1, v - 1} }); // გადავაკეთოთ 1,2,3,4,5,6 -> 0,1,2,3,4,5
		edges.push_back({ w,{ v - 1, u - 1} });
	}
	int Kruskal_MST();
	void Have_Electicity(int a)
	{
		electricity[a - 1] = true;
	}
};
// To represent Disjoint Sets
// სტრუქტურა, რომელიც თანაუკვეთ სიმრავლეებს წარმოადგენს
struct DisjointSets
{
	int* parent, * rnk;
	int n;
	// Constructor.
	DisjointSets(int n)
	{
		// Allocate memory
		this->n = n;
		parent = new int[n];
		rnk = new int[n];
		// Initially, all vertices are in different sets and have rank 0.
		// თავიდან ყველა წვერო არიან განსხვავებულ სიმრავლეებში და აქვთ რანგი 0
		for (int i = 0; i < n; i++)
		{
			rnk[i] = 0;
			//every element is parent of itself
			// ყველა ელემენტი არის თავისი თავის მშობელი
			parent[i] = i;
		}
	}
	// Find the parent of a node 'u' Path Compression
	// პოულობს 'u' წვეროს სიმრავლის ფესვს და აკეთებს გზის დამოკლებას
	int find(int u)
	{
		/* Make the parent of the nodes in the path from u-->parent[u] point to
		parent[u]
		- გზაზე u-დან ფესვამდე ყველა წვეროს მშობელი იქნება ფესვი */
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];
	}
	// Union by rank გაერთიანება რანგის მიხედვით
	void Union(int x, int y)
	{
		/* Make tree with smaller height a subtree of the other tree
		- ხე, რომლის სიმაღლეც უფრო ნაკლებია გავხადოთ მეორე ხის ქვეხე */
		if (rnk[x] > rnk[y])
			parent[y] = x;
		else // If rnk[x] <= rnk[y]
			parent[x] = y;
		if (rnk[x] == rnk[y])
			rnk[y]++;
	}
};
/* Functions returns weight of the MST
ფუნქცია აბრუნებს მინიმალური დამფარავი ხის წონას */
int Graph::Kruskal_MST()
{
	int mst_wt = 0; // Initialize result
	// Sort edges in increasing order on basis of cost
	sort(edges.begin(), edges.end());
	// Create disjoint sets
	DisjointSets ds(V);
	// Iterate through all sorted edges
	vector< pair<int, iPair> >::iterator it;
	for (it = edges.begin(); it != edges.end(); it++)
	{
		int u = it->second.first;
		int v = it->second.second;
		int set_u = ds.find(u);
		int set_v = ds.find(v);

		if (set_u != set_v)
		{
			if (electricity[u] && electricity[v])
			{
				// თუ ორივე ქალაქს გააჩნია ელექტროენერგია მაშინ ისინი უბრალოდ გავაერთიანოთ
				// Merge two sets შევაერთოთ ორი სიმრავლე
				ds.Union(set_u, set_v);
				
			}
			else if (!electricity[u] && electricity[v])
			{
				cout << u + 1 << " - " << v + 1 << endl;

				// Update MST weight განვაახლოთ მინიმალური დამფარავი ხის წონა
				mst_wt += it->first;

				electricity[u] = true;	// ყოველი ელექტრო ენერგიის არ მქონე და მასთან დაკავშირებული სხვა მსგავს ქალაქებს გაუჩნდებათ ელექტროენერგია
				for (auto it1 = sets[u].begin(); it1 != sets[u].end(); ++it1)
				{
					electricity[*it1] = true;
				}

				// Merge two sets შევაერთოთ ორი სიმრავლე
				ds.Union(set_u, set_v);
			}
			else if (electricity[u] && !electricity[v])
			{
				cout << u + 1 << " - " << v + 1 << endl;

				// Update MST weight განვაახლოთ მინიმალური დამფარავი ხის წონა
				mst_wt += it->first;

				electricity[v] = true;	// ყოველი ელექტრო ენერგიის არ მქონე და მასთან დაკავშირებული სხვა მსგავს ქალაქებს გაუჩნდებათ ელექტროენერგია
				for (auto it1 = sets[v].begin(); it1 != sets[v].end(); ++it1)
				{
					electricity[*it1] = true;
				}

				// Merge two sets შევაერთოთ ორი სიმრავლე
				ds.Union(set_u, set_v);
			}
			else
			{
				// Check if the selected edge is creating a cycle or not
				// (Cycle is created if u and v belong to same set)
				// ვამოწმებთ ქმნის თუ არა ამორჩეული წიბო ციკლს
				// (ციკლია თუ u და v ეკუთვნიან ერთი და იგივე ხეს)
				
				// Current edge will be in the MST so print it
				// განხილული წიბო იქნება მინიმალური დამფარავი ხის წიბო, ამიტომ დავბეჭდოთ
				cout << u + 1 << " - " << v + 1 << endl;

				// Update MST weight განვაახლოთ მინიმალური დამფარავი ხის წონა
				mst_wt += it->first;

				// თუ თავიდან დაიწყო ისეთი ქალაქების შეერთება რომლებშიც არაა ელექტროენერგია მაშინ თითოეულისთვის შევქმნათ სიმრავლეები

				// პირველი წვეროს სიმრავლეში შევიყვანოთ მეორე წვერო და მისი მეზობლები, ამავდროულად მეზობლების სიმრავლეებშიც უნდა შევიყვანოთ ეს წვერო
				sets[u].push_back(v);
				for (auto it = sets[v].begin(); it != sets[v].end(); ++it)
				{
					if (*it != u)
					{
						sets[u].push_back(*it);
						sets[*it].push_back(u);
					}
				}

				// მეორე წვეროს სიმრავლეში შევიყვანოთ პირველი წვერო და მისი მეზობლები, ამავდროულად მეზობლების სიმრავლეებშიც უნდა შევიყვანოთ ეს წვერო
				sets[v].push_back(u);
				for (auto it = sets[u].begin(); it != sets[u].end(); ++it)
				{
					if (*it != v)
					{
						sets[v].push_back(*it);
						sets[*it].push_back(v);
					}
				}

				// Merge two sets შევაერთოთ ორი სიმრავლე
				ds.Union(set_u, set_v);
			}
		}
	}
	return mst_wt;
}
int main()
{
	int V = 6, E = 15; // E = V * (V-1) / 2
	Graph g(V, E);

	// adding edges - წიბოების დამატება
	g.addEdge(1, 2, 7);
	g.addEdge(1, 3, 5);
	g.addEdge(1, 4, 3);
	g.addEdge(1, 5, 1);
	g.addEdge(1, 6, 8);

	g.addEdge(2, 3, 2);
	g.addEdge(2, 4, 4);
	g.addEdge(2, 5, 6);
	g.addEdge(2, 6, 2);

	g.addEdge(3, 4, 3);
	g.addEdge(3, 5, 3);
	g.addEdge(3, 6, 1);

	g.addEdge(4, 5, 4);
	g.addEdge(4, 6, 5);

	g.addEdge(5, 6, 4);

	g.Have_Electicity(2);
	g.Have_Electicity(3);
	g.Have_Electicity(5);

	cout << "Electricity Cables between the cities:\n";
	int mst_wt = g.Kruskal_MST();
	cout << "\nMoney for the cables: " << mst_wt << " million Laris" << endl;
}