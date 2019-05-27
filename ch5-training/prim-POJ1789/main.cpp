#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
#include <queue>
#include <vector>

using namespace std;
const int maxn = 2000 + 10;
const int inf = 0x3f3f3f3f;

int n;
int dist[maxn][maxn];

int cnt_weight(const string& str1, const string& str2) {
    int sum = 0;
    for(int i = 0; i < 7; i++) {
        //
        if(str1[i] != str2[i]) sum++;
    }
    return sum;
}

string cargo[maxn];

void init() {
    for(int i = 0; i < maxn; i++) {
        cargo[i].clear();
    }
}

int prim(int n) {
    int mincost[n], vis[n];
    for(int i = 0; i < n; i++) {
        mincost[i] = inf; vis[i] = 0;
    }

    mincost[0] = 0;
    int ans = 0;

    while(true) {
        int tmp = -1;

        for(int u = 0; u < n; u++) {
            if(!vis[u] && (tmp == -1 || mincost[u] < mincost[tmp]))
                tmp = u;
        }

        if(tmp == -1) break;

        vis[tmp] = 1;
        ans += mincost[tmp];

        for(int v = 0; v < n; v++) if(!vis[v]) {
            mincost[v] = min(mincost[v], dist[tmp][v]);
        }
    }
    return ans;
}

int main() {
    while(scanf("%d", &n) && n) {
        init();

        for(int i = 0; i < n; i++) {
            //
            cin >> cargo[i];
        }

        for(int i = 0; i < n-1; i++) {
            for(int j = i+1; j < n; j++) {
                dist[i][j] = dist[j][i] = cnt_weight(cargo[i], cargo[j]);
            }
        }

        // printf("%d\n", prim(n));
        int ans = prim(n);
        printf("The highest possible quality is 1/%d.\n", ans);

    }
}