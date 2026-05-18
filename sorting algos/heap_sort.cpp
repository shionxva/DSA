#include <iostream>
using namespace std;

void heapify(int a[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    // check left child
    if(left < n && a[left] > a[largest])
        largest = left;

    // check right child
    if(right < n && a[right] > a[largest])
        largest = right;

    // swap and continue heapifying if needed
    if(largest != i)
    {
        swap(a[i], a[largest]);
        heapify(a, n, largest);
    }
}

void heapSort(int a[], int n)
{
    // build max heap
    for(int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);

    // extract elements one by one
    for(int i = n - 1; i > 0; i--)
    {
        swap(a[0], a[i]);   // move current max to end
        heapify(a, i, 0);   // restore heap
    }
}

void printArray(int a[], int n)
{
    for(int i = 0; i < n; i++)
        cout << a[i] << " ";

    cout << endl;
}

int main()
{
    int arr[8] = {7, 2, 1, 5, 3, 6, 19, 9};
    int n = 8;

    heapSort(arr, n);

    cout << "heap sorted:\n";
    printArray(arr, n);

    return 0;
}