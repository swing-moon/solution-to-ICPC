//
//  main.cpp
//  UVA524
//
//  Created by zhangmin chen on 2019/6/18.
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
const int maxn = 50;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

int A[maxn + 5], vis[maxn + 5], n;

int isPrime(int val) {
    for(int i = 2; i * i <= val; i++) {
        if(val % i == 0) return 0;
    }
    return 1;
}

void init() {
    Set(A, 0);
    Set(vis, 0);
}

void dfs(int cur) {
    if(cur == n && isPrime(A[n-1] + A[0])) {
        //debug(isPrime(A[n-1] + A[0]))
        _for(i, 0, n) {
            if(i != 0) printf(" ");
            printf("%d", A[i]);
        }
        printf("\n");
    }
    else {
        for(int x = 2; x <= n; x++) {
            if(!vis[x] && isPrime(x + A[cur-1])) {
                A[cur] = x;
                // debug(x);
                vis[x] = 1;
                dfs(cur + 1);
                vis[x] = 0;
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while(scanf("%d", &n) == 1 && n > 0) {
        // debug(n);
        if(kase > 0) cout << endl;
        printf("Case %d:\n", ++kase);
        
        init();
        A[0] = 1;
        dfs(1);
    }
}
