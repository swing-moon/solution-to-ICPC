#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
#include <algorithm>
#include <cmath>

using namespace std;
const int maxn = 100 + 10;
const int inf = 0x3f3f3f3f;

int G[maxn][maxn], n;
int mincost[maxn], vis[maxn];

// mincost only related to one edge

int prim(int n) {
    for(int i = 0; i < n; i++) {
        mincost[i] = inf;
        vis[i] = 0;
    }

    mincost[0] = 0;
    int ans = 0;

    while(true) {
        int tmp = -1;
        for(int u = 0; u < n; u++) {
            if(!vis[u] && (tmp == -1 || mincost[tmp] > mincost[u]))
                tmp = u;
        }

        if(tmp == -1) break;
        vis[tmp] = true;
        ans += mincost[tmp];

        for(int v = 0; v < n; v++) {
            if(!vis[v]) mincost[v] = min(mincost[v], G[tmp][v]);
        }
    }
    return ans;
}


int main() {
    while(scanf("%d", &n) != EOF) {

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++)
                scanf("%d", &G[i][j]);
        }

        memset(mincost, 0, sizeof(mincost));
        memset(vis, 0, sizeof(vis));

        printf("%d\n", prim(n));
    }
}