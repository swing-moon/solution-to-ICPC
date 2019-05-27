//
//  main.cpp
//  UVA11134
//
//  Created by zhangmin chen on 2019/5/19.
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
const int maxn = 5000 + 5;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

bool inRange(int lo, int hi, int x) {
    if(lo > hi) return inRange(hi, lo, x);
    return lo <= x && x <= hi;
}

int xl[maxn], xr[maxn], yl[maxn], yr[maxn];
int x[maxn], y[maxn];

void init() {
    Set(xl, 0);
    Set(xr, 0);
    Set(yl, 0);
    Set(yr, 0);
    Set(x, 0);
    Set(y, 0);
}

bool solve(int* l, int* r, int* res, int n) {
    fill(res, res+n, -1);
    
    _rep(val, 1, n) {
        int p = -1, minr = n+1;
        // choose min interval for each val
        
        _for(i, 0, n) {
            if(val >= l[i]) {
                if(res[i] < 0 && r[i] < minr) { minr = r[i]; p = i; }
            }
        }
        if(val > minr || p < 0) return false;
        res[p] = val;
    }
    return true;
}

int n;

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) == 1 && n) {
        init();
        _for(i, 0, n) cin >> xl[i] >> yl[i] >> xr[i] >> yr[i];
        
        // then solve()
        if(solve(xl, xr, x, n) && solve(yl, yr, y, n)) _for(i, 0, n)
            printf("%d %d\n", x[i], y[i]);
        else
            printf("IMPOSSIBLE\n");
        
        // while finished
    }
}
