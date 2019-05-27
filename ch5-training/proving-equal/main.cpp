#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>

using namespace std;

const int maxn = 20000 + 10;

vector<int> G[maxn], G2[maxn];
vector<int> topo;

int vis[maxn], sccidx[maxn], scc_cnt;

void dfs1(int u) {
    if(vis[u]) return;
    vis[u] = 1;
    for(int i = 0; i < G[u].size(); i++) dfs1(G[u][i]);
    topo.push_back(u);
}

void dfs2(int u) {
    if(sccidx[u]) return;
    sccidx[u] = scc_cnt;
    for(int i = 0; i < G2[u].size(); i++) dfs2(G2[u][i]);
}

void find_scc(int n) {
    scc_cnt = 0;
    topo.clear();
    memset(sccidx, 0, sizeof(sccidx));
    memset(vis, 0, sizeof(vis));

    for(int i = 0; i < n; i++) dfs1(i);
    for(int i = n-1; i >= 0; i--) if(!sccidx[topo[i]]) {
        scc_cnt++;
        dfs2(topo[i]);
    }
}

int in0[maxn], out0[maxn];

int main() {
    int T, n, m;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++) { G[i].clear(); G2[i].clear(); }
        for(int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v); u--; v--;
            G[u].push_back(v);
            G2[v].push_back(u);
        }

        find_scc(n);

        for(int i = 1; i <= scc_cnt; i++) in0[i] = out0[i] = 1;
        for(int u = 0; u < n; u++) {
            for(int i = 0; i < G[u].size(); i++) {
                int v = G[u][i];
                if(sccidx[u] != sccidx[v])
                    in0[sccidx[v]] = out0[sccidx[u]] = 0;
            }
        }

        int a = 0, b = 0;
        for(int i = 1; i <= scc_cnt; i++) {
            if(in0[i]) a++;
            if(out0[i]) b++;
        }
        int ans = max(a, b);
        if(scc_cnt == 1) ans = 0;

        printf("%d\n", ans);
    }
}