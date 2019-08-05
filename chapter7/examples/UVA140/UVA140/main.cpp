//
//  main.cpp
//  UVA140
//
//  Created by zhangmin chen on 2019/6/20.
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

const int maxn = 10;
const int maxc = 256;
const int maxl = 1000 + 10;

int letter[maxn], id[maxc];

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

vector<int> u;
map<int, vector<int> > v;



char str[maxl];



int read() {
    int n = 0;
    for(char c = 'A'; c <= 'Z'; c++) {
        if(strchr(str, c) != NULL) {
            id[c] = n++;
            letter[id[c]] = c;
        }
    }
    
    int p = 0, q = 0;
    int len = (int)strlen(str);
    for(;;) {
        while(p < len && str[p] != ':') p++;
        if(p == len) break;
        
        while(q < len && str[q] != ';') q++;
        u.push_back(id[str[p-1]]);
        
        _for(i, p+1, q) {
            v[id[str[p-1]]].push_back(id[str[i]]);
        }
        
        p++;
        q++;
    }
    return n;
}

int N, ans;
// N = read()

int P[maxn], bestP[maxn], pos[maxn];

void init() {
    Set(letter, 0);
    Set(id, 0);
    Set(P, 0);
    Set(bestP, 0);
    Set(pos, 0);
    u.clear();
    v.clear();
}


void solve() {
    ans = N;
    _for(i, 0, N) P[i] = i;

    for(;;) {
        _for(i, 0, N) pos[P[i]] = i;
        
        int bandwidth = 0;
        _for(i, 0, u.size()) {
            int node = u[i];
            for(auto& x : v[node]) {
                bandwidth = max(bandwidth, abs(pos[node] - pos[x]));
            }
        }
        
        if(bandwidth < ans) {
            ans = bandwidth;
            memcpy(bestP, P, sizeof(P));
        }
        
        if(!next_permutation(P, P + N)) break;
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%s", str) == 1 && str[0] != '#') {
        init();
        N = read();
        solve();
        
        _for(i, 0, N) printf("%c ", letter[bestP[i]]);
        printf("-> %d\n", ans);
    }
}
