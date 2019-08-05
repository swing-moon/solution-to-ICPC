//
//  main.cpp
//  POJ3134
//
//  Created by zhangmin chen on 2019/7/4.
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

const int maxn = 1000 + 10;


#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define _forDown(i, l, r) for(int i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }
#define _forPlus(i, l, d, r) for(int i = (l); i + d < (r); i++)

int n;
int v[maxn];

void init() {
    Set(v, 0);
    v[0] = 1;
}

int h(int* v, int d, int maxd) {
    int maxv = v[0];
    _rep(i, 1, d) maxv = max(maxv, v[i]);
    return maxv << (maxd - d);
}

int dfs(int d, int maxd) {
    if(d == maxd) {
        if(v[d] == n) return true;
        return false;
    }
    
    if(h(v, d, maxd) < n) return false;
    
    // if(dfs(d+1, ...)) return true;
    _forDown(i, d, 0) {
        v[d+1] = v[d] + v[i];
        if(dfs(d+1, maxd)) return true;
        
        v[d+1] = v[d] - v[i];
        if(dfs(d+1, maxd)) return true;
    }
    
    return false;
}

int solve() {
    //
    if(n == 1) return 0;
    v[0] = 1;
    int maxd = 1;
    for(maxd = 1; ; maxd++) {
        //
        if(dfs(0, maxd)) break;
    }
    
    return maxd;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) == 1 && n) {
        init();
        printf("%d\n", solve());
    }
}
