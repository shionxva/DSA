#include <iostream>
using namespace std;

void swap(int &a, int &b){
    int c = a;
    a = b;
    b = c;
}

void selectionSort(int arr[], int n){
    for (int i=0; i<n-1; i++){
        int minIDX = i;
        int min = arr[i];
        for (int j = i+1; j < n; j++){
            if (arr[j] <= min){
                minIDX = j;
                min = arr[minIDX];
            }
        }
        swap(arr[i], arr[minIDX]);
    }
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n ; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main()
{
    int arr[10] = {10,8,2,7,14,6,9,3,0,25};
    selectionSort(arr, 10);
    printArray(arr, 10);

    return 0;
}