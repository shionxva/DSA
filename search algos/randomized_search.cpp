#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int randomizedSearch(int a[], int n, int k)
{
    int i = rand() % n;
    int count = 0;

    while(count < pow(n, 0.9))
    {
        if(a[i] == k)
            return i;
        i = rand() % n;
        count++;
    }

    return -1;
}

int main()
{
    //seed
    srand(time(0));
    
    int arr[8] = {1,2,3,5,6,7,9,19};

    int res1 = randomizedSearch(arr, 8, 6);

    cout << "Random Search: " << res1 << endl;

    return 0;
}