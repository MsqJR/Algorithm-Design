// GROUP:   1
// ID:      20226081
// assign:  10
// assign:  MatChain
// UVA:     348
// Name:    Mark Mounir Sobhy

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <climits>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int p[11]; // the dimensions of matrices

int T[11][11]; // T[t][b]=the optimal number of multiplication of p[t]...p[b]
int D[11][11]; // D[t][b]=the decision (value of k) that gets T[t][b]

// Top down version
int MatChain(int i, int j) {
    if (T[i][j]!=-1) return T[i][j];
    if (j==i+1){
        T[i][j]=0;
        return 0;
    }
    int k,v=INT_MAX,q;
    for(k=i+1;k<j;k++){
         int r=p[i]*p[k]*p[j]+MatChain(i,k) +MatChain(k,j);
         if(r<v){
            v=r;
            q=k;
         }  
    }
    T[i][j]=v;
    D[i][j]=q;
    return v;
}

void MatChainTopDown(int n) {
    memset(T, -1, sizeof(T));
    MatChain(0, n);
}

// BottomUp version
void MatChainBottomUp(int n) {
    for (int i=0;i<n;i++){T[i][i+1]=0;}

    for (int t = 2,j=0; t <= n; t++) {
        for (int i = 0; i+t <= n; i++) {
            j = t + i;
            int k,v=INT_MAX,q;
            for (k = i+1; k < j; k++) {
                int r = T[i][k] + T[k][j] + p[i] * p[k] * p[j];
                if (r < v) {
                    v = r;
                    q = k;
                }
            }
            T[i][j]=v;
            D[i][j]=q;
        }
    }
}

// Recursive to output the solution for both versions
void MatChainSol(int a, int b) {
    if (a +1 == b) { 
        printf("A%d", a+1);
        return;
    }
    printf("(");
    MatChainSol(a, D[a][b]);
    printf(" x ");
    MatChainSol(D[a][b], b);
    printf(")");
}

void Compute() {
    int n, caseNo = 1;
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        for (int i = 0; i < n; i++) {
            scanf("%d %d", &p[i], &p[i + 1]);
        }

        MatChainBottomUp(n);

        printf("Case %d: ", caseNo++);
        MatChainSol(0, n);
        printf("\n");
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main() {
     //freopen("input_assign10_00348.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
