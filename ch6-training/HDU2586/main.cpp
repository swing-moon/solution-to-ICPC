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
#define MPR(a, b) make_pair(a, b)

const int maxn = 50000 + 10;
const int maxt = 20;
int n, m, t;
int T;

// == lca init() ==
int f[maxn][maxt], dist[maxn], dep[maxn];
// == lca finished ==

// == graph ==
int head[maxn], ver[maxn * 2], nxt[maxn * 2], w[maxn * 2];
int tot = 0;

void init() {
    Set(head, 0);
    Set(ver, 0);
    Set(nxt, 0);
    Set(w, 0);
    Set(f, 0);
    Set(dist, 0);
    Set(dep, 0);
    tot = 0;
}
void add(int x, int y, int z) {
    ver[++tot] = y, nxt[tot] = head[x], head[x] = tot;
    w[tot] = z;
}
// == graph finished ==

// == init lca and bfs() ==
queue<int> que;
void bfs() {
    t = (int)(log(n) / log(2)) + 1;

    que.push(1), dep[1] = 1;
    while (!que.empty()) {
        int x = que.front(); que.pop();
        for(int i = head[x]; i; i = nxt[i]) {
            int y = ver[i];
            if(dep[y]) continue;

            dep[y] = dep[x] + 1;
            f[y][0] = x;
            dist[y] = dist[x] + w[i];
            _rep(k, 1, t) f[y][k] = f[f[y][k - 1]][k - 1];

            que.push(y);
        }
    }
}
// == bfs finished

// == lca ==
int lca(int x, int y) {
    if(dep[x] > dep[y]) swap(x, y);
    _forDown(k, t, 0) if(dep[f[y][k]] >= dep[x]) y = f[y][k];

    if(x == y) return x;

    _forDown(k, t, 0) if(f[x][k] != f[y][k]) {
        x = f[x][k], y = f[y][k];
    }

    return f[x][0];
}
// == lca finished ==


int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &T);
    while (T--) {
        init();
        scanf("%d%d", &n, &m);
        _for(i, 1, n) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            add(x, y, z);
            add(y, x, z);
        }
        // == input finished ==

        // bfs and lca
        bfs();
        _rep(i, 1, m) {
            int x, y;
            scanf("%d%d", &x, &y);
            printf("%d\n", dist[x] + dist[y] - 2 * dist[lca(x, y)]);
        }
    }
}