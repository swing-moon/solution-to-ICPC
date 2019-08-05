//
//  main.cpp
//  nQueens02
//
//  Created by zhangmin chen on 2019/6/15.
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

const int maxn = 50;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

int vis[3][maxn], col[maxn], n = 8;
int tot = 0;

void init() {
    Set(vis, 0);
    Set(col, 0);
    tot = 0;
}

void search(int cur) {
    if(cur == n) tot++;
    else {
        _for(i, 0, n) {
            if(!vis[0][i] && !vis[1][cur+i] && !vis[2][cur+ n-i]) {
                col[cur] = i;
                vis[0][i] = vis[1][cur+i] = vis[2][cur+ n-i] = 1;
                search(cur+1);
                vis[0][i] = vis[1][cur+i] = vis[2][cur+ n-i] = 0;
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    
    while(scanf("%d", &n) == 1 && n) {
        init();
        //
        search(0);
        printf("%d\n", tot);
    }
}
