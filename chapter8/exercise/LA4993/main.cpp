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

const int maxn = 10000 + 10;

class Edge {
public:
    int from, to;
    Edge(int f = 0, int t = 0) : from(f), to(t) {}
};

vector<Edge> edges;
vector<int> G[maxn];
int n, m, k;

int color[maxn], vis[maxn];

void init() {
    Set(color, 0);
    Set(vis, 0);
    _for(i, 0, maxn) G[i].clear();
    edges.clear();
    k = 0;
}

void initVis() {
    Set(vis, 0);
}

void addEdge(int from, int to) {
    edges.push_back(Edge(from, to));
    int m = edges.size();
    G[from].push_back(m - 1);
}

void dfs(int u) {
    initVis();
    _for(i, 0, G[u].size()) {
        Edge cur = edges[G[u][i]];
        if(color[cur.to]) vis[color[cur.to]] = 1;
    }

    _rep(i, 1, k) {
        if(!vis[i]) {
            color[u] = i;
            break;
        }
    }

    _for(i, 0, G[u].size()) {
        Edge cur = edges[G[u][i]];
        if(!color[cur.to]) dfs(cur.to);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;

    while (scanf("%d%d", &n, &m) != EOF) {
        init();
        if(++kase > 1) printf("\n");

        int u, v;
        _for(i, 0, m) {
            scanf("%d%d", &u, &v);
            addEdge(u - 1, v - 1);
            addEdge(v - 1, u - 1);
        }
        _for(i, 0, n) k = max(k, (int)G[i].size());

        if(k % 2 == 0) k++;
        cout << k << endl;

        dfs(0);
        _for(i, 0, n) cout << color[i] << endl;
    }
}