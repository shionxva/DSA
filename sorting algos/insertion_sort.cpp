#include <iostream>
using namespace std;

void insertionSort(int arr[], int n){
    //sorted
    for(int i = 0; i < n; i++){
        //shift right array
        int tempKey = arr[i];
        int j = i - 1;
        //logic for ascending sort
        while(j >= 0 && arr[j] > tempKey){
            arr[j+1] = arr[j];
            j--;
        }
        // if the value is no longer > key replace that pos with key val
        arr[j+1] = tempKey;
    }
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main()
{
    int arr[10] = {10,8,2,7,14,6,9,3,0,25};
    insertionSort(arr, 10);
    printArray(arr, 10);

    return 0;
}