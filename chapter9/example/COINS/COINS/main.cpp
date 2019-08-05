//
//  main.cpp
//  COINS
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
const int inf = 0x3f3f3f3f;

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

int V[maxn];
int S, N;

int minV[maxn], maxV[maxn];
int d[maxn];
int minCoin[maxn], maxCoin[maxn];

void init() {
    Set(V, 0);
    Set(minV, inf);
    Set(maxV, -inf);
    Set(d, -1);
    Set(minCoin, 0);
    Set(maxCoin, 0);
}

void dp() {
    minV[0] = maxV[0] = 0;
    _rep(i, 1, S) _rep(j, 1, N) {
        if(i >= V[j]) {
            minV[i] = min(minV[i], minV[i - V[j]] + 1);
            maxV[i] = max(maxV[i], maxV[i - V[j]] + 1);
        }
    }
    printf("%d %d\n", minV[S], maxV[S]);
}

// usage:
// minCoin[coinValue] = coinID

void dp2() {
    minV[0] = maxV[0] = 0;
    _rep(i, 1, S) _rep(j, 1, N) if(i >= V[j]) {
        if(minV[i] > minV[i - V[j]] + 1) {
            minV[i] = minV[i - V[j]] + 1;
            minCoin[i] = j;
        }
        if(maxV[i] < maxV[i - V[j]] + 1) {
            maxV[i] = maxV[i - V[j]] + 1;
            maxCoin[i] = j;
        }
    }
    printf("%d %d\n", minV[S], maxV[S]);
}


void printAns(int* d, int S) {
    while(S) {
        printf("%d ", d[S]);
        S -= V[d[S]];
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    init();
    scanf("%d%d", &N, &S);
    
    _rep(i, 1, N) scanf("%d", &V[i]);
    dp2();
    
    
    printAns(minCoin, S);
    cout << endl;
    printAns(maxCoin, S);
}
