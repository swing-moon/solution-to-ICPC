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
#define Cpy(a, b) memcpy(a, b, sizeof(b))
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

const int inf = 0x3f3f3f3f;
const int maxn = 1000 + 10;
int n, m;
int P[maxn];

// == Graph definition ==
vector<int> G[maxn];

class Edge {
public:
    int from, to, weight;
    Edge() {}
    Edge(int u, int v, int w) : from(u), to(v), weight(w) {}
};

vector<Edge> edges;

void initG() {
    _for(i, 0, maxn) G[i].clear();
    edges.clear();
}

void addEdge(int u, int v, int w) {
    edges.push_back(Edge(u, v, w));
    G[u].push_back(edges.size() - 1);
}
// == Graph finished ==

// == Dijkstra ==
class State {
public:
    int u, gas, cost;
    bool operator< (const State& rhs) const {
        return cost > rhs.cost;
    }

    State() {}
    State(int u, int g, int c) : u(u), gas(g), cost(c) {}
};

int vis[maxn][maxn];
int ans = inf;

void initDij(int st, const int C) {
    Set(vis, 0);
    ans = inf;
}

bool dijkstra(int st, int ed, const int C) {
    initDij(st, C);
    priority_queue<State> que;
    que.push(State(st, 0, 0));

    while (!que.empty()) {
        State x = que.top();
        que.pop();

        if(x.u == ed) {
            ans = x.cost;
            return true;
        }

        if(vis[x.u][x.gas]) continue;
        vis[x.u][x.gas] = 1;

        if(x.gas + 1 <= C) {
            State nxt(x.u, x.gas + 1, x.cost + P[x.u]);
            que.push(nxt);
        }
        _for(i, 0, G[x.u].size()) {
            const Edge& e = edges[G[x.u][i]];
            int y = e.to;

            if(x.gas >= e.weight) {
                State nxt(y, x.gas - e.weight, x.cost);
                que.push(nxt);
            }
        }
    }
    return false;
}
// == Dijkstra finsihed ==

void init() {
    Set(P, 0);
}

void solve() {
    int q;
    scanf("%d", &q);
    while (q--) {
        int st, ed, C;
        scanf("%d%d%d", &C, &st, &ed);
        if(dijkstra(st, ed, C)) printf("%d\n", ans);
        else printf("impossible\n");
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);

    initG();
    init();
    // get data
    _for(i, 0, n) scanf("%d", &P[i]);
    _for(i, 0, m) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        addEdge(u, v, w);
        addEdge(v, u, w);
    }

    // each query, dijkstra
    solve();
}