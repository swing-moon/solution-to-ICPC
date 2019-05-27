#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;
const int MAXNUM = 0x3f3f3f3f;
long RM;
long patHash;
long Q;
const int R = 256;

bool isPrime(int val) {
    if(val == 2 || val == 3) return 1;
    for(int i = 2; i * i <= val; i++) {
        if(val % i == 0) return 0;
    }
    return 1;
}

int getMaxPrime(int n) {
    for(int i = n; i >= 2; i--) {
        if(isPrime(i)) return i;
    }
    return 2;
}

// random longest Prime

long Hash(const string& str, int len, long Q) {
    long h = 0;
    for(int i = 0; i < len; i++) {
        h = (h * R + str[i]) % Q;
    }
    return h;
}

// method:

void RabinKarp(const string& pat) {
    Q = getMaxPrime(MAXNUM);
    RM = 1;
    for(int i = 1; i <= pat.length()-1; i++)
        RM = (R * RM) % Q;

    patHash = Hash(pat, pat.length(), Q);
}

int search(const string& txt, const string& pat) {
    //
    long txtHash = Hash(txt, pat.length(), Q);
    // is pat.length(), not txt.length()

    if(txtHash == patHash) return 0;

    int len1 = pat.length(), len2 = txt.length();
    for(int i = len1; i < len2; i++) {
        txtHash = (txtHash + Q - txt[i-len1]* RM % Q) % Q;
        txtHash = (txtHash * R + txt[i]) % Q;

        if(txtHash == patHash) return i - len1 + 1;
    }
    return len2;
}

int main() {
    freopen("input.txt", "r", stdin);
    string txt, pat;
    cin >> txt >> pat;
    printf("指针的位置在：");
    RabinKarp(pat);
    cout << search(txt, pat) << endl;
}