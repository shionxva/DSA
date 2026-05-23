#include <iostream>
#include <stack>
using namespace std;

int main()
{
    stack<int> s;
    int A[5] = {4, 8, 5, 2, 25};
    int result[5];
    
    for (int i =0; i < 5; i++){
        if (s.empty()){
            s.push(i);
        }
        
        else{
            while( !s.empty() && A[s.top()] > A[i]){
                result[s.top()] = A[i];
                s.pop();
            }
            s.push(i);
        }
    }
    
    while(!s.empty()){
        result[s.top()] = -1;
        s.pop();
    }
    
    for (int x : result){
        cout << x << endl;
    }
    return 0;
}

/* Explanation
i   A[i]    Stack(indices)  Action
0    4       [0]            Stack empty → push 0
1    8       [0, 1]         A[0]=4 < A[1]=8, no pop → push 1
2    5       [0, 2]         A[1]=8 > 5 → result[1]=5, pop; A[0]=4 < 5, stop → push 2
3    2       [3]            A[2]=5 > 2 → result[2]=2, pop; A[0]=4 > 2 → result[0]=2, pop → push 3
4    25      [3, 4]         A[3]=2 < 25, no pop → push 4

After the loop, remaining indices {3, 4} have no smaller element → result = -1
*/