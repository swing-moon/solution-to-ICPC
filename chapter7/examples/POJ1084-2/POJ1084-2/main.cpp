//
//  main.cpp
//  POJ1084-2
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

const int maxn = 60 + 5;

int n, tot, k;
int exist[maxn];
int contains[maxn][maxn];
int full[maxn], sqr[maxn];
int sqrN;

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

void init1() {
    Set(exist, 0);
    Set(contains, 0);
    Set(sqr, 0);
    Set(full, 0);
}

void initSqr(int k) {
    _for(i, 0, tot) exist[i] = 1;
    // debug(tot);
    while (k--) {
        int a;
        scanf("%d", &a);
        exist[a - 1] = 0;
    }
}

int getR(int x, int y) {
    return (2 * n + 1) * x + y;
}

int getC(int x, int y) {
    return (2 * n + 1) * x + y + n;
}

int build() {
    int cnt = 0;
    _rep(sz, 1, n) {
        _forPlus(x, 0, sz - 1, n) _forPlus(y, 0, sz - 1, n) {
            full[cnt] = 4 * sz;
            sqr[cnt] = 0;
            
            _for(dl, 0, sz) {
                int up = getR(x, y + dl);
                int down = getR(x + sz, y + dl);
                int left = getC(x + dl, y);
                int right = getC(x + dl, y + sz);
                
                contains[cnt][up] = 1;
                contains[cnt][down] = 1;
                contains[cnt][left] = 1;
                contains[cnt][right] = 1;
                
                sqr[cnt] += (exist[up] + exist[down] + exist[left] + exist[right]);
            }
            
            cnt++;
        }
    }
    
    return cnt;
}



int dfs(int d, int maxd) {
    if(d == maxd) {
        _for(i, 0, sqrN) if(sqr[i] == full[i]) return false;
        return true;
    }
    
    //if(d + h() > maxd) return false;
    
    int del = 0;
    // del is the id number of square to be destoryed
    _for(i, 0, sqrN) if(sqr[i] == full[i]) {
        del = i;
        break;
    }
    
    _for(i, 0, tot) {
        // debug(tot);
        if(contains[del][i]) {
            _for(k, 0, sqrN) if(contains[k][i]) sqr[k]--;
            if(dfs(d+1, maxd)) return true;
            _for(k, 0, sqrN) if(contains[k][i]) sqr[k]++;
        }
    }
    
    return false;
}

int solve() {
    int maxd = 1;
    for (maxd = 1; ; maxd++) {
        if(dfs(0, maxd)) break;
    }
    return maxd;
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);
    
    while (kase--) {
        init1();
        
        scanf("%d%d", &n, &k);
        tot = 2 * n * (n + 1);
        initSqr(k);
        sqrN = build();
        
        printf("%d\n", solve());
    }
}
