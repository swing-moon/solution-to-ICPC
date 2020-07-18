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
typedef long long ll;
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

const int maxn = 100000 + 10;

// == define Edge and Graph ==
class Edge {
public:
    int to;
    Edge() {}
    Edge(int to) : to(to) {}
};

vector<Edge> edges;
vector<int> G[maxn];
// == Edge and Graph finished ==

// == eDCC graph ==
vector<Edge> eDCC;
vector<int> GC[maxn];
// == eDCC finsihed ==

// == tarjan info ==
int n, m;
int dfn[maxn], low[maxn];
bool bridge[maxn << 1];
int Clock = 0;

void init() {
    Clock = 0;
    edges.clear();
    edges.push_back(Edge());
    edges.push_back(Edge());
    // NIL edges

    Set(dfn, 0);
    Set(low, 0);
    Set(bridge, 0);
}
// == tarjan info finsihed ==

// == tarjan ==
void addEdge(int u, int v) {
    edges.push_back(Edge(v));
    G[u].push_back(edges.size() - 1);
}

void tarjan(int u, int in_edge) {
    dfn[u] = low[u] = ++Clock;
    _for(i, 0, G[u].size()) {
        int eid = G[u][i], v = edges[eid].to;

        if(!dfn[v]) {
            tarjan(v, eid);
            low[u] = min(low[u], low[v]);

            if(low[v] > dfn[u]) bridge[eid] = bridge[eid^1] = 1;
        }
        else if(eid != (in_edge^1)) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
// == tarjan finsihed ==

// == calculate eDCC ==
int dcc = 0;
int belong[maxn];
void initDCC() {
    eDCC.clear();
    eDCC.push_back(Edge());
    eDCC.push_back(Edge());
    // used as NIL

    dcc = 0;
    Set(belong, 0);
}

void add_c(int u, int v) {
    eDCC.push_back(Edge(v));
    GC[u].push_back(eDCC.size() - 1);
}

void dfs(int u) {
    belong[u] = dcc;
    _for(i, 0, G[u].size()) {
        int eid = G[u][i], v = edges[eid].to;
        if(belong[v] || bridge[eid]) continue;
        dfs(v);
    }
}

void getDCC() {
    _rep(i, 1, n) {
        if(!belong[i]) {
            ++dcc;
            dfs(i);
        }
    }
    printf("There are %d e-DCCs.\n", dcc);
    _rep(i, 1, n) printf("%d belongs to DCC %d.\n", i, belong[i]);

    _for(i, 2, edges.size()) {
        int u = edges[i^1].to, v = edges[i].to;
        if(belong[u] == belong[v]) continue;
        add_c(belong[u], belong[v]);
    }

    printf("缩点之后的森林，点数 %d，边数 %d\n", dcc, (eDCC.size()-1)>>1);
    for(int i = 2; i < eDCC.size(); i += 2) {
        printf("eDCC%d  <--->  eDCC%d\n", eDCC[i^1].to, eDCC[i].to);
    }
}
// == eDCC finsihed ==

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> m;

    init();
    _rep(i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    // == tarjan ==
    _rep(i, 1, n) if(!dfn[i]) tarjan(i, 0);
    for(int i = 2; i < edges.size(); i += 2) if(bridge[i]) {
        printf("%d %d\n", edges[i^1].to, edges[i].to);
    }

    // == eDCC ==
    initDCC();
    getDCC();
}