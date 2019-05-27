#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <stack>
#include <queue>
#include <cstring>

using namespace std;
const int maxn = 200000 + 10;

int pre[maxn], d[maxn], bridge[maxn];
int pa[maxn];
vector<int> G[maxn];
int n, m, dfs_clock, cnt;
int root;

void init() {
    memset(pre, 0, sizeof(pre));
    memset(d, 0, sizeof(d));
    memset(bridge, 0, sizeof(bridge));
    memset(pa, 0, sizeof(pa));
    for(int i = 0; i < maxn; i++) G[i].clear();
    dfs_clock = 0, cnt = 0;

    for(int i = 0; i <= n; i++) pa[i] = i;
}

void addEdge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

int tarjan(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    d[u] = d[pa[u]] + 1;
    int cld = 0;

    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(!pre[v]) {
            cld++;
            pa[v] = u;
            int lowv = tarjan(v, u);
            lowu = min(lowu, lowv);

            if(lowv > pre[u]) {
                bridge[v] = 1;
                cnt++;
            }
        }
        else if(pre[v] < pre[u] && v != fa) {
            lowu = min(lowu, pre[v]);
        }
    }

    return lowu;
}

void lca(int u, int v) {
    while(d[u] > d[v]) {
        if(bridge[u]) { cnt--; bridge[u] = 0; }
        u = pa[u];
    }
    while(d[v] > d[u]) {
        if(bridge[v]) { cnt--; bridge[v] = 0; }
        v = pa[v];
    }

    while(u != v) {
        if(bridge[u]) { cnt--; bridge[u] = 0; }
        if(bridge[v]) { cnt--; bridge[v] = 0; }
        u = pa[u];
        v = pa[v];
    }
}

int main() {
    int kase = 0;
    while(scanf("%d%d", &n, &m) && n) {
        init();
        printf("Case %d:\n", ++kase);

        while(m--) {
            int u, v;
            scanf("%d%d", &u, &v);
            addEdge(u ,v);
            addEdge(v, u);
        }

        root = 1;
        tarjan(root, -1);

        int q;
        scanf("%d", &q);
        while(q--) {
            int u, v;
            scanf("%d%d", &u, &v);
            lca(u, v);
            printf("%d\n", cnt);
        }
        puts("");
    }
}