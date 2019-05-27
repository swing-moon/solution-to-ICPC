//
//  main.cpp
//  LA6393
//
//  Created by zhangmin chen on 2019/5/23.
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

const int maxn = 52 + 5;
const int maxl = 10;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

int G[maxn][maxn], vis[maxn];

void init() {
    Set(G, 0);
    Set(vis, 0);
}

int ID(char a, char b) {
    return (a - 'A') * 2 + (b == '+' ? 0 : 1);
}

void connect(char a1, char a2, char b1, char b2) {
    if(a1 == '0' || b1 == '0') return;
    int u = ID(a1, a2), v = ID(b1, b2) ^ 1;
    G[u][v] = 1;
}

bool dfs(int u) {
    vis[u] = -1;

    _for(v, 0, maxn) {
        if(G[u][v]) {
            if(vis[v] < 0) return false;
            else if(!vis[v] && !dfs(v)) return false;
        }
    }
    
    vis[u] = 1;
    return true;
}

bool toposort() {
    _for(u, 0, maxn) {
        if(!vis[u]) if(!dfs(u)) return false;
    }
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    
    while(scanf("%d", &n) == 1 && n) {
        init();
        while(n--) {
            char cube[maxl];
            scanf("%s", cube);
            _for(i, 0, 4) _for(j, 0, 4) {
                if(i != j) connect(cube[i * 2], cube[i * 2 + 1], cube[j * 2], cube[j * 2 + 1]);
            }
        }
        // we get data
        // then find cycle by topo sort
        
        if(!toposort()) cout << "unbounded" << endl;
        else cout << "bounded" << endl;
    }
}
