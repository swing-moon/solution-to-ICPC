#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <string.h>

using namespace std;
typedef long long llong;

struct BigInteger{
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    vector<int> bit;

    BigInteger(llong num = 0) { *this = num; }
    BigInteger operator= (llong num){
        bit.clear();
        do{
            bit.push_back(num % BASE);
            num /= BASE;
        }while(num > 0);
        return *this;
    }
    BigInteger operator= (const string& str){
        bit.clear();
        int x;
        int len = (str.length()-1)/WIDTH + 1;

        for(int i = 0; i < len; i++){
            int end = str.length()-i*WIDTH;
            //end :[start..end-1] end empty
            int start = max(0,end-WIDTH);
            sscanf(str.substr(start,end-start).c_str(),"%d",&x);
            bit.push_back(x);
        }
        return *this;
    }
    BigInteger operator+ (const BigInteger& b) const{
        BigInteger sum;
        sum.bit.clear();

        for(int i = 0, carry = 0; ;i++){
            if(carry == 0 && i >= bit.size() && i >= b.bit.size())
                break;

            int x = carry;
            if(i < bit.size())
                x += bit[i];
            if(i < b.bit.size())
                x += b.bit[i];

            sum.bit.push_back(x % BASE);
            carry = x / BASE;
        }
        return sum;
    }

    BigInteger operator+= (const BigInteger& b){
        *this = *this + b;
        return *this;
    }

    bool operator < (const BigInteger& b) const {
        if(bit.size() != b.bit.size())
            return bit.size() < b.bit.size();

        for(int i = bit.size()-1; i >= 0; i--){
            if(bit[i] != b.bit[i])
                return bit[i] < b.bit[i];
        }
        return false;
    }
};

ostream& operator<< (ostream &out, const BigInteger& x){
    out << x.bit.back();
    for(int i = x.bit.size()-2; i >= 0; i--){
        char buffer[20];
        sprintf(buffer,"%08d",x.bit[i]);
        for(int j = 0; j < strlen(buffer); j++)
            out << buffer[j];
    }
    return out;
}

istream& operator>> (istream &in, BigInteger& x){
    string s;
    if(!(in >> s))
        return in;
    x = s;
    return in;
}

int main(){
    int kase, pid = 0;
    cin >> kase;
    while(kase--){
        BigInteger a,b;
        cin >> a >> b;
        printf("Case %d:\n",++pid);
        cout << a << " + " << b << " = " << a+b << endl;
        if(kase != 0) printf("\n");
    }
}