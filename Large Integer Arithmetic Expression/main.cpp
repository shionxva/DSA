#include <iostream>
using namespace std;
const int MAX_SIZE = 101;

struct BigInteger
{
    char digit[MAX_SIZE];
    //'123' -> digit  = 3 2 1 0 0 0
    int digitCount = 0;
    BigInteger() {};
    
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
        //sum = digit1[i] + digit2[i] + car
        //sum[i] = sum % 10
        //car = sum // 10
        for (int i = 0; i < sum.digitCount; i++){
            int s = digit[i] + other.digit[i] + car;
            sum.digit[i] = s % 10;
            car = s / 10;
        }
        
        //remove excess 0
        if(sum.digit[sum.digitCount - 1] == 0){
            sum.digitCount--;
        }
        return sum;
    }
};

int main()
{
    BigInteger num1("999"), num2("23");
    num1.print(), num2.print();
    BigInteger sum = num1.add(num2);
    //print();
    sum.print();

    return 0;
}