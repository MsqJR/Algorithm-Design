// GROUP:   1
// ID:      20226081
// Assign:  03
// Assign:  Graphs
// UVA:     924
// Name:    Mark Mounir Sobhy

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class Value>
struct Array
{
	int n, sz;
	Value *arr;

	void Initialize()
	{
		n = 0;
		sz = 1;
		arr = new Value[sz];
	}

	void Destroy()
	{
		delete[] arr;
		arr = nullptr;
	}

	void AddLast(Value v)
	{
		if (n == sz)
		{
			Value *newarr = new Value[sz *= 2];
			for (int i = 0; i < n; i++)
			{
				newarr[i] = arr[i];
			}
			delete[] arr;
			arr = newarr;
		}
		arr[n++] = v;
	}

	void RemoveLast()
	{
		if (n > 0)
			n--;
	}

	Value &operator[](int i)
	{
		return arr[i];
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Node
{
	Array<int> adj;

	void Initialize()
	{
		adj.Initialize();
	}

	void Destroy()
	{
		adj.Destroy();
	}
};

struct Graph
{
	int n;
	Node *nodes;

	void Initialize(int _n)
	{
		nodes = new Node[_n];
		n = _n;
		for (int i = 0; i < _n; i++)
		{
			nodes[i].Initialize();
		}
	}

	void Destroy()
	{
		for (int i = 0; i < n; i++)
			nodes[i].Destroy();
		delete[] nodes;
		nodes = nullptr;
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class Type>
struct Queue
{
	int f, n;
	Type *elems;

	void Initialize(int size)
	{
		f = 0;
		n = 0;
		elems = new Type[size];
	}

	void Destroy()
	{
		delete[] elems;
	}

	void Add(Type t)
	{
		elems[n++] = t;
	}

	Type Pop()
	{
		return elems[f++];
	}

	Type Peek()
	{
		return elems[f];
	}

	int Num()
	{
		return n - f;
	}
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	int E;
	cin >> E;
	Graph graph;
	graph.Initialize(E);
	for (int i = 0; i < E; i++)
	{
		int no_Friends;
		cin >> no_Friends;
		for (int j = 0; j < no_Friends; j++)
		{
			int frnd_indx;
			cin >> frnd_indx;
			graph.nodes[i].adj.AddLast(frnd_indx);
		}
	}
	int T;
	cin >> T;
	while (T--)
	{
		int src;
		cin >> src;
		if (graph.nodes[src].adj.n == 0)
		{
			cout << 0 << endl;
			continue;
		}
		bool *visited = new bool[E];
		memset(visited, false, E * sizeof(bool));
		Queue<int> q;
		q.Initialize(E);
		q.Add(src);
		visited[src] = true;
		int day = 0;
		int MDB = 0, FBD = 0;
		while (q.Num() > 0)
		{
			int currentboomsize = q.Num();
			if (currentboomsize > MDB)
			{
				MDB = currentboomsize;
				FBD = day;
			}
			for (int i = 0; i < currentboomsize; i++)
			{
				int u = q.Pop();
				for (int j = 0; j < graph.nodes[u].adj.n; j++)
				{
					int v = graph.nodes[u].adj[j];
					if (!visited[v])
					{
						q.Add(v);
						visited[v] = true;
					}
				}
			}
			day++;
		}
		if (FBD == 0)
			FBD = 1;
		cout << MDB << " " << FBD << endl;
		q.Destroy();
		delete[] visited;
	}
	graph.Destroy();
	return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////