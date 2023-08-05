// C++ program for Kruskal's algorithm to find Minimum Spanning Tree
// of a given connected, undirected and weighted graph
// Kruskal C++ პროგრამა რომელიც მოცემული ბმული არაორიენტირებული შეწონილი გრაფისთვის
// პოულობს მინიმალურ დამფარავ ხეს კრასკალის ალგორითმით
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>

using namespace std;

// Creating shortcut for an integer pair
// ქმნის სახელს რომელიც აღწერს მთელების წყვილს
typedef pair<int, int> iPair;

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

	~DisjointSets()
	{
		delete[] parent;
		delete[] rnk;
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

struct Graph
{
	int V, E;
	bool* visited;
	list<int>* adj; // გრაფის წარმოდგენა მეზობელი წვეროების სიმრავლით

	vector < pair<int, iPair> > edges; // წიბოების სიმრავლე (ორი წვერო და ამ წვეროებს შორის არსებული წიბოს წონა)

	int Tree_Weight; // ხის წონა

	// უმცირესი დამფარავი ხის წონას შეესაბამება თვითონ ხე, რომელიც არის ასევე წიბოს წონისა და წვეროების შესაბამისობათა ერთობლიობა ვექტორის სახით წარმოდგენილი
	vector< pair<int, vector<pair<int, iPair>>> > Treesets;

	vector< pair<int, iPair> > Tree; // ხე არის წიბოს წონათა და წვეროთა შესაბამისობა

	Graph(int V, int E)
	{
		this->V = V;
		this->E = E;
		visited = new bool[V];
		adj = new list<int>[V];
		Tree_Weight = -1;
	}

	Graph(const Graph& other)
	{
		this->V = other.V;
		this->E = other.E;
		visited = new bool[V];
		adj = new list<int>[V];
		for (int i = 0; i < V; ++i)
		{
			this->visited[i] = other.visited[i];
			for(auto it = other.adj[i].begin(); it != other.adj[i].end(); ++it)
				this->adj[i].push_back(*it);
		}

		for (int i = 0; i < other.edges.size(); ++i)
		{
			this->edges.push_back(other.edges[i]);
		}

		Tree_Weight = other.Tree_Weight;
	}

	~Graph()
	{
		delete[] visited;
		delete[] adj;
	}

	void addEdge(char u, char v, int w)
	{
		adj[toInt(u)].push_back(toInt(v)); // BFS-სთვის
		adj[toInt(v)].push_back(toInt(u));

		edges.push_back({ w,{ toInt(u), toInt(v) } });
	}

	void removeEdge(pair<int,iPair> edg)
	{
		// წავშალოთ (u,v) adj სიაში
		list<int>::iterator findIter = find(adj[edg.second.first].begin(), adj[edg.second.first].end(), edg.second.second);
		adj[edg.second.first].erase(findIter);

		// ასევე წავშალოთ (v,u) adj სიაში
		findIter = find(adj[edg.second.second].begin(), adj[edg.second.second].end(), edg.second.first);
		adj[edg.second.second].erase(findIter);

		// ასევე წავშალოთ (u,v) იგივე (v,u) წიბო edges ვექტორიდან
		vector<pair<int, iPair>>::iterator erit, it;

		for (it = edges.begin(); it != edges.end(); ++it)
		{
			if (it->second.first == edg.second.first && it->second.second == edg.second.second)
			{
				erit = it;
				break;
			}
		}
		if (it == edges.end()) // თუ ვერ ვიპოვეთ მსგავსი წიბო ვერ წავშლით მაგრამ ეს შეუძლებელია რადგან MST-ის წიბოებს ვიხილავთ
		{
			cout << "Can't remove Edge" << endl;
		}
		else
		{
			edges.erase(erit);
		}
	}

	char tochar(int a)
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
		case 9: return 'j';
		case 10: return 'k';
		default: return 'Z'; // :)
		}
	}

	int toInt(char a)
	{
		switch (a)
		{
		case 'a': return 0;
		case 'b': return 1;;
		case 'c': return 2;
		case 'd': return 3;
		case 'e': return 4;
		case 'f': return 5;
		case 'g': return 6;
		case 'h': return 7;
		case 'i': return 8;
		case 'j': return 9;
		case 'k': return 10;
		default: return -1; // :)
		}
	}

	void Kruskal_MST();

	bool BFS();

	void NextMST();
};

/* Functions returns weight of the MST
ფუნქცია აბრუნებს მინიმალური დამფარავი ხის წონას */
void Graph::Kruskal_MST()
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
			// Update MST weight განვაახლოთ მინიმალური დამფარავი ხის წონა
			mst_wt += it->first;

			// Merge two sets შევაერთოთ ორი სიმრავლე
			ds.Union(set_u, set_v);

			// ხეში ვამატებთ მოცემული გრაფის უმცირესი დამფარავი ხის წიბოებს
			Tree.push_back({ it->first,{it->second.first, it->second.second} });
		}
	}
	// ვანიჭებთ მნიშვნელობას უმცირესი დამფარავი ხის წონას
	Tree_Weight = mst_wt;
}

bool Graph::BFS()
{
	int s = 0;

	for (int i = 0; i < V; ++i)
	{
		visited[i] = false;
	}

	list<int> queue;

	visited[s] = true;
	queue.push_back(s);

	list<int>::iterator i;

	while (!queue.empty())
	{
		s = queue.front();
		queue.pop_front();

		for (i = adj[s].begin(); i != adj[s].end(); ++i)
		{
			if (!visited[*i])
			{
				visited[*i] = true;
				queue.push_back(*i);
			}
		}
	}

	// თუ საწყისი წვეროდან (default-ად 0-დან) ყველა წვერომდე მივიდა(არაორიენტირებული გრაფია) BFS მაშინ ვაბრუნებთ true-ს, ისე კი false-ს
	for (int i = 0; i < V; ++i)
	{
		if (!visited[i])
			return false;
	}
	return true;
}

void Graph::NextMST()
{
	// ვიპოვოთ უმცირესი დამფარავი ხე ჩვენი გრაფისთვის
	this->Kruskal_MST();

	cout << "1_Level_MST with weight = " << this->Tree_Weight << '\n' << endl;
	for (int i = 0; i < Tree.size(); ++i)
	{
		cout << '\'' << tochar(Tree[i].second.first) << "\' -- " << Tree[i].first
			<< " -- \'" << tochar(Tree[i].second.second) << '\'' << endl;
	}
	cout << endl << endl;

	int ItsATree = 0; // ვიყენებთ იმის დასადგენად არის თუ არა ჩვენი გრაფი ხე

	for (int i = 0; i < Tree.size(); i++) // გავიაროთ უმცირესი დამფარავი ხე
	{
		// და ყოველ ჯერზე შევქმნათ ახალი გრაფი ერთ-ერთი MST-ის წიბოს გარეშე ანუ საწყისი გრაფიდან "ამოვიღოთ"/"ამოვშალოთ" უმცირესი დამფარავი ხის ერთ-ერთი წიბო
		Graph Poterncial_Graph(*this);
		Poterncial_Graph.removeEdge(Tree[i]);

		// თუ წიბოს ამოღების შემდეგ გრაფი დაიშალა ორ კომპონენტად მაშინ ამოვიღოთ სხვა წიბო
		if (!Poterncial_Graph.BFS())
		{
			++ItsATree;
			continue;
		}

		// შემდეგ ვიპოვოთ MST ჩვენ მიერ შექმნილ ახალ გრაფში
		Poterncial_Graph.Kruskal_MST();

		// შევინახოთ მიღებული უმცირესი დამფარავი ხე და მისი წონა ხეთა სიმრავლეში
		Treesets.push_back({ Poterncial_Graph.Tree_Weight, Poterncial_Graph.Tree });
	}
	
	// თუ ჩვენი მთვლელი გახდა ხის ზომის ტოლი გამოდის რომ ნებისმიერი წიბოს ამოღების დროს გრაფი ორად იშლება ანუ ხეა
	if (ItsATree == Tree.size())
	{
		cout << "This Graph is a Minimal Spanning Tree (MST) itself!\n" << endl;
		return;
	}

	// დავსორტოთ მიღებული ხეთა სიმრავლე წონების მიხედვით
	sort(Treesets.begin(), Treesets.end());
	
	int count = 1, Tree_W = Tree_Weight;

	// სანამ ხეთა სიმრავლე არ დაცარიელდება
	while (!Treesets.empty())
	{
		// თუ ხეთა სიმრავლის ელემენტის(ხის) წონა ემთხვევა MST-ის წონას ესეიგი კიდევ ერთი MST ვიპოვეთ
		if (Treesets[0].first == Tree_W)
		{
			cout << "We found another " << count << "_Level_MST with same weight = " << Treesets[0].first << '\n' << endl;
			for (int j = 0; j < Treesets[0].second.size(); ++j)
			{
				cout << '\'' << tochar(Treesets[0].second[j].second.first) << "\' -- " << Treesets[0].second[j].first
					<< " -- \'" << tochar(Treesets[0].second[j].second.second) << '\'' << endl;
			}
			cout << endl << endl;
		}
		// თუ კონკრეტული ხის წონა წინა ხის წონაზე მაღალია ესეიგი შემდეგ დონის დამფარავი ხე ვიპოვეთ
		else if (Treesets[0].first > Tree_W)
		{
			Tree_W = Treesets[0].first; // წონა გავაახლოთ (update)

			cout << "We found " << ++count << "_Level_MST with weight = " << Treesets[0].first << '\n' << endl;
			for (int j = 0; j < Treesets[0].second.size(); ++j)
			{
				cout << '\'' << tochar(Treesets[0].second[j].second.first) << "\' -- " << Treesets[0].second[j].first
					<< " -- \'" << tochar(Treesets[0].second[j].second.second) << '\'' << endl;
			}
			cout << endl << endl;
		}
		Treesets.erase(Treesets.begin()); // ამოვიღოთ პირველივე ელემენტი ხეთა სიმრავლიდან რადგან ის უკვე დავბეჭდეთ
	}
}


int main()
{
	// შენიშვნა*: წვეროების რაოდენობა ზუსტად მიუთითეთ!
	int V = 5, E = 7;

	Graph g(V, E);

	// adding edges - წიბოების დამატება
	g.addEdge('a', 'b', -1);
	g.addEdge('a', 'c', -2);
	//g.addEdge('a', 'd', -3);

	//g.addEdge('b', 'c', -4);
	g.addEdge('b', 'd', -5);
	//g.addEdge('c', 'd', -6);

	g.addEdge('d', 'e', -100);

	g.NextMST();
}