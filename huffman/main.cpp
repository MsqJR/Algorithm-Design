#include <bits/stdc++.h>
using namespace std;
struct node
{
    char ch;
    node* leftch;
    node* rightch;
};
/*int freq (char chs [] ){
    int sz=sizeof chs/sizeof chs[0];
    int freqs[sz];
    for(int i=0;i<sz;i++){
        freqs[i]=0;
    }
}*/
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
template<class Elem>
struct Heap
{

    Array<Elem> a;
    bool (*IsBefore)(Elem&, Elem&);
    void Initialize(bool (*_IsBefore)(Elem&, Elem&)){
        IsBefore = _IsBefore;
        a.Initialize();

    };
    void Destroy(){
        a.Destroy();

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
struct Edge {
    int w;
    char c;
int side;
};
bool IsBefore(Edge& a,Edge& b)
{
    return a.w>b.w;
}
int main() {
Heap<Edge> arr;
arr.Initialize(IsBefore);
cin>>arr.a.sz;
for (int i=0;i<arr.a.sz;i++){
    Edge in;
    cin>>in.c;
    cin >>in.w;
  arr.Add({in.w,in.c});
}
for(int i=0;i<arr.a.sz;i++){
    if (i==0)cout<<arr.RetrieveFirst().c<<"0";
    else if (i==(arr.a.sz-1)) {
        cout <<arr.RetrieveFirst().c;
        for (int j = 0;j<arr.a.sz-1;j++)cout <<"1";
    }
    else {
        cout <<arr.RetrieveFirst().c;
        for (int j=0;j<i;j++)cout <<"1";
        cout <<"0";
    }
    cout <<endl;
}
    return 0;
}
