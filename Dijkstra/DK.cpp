// GROUP:   1
// ID:      20226081
// Assign:  07
// Assign:  Dijkstra
// UVA:     10986
// Name:    Mark Mounir Sobhy

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Value>
struct Array
{
    int  n, sz;
    Value* arr;

    void Initialize(){
        n = 0;
        sz = 5; // Initial size of the array
        arr = new Value[sz];
    };
    void Destroy(){
        delete[] arr;
    };
    void AddLast(Value v){
        if(n >= sz)
        {
            sz = sz * 2;
            Value* newarr = new Value[sz];
            for (int i = 0; i < n; i++){
                newarr[i] = arr[i];
            }
            delete[] arr;
            arr = newarr;
        }
        arr[n++] = v;
    };
    void RemoveLast(){
        if (n > 0)
            n--;
    };
    Value& operator[](int i){
        return arr[i];
    };
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Elem>
struct Heap
{
    int* pos; // pos[v]=i where a[i].v=v, otherwise pos[v]=-1
    Array<Elem> a;
    bool (*IsBefore)(Elem&, Elem&);

    void Initialize(bool (*_IsBefore)(Elem&, Elem&), int n){
        IsBefore = _IsBefore;
        a.Initialize();
        pos = new int[n];
        for (int i = 0; i < n; i++){
            pos[i] = -1;
        }
    }; // n is required to allocate and initialize pos[]
    void Destroy(){
        a.Destroy();
        delete[] pos;
    };
    void Print(int* pred, int T){
        if (pred[T] == -1) { cout << T; return; }
        Print(pred, pred[T]);
        cout << " -> " << T;
    };
    int Child(int i){
        return (2 * i) + 1;
    };
    int Parent(int i){
        return (i - 1) / 2;
    };
    Elem GetFirst(){
        return a[0];
    };
    Elem RetrieveFirst(){
        Elem First = a[0];
        a[0] = a[a.n - 1];
        a.RemoveLast();
        MoveDown(0);
        return First;
    };
    void Add(Elem e){
        a.AddLast(e);
        MoveUp(a.n - 1);
    };
    void MoveUp(int ind){
        while(ind > 0 && IsBefore(a[ind], a[Parent(ind)])){
            swap(a[ind], a[Parent(ind)]);
            ind = Parent(ind);
        }
    };
    void MoveDown(int ind){
        int left = Child(ind);
        while(left < a.n){
            int right = left + 1;
            int smallest = left;
            if (right < a.n && IsBefore(a[right], a[left])){
                smallest = right;
            }
            if (IsBefore(a[ind], a[smallest])){
                break;
            }
            swap(a[ind], a[smallest]);
            ind = smallest;
            left = Child(ind);
        }
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
    int v;
    int w;
};

struct Node
{
    Array<Edge> adj;

    void Initialize(){
        adj.Initialize();
    };
    void Destroy(){
        adj.Destroy();
    };
};

struct Graph
{
    int n;
    Node* nodes;

    void Initialize(int _n)
    {
        n = _n;
        nodes = new Node[n];
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

bool IsBefore(Edge& a, Edge& b)
{
    return a.w < b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int N;
    cin >> N;
    for (int case_num = 1; case_num <= N; ++case_num)
    {
        int n, m, S, T;
        cin >> n >> m >> S >> T;

        Graph graph;
        graph.Initialize(n);

        for (int i = 0; i < m; ++i)
        {
            int u, v, w;
            cin >> u >> v >> w;
            graph.nodes[u].adj.AddLast({v, w});
            graph.nodes[v].adj.AddLast({u, w});
        }

        const int INF = 1e9;
        int* dist = new int[n];
        for (int i = 0; i < n; ++i)
            dist[i] = INF;

        Heap<Edge> heap;
        heap.Initialize(IsBefore, n);
        int* pred = new int[n];
        for (int i = 0; i < n; ++i)
            pred[i] = -1;
        dist[S] = 0;
        heap.Add({S, 0});
        while (heap.a.n > 0)
        {
            Edge edge = heap.RetrieveFirst();
            int u = edge.v;
            int d = edge.w;

            if (d > dist[u]) continue;

            for (int i = 0; i < graph.nodes[u].adj.n; ++i)
            {
                Edge& e = graph.nodes[u].adj[i];
                int v = e.v;
                int w = e.w;

                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    pred[v] = u;
                    heap.Add({v, dist[v]});
                }
            }
        }
        heap.Print(pred,T);
        for (size_t i = 0; i < n; i++)
        {
            cout<<" the distance to "<< i << " is "<< dist[i]<<endl;
        }

        cout << "Case #" << case_num << ": ";
        if (dist[T] == INF)
        {
            cout << "unreachable" << endl;
        }
        else
        {
            cout << dist[T] << endl;
        }
        delete[] dist;
        heap.Destroy();
        graph.Destroy();
        delete[] pred;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
