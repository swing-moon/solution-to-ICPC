#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

/*
core algorithm: lowv >= pre[u]
1. edge (u, v), v is the child of u, we calculate v
2. use lowv to update lowu
than judge lowv and pre[u]

3. may be v is the ancestor, lowu may be updated
   to the min-time ancestor
*/

const int maxn = 1000000 + 10;
int n, m;
int dfs_clock = 0;
vector<int> G[maxn];

int pre[maxn], low[maxn];
bool iscut[maxn];


int dfs(int u, int fa) {
    int cld = 0;
    int lowu = pre[u] = ++dfs_clock;

    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(!pre[v]) {
            cld++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);

            if(lowv >= pre[u]) {
                iscut[u] = true;
                if(lowv > pre[u]) {
                    printf("bridge is (%d, %d)\n", u, v);
                }
            }
        }
        else if(pre[v] < pre[u] && v != fa) {
            lowu = min(lowu, pre[v]);
        }
    }

    if(fa < 0 && (cld == 0 || cld == 1)) {
        iscut[u] = false;
    }
    return low[u] = lowu;
}

int main() {
    while(scanf("%d%d", &n, &m) == 2 && n) {
        dfs_clock = 0;
        memset(iscut, 0, sizeof(iscut));
        memset(pre, 0, sizeof(pre));

        for(int i = 0; i < n; i++)  G[i].clear();
        for(int i = 0; i < m; i++) {
            int u, v;
            scanf("%d%d", &u, &v);
            G[u].push_back(v);
            G[v].push_back(u);
        }

        dfs(0, -1);
        for(int i = 0; i < n; i++) if(iscut[i])
            printf("cut-vertex is : %d\n", i);
    }
}