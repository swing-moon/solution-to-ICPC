#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;

const int maxn = 5000 + 10;
int n, m;
vector<int> G[maxn];

int pre[maxn], low[maxn], deg[maxn], dfs_clock;
int bcccnt = 0, bcc[maxn];


struct Edge {
    int from, to;
};

stack<int> stk;

void tarjan(int u, int fa) {
    low[u] = pre[u] = ++dfs_clock;
    stk.push(u);
    int flag = 0;

    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(v == fa && !flag) { flag = 1; continue; }

        if(!pre[v]) {
            tarjan(v, u);
            low[u] = min(low[u], low[v]);
        }
        else {
            low[u] = min(low[u], pre[v]);
        }
    }

    if(low[u] == pre[u]) {
        // a new bcc
        bcccnt++;
        for(;;) {
            int x = stk.top();
            stk.pop();
            bcc[x] = bcccnt;

            if(stk.empty() || x == u) break;
        }
    }
}

void init() {
    dfs_clock = 0, bcccnt = 0;
    memset(pre, 0, sizeof(pre));
    memset(low, 0, sizeof(low));
    memset(deg, 0, sizeof(deg));
    memset(bcc, 0, sizeof(bcc));

    for(int i = 0; i < maxn; i++) G[i].clear();
}

void addEdge(int u, int v) {
    G[u].push_back(v);
    G[v].push_back(u);
}

int main() {
    scanf("%d%d", &n, &m);
    init();

    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
    }

    for(int i = 1; i <= n; i++) if(!pre[i]) tarjan(i, -1);

    for(int u = 1; u <= n; u++) {
        for(int i = 0; i < G[u].size(); i++) {
            int v = G[u][i];
            if(bcc[u] == bcc[v]) continue;
            else {
                deg[bcc[v]]++;
            }
        }
    }

    int sum = 0;
    for(int i = 0; i <= bcccnt; i++) if(deg[i] == 1)
            sum++;

    printf("%d\n", (sum+1)/2);
}