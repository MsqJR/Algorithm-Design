    // GROUP:   1
    // ID:      20226081
    // Assign:  02
    // Assign:  DisjointSets
    // UVA:     10608
    // Name:    mark mounir sobhy

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
                parent = new int[n];
                num_nodes= new int[n];
                for(int i=1;i<=n;i++){
                    parent[i]=i; 
                    num_nodes[i]=1;
                }
                    };
        void Destroy(){
            parent=num_nodes=nullptr;
            delete[] parent;
            delete[] num_nodes;
        };
       int Find(int i) {
    
        if (i < 1 || i > n) {
        cerr << "Index out of bounds: " << i << endl;
        exit(EXIT_FAILURE);
    }
    if (parent[i] == i) return i;
    else return parent[i] = Find(parent[i]); 
}
        bool Union(int i, int j) {
            
    int root_i = Find(i);
    int root_j = Find(j);
    if (root_i == root_j) return false;
    parent[root_j] = root_i;
    num_nodes[root_i] += num_nodes[root_j];
    return true;
}
    };

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////

    int main()
    {
       int num_sets=0,num_f,R;
       cin>>num_sets;
       for(int i=0;i<num_sets;i++){
        DisjointSets D;
        cin>>num_f>>R;
        D.Initialize(num_f);
        for(int i=0;i<R;i++){
            int x=0,y=0;
            cin>>x>>y;
            D.Union(x,y);
        }
        int largest=0;
        for (int i=1;i<=num_f;i++){
            if(D.num_nodes[i]>largest) largest=D.num_nodes[i];
        }
        cout<<largest;
        D.Destroy();
       }

        return 0;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////