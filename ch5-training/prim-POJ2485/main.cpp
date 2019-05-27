#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>

using namespace std;
const int maxn = 500 + 10;
const int inf = 0x3f3f3f3f;

int G[maxn][maxn];
int n;

int prim(int n) {
    int mincost[n], used[n];
    for(int i = 0; i < n; i++) {
        mincost[i] = inf, used[i] = 0;
    }

    mincost[0] = 0; int ans = 0;

    while(true) {
        int tmp = -1;
        for(int i = 0; i < n; i++) {
            if(!used[i] && (tmp == -1 || mincost[i] < mincost[tmp]))
                tmp = i;
        }


        if(tmp == -1) break;
        used[tmp] = 1; ans = max(ans, mincost[tmp]);

        for(int i = 0; i < n; i++) {
            mincost[i] = min(mincost[i], G[tmp][i]);
        }
    }
    return ans;
}

int main() {
    freopen("a.txt", "r", stdin);

    int T;
    scanf("%d", &T);

    while(T--) {
        memset(G, 0, sizeof(G));
        scanf("%d", &n);

        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                scanf("%d", &G[i][j]);
            }
        }

        int res = prim(n);
        cout << res << endl;
    }
}