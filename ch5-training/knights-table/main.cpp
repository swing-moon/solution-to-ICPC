#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <stack>
#include <queue>
#include <vector>

using namespace std;

struct Edge {
    int from, to;
};

const int maxn = 1000 + 10;
int pre[maxn], iscut[maxn], idx[maxn];
vector<int> G[maxn], bcc[maxn];
int dfs_clock, bcc_cnt;

stack<Edge> stk;


int tarjan(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    int cld = 0;

    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        Edge e = (Edge) {u, v};

        if(!pre[v]) {
            stk.push(e); cld++;
            int lowv = tarjan(v, u);
            lowu = min(lowu, lowv);

            if(lowv >= pre[u]) {
                iscut[u] = true;

                bcc_cnt++; bcc[bcc_cnt].clear();
                for(;;) {
                    Edge x = stk.top(); stk.pop();

                    if(idx[x.from] != bcc_cnt) {
                        idx[x.from] = bcc_cnt;
                        bcc[bcc_cnt].push_back(x.from);
                    }
                    if(idx[x.to] != bcc_cnt) {
                        idx[x.to] = bcc_cnt;
                        bcc[bcc_cnt].push_back(x.to);
                    }

                    if(x.from == u && x.to == v) break;
                }
            }
        }
        else if(pre[v] < pre[u] && v != fa) {
            stk.push(e);
            lowu = min(lowu, pre[v]);
        }
    }

    if(fa < 0 && cld == 1) iscut[u] = 0;
    return lowu;
}

void find_bcc(int n) {
    memset(pre, 0, sizeof(pre));
    memset(iscut, 0, sizeof(iscut));
    memset(idx, 0, sizeof(idx));

    dfs_clock = bcc_cnt = 0;

    for(int i = 0; i < n; i++) {
        if(!pre[i]) tarjan(i, -1);
    }
}

int hates[maxn][maxn];
int color[maxn], odd[maxn];
int n, m;
// node start from 0

bool bipart(int u, int b_idx) {
    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(idx[v] != b_idx) continue;

        if(color[u] == color[v]) return false;
        if(!color[v]) {
            color[v] = 3 - color[u];
            if(!bipart(v, b_idx)) return false;
        }
    }
    return true;
}

int main() {
    while(scanf("%d%d", &n, &m) == 2 && n) {
        for(int i = 0; i < n; i++) G[i].clear();

        memset(hates, 0, sizeof(hates));
        for(int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v); u--; v--;
            hates[u][v] = hates[v][u] = 1;
        }

        for(int u = 0; u < n; u++) {
            for(int v = u+1; v < n; v++) {
                if(!hates[u][v]) {
                    G[u].push_back(v);
                    G[v].push_back(u);
                }
            }
        }

        find_bcc(n);
        // then judge odd circle

        memset(odd, 0, sizeof(odd));
        for(int i = 1; i <= bcc_cnt; i++) {
            memset(color, 0, sizeof(color));

            for(int j = 0; j < bcc[i].size(); j++) idx[bcc[i][j]] = i;

            int u = bcc[i][0];
            color[u] = 1;
            // I made a bug here!
            // remember assign color of root

            if(!bipart(u, i)) {
                for(int j = 0; j < bcc[i].size(); j++) odd[bcc[i][j]] = 1;
            }
        }

        int ans = n;
        for(int i = 0; i < n; i++) if(odd[i]) ans--;

        printf("%d\n", ans);
    }
}