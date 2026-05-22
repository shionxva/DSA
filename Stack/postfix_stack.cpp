#include <iostream>
#include <stack>
#include <string>
using namespace std;

int evalPostfix(string exp) {
    stack<int> s;
    for(int i = 0; i < exp.length(); i++){
        char c = exp[i];
        if(c == ' ') continue;
        if(isdigit(c)){
            s.push(c - '0');
        }
        else{
            int val1 = s.top(); s.pop();
            int val2 = s.top(); s.pop();
            switch(c){
                case '+':
                    s.push(val2 + val1);
                    break;
                case '-':
                    s.push(val2 - val1);
                    break;
                case '*':
                    s.push(val2 * val1);
                    break;
                case '/':
                    s.push(val2 / val1);
                    break;
            }
        }
    }
    return s.top();
}

int getPrecedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

string inToPosFix(string exp){
    stack<char> op;
    string output = "";
    
    for(int i =0; i < exp.length(); i++){
        char c = exp[i];
        if (c == ' ') continue;
        if(isdigit(c)){
            output+= c;
        }
        
        else if (c == '(') {
            op.push(c);
        }
        else if (c == ')') {
            while (!op.empty() && op.top() != '(') {
                output += op.top(); op.pop();
            }
            if (!op.empty()) op.pop();
        }
        
        else{
            while (!op.empty() && op.top() != '(' && getPrecedence(op.top()) >= getPrecedence(c)){
                output+= op.top(); op.pop();
            }
            op.push(c);
        }
    }    
    while (!op.empty()) {
        output += op.top();
        op.pop();
    }
    return output;
}


int main() {
    string exp = "1 2 4 * + 3 -";
    cout << "Expression: " << exp << endl;
    cout << "And the result isss : " << evalPostfix(exp) << endl;
    
    string exp2 = "2 * (4 + 8)";
    cout << "Expression: " << exp2 << endl;
    cout << "In -> Postfix result isss : " << inToPosFix(exp2) << endl;
    return 0;
}