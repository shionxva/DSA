/*  this implement both stack and queue data struct
    as stack -> reverse order 
    and queue -> preserve it
*/
#include <iostream>
#include <stack>
#include <queue>
#include <cctype>
using namespace std;

bool isPalindrome(const string& str) {
    stack<char> s;
    queue<char> q;
    
    for (char ch : str) {
        if (isalnum(ch)) {
            char lower = tolower(ch);
            s.push(lower);
            q.push(lower);
        }
    }
    
    while (!s.empty()) {
        if (s.top() != q.front())
            return false;
        s.pop();
        q.pop();
    }
    return true;
}

int main() {
    string input;
    cout << "Enter a string: ";
    getline(cin, input);
    
    if (isPalindrome(input))
        cout << "The string is a palindrome.\n";
    else
        cout << "The string is not a palindrome.\n";
    return 0;
}