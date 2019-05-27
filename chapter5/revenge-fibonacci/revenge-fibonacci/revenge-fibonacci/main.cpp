//
//  main.cpp
//  revenge-fibonacci
//
//  Created by zhangmin chen on 2018/8/20.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#include <sstream>

using namespace std;

const int BASE = 10000;

template<int MaxNode, int Sigma_size>
struct Trie {
    int ch[MaxNode][Sigma_size], val[MaxNode], sz;
    Trie() {
        sz = 1;
        memset(ch[0], 0, sizeof(ch[0]));
        memset(val, 0, sizeof(val));
    }
    
    int idx(char c) const {  return c - '0';  }
    
    void insert(const string& s, int v) {
        int u = 0, n = s.size();
        for(int i = 0; i < n; i++) {
            int c = idx(s[i]);
            if(!ch[u][c]) {
                memset(ch[sz], 0, sizeof(ch[sz]));
                val[sz] = v;
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        if(!val[u])
            val[u] = v;
        
//        cout << "insert - " << s << ",u = " << u << " , v = " << val[u] << endl;
    }
    
    int getValue(const string& s) const {
        int v = -1, u = 0, n = s.size();
        for(int i = 0; i < n; i++) {
            int c = idx(s[i]);
            if(!ch[u][c])   return v;
            u = ch[u][c];
        }
//        cout << "getvalue " << s << ", u = " << u << " ,v = " << val[u] << endl;
        if(val[u])  v = val[u];
        return v;
    }
};
//data in trie is reversed!

const int MAXLEN = 6000, MAXF = 100000;
template<int maxn>
struct Bign {
    int len, s[maxn];
    Bign() {  memset(s, 0, sizeof(s));  len = 1;  }
    Bign& operator = (int num) {
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
    
    Bign& operator = (const Bign& rhs) {
        len = rhs.len;
        copy(rhs.s, rhs.s+rhs.len, s);
        return *this;
    }
    Bign(int num) { *this = num; }
};
typedef Bign<MAXLEN> fBig;

ostream& operator<< (ostream& os, const fBig& x) {
    char buf[8];
    stringstream ss;
    bool first = true;
    for(int i = x.len-1; i >= 0; i--) {
        if(first) {
            first = false;
            ss << x.s[i];
        } else {
            sprintf(buf, "%04d", x.s[i]);
            ss << buf;
        }
    }
    
    const string& s = ss.str();
    if(s.empty())   return os << 0;
    return os << s;
}

void Add(const fBig& a, const fBig& b, fBig& c) {
    int *c_res = c.s;
    int l = 0;
    int rLen = max(a.len, b.len);
    for(int i = 0, carry = 0; carry || i < rLen; i++) {
        int x = carry;
        if(i < a.len)   x += a.s[i];
        if(i < b.len)   x += b.s[i];
        c_res[l++] = x % BASE;
        carry = x / BASE;
    }
    c.len = l;
}

string savedata(const fBig& f) {
    //we want to save f to trie tree
    //it must be reversed!
    int len = 41;
    int olen = 0;
    char buf[8];
    stringstream ss;
    bool first = true;
    for(int i = 0; i < f.len; i++) {
        if(first) {
            first = false;
            sprintf(buf, "%d", f.s[f.len-1-i]);
        } else {
            sprintf(buf, "%04d", f.s[f.len-1-i]);
        }
        ss << buf;
        olen += strlen(buf);
        if(olen >= 41)  break;
    }
    return ss.str();
}

fBig f0 = 0, f1 = 1, f;
Trie<3817223, 10> fseq;


int main() {
    for(int i = 2; i < MAXF; i++) {
        Add(f0, f1, f);
        string cur = savedata(f);
        fseq.insert(cur, i-1);
        f0 = f1;
        f1 = f;
    }
    
    int T;
    scanf("%d", &T);
    char buf[60];
    for(int t = 1; t <= T; t++) {
        scanf("%s",buf);
        int ans = 0;
        string p(buf);
        // prefix of buf --> search in trie --> we will get suffix
        // the last char of the string!
        if(p != "1")    ans = fseq.getValue(p);
        printf("Case #%d: %d\n", t, ans);
    }
}
