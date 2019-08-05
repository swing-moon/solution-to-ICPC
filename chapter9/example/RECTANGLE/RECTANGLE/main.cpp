//
//  main.cpp
//  RECTANGLE
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

class Rec {
public:
    int a, b;
};

Rec rec[maxn];
int G[maxn][maxn];
int n;

int F[maxn];

void init() {
    Set(G, 0);
    Set(F, -1);
}

bool valid(Rec& lhs, Rec& rhs) {
    return (lhs.a < rhs.a && lhs.b < rhs.b) || (lhs.a < rhs.b && lhs.b < rhs.a);
}

// i in j
// G[i][j] = 1
// i -> j

int dp(int x) {
    if(F[x] != -1) return F[x];
    
    int& ans = F[x];
    ans = 1;
    
    _rep(i, 1, n) if(G[x][i]) ans = max(ans, dp(i) + 1);
    return ans;
}

void printAns(int u) {
    printf("%d ", u);
    _rep(i, 1, n) if(G[u][i] && F[u] == F[i] + 1) {
        printAns(i);
        break;
    }
    return;
}

int main() {
    freopen("input.txt", "r", stdin);
    init();
    scanf("%d", &n);
    
    _rep(i, 1, n) scanf("%d%d", &rec[i].a, &rec[i].b);
    _rep(i, 1, n) _rep(j, 1, n) G[i][j] = valid(rec[i], rec[j]);
    
    _rep(i, 1, n) if(F[i] == -1) F[i] = dp(i);
    
    int tid = 0;
    _rep(i, 1, n) if(F[i] > F[tid]) tid = i;
    cout << F[tid] << endl;
    
    printAns(tid);
    cout << endl;
    
}
