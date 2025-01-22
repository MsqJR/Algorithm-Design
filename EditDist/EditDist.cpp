// GROUP:   1
// ID:      20226081
// Assign:  11
// Assign:  EditDist
// UVA:     526
// Name:    Mark Mounir Sobhy

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

char a[82];
char b[82];

int D[81][81]; // D[][] is the same for all versions (no memory reduction)

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T1[81][81];
int EditDist1(int n, int m);
int ComputeEditDist1(int N, int M) // Recursive - memoization - initialize T then call EditDist1(N,M)
{
    memset(T1, -1, sizeof(T1));
    return EditDist1(N, M);
}

int EditDist1(int n, int m)
{
    if (n == 0) return m;
    if (m == 0) return n;
    if (T1[n][m] != -1) return T1[n][m];

    if (a[n - 1] == b[m - 1])
        return T1[n][m] = EditDist1(n - 1, m - 1);

    
    int insert = EditDist1(n, m - 1) + 1;
    int del = EditDist1(n - 1, m) + 1;
    int replace = EditDist1(n - 1, m - 1) + 1;
     if (insert<del&&insert<replace) D[n][m]=1;
     else if(del<insert&&del<replace) D[n][m]=2;
     else if (replace<insert&&insert<del) D[n][m]=3;   
    return T1[n][m] = min(insert, min(del, replace));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T2[81][81];
int ComputeEditDist2(int N, int M) // Bottom-up, do not save space
{
    for (int i = 0; i <= N; ++i) T2[i][0] = i;
    for (int j = 0; j <= M; ++j) T2[0][j] = j;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (a[i - 1] == b[j - 1])
                T2[i][j] = T2[i - 1][j - 1];
            else
                T2[i][j] = min(T2[i - 1][j], min(T2[i][j - 1], T2[i - 1][j - 1])) + 1;
        }
    }
    return T2[N][M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T3[2][81];
int ComputeEditDist3(int N, int M) // Bottom-up, use two rows only
{
    for (int j = 0; j <= M; ++j) T3[0][j] = j;

    for (int i = 1; i <= N; ++i) {
        T3[i % 2][0] = i;
        for (int j = 1; j <= M; ++j) {
            if (a[i - 1] == b[j - 1])
                T3[i % 2][j] = T3[(i - 1) % 2][j - 1];
            else
                T3[i % 2][j] = min(T3[(i - 1) % 2][j], min(T3[i % 2][j - 1], T3[(i - 1) % 2][j - 1])) + 1;
        }
    }
    return T3[N % 2][M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int T4[81];
int ComputeEditDist4(int N, int M) // Bottom-up, save maximum space
{
    for (int m = 0; m <= M; ++m) T4[m] = m;

    for (int n = 1; n <= N; ++n) {
        int prev = T4[0];
        T4[0] = n;
        for (int m = 1; m <= M; ++m) {
            int temp = T4[m];
            if (a[n - 1] == b[m - 1])
                T4[m] = prev;
            else
                int insert=T4[m];
                int del=T4[m - 1];
                int replace= prev;
                T4[m] = min(T4[m], min(T4[m - 1], prev)) + 1;
            prev = temp;
        }
    }
    return T4[M];
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Oper
{
    int n, m;
    int oper;
};

Oper opers[81];

int EditDistSol(int N, int M) // Print the solution using D[][]
{
    for (int i = 0; i <= N; ++i) D[i][0] = i;
    for (int j = 0; j <= M; ++j) D[0][j] = j;

    for (int i = 1; i <= N; ++i) {
        for (int j = 1; j <= M; ++j) {
            if (a[i - 1] == b[j - 1]) {
                D[i][j] = D[i - 1][j - 1];
            } else {
                int del = D[i - 1][j] + 1;
                int insert = D[i][j - 1] + 1;
                int replace = D[i - 1][j - 1] + 1;
                D[i][j] = min(del,min(insert, replace));
            }
        }
    }
    int i = N, j = M, steps = 0;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && a[i - 1] == b[j - 1]) {
            --i;
            --j;
        } else if (i > 0 && D[i][j] == D[i - 1][j] + 1) {
            ++steps;
            --i;
        } else if (j > 0 && D[i][j] == D[i][j - 1] + 1) {
            ++steps;
            --j;
        } else {
            ++steps;
            --i;
            --j;
        }
    }
    cout<<steps<<endl;
    i = N, j = M; 
    int step = 0;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && a[i - 1] == b[j - 1]) {
            --i;
            --j;
        } else if (i > 0 && D[i][j] == D[i - 1][j] + 1) {
           
            cout << ++step << " Delete " << i << endl;
            --i;
        } else if (j > 0 && D[i][j] == D[i][j - 1] + 1) {
            
            cout << ++step << " Insert " << i + 1 << "," << b[j - 1] << endl;
            --j;
        } else {
            
            cout << ++step << " Replace " << i << "," << b[j - 1] << endl;
            --i;
            --j;
        }
    }
    cout<<endl;
    return step;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int ComputeEditDist(int N, int M) // Here we can choose the method
{
    //return ComputeEditDist1(N,M);
    //return ComputeEditDist2(N,M);
    //return ComputeEditDist3(N,M);
    return ComputeEditDist4(N,M);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// This function does not need any modification:
void Compute() // Get input and call ComputeEditDist() whenever needed
{
    int cas = 0;
    while (true) {
        a[0] = 0; b[0] = 0;
        if (!fgets(a, 82, stdin)) break;
        fgets(b, 82, stdin);
        a[strlen(a) - 1] = 0;
        b[strlen(b) - 1] = 0;
        if (cas) cout << endl; // print an empty line between test cases
        int N = strlen(a), M = strlen(b);
        ComputeEditDist(N, M);
        EditDistSol(N, M);
        cas++;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    //freopen("input_assign11_00526.txt", "r", stdin);
    Compute();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

