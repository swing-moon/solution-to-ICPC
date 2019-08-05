//
//  main.cpp
//  LA5218
//
//  Created by zhangmin chen on 2019/7/11.
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

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;

const int maxn = 15;


#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
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

int n;
int G[maxn][maxn];
int vis[maxn];

void init() {
    Set(G, 0);
    Set(vis, 0);
}

int deg(const int u, const bitset<maxn>& opened) {
    if(opened.test(u)) return 0;
    int ans = 0;
    _for(v, 0, n) if(G[u][v] && !opened.test(v)) ans++;
    return ans;
}

bool canDfs(const int u, const int pa, const bitset<maxn>& opened) {
    if(vis[u] == 1) return true;
    if(vis[u] == -1) return false;
    
    if(opened.test(u)) {
        vis[u] = 1;
        return true;
    }
    
    vis[u] = -1;
    // dfs v
    
    _for(v, 0, n) if(v != pa && G[u][v]) if(!canDfs(v, u, opened)) return false;
    
    vis[u] = 1;
    return true;
}

void initVis() {
    Set(vis, 0);
}

int solve() {
    int ans = n;
    bitset<maxn> opened;
    
    _for(x, 0, 1 << n) {
        opened.reset();
        bool ok = true;
        
        // check line
        _for(i, 0, n) if((1 << i) & x) opened.set(i);
        _for(i, 0, n) if(deg(i, opened) > 2 && !opened.test(i)) {
            ok = false;
            break;
        }
        
        if(!ok) continue;
        
        // check circle and component
        initVis();
        int ti = 0;
        _for(u, 0, n) {
            if(opened.test(u)) continue;
            if(!vis[u]) ti++;
            if(!canDfs(u, -1, opened)) {
                ok = false;
                break;
            }
        }
        
        if(!ok) continue;
        
        int kc = (int)opened.count();
        //debug(ti);
        if(ti <= kc + 1) ans = min(ans, kc);
    }
    return ans;
    
}

int main() {
    freopen("input.txt", "r", stdin);
    for(int kase = 1; scanf("%d", &n) == 1 && n; kase++) {
        init();
        int from, to;
        while (true) {
            scanf("%d%d", &from, &to);
            if(from == -1 || to == -1) break;
            from--; to--;
            G[from][to] = G[to][from] = 1;
        }
        // input finished
        // then solve
        
        int ans = solve();
        // cout << ans << endl;
        printf("Set %d: Minimum links to open is %d\n", kase, ans);
    }
}
