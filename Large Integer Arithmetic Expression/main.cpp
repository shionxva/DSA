#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype> //handling whitespaces
using namespace std;
const int MAX_SIZE = 111;

struct BigIntError {
    string message;
};

struct BigNum{
    char digit[MAX_SIZE];
    //'123' -> digit  = 3 2 1 0 0 0
    int digitCount = 0;
    bool negative = false;
    int decimalPlaces = 0;

    BigNum() { //default constructor to prevent garbage value :c
        digitCount = 1;
        for(int i = 0; i < MAX_SIZE; i++)
            digit[i] = 0;
    }
    
    BigNum(const string& s){
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
    
    void print(ostream& out) const {
        BigNum r = round();
        if(r.negative && !(r.digitCount == 1 && r.digit[0] == 0))
            out << "-";

        int intDigits = r.digitCount - r.decimalPlaces;

        int trimmed = 0;
        if (r.decimalPlaces > 0) {
            while (trimmed < r.decimalPlaces && r.digit[trimmed] == 0)
                trimmed++;
        }

        for(int i = r.digitCount - 1; i >= trimmed; i--){
            if (r.decimalPlaces > 0 && i == r.decimalPlaces - 1)
                out << ".";
            out << (int)r.digit[i];
        }

        if (intDigits <= 0)
            out << "0";
        out << endl;
    }

    int compareABS(const BigNum& other) const{
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

    int compare(const BigNum& other) const{
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

    static void align( BigNum& a, BigNum& b) {
        int diff = a.decimalPlaces - b.decimalPlaces;

        if (diff > 0) {
            // b needs 'diff' more decimal digits (shift left = insert zeros at low end)
            for (int i = b.digitCount + diff - 1; i >= diff; i--)
                b.digit[i] = b.digit[i - diff];
            for (int i = 0; i < diff; i++)
                b.digit[i] = 0;
            b.digitCount += diff;
            b.decimalPlaces += diff;
        } else if (diff < 0) {
            diff = -diff;
            for (int i = a.digitCount + diff - 1; i >= diff; i--)
                a.digit[i] = a.digit[i - diff];
            for (int i = 0; i < diff; i++)
                a.digit[i] = 0;
            a.digitCount += diff;
            a.decimalPlaces += diff;
        }
    }

    BigNum round() const {
        BigNum r = *this;
        if (r.decimalPlaces <= 2) return r;

        // Check the third decimal digit (index decimalPlaces - 3)
        int roundDigit = r.digit[r.decimalPlaces - 3];

        // Truncate to 2 decimal places: shift digits down
        int drop = r.decimalPlaces - 2;
        for (int i = drop; i < r.digitCount; i++)
            r.digit[i - drop] = r.digit[i];
        for (int i = r.digitCount - drop; i < r.digitCount; i++)
            r.digit[i] = 0;
        r.digitCount -= drop;
        r.decimalPlaces = 2;

        if (roundDigit >= 5) {
            int carry = 1;
            for (int i = 0; i < r.digitCount && carry; i++) {
                int s = r.digit[i] + carry;
                r.digit[i] = s % 10;
                carry = s / 10;
            }
            if (carry) {
                r.digit[r.digitCount] = carry;
                r.digitCount++;
            }
        }

        if (r.digitCount == 1 && r.digit[0] == 0) r.negative = false;
        return r;
    }
    
    //arithmetics
    BigNum add(const BigNum& other) const{
        BigNum sum;
        BigNum a = *this, b = other;
        align(a, b);  
        int sumDigitCount = a.digitCount > b.digitCount ? a.digitCount : b.digitCount;
        sum.digitCount = sumDigitCount + 1;
        int car = 0;

        if(negative == b.negative){ //same sign
            for (int i = 0; i < sum.digitCount; i++){
                int r = a.digit[i] + b.digit[i] + car;
                sum.digit[i] = r % 10;
                car = r / 10;
            }

            //remove excess 0
            if(sum.digit[sum.digitCount - 1] == 0){
                sum.digitCount--;
            }
            sum.negative = a.negative;
            sum.decimalPlaces = a.decimalPlaces;
            if(sum.digitCount == 1 && sum.digit[0] == 0) sum.negative = false;
            return sum;
        }

        else{//dif sign ( + - )
            if(a.compareABS(b) >= 0){ //if this > other
                sum = a.subABS(b);
                sum.negative = a.negative;
            }
            else{
                sum = b.subABS(a);
                sum.negative = b.negative;
            }
            if(sum.digitCount == 1 && sum.digit[0] == 0) sum.negative = false;
            sum.decimalPlaces = a.decimalPlaces;
            return sum;
        }
    }

    BigNum subABS(const BigNum& other) const{ //sub WITHOUT sign
        BigNum sub;
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

    BigNum sub(const BigNum& other) const {
        BigNum temp = other;

        // flip sign of other
        temp.negative = !temp.negative;

        // now do addition
        return this->add(temp);
        //-5 - 3 -> -5 + (-3) use add instead since add already distinct sign
    }

    BigNum mul(const BigNum& other) const{
        BigNum mul;
        mul.negative = (negative != other.negative);
        mul.digitCount = digitCount + other.digitCount;
        if (mul.digitCount > MAX_SIZE) {
            throw BigIntError{"Error"};
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
        mul.decimalPlaces = decimalPlaces + other.decimalPlaces;
        return mul;
    }

    //division

    BigNum div(const BigNum& other, int precision = 10) const{
        //div by 0 error
        if(other.digitCount== 1 && other.digit[0] == 0){
            throw BigIntError{"Error"};
        }

        BigNum absThis = *this;   absThis.negative = false;
        BigNum absOther = other;  absOther.negative = false;
        align(absThis, absOther);
        // now both have equal decimalPlaces, which cancel in division
        absThis.decimalPlaces = 0;
        absOther.decimalPlaces = 0;

        BigNum current;
        BigNum quotient;

        quotient.digitCount = 0;
        int totalDigits = absThis.digitCount + precision;

        for(int i = absThis.digitCount - 1; i >= -precision; i--){
            //bring digits from other down to current one by one
            //so we need current = current * 10 + newDigit
            for(int j = current.digitCount; j > 0; j--){
                current.digit[j] = current.digit[j - 1];
            }

            // Bring down next digit (0 if we're in the decimal extension)
            current.digit[0] = (i >= 0) ? absThis.digit[i] : 0;
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
        quotient.decimalPlaces = precision;
        if (quotient.digitCount == 1 && quotient.digit[0] == 0) quotient.negative = false;
        return quotient;
    }

    //op
    BigNum op(const BigNum& other, char op) const{
        BigNum res;
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
    string s;
    int pos = 0;
    BigNum result;

    //constructor
    Parser(const string& s){
        this->s = s;
        result = this->parseExpression();
    };

    BigNum parseNumber()
    {
        string num = "";;

        // Read consecutive digits
        while(pos < s.length() && isdigit(s[pos])){
            num += s[pos];
            pos++;
        }

        if (num == ""){
            throw BigIntError{"Error"};
        }

        return BigNum(num);
    }

    BigNum parseExpression(){
        // Parse the first term
        BigNum left = parseTerm();

        // Continue while we see + or -
        while(pos < s.length() && (s[pos] == '+' || s[pos] == '-')){
            char op = s[pos];
            pos++;

            // Parse the next term
            BigNum right = parseTerm();

            // Apply operation
            left = left.op(right, op);
        }
        return left;
    }

    BigNum parseTerm(){
        // Parse the first factor
        BigNum left = parseFactor();

        // Continue while we see + or -
        while(pos < s.length() && (s[pos] == '*' || s[pos] == '/')){
            char op = s[pos];
            pos++;

            // Parse the next term
            BigNum right = parseFactor();

            // Apply operation
            left = left.op(right, op);
        }
        return left;
    }

    BigNum parseFactor(){
        // unary minus
        if(pos < s.length() && s[pos] == '-'){
            pos++;
            BigNum val = parseFactor();

            // flip sign
            if(!(val.digitCount == 1 && val.digit[0] == 0)){
                val.negative = !val.negative;
            }
            return val;
        }

        if(pos < s.length() && s[pos] == '('){
            pos++; //skip start paren
            BigNum val = parseExpression();

            if (pos >= s.length() || s[pos] != ')'){
                throw BigIntError{"Error"};
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
            cout    << e.message << endl;
            outFile << e.message << endl;
        }
    }
    outFile.close();
    fin.close();
    return 0;
}