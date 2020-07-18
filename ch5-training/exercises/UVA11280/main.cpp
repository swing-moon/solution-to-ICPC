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

const int maxn = 100 + 10;
const int inf = 0x3f3f3f3f;
int tot = 0;
map<string, int> id;
int n, m;

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
    int u, k, dist;
    State() {}
    State(int u, int k, int dist) : u(u), k(k), dist(dist) {}

    bool operator< (const State& rhs) const {
        return dist > rhs.dist;
    }
};


int vis[maxn][maxn];
int D[maxn][maxn];

void initDij(const int st) {
    Set(vis, 0);
    Set(D, inf);
    D[st][0] = 0;
}

void dijkstra(const int st) {
    initDij(st);
    priority_queue<State> que;
    que.push(State(st, 0, 0));

    while (!que.empty()) {
        State x = que.top();
        que.pop();
        if(vis[x.u][x.k]) continue;
        vis[x.u][x.k] = 1;

        _for(i, 0, G[x.u].size()) {
            const Edge& e = edges[G[x.u][i]];
            int y = e.to;

            if(D[y][x.k+1] > D[x.u][x.k] + e.weight) {
                D[y][x.k+1] = D[x.u][x.k] + e.weight;
                que.push(State(y, x.k+1, D[y][x.k+1]));
            }
        }
    }
}
// == Dijkstra finished ==

inline void getID(const string& str) {
    if(id.count(str)) return;
    else {
        id[str] = ++tot;
        return;
    }
}

void solve() {
    int q;
    scanf("%d", &q);
    while (q--) {
        int S;
        scanf("%d", &S);

        int ans = inf;
        _rep(k, 1, S + 1) ans = min(ans, D[n][k]);

        //debug(ans);
        if(ans != inf) printf("Total cost of flight(s) is $%d\n", ans);
        else printf("No satisfactory flights\n");
    }
}

void init() {
    tot = 0;
    id.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    int T = 0;
    scanf("%d", &T);

    _rep(kase, 1, T) {
        printf("Scenario #%d\n", kase);
        init();
        initG();

        // get city data
        scanf("%d", &n);
        _for(i, 0, n) {
            string str;
            cin >> str;
            getID(str);
        }
        // get flights data
        scanf("%d", &m);
        _for(i, 0, m) {
            string from, to;
            int w;
            cin >> from >> to >> w;
            int u = id[from], v = id[to];
            //debug(u), debug(v), debug(w), puts("");

            addEdge(u, v, w);
        }
        // get query
        dijkstra(1);
        solve();
        if(kase != T) cout << endl;
    }
}