#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

const int maxn = 10000 + 10;

int pre[maxn], iscut[maxn], idx[maxn], bcc_cnt, dfs_clock;
vector<int> G[maxn], bcc[maxn];

struct Edge {
    int from, to;
};

stack<Edge> edges;

int dfs(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    int cld = 0;

    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        Edge e = (Edge){u, v};

        if(!pre[v]) {
            // (u,v) stretching
            cld++;
            edges.push(e);

            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);
            if(lowv >= pre[u]) {
                iscut[u] = true;
                bcc_cnt++; bcc[bcc_cnt].clear();

                for(;;) {
                    Edge x = edges.top(); edges.pop();
                    if(idx[x.from] != bcc_cnt) { idx[x.from] = bcc_cnt; bcc[bcc_cnt].push_back(x.from); }
                    if(idx[x.to] != bcc_cnt) { idx[x.to] = bcc_cnt; bcc[bcc_cnt].push_back(x.to); }
                    if(x.from == u && x.to == v) break;
                }
            }
        }
        else if(pre[v] < pre[u] && v != fa) {
            edges.push(e);
            lowu = min(lowu, pre[v]);
        }
    }

    if(fa < 0 && (cld == 0 || cld == 1)) iscut[u] = false;
    return lowu;
}

void find_cc(int n) {
    memset(pre, 0, sizeof(pre));
    memset(idx, 0, sizeof(idx));
    memset(iscut, 0, sizeof(iscut));

    dfs_clock = bcc_cnt = 0;
    for(int i = 0; i < n; i++)
        if(!pre[i]) dfs(i, -1);
}

int main() {
    int n, m, u, v;
    scanf("%d%d", &n, &m);

    for(int i = 0; i < m; i++) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    find_cc(n);
    printf("%d\n", bcc_cnt);

    for(int i = 1; i <= bcc_cnt; i++) {
        for(int j = 0; j < bcc[i].size(); j++) {
            printf("%d ", bcc[i][j]);
        }
        printf("\n");
    }
}