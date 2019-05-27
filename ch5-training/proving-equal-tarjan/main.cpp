#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>

using namespace std;
const int maxn = 20000 + 10;

vector<int> G[maxn];
int pre[maxn], low[maxn], sccidx[maxn], dfs_clock, scc_cnt;
stack<int> stk;

void tarjan(int u) {
    low[u] = pre[u] = ++dfs_clock;
    // note: refresh dfs_clock, scc_cnt
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
    memset(pre, 0, sizeof(pre));
    memset(low, 0, sizeof(low));
    memset(sccidx, 0, sizeof(sccidx));

    for(int i = 0; i < n; i++) {
        if(!pre[i]) tarjan(i);
    }
}

int in0[maxn], out0[maxn];

int main() {
    int T, n, m;
    scanf("%d", &T);

    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 0; i < n; i++) G[i].clear();
        for(int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v); u--; v--;
            G[u].push_back(v);
        }

        find_scc(n);

        for(int i = 1; i <= scc_cnt; i++) in0[i] = out0[i] = 1;
        for(int u = 0; u < n; u++) {
            for(int i = 0; i < G[u].size(); i++) {
                int v = G[u][i];
                if(sccidx[u] != sccidx[v]) {
                    out0[sccidx[u]] = in0[sccidx[v]] = 0;
                }
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
    return 0;
}