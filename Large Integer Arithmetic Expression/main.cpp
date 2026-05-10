#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype> //handling whitespaces
using namespace std;
const int MAX_SIZE = 101;

struct BigIntError {
    string message;
};

struct BigInteger{
    char digit[MAX_SIZE];
    //'123' -> digit  = 3 2 1 0 0 0
    int digitCount = 0;
    bool negative = false;

    BigInteger() { //default constructor to prevent garbage value :c
        digitCount = 1;
        for(int i = 0; i < MAX_SIZE; i++)
            digit[i] = 0;
    }
    
    BigInteger(const string& s){
        int start = 0;
        if(s[0] == '-'){
            negative = true;
            start = 1;
        }
        digitCount = s.length() - start;

        for(int i = 0; i < digitCount; i++){
            digit[i] = s[s.length() - i - 1] - '0';
        }

        for(int i = digitCount; i < MAX_SIZE; i++){
            digit[i] = 0;
        }
    }
    
    void print(ostream& out) const{
        if(negative && !(digitCount == 1 && digit[0] == 0)){
            out << "-";
        }
        for(int i = digitCount - 1; i >= 0; i--){
            out << (int)digit[i];
        }
        out << endl;
    }

    int compareABS(const BigInteger& other) const{
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

    int compare(const BigInteger& other) const{
        // positive > negative
        if(!negative && other.negative) return 1;
        // negative < positive
        if(negative && !other.negative) return -1;
        // both positive
        if(!negative && !other.negative){
            return compareABS(other);
        }
        // both negative then we reverse
        return -compareABS(other);
    }
    
    //arithmetics
    BigInteger add(const BigInteger& other) const{
        BigInteger sum;
        int sumDigitCount = digitCount > other.digitCount ? digitCount : other.digitCount;
        sum.digitCount = sumDigitCount + 1;
        int car = 0;

        if(negative == other.negative){ //same sign
            for (int i = 0; i < sum.digitCount; i++){
                int r = digit[i] + other.digit[i] + car;
                sum.digit[i] = r % 10;
                car = r / 10;
            }

            //remove excess 0
            if(sum.digit[sum.digitCount - 1] == 0){
                sum.digitCount--;
            }
            sum.negative = negative;
            if(sum.digitCount == 1 && sum.digit[0] == 0) sum.negative = false;
            return sum;
        }

        else{//dif sign ( + - )
            if(compareABS(other) >= 0){ //if this > other
                sum = this->subABS(other);
                sum.negative = negative;
            }
            else{
                sum = other.subABS(*this);
                sum.negative = other.negative;
            }
            if(sum.digitCount == 1 && sum.digit[0] == 0) sum.negative = false;
            return sum;
        }
    }

    BigInteger subABS(const BigInteger& other) const{ //sub WITHOUT sign
        BigInteger sub;
        sub.digitCount = digitCount;

        int borrow = 0;

        for(int i = 0; i < digitCount; i++){
            int d1 = digit[i] - borrow;
            int d2 = (i < other.digitCount) ? other.digit[i] : 0;

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

    BigInteger sub(const BigInteger& other) const {
        BigInteger temp = other;

        // flip sign of other
        temp.negative = !temp.negative;

        // now do addition
        return this->add(temp);
        //-5 - 3 -> -5 + (-3) use add instead since add already distinct sign
    }

    BigInteger mul(const BigInteger& other) const{
        BigInteger mul;
        mul.negative = (negative != other.negative);
        mul.digitCount = digitCount + other.digitCount;
        if (mul.digitCount > MAX_SIZE) {
            throw BigIntError{"result exceeds maximum digit size"};
        }

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
        if (mul.digitCount == 1 && mul.digit[0] == 0) mul.negative = false;
        return mul;
    }

    //division

    BigInteger div(const BigInteger& other) const{
        //div by 0 error
        if(other.digitCount== 1 && other.digit[0] == 0){
            throw BigIntError{"division by zero"};
        }

        BigInteger absThis = *this;   absThis.negative = false;
        BigInteger absOther = other;  absOther.negative = false;

        BigInteger current;
        BigInteger quotient;

        quotient.digitCount = 0;

        for(int i = absThis.digitCount - 1; i >= 0; i--){
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

            while(current.compareABS(absOther) >= 0){
                current = current.subABS(absOther);
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

        quotient.negative = (negative != other.negative);
        if (quotient.digitCount == 1 && quotient.digit[0] == 0) quotient.negative = false;
        return quotient;
    }

    //op
    BigInteger op(const BigInteger& other, char op) const{
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

/*expression = 
    term
    | expression "+" term
    | expression "-" term .
term = 
    factor
    | term "*" factor
    | term "/" factor .
factor = 
    number
    | "(" expression ")" .*/

struct Parser{
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
            throw BigIntError{"number parser"};
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
        // unary minus
        if(pos < s.length() && s[pos] == '-'){
            pos++;
            BigInteger val = parseFactor();

            // flip sign
            if(!(val.digitCount == 1 && val.digit[0] == 0)){
                val.negative = !val.negative;
            }
            return val;
        }

        if(pos < s.length() && s[pos] == '('){
            pos++; //skip start paren
            BigInteger val = parseExpression();

            if (pos >= s.length() || s[pos] != ')'){
                throw BigIntError{"factor parser"};
            }

            pos++; //skip end paren
            return val;
        }
        else{
            return parseNumber();
        }
    }
};


int main(int argc, char* argv[])
{
    string file_name = argv[0];
    string input_file  = argv[1];
    string output_file = argv[2];
    
    ifstream fin(input_file);
    ofstream outFile(output_file);
    if (!fin) { cerr << "Error: cannot open " << input_file << "\n"; return 1; }

    string exp;
    while (getline(fin, exp)) {
        exp.erase(remove_if(exp.begin(), exp.end(),[](unsigned char ch){ return isspace(ch); }), exp.end());
        try {
            Parser parse(exp);
            parse.result.print(cout);
            parse.result.print(outFile);
        } catch (const BigIntError& e) {
            cout    << "Error: " << e.message << " from: " << exp << endl;
            outFile << "Error: " << e.message << " from: " << exp << endl;
        }
    }
    outFile.close();
    fin.close();
    return 0;
}