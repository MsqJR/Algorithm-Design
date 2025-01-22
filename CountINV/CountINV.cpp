	// GROUP:   S1
	// ID:      20226081
	// Assign:  04
	// Assign:  CountInv
	// UVA:     10810
	// Name:    Mark Mounir
	#include <cstdio>
	#include <cstdlib>
	#include <cstring>
	#include <iostream>
	using namespace std;
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	long long CountInvMerge(long long *a, int n)
	{ if (n<=1) return 0;
		int mid = n / 2;
		long long noInvs = 0;
		int i = 0, j = mid, t = 0;
		long long *temp = new long long[n];
		while (i < mid && j < n)
		{
			if (a[i] > a[j])
			{
				noInvs += (mid - i);int current=(mid - i);
				temp[t++] = a[j++];
			}
			else
			{
				temp[t++] = a[i++];
			}
		}
		while (i < mid)
		{
			temp[t++] = a[i++];
		}
		while (j < n)
		{
			temp[t++] = a[j++];
		}
		for (int i = 0; i < n; i++)
		{
			a[i] = temp[i];
		}
		delete[] temp;
		return noInvs;
	}
	long long CountInv(long long *a, int n)
	{
		if (n <= 1)
			return 0;
		long long C1 = CountInv(a, n / 2);
		long long C2 = CountInv(a + (n / 2), n - (n / 2));
		long long C3 = CountInvMerge(a, n);
		return C1 + C2 + C3;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////
	int main()
	{
		int sZ = 1;
		cin>>sZ;
		while(sZ!=0){
			if (sZ == 0)
				break;
			long long elem = 0;
			long long *arr = new long long[sZ];
			for (int i = 0; i < sZ; i++)
			{
				cin >> elem;
				arr[i] = elem;
			}

			cout << CountInv(arr, sZ)<<endl;
			delete[] arr;
			cin>>sZ;
		}
		return 0;
	}
	////////////////////////////////////////////////////////////////////////////////////////////////////////////