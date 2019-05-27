//
//  main.cpp
//  UVA12333
//
//  Created by zhangmin chen on 2019/5/7.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;
typedef long long llong;
typedef set<string>::iterator ssii;

const int BASE = 10000;
const int MAXLEN = 6000;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

template <int maxn>
class BigInt {
public:
    int len, s[maxn];
    BigInt() {
        Set(s, 0);
        len = 1;
    }
    
    BigInt& operator= (int num) {
        if(num == 0) {
            len = 1;
            return *this;
        }
        
        len = 0;
        while(num > 0) {
            s[len++] = num % BASE;
            num /= BASE;
        }
        return *this;
    }
    
    BigInt& operator= (const BigInt& rhs) {
        len = rhs.len;
        copy(rhs.s, rhs.s + rhs.len, s);
        return *this;
    }
    
    BigInt(int num) {
        *this = num;
    }
};

typedef BigInt<MAXLEN> fBig;

string Reverse(const fBig& fi) {
    int tot = 0;
    char buf[8];
    
    stringstream ss;
    bool first = true;
    for(int i = 0; i < fi.len; i++) {
        if(first) {
            first = false;
            sprintf(buf, "%d", fi.s[fi.len - 1 - i]);
        } else sprintf(buf, "%04d", fi.s[fi.len - 1 - i]);
        
        ss << buf;
        tot += strlen(buf);
        if(tot >= 41) break;
    }
    return ss.str();
}


template <int maxNode, int sigmaSize>
class Trie {
public:
    int ch[maxNode][sigmaSize], val[maxNode];
    int sz;
    
    Trie() {
        Set(ch[0], -1);
        Set(val, 0);
        sz = 1;
    }
    
    int idx(char c) const { return c - '0'; }
    
    void insert(const string& str, int v) {
        int u = 0;
        for(int i = 0; i < str.length(); i++) {
            //
            int c = idx(str[i]);
            if(ch[u][c] == -1) {
                //
                Set(ch[sz], -1);
                val[sz] = v;
                ch[u][c] = sz++;
            }
            
            u = ch[u][c];
        }
        
        val[u] = v;
    }
    
    int getVal(const string& str) const {
        int v = -1, u = 0;
        for(int i = 0; i < str.length(); i++) {
            //
            int c = idx(str[i]);
            if(ch[u][c] == -1) return v;
            u = ch[u][c];
        }
        
        if(val[u]) v = val[u];
        return v;
    }
    
};

void Add(const fBig& f1, const fBig& f2, fBig& f3) {
    
    int len = max(f1.len, f2.len);
    
    int p = 0;
    for(int i = 0, carry = 0; ; i++) {
        if(carry == 0 && i >= len) break;
        int x = carry;
        if(i < f1.len) x += f1.s[i];
        if(i < f2.len) x += f2.s[i];
        
        f3.s[p++] = x % BASE;
        carry = x / BASE;
    }
    f3.len = p;
}

/*
ostream& operator<< (ostream& os, const fBig& fi) {
    char buf[8];
    stringstream ss;
    bool first = true;
    for(int i = fi.len - 1; i >= 0; i--) {
        if(first) {
            first = false;
            ss << fi.s[i];
        } else {
            sprintf(buf, "%04d", fi.s[i]);
            ss << buf;
        }
    }
    const string& str = ss.str();
    if(str.empty()) return os << 0;
    return os << str;
}
 */

Trie<4000000, 10> trie;
fBig f0 = 0, f1 = 1, f;
const int MAXF = 100000;

int main() {
    freopen("input.txt", "r", stdin);
    for(int i = 2; i < MAXF; i++) {
        Add(f0, f1, f);
        string rev = Reverse(f);
        
        trie.insert(rev, i-1);
        f0 = f1;
        f1 = f;
    }
    
    int kase;
    scanf("%d", &kase);
    char buf[60];
    for(int k = 1; k <= kase; k++) {
        scanf("%s", buf);
        int ans = 0;
        string str(buf);
        if(str != "1") ans = trie.getVal(str);
        printf("Case #%d: %d\n", k, ans);
    }
}
