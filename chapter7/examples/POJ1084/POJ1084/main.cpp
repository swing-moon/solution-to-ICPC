//
//  main.cpp
//  POJ1084
//
//  Created by zhangmin chen on 2019/7/2.
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

const int maxn = 60;
const int maxs = 5 + 1;


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

llong cell[maxs][maxs];
llong bit[maxn];
int n, tot, k;
llong st;

llong sqr[maxn];
int sqrN;

void init1() {
    Set(cell, 0);
    Set(sqr, 0);
}

void init2() {
    bit[0] = 1;
    _rep(i, 1, maxn) bit[i] = (bit[i-1] << 1);
}

int getR(int x, int y) {
    return (2 * n + 1) * x + y;
}

int getC(int x, int y) {
    return (2 * n + 1) * x + y + n;
}

int build() {
    int cnt = 0;
    // then cnt how many square
    
    _for(i, 0, n) _for(j, 0, n) {
        cell[i][j] |= (bit[getR(i, j)] | bit[getR(i, j) + (2 * n + 1)]);
        cell[i][j] |= (bit[getC(i, j)] | bit[getC(i, j) + 1]);
        sqr[cnt] = cell[i][j];
        cnt++;
    }
    
    _rep(sz, 2, n) {
        _forPlus(x, 0, sz - 1, n) _forPlus(y, 0, sz - 1, n) {
            _for(dx, 0, sz) _for(dy, 0, sz) { sqr[cnt] ^= cell[x + dx][y + dy]; }
            cnt++;
        }
    }
    
    return cnt;
}

int h(llong st) {
    int cnt = 0;
    _for(i, 0, sqrN) if( (sqr[i] & st) == sqr[i] ) {
        cnt++;
        st ^= sqr[i];
    }
    
    return cnt;
}

int dfs(int d, int maxd, llong st) {
    //
    if(d == maxd) {
        _for(i, 0, sqrN) if( (sqr[i] & st) == sqr[i] ) return false;
        return true;
    }
    
    if(h(st) + d > maxd) return false;
    
    // then recurse:
    // del is the square to be destroyed
    llong del = 0;
    _for(i, 0, sqrN) if( (st & sqr[i]) == sqr[i] ) {
        if(!del) {
            del = sqr[i];
            break;
        }
    }
    
    _for(i, 0, tot) if( (bit[i] & del) == bit[i]) {
        if(dfs(d+1, maxd, st ^ bit[i])) return true;
    }
    
    
    return false;
}

int solve(llong st) {
    int maxd = 1;
    for (maxd = 1; ; maxd++) {
        if(dfs(0, maxd, st)) break;
    }
    return maxd;
}

int main() {
    freopen("input.txt", "r", stdin);
    
    int kase;
    scanf("%d", &kase);
    
    while (kase--) {
        init1();
        init2();
        
        scanf("%d%d", &n, &k);
        tot = 2 * n * (n + 1);
        st = bit[tot] - 1;
        _for(i, 0, k) {
            int a;
            scanf("%d", &a);
            st ^= bit[a-1];
        }
        
        // finish input, then build square
        sqrN = build();
        printf("%d\n", solve(st));
    }
}
