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
    int from, to;
    Edge(int f = 0, int t = 0) : from(f), to(t) {}
};

vector<Edge> edges;
vector<int> G[maxn];
int n, m;
// == Edge and Graph finished ==

// == info for tarjan ==
int dfn[maxn], low[maxn];
bool bridge[maxn];
int Clock = 0;

void init() {
    edges.clear();
    edges.push_back(Edge());
    edges.push_back(Edge());
    // just for NIL

    Set(dfn, 0);
    Set(low, 0);
    Set(bridge, 0);

    Clock = 0;
}
// == info finished ==

// == tarjan ==
void addEdge(int u, int v) {
    edges.push_back(Edge(u, v));
    G[u].push_back(edges.size() - 1);
}

void tarjan(int u, int eID) {
    dfn[u] = low[u] = ++Clock;
    _for(i, 0, G[u].size()) {
        int id = G[u][i];
        int v = edges[id].to;

        if(!dfn[v]) {
            tarjan(v, id);
            low[u] = min(low[u], low[v]);

            if(low[v] > dfn[u]) bridge[id] = bridge[id^1] = 1;
        }
        else if(id != (eID^1)) {
            low[u] = min(low[u], dfn[v]);
        }
    }
}
// == tarjan fisihed ==

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> m;
    init();

    _rep(i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v), addEdge(v, u);
    }
    _rep(i, 1, n) if(!dfn[i]) tarjan(i, 0);
    for(int i = 2; i < edges.size(); i += 2) {
        if(bridge[i]) printf("%d %d\n", edges[i^1].to, edges[i].to);
    }
}