#include <iostream>
#include <list>
#include <string>

using namespace std;

class Graph
{
	static int Time; // დრო რომელიც მუდამ იზრდება

	int V; // წვეროთა რაოდენობა
	list<int>* adj; // სიების მასივი წიბოებისთვის
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

	void addEdge(char v, char u)
	{
		// მასივის დიაპაზონს ვერ გავცდებით
		if (IntoInt(v) >= 0 && IntoInt(v) < V)
		{
			adj[IntoInt(v)].push_back(IntoInt(u)); // წიბო (v, u)
		}
		else
		{
			cout << "We cant create Edge (\'" << v << "\', \'" << u << "\')" << endl;
		}
	}

	void DFS()
	{
		// ყოველი წვეროსთვის
		for (int i(0); i < V; ++i)
		{
			if (color[i] == 0) // თუ წვერო არ არის მონახულებული
			{
				DFSvisit(i); // მაშინ მოვინახულოთ
				cout << endl;
			}
			// დავბეჭდოთ ინფორმაცია მოცემულ წვეროზე
			cout << "Vertex: \'" << IntoChar(i) << "\'    Color: " << Color(color[i])
				<< "    d[" << IntoChar(i) << "] = " << d[i] << "    f[" << IntoChar(i) << "] = " << f[i] << '\n' << endl;
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
				cout << "Tree Edge: \'" << IntoChar(v) << "\' --> \'" << IntoChar(*it) << '\'' << endl; // თუ წვერო თეთრია, მაშინ ხის წიბო გვაქვს
				DFSvisit(*it); // რეკურსია (დინამიური დაპროგრამება)
			}
			else if (color[*it] == 1) // თუ წვერო რუხია, მაშინ უკუ წიბო გვაქვს
			{
				cout << "Back Edge: \'" << IntoChar(v) << "\' --> \'" << IntoChar(*it) << '\'' << endl;
			}
			else if (color[*it] == 2) // თუ წვერო შავია, მაშინ ან ჯვარედინი წიბო გვაქვს ან პირდაპირი
			{
				cout << "Cross or Direct Edge: \'" << IntoChar(v) << "\' --> \'" << IntoChar(*it) << '\'' << endl;
			}
		}
		//----------------------------------------------------------------

		// წვეროს შესწავლის დასრულება
		++Time;
		color[v] = 2;
		f[v] = Time;
		//--------------------------
	}

	// აბრუნებს ფერებს შესაბამისი ციფრების მიხედვით
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

													// დამატებული კოდი ძლიერად ბმული გრაფის დასადგენად

	// სიღრმეში ძებნის ალგორითმი გადაცემული წვეროდან
	void DFS(int v)
	{
		if (color[v] == 0)
		{
			DFS_OnlyColorvisit(v); // თუ წვერო თეთრია მაშინ მოვინახულოთ
		}
	}

	// მოცემული ფუნქცია მუშაობს მხოლოდ ფერებთან, რადგან იგი გვეხმარება დავადგინოთ გრაფი ძლიერად ბმულია თუ არა
	void DFS_OnlyColorvisit(int v)
	{
		// წვეროს მონახულება
		color[v] = 1;
		//---------------------

		// წვეროს შესწავლა მეზობლებითა და მათი შთამომავლებითურთ
		for (auto it = adj[v].begin(); it != adj[v].end(); ++it)
		{
			if (color[*it] == 0)
			{
				DFS_OnlyColorvisit(*it); // რეკურსია (დინამიური დაპროგრამება)
			}
		}
		//----------------------------------------------------------------

		// წვეროს შესწავლის დასრულება
		color[v] = 2;
		//--------------------------
	}

	// მოცემული ფუნქცია ადგენს გრაფი ძლიერად ბმულია თუ არა
	bool StronglyLinked()
	{
		// გრაფის ყველა წვეროს ფერი გავათეთროთ
		for (int i = 0; i < V; ++i)
		{
			color[i] = 0;
		}

		for (int i = 0; i < V; ++i) // გრაფის ყოველი წვეროსთვის
		{
			this->DFS(i); // ამ წვეროდან გავუშვათ სიღრმეში ძებნის ალგორითმი

			// ამის შემდეგ, თუ ალგორითმმა ყველა სხვა წვერომდე ვერ მიაღწია
			// მაშინ გამოდის რომ არ არსებობს გზა ყოველი წვეროდან ყოველ სხვა წვერომდე.
			for (int j = 0; j < V; ++j)
			{
				if (color[j] == 0) // ანუ თუ რომელიმე წვერო ისევ თეთრი დარჩა
					return false;
			}

			// გავათეთროთ ისევ ყველა წვერო, რათა იგივე გავიმეოროთ სხვა წვეროებისთვისაც
			for (int k = 0; k < V; ++k)
			{
				color[k] = 0;
			}
		}

		// თუ კოდმა აქამდე მოაღწია, გამოდის, რომ გრაფი ძლიერად ბმულია
		return true;
	}

	// ლათინური ასო გადაჰყავს რიცხვში
	int IntoInt(char k)
	{
		switch (k)
		{
		case 'a': return 0;
		case'b': return 1;
		case'c': return 2;
		case'd': return 3;
		case'e': return 4;
		case'f': return 5;
		case'g': return 6;
		default: return V;
		}
	}

	// რიცხვი გადაჰყავს ლათინურ ასოში
	char IntoChar(int a)
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
		default: return 'Z';
		}
	}
};

int Graph::Time = 0;

int main()
{
	// DFS

	Graph Luka(5);

	Luka.addEdge('a', 'b');
	Luka.addEdge('d', 'a');
	Luka.addEdge('b', 'd');
	Luka.addEdge('d', 'e');
	Luka.addEdge('e', 'b');
	Luka.addEdge('c', 'e');
	//Luka.addEdge('b', 'c');

	Luka.DFS();


											// დამატებული კოდი ძლიერად ბმული გრაფის დასადგენად

	if (Luka.StronglyLinked())
	{
		cout << "\nThis Graph is Strongly Linked!" << endl;
	}
	else
	{
		cout << "\nThis Graph is NOT Strongly Linked!" << endl;
	}
}