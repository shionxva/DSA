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