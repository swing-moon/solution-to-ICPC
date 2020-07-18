#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>
#include <cmath>
#include <bitset>
#include <assert.h>

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _forS(i, l, r) for(set<int>::iterator i = (l); i != (r); i++)
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define _forDown(i, l, r) for(int i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }
#define _forPlus(i, l, d, r) for(int i = (l); i + d < (r); i++)
#define lowbit(i) (i & (-i))

const int maxn = 200000 + 10;
const int inf = 0x3f;
int N;

class Graph {
public:
    int tot;
    int head[maxn], ver[maxn * 2], nxt[maxn * 2];
    int w[maxn * 2];

    void clear() {
        tot = 1;
        Set(head, 0);
        Set(ver, 0);
        Set(nxt, 0);
        Set(w, 0);
    }

    void add(int x, int y, int z) {
        ver[++tot] = y;

        w[tot] = z;

        nxt[tot] = head[x];
        head[x] = tot;
    }
};

Graph G;
int deg[maxn], vis[maxn];
int ds[maxn], f[maxn];

void init() {
    G.clear();
    Set(deg, 0);
    Set(vis, 0);
    Set(ds, 0);
    Set(f, 0);
}

void dp(int x) {
    assert(vis[x] == 0);
    ds[x] = 0;
    vis[x] = 1;

    for(int i = G.head[x]; i; i = G.nxt[i]) {
        int y = G.ver[i];
        if(vis[y]) continue;
        dp(y);

        if(deg[y] == 1) ds[x] += G.w[i];
        else ds[x] += min(G.w[i], ds[y]);
    }
}

void initdfs(int root) {
    Set(vis, 0);
    f[root] = ds[root];
}

void dfs(int x) {
    vis[x] = 1;
    for(int i = G.head[x]; i; i = G.nxt[i]) {
        int y = G.ver[i];
        if(vis[y]) continue;

        int flow = min(ds[y], G.w[i]);
        if(deg[x] == 1) f[y] = ds[y] + G.w[i];
        else {
            f[y] = ds[y] + min(G.w[i], f[x] - flow);
        }

        dfs(y);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    while (T--) {
        init();
        scanf("%d", &N);

        _for(i, 1, N) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            G.add(x, y, z);
            G.add(y, x, z);

            deg[x]++;
            deg[y]++;
        }

        // then dp
        int root = 1;
        dp(root);

        initdfs(root);
        dfs(root);

        int ans = 0;
        _rep(i, 1, N) ans = max(ans, f[i]);

        cout << ans << endl;
    }
}