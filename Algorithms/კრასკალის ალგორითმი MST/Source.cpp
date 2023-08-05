// C++ program for Kruskal's algorithm to find Minimum Spanning Tree
// of a given connected, undirected and weighted graph
// Kruskal C++ პროგრამა რომელიც მოცემული ბმული არაორიენტირებული შეწონილი გრაფისთვის
// პოულობს მინიმალურ დამფარავ ხეს კრასკალის ალგორითმით
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
// Creating shortcut for an integer pair
// ქმნის სახელს რომელიც აღწერს მთელების წყვილს
typedef pair<int, int> iPair;
struct Graph
{
	int V, E;
	vector < pair<int, iPair> > edges;
	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
	}
	void addEdge(int u, int v, int w)
	{
		edges.push_back({ w,{ u, v } });
		edges.push_back({ w,{ v, u } });
	}
	int Kruskal_MST();
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
		// Check if the selected edge is creating a cycle or not
		// (Cycle is created if u and v belong to same set)
		// ვამოწმებთ ქმნის თუ არა ამორჩეული წიბო ციკლს
		// (ციკლია თუ u და v ეკუთვნიან ერთი და იგივე ხეს)
		if (set_u != set_v)
		{
			// Current edge will be in the MST so print it
			// განხილული წიბო იქნება მინიმალური დამფარავი ხის წიბო, ამიტომ დავბეჭდოთ
			cout << u << " - " << v << endl;

			// Update MST weight განვაახლოთ მინიმალური დამფარავი ხის წონა
			mst_wt += it->first;

			// Merge two sets შევაერთოთ ორი სიმრავლე
			ds.Union(set_u, set_v);
		}
	}
	return mst_wt;
}
int main()
{
	int V = 9, E = 14;
	Graph g(V, E);
	// adding edges - წიბოების დამატება
	g.addEdge(0, 1, 4);
	g.addEdge(0, 7, 8);
	g.addEdge(1, 2, 8);
	g.addEdge(1, 7, 11);
	g.addEdge(2, 3, 7);
	g.addEdge(2, 8, 2);
	g.addEdge(2, 5, 4);
	g.addEdge(3, 4, 9);
	g.addEdge(3, 5, 14);
	g.addEdge(4, 5, 10);
	g.addEdge(5, 6, 2);
	g.addEdge(6, 7, 1);
	g.addEdge(6, 8, 6);
	g.addEdge(7, 8, 7);
	cout << "Edges of MST are:\n";
	int mst_wt = g.Kruskal_MST();
	cout << "\nWeight of MST is: " << mst_wt << endl;
}