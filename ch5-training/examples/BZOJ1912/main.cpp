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

const int maxn = 100000 + 10;

class Edge {
public:
    int to, weight;
    Edge(int t = 0, int w = 0) : to(t), weight(w) {}
};

vector<Edge> edges;
vector<int> G[maxn];
int n, k;
int pa[maxn * 2], d[maxn * 2], vis[maxn * 2];

void init() {
    edges.push_back(Edge());
    edges.push_back(Edge());

    _for(i, 0, maxn) G[i].clear();
    Set(pa, 0);
    Set(d, 0);
    Set(vis, 0);
}

void addEdge(int from, int to, int w) {
    edges.push_back(Edge(to, w));
    G[from].push_back(edges.size() - 1);
}

void dfs(int u, int& to) {
    vis[u] = 1;

    _for(i, 0, G[u].size()) {
        int eid = G[u][i], v = edges[eid].to;

        if(vis[v]) continue;
        if((d[v] = d[u] + edges[eid].weight) >= d[to]) to = v;
        pa[v] = eid;

        dfs(v, to);
    }

    vis[u] = 0;
}

void dp(int u, int& ans) {
    vis[u] = 1;
    _for(i, 0, G[u].size()) {
        int eid = G[u][i], v = edges[eid].to;

        if(vis[v]) continue;
        dp(v, ans);

        ans = max(ans, d[u] + d[v] + edges[eid].weight);
        d[u] = max(d[u], d[v] + edges[eid].weight);
    }
}

int main() {
    freopen("input.txt", "r", stdin);

    init();
    scanf("%d%d", &n, &k);
    _for(i, 0, n) {
        int u, v;
        scanf("%d%d", &u, &v);

        addEdge(u, v, 1);
        addEdge(v, u, 1);
    }

    // then solve the problem
    int to = 1;
    dfs(1, to);

    d[to] = pa[to] = 0;
    int tto = to;
    dfs(to, tto);
    // [to, tto] is the longest path in a tree

    int ans = ((n - 1) << 1) - d[tto] + 1;

    if(k == 2) {
        while (pa[tto]) {
            int eid = pa[tto];
            edges[eid].weight = edges[eid ^ 1].weight = -1;
            tto = edges[eid ^ 1].to;
        }

        tto = 0;
        Set(d, 0);
        Set(vis, 0);
        dp(to, tto);
        ans -= (tto - 1);
    }

    printf("%d\n", ans);
}