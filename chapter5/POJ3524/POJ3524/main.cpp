//
//  main.cpp
//  POJ3524
//
//  Created by zhangmin chen on 2019/5/18.
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

const int inf = 0x3f3f3f3f;
const int maxn = 256;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

class Array {
public:
    int len;
    map<int, int> val;
    
    void remove() {
        len = -1;
        val.clear();
    }
    
    Array() { remove(); }
    
    void resz(int sz) {
        len = sz;
        val.clear();
    }
    
    bool declare() {
        return len >= 0;
    }
    
    bool exist(int id) {
        if(val.count(id)) return true;
        else return false;
    }
    
    bool assign(int idx, int v) {
        if(idx >= len) return false;
        val[idx] = v;
        return true;
    }
};

Array arr[maxn];

// string a[] = xxx
int IDX(const string& str, int p, bool& bugfree) {
    if(isdigit(str[p])) {
        int ans = 0;
        while(isdigit(str[p])) {
            ans = ans * 10 + str[p] - '0';
            p++;
        }
        return ans;
    }
    else if(isalpha(str[p])) {
        // str[p]: name
        char c = str[p];
        int id = IDX(str, p+2, bugfree);
        
        Array& ar = arr[c];
        if(ar.declare()) {
            //
            // if exist arr[c].val[idx], return value of val[idx]
            // else bugfree = false
            if(id < ar.len && ar.exist(id)) return ar.val[id];
            else bugfree = 0;
        }
        else bugfree = 0;
    }
    
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    
    int bugL = 0, L = 0;
    string line;
    
    while(getline(cin, line)) {
        if(line[0] == '.') {
            if(L) printf("%d\n", bugL);
            _for(i, 0, maxn) arr[i].remove();
            bugL = 0; L = 0;
            continue;
        }
        if(bugL) continue;
        
        int p = (int)line.find('=');
        if(p != string::npos) {
            //
            bool bugfree = true;
            string lhs = line.substr(0, p);
            
            int idx = IDX(lhs, 2, bugfree);
            int rhs = IDX(line, p+1, bugfree);
            
            Array& ar = arr[line[0]];
            if(bugfree && ar.declare() && ar.assign(idx, rhs)) L++;
            else bugL = L + 1;
            
        }
        else {
            // declare but not init
            char name;
            int idx;
            sscanf(line.c_str(), "%c[%d]", &name, &idx);
            arr[name].resz(idx);
            L++;
        }
    }
}
