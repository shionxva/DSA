#include <iostream>
using namespace std;

int linearSearch(int a[], int n, int k) {
    int position = -1;
    for(int i=0;i<n;i++){
        if(a[i] == k){
            position = i;
            break;
        }
    }
    return position; 
}

int sentinelLinearSearch(int a[], int n, int k)
{
    int last = a[n - 1];   // save last element
    a[n - 1] = k;          // place sentinel

    int i = 0;
    while (a[i] != k)
        i++;

    a[n - 1] = last;       // restore last element

    // check if found before last position
    // or if original last element was k
    if (i < n - 1 || last == k)
        return i;

    return -1;
}

int main()
{
    int arr[8] = {7,2,1,5,3,6,19,9};
    int res1 = linearSearch(arr, 8, 20);
    int res2 = sentinelLinearSearch(arr, 8, 19);
    cout << "Linear Search: "<< res1 << endl;
    cout << "Sentinel Linear Search: "<< res2 << endl;
    return 0;
}