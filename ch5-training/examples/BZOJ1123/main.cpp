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
    int from, to;
    Edge(int f = 0, int t = 0) : from(f), to(t) {}
};

vector<Edge> edges;
vector<int> G[maxn];
int dfn[maxn], low[maxn], cut[maxn], size[maxn];
llong ans[maxn];
int clk;
int root;

int n, m;

void init() {
    edges.clear();
    edges.push_back(Edge());

    Set(dfn, 0);
    Set(low, 0);
    Set(ans, 0);
    Set(cut, 0);
    Set(size, 0);

    clk = 0;
}

void addEdge(int u, int v) {
    edges.push_back(Edge(u, v));
    G[u].push_back(edges.size() - 1);
}

void tarjan(int u) {
    dfn[u] = low[u] = ++clk;
    size[u] = 1;

    int cld = 0, sum = 0;

    _for(i, 0, G[u].size()) {
        int eid = G[u][i];
        int v = edges[eid].to;
        //debug(v);

        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            size[u] += size[v];

            if(low[v] >= dfn[u]) {
                cld++;
                ans[u] += (llong)(size[v]) * (n - size[v]);
                sum += size[v];

                if(u != root || cld > 1) cut[u] = 1;
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
    if(!cut[u]) ans[u] = 2 * (n - 1);
    else {
        ans[u] += ((n - 1) + (llong)(n - 1 - sum) * (sum + 1));
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    init();

    scanf("%d%d", &n, &m);

    _for(i, 0, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        if(u == v) continue;

        addEdge(u, v);
        addEdge(v, u);
    }
    // node start from 1

    root = 1;
    tarjan(root);

    _rep(i, 1, n) printf("%lld\n", ans[i]);
}