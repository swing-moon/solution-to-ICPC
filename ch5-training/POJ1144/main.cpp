#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
typedef long long llong;
const int maxn = 500 + 10;

int pre[maxn], low[maxn], dfs_clock = 0;
bool iscut[maxn];
vector<int> G[maxn];
int getval[maxn];

int dfs(int u, int fa) {
    int lowu = pre[u] = ++dfs_clock;
    int cld = 0;

    for(int i = 0; i < G[u].size(); i++) {
        int v = G[u][i];
        if(!pre[v]) {
            cld++;
            int lowv = dfs(v, u);
            lowu = min(lowu, lowv);

            if(lowv >= pre[u]) {
                iscut[u] = true;
            }
        }
        else if(pre[v] < pre[u] && v != fa) {
            lowu = min(lowu, pre[v]);
        }
    }
    if(fa < 0 && (cld == 0 || cld == 1)) {
        iscut[u] = false;
    }

    return lowu;
}

void targan_init() {
    memset(pre, 0, sizeof(pre));
    memset(low, 0, sizeof(low));
    memset(iscut, 0, sizeof(iscut));
    dfs_clock = 0;
}

int main() {
    int n;
    while(scanf("%d", &n) != EOF) {
        if(n == 0) break;

        for(int i = 1; i <= n; i++) G[i].clear();
        int u, v;

        while(scanf("%d", &u) && u) {
            while(getchar() != '\n') {
                scanf("%d", &v);
                G[u].push_back(v);
                G[v].push_back(u);
            }
        }

        targan_init();
        dfs(1, -1);

        int ans = 0;
        for(int i = 1; i <= n; i++) if(iscut[i])
            ans++;

        printf("%d\n", ans);

    }
    return 0;
}
