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

inline void addEdge(int u, int v) {
    edges.push_back(Edge(v));
    G[u].push_back(edges.size() - 1);
}
// == Edge and Graph finsihed ==

// == SCC Graph ==
vector<int> GC[maxn];
vector<int> SCC[maxn];
vector<Edge> eSCC;

inline void add_c(int u, int v) {
    eSCC.push_back(Edge(v));
    GC[u].push_back(eSCC.size() - 1);
}
// == SCC finished ==

// == tarjan info ==
int dfn[maxn], low[maxn];
int ins[maxn];
int cnt = 0, Clock = 0;
int belong[maxn];
stack<int> stk;

void init() {
    Set(dfn, 0);
    Set(low, 0);
    cnt = Clock = 0;

    edges.push_back(Edge());
    edges.push_back(Edge());
    // used as NIL
}

void initSCC() {
    Set(belong, 0);
    Set(ins, 0);

    eSCC.push_back(Edge());
    eSCC.push_back(Edge());
    // used as NIL

    while (!stk.empty()) stk.pop();
}
// == tarjan info finished ==

// == tarjan and get SCC ==
void tarjan(int u) {
    dfn[u] = low[u] = ++Clock;
    stk.push(u), ins[u] = 1;

    _for(i, 0, G[u].size()) {
        int v = edges[G[u][i]].to;
        if(!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if(ins[v]) {
            low[u] = min(low[u], dfn[v]);
        }
    }

    if(low[u] == dfn[u]) {
        cnt++;
        for(;;) {
            int z = stk.top(); stk.pop(); ins[z] = 0;
            belong[z] = cnt;
            SCC[cnt].push_back(z);

            if(z == u) break;
        }
    }
}
// == tarjan and SCC finsihed ==

int n, m;
int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> m;

    init();
    initSCC();

    _rep(i, 1, m) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
    }

    _rep(i, 1, n) if(!dfn[i]) tarjan(i);

    _rep(u, 1, n) _for(i, 0, G[u].size()) {
        int v = edges[G[u][i]].to;
        if(belong[v] == belong[u]) continue;

        add_c(belong[u], belong[v]);
    }

    // print ans
    _rep(i, 1, cnt) {
        printf("连通分量#%d含有的点为:", i);
        _for(j, 0, SCC[i].size()) printf(" %d", SCC[i][j]);
        printf("\n");
    }
    puts("");

    printf("缩点之后的图显示如下： \n");
    _rep(i, 1, cnt + 1) {
        if(GC[i].size() == 0) continue;

        _for(j, 0, GC[i].size()) {
            int v = eSCC[GC[i][j]].to;
            printf("#%d <==> #%d\n", i, v);
        }
    }

    _rep(i, 1, n) {
        printf("low[%d]=%d ",i, low[i]);
    }
    puts("");
}