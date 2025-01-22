// GROUP:   X
// ID:      XXXXXXXX
// Assign:  05
// Assign:  Kruskal
// UVA:     11631
// Name:    XXX MY FULL NAME

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
	int n;
	int* parent;
	int* num_nodes;

	void Initialize(int _n){
        n=_n;
        parent=new int[n];
        num_nodes=new int[n];
        for (int i=0;i<n;i++){
            parent[i]=i;
            num_nodes[i]=1;
        }
    };
	void Destroy(){
        delete[] parent;
        delete[] num_nodes;
    };
	int Find(int i){
        if(parent[i]==i) return parent[i];
        else return Find(parent[i]);
    }
	bool Union(int i, int j){
       int root_i=Find(i);
       int root_j=Find(j);
       if (root_i==root_j) return false;
       parent[root_j]=root_i;
       num_nodes[root_i]+=num_nodes[root_j];
       return true;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)){
int mid=n/2;
Type* aux=new Type[n];
int left=0,right=mid,auxind=0;

while(left<mid&&right<n){

if(IsBefore(a[left],a[right])) aux[auxind++]=a[left++];
else {aux[auxind++]=a[right++];}
}
while(left<mid){
aux[auxind++]=a[left++];
}
while(right<n){aux[auxind++]=a[right++];}

for(int i=0;i<n;i++) {a[i]=aux[i];}
delete[] aux;
};

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)){
if(n<=1)return;
MergeSort(a,n/2,IsBefore);
MergeSort(a+(n/2),n-(n/2),IsBefore);
Merge(a,n,IsBefore); 
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Edge
{
	int u, v;
	int w;
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
	return a.w<b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int n=0,m=0;
    while(true){
    cin>>m>>n;
    if(m==0&&n==0) break;
    Edge *edges=new Edge[n];
    int total_weight=0;
    for(int i=0;i<n;i++){
        cin>>edges[i].u>>edges[i].v>>edges[i].w;
        total_weight+=edges[i].w;
    }
    MergeSort(edges,n,IsBeforeEdge);
    DisjointSets ds;
    ds.Initialize(m);

    int usdedges=0,myweight=0;
    for (int i = 0; i < n&&usdedges<=m-1; i++)
    {
       int u=edges[i].u;
       int v=edges[i].v;
       int w=edges[i].w;
     if(ds.Union(u,v)){
        myweight+=w;
        usdedges++;
     }   
    }
    int savings= total_weight - myweight ;
    cout<<savings<<endl;
    ds.Destroy();
    delete[] edges;
    }
    
	return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////