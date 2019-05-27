#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 20 + 10;
const int maxs = 200;

int n, G[maxn][maxn];
int vis[maxn];
vector<int> topo;

// vis[] = -1 means visited!
// vis[] = 1 means finished!

bool dfs(int u) {
    vis[u] = -1;
    for(int v = 0; v <= n; v++) {
        if(G[u][v]) {
            if(vis[v] < 0) return false;
            else if(!vis[v]) dfs(v);
        }
    }

    vis[u] = 1;
    topo.push_back(u);
    return true;
}

bool toposort() {
    topo.clear();
    memset(vis, 0, sizeof(vis));

    for(int u = 0; u <= n; u++) {
        if(!vis[u]){
            if(!dfs(u)) return false;
        }
    }

    reverse(topo.begin(), topo.end());
    return true;
}

int pa[maxn];
int findset(int x) { return pa[x] != x ? pa[x] = findset(pa[x]) : x; }

int main() {
    int T;
    scanf("%d", &T);

    while(T--) {
        char symbol[maxs], matrix[maxn][maxn];
        scanf("%d%s", &n, symbol);

        for(int i = 0; i <= n; i++) pa[i] = i;

        int idx = 0;
        for(int i = 1; i <= n; i++) {
            for(int j = i; j <= n; j++) {
                matrix[i][j] = symbol[idx++];
                if(matrix[i][j] == '0') pa[j] = i-1;
            }
        }

        memset(G, 0, sizeof(G));
        for(int i = 1; i <= n; i++) {
            for(int j = i; j <= n; j++) {
                if(matrix[i][j] == '-') G[findset(j)][findset(i-1)] = 1;
                if(matrix[i][j] == '+') G[findset(i-1)][findset(j)] = 1;
            }
        }

        toposort();
        int sum[maxn], val = 0;
        for(int i = 0; i <= n; i++) sum[topo[i]] = val++;
        for(int i = 1; i <= n; i++) {
            sum[i] = sum[findset(i)];
            if(i > 1) printf(" ");
            printf("%d", sum[i]-sum[i-1]);
        }
        printf("\n");
    }
}