#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
const int maxn = 5000 + 10;

struct Edge {
    int from, to;
};

int pre[maxn], low[maxn];
int vis[maxn], bcc[maxn];


int dfs_clock, bcc_cnt;
vector<int> G[maxn];
vector<Edge> bridge;

int n, m;

int targan(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;

    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(!pre[v]) {
            int lowv = targan(v, u);
            lowu = min(lowu, lowv);
            if(lowv > pre[u]) bridge.push_back((Edge){u, v});
        }
        else if(pre[v] < pre[u] && v != fa) {
            lowu = min(lowu, pre[v]);
        }
    }
    return low[u] = lowu;
}



// bridge: low[u] != low[v]

void dfs(int u) {
    vis[u] = 1;
    bcc[u] = bcc_cnt;
    int flag = 0;

    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        for(int k = 0; k < bridge.size(); k++) {
            Edge x = bridge[k];
            if( (x.from == u && x.to == v) ) { flag = 1; break; }
        }
        if(flag || vis[v]) continue;
        dfs(v);
    }
}

void find_cc() {
    memset(pre, 0, sizeof(pre));
    memset(low, 0, sizeof(low));
    dfs_clock = 0;

    for(int i = 0; i < n; i++) {
        if(!pre[i]) targan(i, -1);
    }

    bcc_cnt = 0;
    memset(bcc, -1, sizeof(bcc));
    memset(vis, 0, sizeof(vis));

    for(int u = 0; u < n; u++) {
        if(!vis[u]) {
            bcc_cnt++;
            dfs(u);
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < m; i++) {
        int u, v;
        scanf("%d%d", &u, &v); u--; v--;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    find_cc();
    cout << "bcc cnt: " << bcc_cnt << endl;
    for(int i = 1; i <= bcc_cnt; i++) {
        for(int u = 0; u < n; u++) if(bcc[u] == i)
            printf("%d ", u);

        printf("\n");
    }

    printf("\nlow value: \n");
    for(int i = 0; i < n; i++) {
        printf("%d ", low[i]);
    }
}