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

int targan(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;

    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(v == fa) continue;

        if(!pre[v]) {
            int lowv = targan(v, u);
            lowu = min(lowu, lowv);
        }
        else if(pre[v] < pre[u])
            lowu = min(lowu, pre[v]);
    }
    return low[u] = lowu;
}

int main() {
    scanf("%d%d", &n, &m);
    dfs_clock = 0;
    memset(pre, 0, sizeof(pre));
    memset(low, 0, sizeof(low));
    memset(deg, 0, sizeof(deg));

    for(int i = 1; i <= n; i++) G[i].clear();
    for(int i = 1; i <= m; i++) {
        int u, v;
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }

    targan(1, -1);
    for(int i = 1; i <= n; i++) {
        for(int j = 0; j < G[i].size(); j++) {
            int v = G[i][j];
            // edge(i, v)
            if(low[i] != low[v]) deg[low[v]]++;
        }
    }

    int cnt = 0;
    for(int i = 1; i <= n; i++) if(deg[i] == 1)
        cnt++;

    printf("%d\n", (cnt+1)/2);
}