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

// == Edge and Graph definition ==
class Edge {
public:
    int to;
    Edge() {};
    Edge(int to) : to(to) {}
};

vector<Edge> edges;
vector<int> G[maxn];
int n, m;
// == Edge and Graph finsihed ==

// == info used for tarjan ==
int dfn[maxn], low[maxn];
bool cut[maxn];
int Clock = 0;
int root = 0;

void init() {
    Clock = 0;
    root = 0;
    edges.clear();
    edges.push_back(Edge());
    edges.push_back(Edge());
    // NIL edges

    Set(dfn, 0);
    Set(low, 0);
    Set(cut, 0);
}
// == info finished ==

// == tarjan ==
void addEdge(int u, int v) {
    edges.push_back(Edge(v));
    G[u].push_back(edges.size() - 1);
}

void tarjan(int u) {
    dfn[u] = low[u] = ++Clock;
    int cld = 0;

    _for(i, 0, G[u].size()) {
        int v = edges[G[u][i]].to;

        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if(low[v] >= dfn[u]) {
                cld++;
                if(u != root || cld > 1) cut[u] = true;
            }
        }
        else low[u] = min(low[u], dfn[v]);
    }
}
// == tarjan finsihed ==

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> m;
    init();

    _rep(i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v), addEdge(v, u);
    }

    _rep(i, 1, n) if(!dfn[i]) {
        root = i;
        tarjan(i);
    }

    _rep(i, 1, n) if(cut[i]) printf("%d ", i);
    puts("are cut-vertexes");
}
