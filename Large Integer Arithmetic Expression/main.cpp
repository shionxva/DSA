#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;
const int MAX_SIZE = 101;

struct BigInteger{
    char digit[MAX_SIZE];
    //'123' -> digit  = 3 2 1 0 0 0
    int digitCount = 0;


    BigInteger() { //default constructor to prevent garbage value :c
        digitCount = 1;

        for(int i = 0; i < MAX_SIZE; i++)
            digit[i] = 0;
    }
    
    BigInteger(const string& s){
        digitCount = s.length();
        for(int i=0; i<digitCount; i++){
            digit[i] = s[digitCount - i -1] -'0'; 
        }
        for(int i=digitCount; i < MAX_SIZE; i++) digit[i] = 0;
    }
    
    void print() const{
        for(int i = digitCount - 1; i >= 0; i--)
            cout << (int)digit[i];
        cout << endl;
    }
    
    //arithmetics
    BigInteger add(const BigInteger& other){
        BigInteger sum;
        int sumDigitCount = digitCount > other.digitCount ? digitCount : other.digitCount;
        sum.digitCount = sumDigitCount + 1;
        int car = 0;
        for (int i = 0; i < sum.digitCount; i++){
            int r = digit[i] + other.digit[i] + car;
            sum.digit[i] = r % 10;
            car = r / 10;
        }
        
        //remove excess 0
        if(sum.digit[sum.digitCount - 1] == 0){
            sum.digitCount--;
        }
        return sum;
    }

    BigInteger sub(const BigInteger& other){
        BigInteger sub;
        sub.digitCount = digitCount;

        int borrow = 0;

        for(int i = 0; i < digitCount; i++){
            int d1 = digit[i] - borrow;
            int d2 = other.digit[i];

            if(d1 < d2){
                d1 += 10;
                borrow = 1;
            }
            else{
                borrow = 0;
            }

            sub.digit[i] = d1 - d2;
        }

        //multiple leading 0's case
        while(sub.digitCount > 1 && sub.digit[sub.digitCount - 1] == 0){
            sub.digitCount--;
        }

        return sub;
    }

    BigInteger mul(const BigInteger& other){
        BigInteger mul;

        mul.digitCount = digitCount + other.digitCount;

        for(int i = 0; i < digitCount; i++){
            int carry = 0;
            for(int j = 0; j < other.digitCount; j++){
                int r = mul.digit[i + j] + digit[i] * other.digit[j] + carry;
                mul.digit[i + j] = r % 10;
                carry = r / 10;
            }

            mul.digit[i + other.digitCount] += carry;
        }

        //similar to subtraction
        while(mul.digitCount > 1 && mul.digit[mul.digitCount - 1] == 0){
            mul.digitCount--;
        }

        return mul;
    }

    //division

    int compare(const BigInteger& other) const{

        //compare len
        if(digitCount > other.digitCount) return 1;
        if(digitCount < other.digitCount) return -1;

        //if same len compare most significant digit value
        for(int i = digitCount - 1; i >= 0; i--){
            if(digit[i] > other.digit[i]) return 1;
            if(digit[i] < other.digit[i]) return -1;
        }

        return 0;
    }

    BigInteger div(const BigInteger& other){
        //div by 0 error
        if(other.digitCount== 1 && other.digit[0] == 0){
            cout << "Error: division by zero" << endl;
            return BigInteger("0");
        }

        BigInteger current;
        BigInteger quotient;

        quotient.digitCount = 0;

        for(int i = digitCount - 1; i >= 0; i--){

            //bring digits from other down to current one by one
            //so we need current = current * 10 + newDigit

            for(int j = current.digitCount; j > 0; j--){
                current.digit[j] = current.digit[j - 1];
            }
            current.digit[0] = digit[i];
            current.digitCount++;

            // remove leading zeros
            while(current.digitCount > 1 && current.digit[current.digitCount - 1] == 0){
                current.digitCount--;
            }

            int qdigit = 0;

            while(current.compare(other) >= 0){
                current = current.sub(other);
                qdigit++;
            }

            quotient.digit[quotient.digitCount] = qdigit;
            quotient.digitCount+= 1;
        }
        
        // because quotient is stored fowared direction we need to reverse the position
        for(int i = 0; i < quotient.digitCount / 2; i++){
            swap(quotient.digit[i], quotient.digit[quotient.digitCount - i - 1]);
        }

        // remove excess 0 again
        while(quotient.digitCount > 1 && quotient.digit[quotient.digitCount - 1] == 0){
            quotient.digitCount--;
        }

        return quotient;
    }

    //op
    BigInteger op(const BigInteger& other, char op){
        BigInteger res;
        if(op == '+'){
            res = this->add(other);
        }
        if(op == '-'){
            res = this->sub(other);
        }
        if(op == '*'){
            res = this->mul(other);
        }
        if(op == '/'){
            res = this->div(other);
        }
        return res;
    }

};

struct Parser{

    //expression := term { (+|-) term } term := factor { (*|/) factor } factor := number | '(' expression ')'
    string s;
    int pos = 0;
    BigInteger result;

    //constructor
    Parser(const string& s){
        this->s = s;
        result = this->parseExpression();
    };

    BigInteger parseNumber()
    {
        string num = "";;

        // Read consecutive digits
        while(pos < s.length() && isdigit(s[pos])){
            num += s[pos];
            pos++;
        }

        if (num == ""){
            cout<< "error number parser" << endl;
            exit(1);
        }

        return BigInteger(num);
    }

    BigInteger parseExpression(){
        // Parse the first term
        BigInteger left = parseTerm();

        // Continue while we see + or -
        while(pos < s.length() && (s[pos] == '+' || s[pos] == '-')){
            char op = s[pos];
            pos++;

            // Parse the next term
            BigInteger right = parseTerm();

            // Apply operation
            left = left.op(right, op);
        }
        return left;
    }

    BigInteger parseTerm(){
        // Parse the first factor
        BigInteger left = parseFactor();

        // Continue while we see + or -
        while(pos < s.length() && (s[pos] == '*' || s[pos] == '/')){
            char op = s[pos];
            pos++;

            // Parse the next term
            BigInteger right = parseFactor();

            // Apply operation
            left = left.op(right, op);
        }
        return left;
    }

    BigInteger parseFactor(){
        if(pos < s.length() && s[pos] == '('){
            pos++; //skip start paren
            BigInteger val = parseExpression();

            if (pos >= s.length() || s[pos] != ')'){
            cout<< "error factor parser" << endl;
            exit(1);
            }

            pos++; //skip end paren
            return val;
        }
        else{
            return parseNumber();
        }
    }
};

int main()
{
    ifstream fin("tests.txt");

    // string n1, n2;
    // char op;

    // while(fin >> n1 >> op >> n2)
    // {
    //     BigInteger num1(n1);
    //     BigInteger num2(n2);

    //     num1.print();
    //     cout << op << endl;
    //     num2.print();
    //     cout << "---------" << endl;

    //     BigInteger result = num1.op(num2, op);
    //     cout << endl;
    // }

    string exp;
    while(getline(fin, exp)){
        cout << exp << endl;
        cout<< "-------:3--------" << endl;
        Parser parse(exp);
        parse.result.print();
        cout<<endl;
    }

    fin.close();

    return 0;
}