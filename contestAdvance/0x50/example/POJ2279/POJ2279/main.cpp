//
//  main.cpp
//  POJ2279
//
//  Created by zhangmin chen on 2019/7/31.
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
#include <bitset>
#include <assert.h>


using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;

const int maxn = 5 + 1;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _forS(i, l, r) for(set<int>::iterator i = (l); i != (r); i++)
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define _forDown(i, l, r) for(int i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }
#define _forPlus(i, l, d, r) for(int i = (l); i + d < (r); i++)

int N[maxn], k;

void solve() {
    //
    _rep(i, 1, k) scanf("%d", &N[i]);
    while(k < 5) N[++k] = 0;
    // _rep(i, 0, 5) debug(N[i]);
    // cout << endl;
    
    llong f[N[1] + 1][N[2] + 1][N[3] + 1][N[4] + 1][N[5] + 1];
    Set(f, 0);
    
    // then DP
    f[0][0][0][0][0] = 1;
    _rep(i, 0, N[1]) _rep(j, 0, N[2]) _rep(k, 0, N[3]) _rep(l, 0, N[4]) _rep(m, 0, N[5]) {
        if(i < N[1]) f[i + 1][j][k][l][m] += f[i][j][k][l][m];
        if(j < N[2] && j < i) f[i][j + 1][k][l][m] += f[i][j][k][l][m];
        if(k < N[3] && k < j) f[i][j][k + 1][l][m] += f[i][j][k][l][m];
        if(l < N[4] && l < k) f[i][j][k][l + 1][m] += f[i][j][k][l][m];
        if(m < N[5] && m < l) f[i][j][k][l][m + 1] += f[i][j][k][l][m];
    }
    
    cout << f[N[1]][N[2]][N[3]][N[4]][N[5]] << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    while(scanf("%d", &k) == 1 && k) solve();
}
