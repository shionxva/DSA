#include <iostream>
using namespace std;

int linearSearch(int a[], int n, int k) {
    int position = -1;
    for(int i=0;i<n;i++){
        if(a[i] == k){
            position =i;
            break;
        }
    }
    
    return position; 
}

int main()
{
    int arr[8] = {7,2,1,5,3,6,19,9};
    int position = linearSearch(arr, 8, 5);
    cout << position << endl;
    return 0;
}