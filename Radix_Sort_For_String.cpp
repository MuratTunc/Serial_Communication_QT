#include <iostream>
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* strtoull */
#include <bits/stdc++.h>

using namespace std;
void printVector(vector<string>& vec)
{
    for (string a : vec)
        cout << a << " ";

    cout<<endl;
}


// A function to do counting sort of arr[] according to
// the digit represented by exp.
void countSortString(vector<string> &arr, int n, int exp)
{
    vector<string> output(n); // output array
    int i, count[10] = {0};

    // Store count of occurrences in count[]
    for (i = 0; i < n; i++)
    {
        if(exp<=arr[i].size())
            count[ static_cast<int>(arr[i][arr[i].size()-exp]) - 48 ]++;
        else
            count[0]++;
    }

    // Change count[i] so that count[i] now contains actual
    //  position of this digit in output[]
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array
    for (i = n - 1; i >= 0; i--)
    {

        if(exp<=arr[i].size())
        {
            output[count[ static_cast<int>(arr[i][arr[i].size()-exp]) - 48 ] - 1] = arr[i];
            count[ static_cast<int>(arr[i][arr[i].size()-exp]) - 48 ]--;
        }

        else
        {
            output[count[0] -1] = arr[i];
            count[0]--;

        }
    }
    // Copy the output array to arr[], so that arr[] now
    // contains sorted numbers according to current digit
    for (i = 0; i < n; i++)
        arr[i] = output[i];
}


int main()
{

    int n = 20000000;
    cout<<"n="<<n<<endl;
    vector<string> unsorted(n);
    for( int i = 0; i < n; ++i ) {
        unsorted[i]=to_string( rand() % 9999999999999 + 1 );
    }

    int mx=0;
    for (int i = 1; i < n; i++)
    {    if (unsorted[i].size() > mx)
            mx = unsorted[i].size();
    }

    for (int exp = 1; exp <=mx; exp++)
        countSortString(unsorted, n, exp);

    for(int i=0;i<n;i++)
        cout<<unsorted[i]<<endl;

    cout<<endl;
    return 0;
}


