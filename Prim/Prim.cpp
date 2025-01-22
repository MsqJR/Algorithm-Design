#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
using namespace std;

template<class Value>
struct Array
{
    int n, sz;
    Value* arr;
    void Initialize()
    {
        n = 0;
        sz = 1;
        arr = new Value[sz];
    }
    void Destroy()
    {
        delete[] arr;
    }
    void AddLast(Value v)
    {
        if (sz == n)
        {
            sz *= 2;
            Value* newarr = new Value[sz];
            for (int i = 0; i < n; i++) {
                newarr[i] = arr[i];
            }
            delete[] arr;
            arr = newarr;
        }
        arr[n++] = v;
    }

    Value& operator[](int i)
    {
        return arr[i];
    }
};

struct Edge
{
    int    v;  // id of the adjacent node
    double  w;  // edge weight = distance between the two nodes
};
struct Node
{
    int x,y; // x and y coordinates of the node
    Array<Edge> adj;

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
    Node* nodes;

    void Initialize(int _n)
    {
        n = _n;
        nodes = new Node[n];
        for (int i = 0; i < n; i++) {
            nodes[i].Initialize();
        }
    }
    void Destroy()
    {
        for (int i = 0; i < n; i++) {
            nodes[i].Destroy();
        }
        delete[] nodes;
    }

};

// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n=100){
    double a=0,b=n,m=0;
    for (int i=0;i<n;i++){
        m=(a+b)/2;
        if(m*m>v)b=m;
        else a=m;
    }
    return m;
};

double distance(Node a, Node b) {
    double xcor=(a.x-b.x)*(a.x-b.x),ycor=(a.y-b.y)*(a.y-b.y);
    return Sqrt(xcor+ycor);
}

int main()
{
    Graph g;

    int num_nodes;
    int scen=1;
    cin>>num_nodes;
    while(num_nodes!=0)
    {
        g.Initialize(num_nodes);
        for(int i=0;i<num_nodes;i++)
        {
            cin>>g.nodes[i].x>>g.nodes[i].y;
        }
        cout<<"\n";
        for (int i = 0; i < num_nodes; i++)
        {
            for (int j = i + 1; j < num_nodes; j++)
            {
                double dist = distance(g.nodes[i], g.nodes[j]);
                g.nodes[i].adj.AddLast({ j, dist });
                g.nodes[j].adj.AddLast({ i, dist });
            }
        }
        bool *visited = new bool[num_nodes];
        double* minDist = new double[num_nodes];
        for (int i = 0; i < num_nodes; i++)
        {
            visited[i] = false;
            minDist[i] = 9999999;
        }
        minDist[0] = 0;

        double maxJump = 0.0;

        for (int i = 0; i < num_nodes; i++)
        {
            int u = -1;
            for (int j = 0; j < num_nodes; j++) {
                if (!visited[j] && (u == -1 || minDist[j] < minDist[u])) {
                    u = j;

                    // Update maxJump when node 1's distance is updated
                    if (j == 1 && minDist[j] < 9999999) {
                        maxJump =  minDist[j];
                    }
                }

                for (int k = 0; k < g.nodes[u].adj.n; k++) {
                    Edge e = g.nodes[u].adj[k];
                    if (!visited[e.v] && e.w < minDist[e.v]) {
                        minDist[e.v] = e.w;
                    }
                }
            }

            visited[u] = true;
        }

        cout << "Scenario #" << scen++ << endl;
        cout << "Frog Distance = "
             << setprecision(3)
             << fixed
             << maxJump
             << endl
             << endl;

        delete[] visited;
        delete[] minDist;
        g.Destroy();
        cin>>num_nodes;
    }
    return 0;
}