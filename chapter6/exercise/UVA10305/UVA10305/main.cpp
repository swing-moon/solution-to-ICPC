//
//  main.cpp
//  UVA10305
//
//  Created by zhangmin chen on 2019/5/21.
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

const int maxn = 1000;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

int G[maxn][maxn], n, m;
int vis[maxn];
vector<int> topo;

void init() {
    Set(G, 0);
    Set(vis, 0);
    topo.clear();
}



bool dfs(int u) {
    vis[u] = -1;
    _for(v, 0, n) {
        if (G[u][v]) {
            if(vis[v] < 0) return false;
            // circle
            else if(!vis[v]) dfs(v);
        }
    }
    vis[u] = 1;
    topo.push_back(u);
    return true;
}

bool toposort() {
    _for(u, 0, n) {
        if(!vis[u]) if(!dfs(u)) return false;
    }
    reverse(topo.begin(), topo.end());
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    while(scanf("%d%d", &n, &m) == 2 && n) {
        //
        init();
        _for(i, 0, m) {
            int u, v;
            cin >> u >> v; u--; v--;
            G[u][v] = 1;
        }
        
        if(toposort()) {
            //
            _for(i, 0, n-1) printf("%d ", topo[i]+1);
            printf("%d\n", topo[n-1]+1);
        }
        else printf("No\n");
    }
}




