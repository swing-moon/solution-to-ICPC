//
//  main.cpp
//  OPENJUDGE2760
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
#include <unordered_set>

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;

const int maxn = 100 + 10;

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

int dp[maxn][maxn];
int tb[maxn][maxn];
int n;

void init() {
    Set(dp, -1);
    Set(tb, 0);
}

int solve(int i, int j) {
    if(dp[i][j] >= 0) return dp[i][j];
    int& ans = dp[i][j];
    
    return ans = tb[i][j] + (i == n ? 0 : max(solve(i + 1, j), solve(i + 1, j + 1)));
}

int main() {
    freopen("input.txt", "r", stdin);
    init();
    scanf("%d", &n);
    
    _rep(i, 1, n) _rep(j, 1, i) scanf("%d", &tb[i][j]);
    cout << solve(1, 1) << endl;
}
