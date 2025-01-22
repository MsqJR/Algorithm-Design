// GROUP:   1
// ID:      20226081
// Assign:  08
// Assign:  ClosetsPair
// UVA:     10245
// Name:    Mark Mounir

#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <cmath>     // please use the built-in sqrt() function
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)){
    int mid = n / 2;
    int i = 0, j = mid, k = 0;
    Type* temp = new Type[n];
    while (i < mid && j < n) {
        if (IsBefore(a[i], a[j])) temp[k++] = a[i++];
        else temp[k++] = a[j++];
    }
    while (i < mid) temp[k++] = a[i++];
    while (j < n) temp[k++] = a[j++];
    for (i = 0; i < n; i++) a[i] = temp[i];
    delete[] temp;
}

template<class Type>
void MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b)){   if (n <= 1) return;
    int mid = n / 2;
    MergeSort(a, mid, IsBefore);
    MergeSort(a + mid, n - mid, IsBefore);
    Merge(a, n, IsBefore);}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Point
{
	double x,y;
};

bool IsBeforeX(Point& a, Point& b){
    return a.x<b.x;

};
bool IsBeforeY(Point& a, Point& b){
    return a.y<b.y;
};

double dist(Point& a, Point& b){
  return sqrt((pow(a.x-b.x,2)+pow(a.y-b.y,2)));
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Sort the points p according to x before calling this function
double ClosestPair(Point* p, int n){
    if (n <= 3) {
	MergeSort(p,n,IsBeforeY);
        double minDist = 1e9;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                minDist = min(minDist, dist(p[i], p[j]));
            }
        }
        return minDist;
    }
    int mid =n/2;
    double d1= ClosestPair(p,mid);
    double d2= ClosestPair(p+mid,n-mid);
    double d= min(d1,d2);
    Point * strip= new Point[n];
    int stripcount =0;
    for (int i=0 ;i<n;i++){
	    if ((abs(p[i].x-p[mid].x))<d){
		strip[stripcount++]= p[i];
	    }
    }
    MergeSort(strip,stripcount,IsBeforeY);
    for (int i=0 ; i<stripcount;i++){
	    for (int j = i+1; j <stripcount ; ++j) {
		    if((strip[j].y-strip[i].y)>d) break;
		    else d=min(d,dist(strip[i],strip[j]));
	    }
    }
    delete[] strip;
    return d;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int n;
    while (cin>>n&&n!=0) {
        Point* points = new Point[n];
        for (int i = 0; i < n; ++i) {
            cin >> points[i].x >> points[i].y;
        }
        MergeSort(points, n, IsBeforeX);
        double result = ClosestPair(points, n);

        if (result >= 10000.0) {
            cout << "INFINITY" << endl;
        } else {
            cout<< setprecision(5) << result << endl;
        }

        delete[] points;
    }
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
