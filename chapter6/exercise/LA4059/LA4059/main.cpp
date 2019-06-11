//
//  main.cpp
//  LA4059
//
//  Created by zhangmin chen on 2019/5/27.
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

using namespace std;
typedef long long llong;
const int maxn = 1000 + 10;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)

vector<int> G[maxn];
int vis[maxn];

int V, E, T;
void init() {
    _for(i, 0, maxn) G[i].clear();
    Set(vis, 0);
}

int dfs(int u) {
    if(vis[u]) return 0;
    vis[u] = 1;
    
    int P = G[u].size() % 2;
    _for(i, 0, G[u].size()) {
        int v = G[u][i];
        P += dfs(v);
    }
    return P;
}

// cc:
/*
 int main()
     _for(i, 0, N)
        if(vis[i] || G[i].empty()) continue;
        cc++;
        res += max(0, (dfs(i)-1) / 2)
 */

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    for(int from, to, kase = 1; cin >> V >> E >> T && V; kase++) {
        init();
        _for(i, 0, E) {
            cin >> from >> to;
            G[from-1].push_back(to-1);
            G[to-1].push_back(from-1);
        }
        
        int cc = 0, res = E;
        _for(i, 0, V) {
            if(vis[i] || G[i].empty()) continue;
            cc++;
            res += max(0, (dfs(i) - 2) / 2);
        }
        printf("Case %d: %d\n", kase, T*(res + max(0, cc-1)));
    }
}
