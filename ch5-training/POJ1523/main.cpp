#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
const int maxn = 1000 + 10;

int pre[maxn], sub[maxn], dfs_clock;
int root, isroot[maxn];
vector<int> G[maxn];

int tarjan(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    int cld = 0;

    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(!pre[v]) {
            cld++;
            int lowv = tarjan(v, u);
            lowu = min(lowu, lowv);

            if( (u == root && cld > 1) || (u != root && lowv >= pre[u]) ) {
                sub[u]++;
            }
        }
        else if(pre[v] < pre[u] && v != fa) lowu = min(lowu, pre[v]);
    }
    return lowu;
}


int main() {
    bool first = 0; int kase = 0;
    int u, v;

    while(true) {
        if(first) printf("\n");
        else first = 1;

        for(int i = 0; i < maxn; i++) G[i].clear();
        scanf("%d", &u);
        if(u == 0) break;
        scanf("%d", &v);
        G[u].push_back(v); G[v].push_back(u);

        while(true) {
            scanf("%d", &u);
            if(u == 0) break;
            scanf("%d", &v);
            G[u].push_back(v); G[v].push_back(u);
        }

        memset(pre, 0, sizeof(pre));
        memset(sub, 0, sizeof(sub));
        memset(isroot, 0, sizeof(isroot));

        for(int i = 1; i <= 1000; i++) {
            if(!pre[i] && G[i].size() > 0) {
                isroot[i] = true;
                root = i;
                dfs_clock = 0;
                tarjan(root, -1);
            }
        }

        printf("Network #%d\n", ++kase);
        bool flag = 0;
        for(int i = 1; i <= 1000; i++) {
            if(sub[i]) {
                flag = 1;
                printf("  SPF node %d leaves %d subnets\n", i, sub[i]+1);
            }
        }

        if(!flag) printf("  No SPF nodes\n");
    }
}