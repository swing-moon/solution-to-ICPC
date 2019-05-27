//
//  main.cpp
//  HDU1116
//
//  Created by zhangmin chen on 2019/5/22.
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

const int maxn = 100;
const int maxl = 2000 + 10;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

int kase, G[maxn][maxn], vis[maxn];
int ideg[maxn], odeg[maxn];
int m, u, v;

const int N = 26;

void init() {
    Set(G, 0);
    Set(vis, 1);
    Set(ideg, 0);
    Set(odeg, 0);
}

void dfs(int u) {
    vis[u] = 1;
    _for(i, 0, N) {
        if(G[u][i] && !vis[i]) dfs(i);
    }
}
// find which node has been visited


int main() {
    freopen("input.txt", "r", stdin);
    char str[maxl];
    
    cin >> kase;
    while(kase--) {
        init();
        cin >> m;
        
        _for(i, 0, m) {
            scanf("%s", str);
            int u = str[0] - 'a';
            int v = str[strlen(str) - 1] - 'a';
            
            G[u][v] = 1;
            vis[u] = vis[v] = 0;
            ideg[v]++; odeg[u]++;
        }
        
        bool exist = 0;
        int root = 0, fromN = 0, toN = 0, odd = 0;
        
        _for(i, 0, N) {
            if(ideg[i] == odeg[i]) continue;
            else if(ideg[i] == odeg[i] + 1) toN++;
            else if(odeg[i] == ideg[i] + 1) {
                fromN++;
                root = i;
            }
            else odd++;
        }
        
        if(odd > 0) {
            printf("The door cannot be opened.\n");
            continue;
        }
        
        if( (fromN == 1 && toN == 1) || (fromN == 0 && toN == 0) ) exist = 1;
        else exist = 0;
        
        dfs(root);
        _for(i, 0, N) if(!vis[i]) exist = 0;
        
        if(exist) printf("Ordering is possible.\n");
        else printf("The door cannot be opened.\n");
    }
}
