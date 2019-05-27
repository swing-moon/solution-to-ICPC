#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
const int maxn = 1000 + 10;

vector<int> G[maxn];
int pre[maxn], low[maxn], sccidx[maxn], dfs_clock, scc_cnt;
stack<int> stk;

void tarjan(int u) {
    low[u] = pre[u] = ++dfs_clock;
    stk.push(u);

    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(!pre[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        } else if(!sccidx[v]) {
            low[u] = min(low[u], pre[v]);
        }
    }

    if(low[u] == pre[u]) {
        scc_cnt++;
        for(;;) {
            int x = stk.top(); stk.pop();
            sccidx[x] = scc_cnt;
            if(x == u) break;
        }
    }
}


void find_scc(int n) {
    dfs_clock = scc_cnt = 0;
    // init

    memset(pre, 0, sizeof(pre));
    memset(low, 0, sizeof(low));
    memset(sccidx, 0, sizeof(sccidx));

    for(int i = 0; i < n; i++) {
        if(!pre[i]) tarjan(i);
    }
}

int sz[maxn], TG[maxn][maxn];
int d[maxn];

// dp in scc_cnt
int dp(int sccu) {
    int& ans = d[sccu];
    if(ans >= 0) return ans;

    ans = sz[sccu];
    for(int v = 1; v <= scc_cnt; v++) {
        if(v != sccu && TG[sccu][v]) ans = max(ans, dp(v) + sz[sccu]);
    }
    return ans;
}

int main() {
    int T, n, m;
    scanf("%d", &T);

    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++) G[i].clear();
        // init

        for(int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v); u--; v--;
            G[u].push_back(v);
        }

        find_scc(n);

        // build SCC-G
        memset(TG, 0, sizeof(TG));
        memset(sz, 0, sizeof(sz));
        for(int u = 0; u < n; u++) {
            sz[sccidx[u]]++;
            for(int i = 0; i < G[u].size(); i++) {
                int v = G[u][i];
                TG[sccidx[u]][sccidx[v]] = 1;
            }
        }


        // dp:
        int res = 0;
        memset(d, -1, sizeof(d));
        for(int i = 1; i <= scc_cnt; i++) {
            res = max(res, dp(i));
        }
        printf("%d\n", res);
    }
}