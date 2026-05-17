#include <iostream>
using namespace std;

int RbinarySearch(int a[], int left, int right, int k)
{
    if(left > right)
        return -1;
    int mid = (left + right)/2;
    if(a[mid] == k)
        return mid;
    if(k > a[mid])
        return RbinarySearch(a, mid+1, right, k);
    return RbinarySearch(a, left, mid-1, k);
}

int NRbinarySearch(int a[], int n, int k) {
    int result = -1, left = 0, right = n - 1;
    while(left <= right){
        int mid = (left + right)/2;
        
        if(a[mid] == k){
            result = mid;
            break;
        }
        if(k > a[mid])
            left = mid + 1;
        else
            right = mid - 1;
    }
    return result; 
}

int main()
{
    int arr[8] = {1,2,3,5,6,7,9,19}; //array must be sorted
    
    int n = 8; //array size
    int left = 0;
    int right = n - 1;
    
    int res1 = RbinarySearch(arr, left, right, 6);
    int res2 = NRbinarySearch(arr, n, 6);
    
    cout << "Recursive BSearch: "<< res1 << endl;
    cout << "Non-Recursive BSearch: "<< res1 << endl;
    return 0;
}