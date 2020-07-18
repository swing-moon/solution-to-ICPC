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

const int maxn = 1e3 + 10;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int n, m, st, ed;

// == Graph definition ==
vector<int> G[maxn];
int vis[maxn];
ll D[maxn];

class Edge {
public:
    int to, w;
    Edge(int t, int w) : to(t), w(w) {}
    Edge() {}
};

vector<Edge> edges;

void addEdge(int u, int v, int w) {
    edges.push_back(Edge(v, w));
    G[u].push_back(edges.size() - 1);
}

void initG(int st) {
    _for(i, 0, maxn) D[i] = inf;
    D[st] = 0;
    Set(vis, 0);
}
// == Graph finished ==

// == Dijkstra ==
struct Node {
    int u;
    ll dist;
    Node() {}
    Node(int u, ll d) : u(u), dist(d) {}
    bool operator< (const Node& rhs) const {
        return dist > rhs.dist;
    }
};

void dijkstra(int st) {
    priority_queue<Node> que;
    que.push(Node(st, 0));

    while (!que.empty()) {
        int x = que.top().u;
        que.pop();
        if(vis[x]) continue;
        vis[x] = true;

        _for(i, 0, G[x].size()) {
            const Edge& e = edges[G[x][i]];
            int y = e.to;
            if(D[y] > D[x] + 1ll * e.w) {
                D[y] = D[x] + 1ll * e.w;
                que.push(Node(y, D[y]));
            }
        }
    }
}
// == Dijkstra finished ==

// == dp ==
ll f[2][maxn];
bool cmp(int a, int b) {
    return D[a] < D[b];
}
int ord[maxn];

void initDp() {
    Set(f, 0);
    f[0][st] = 1ll;
    _rep(i, 1, n) ord[i] = i;
    sort(ord + 1, ord + 1 + n, cmp);
}

void dp() {
    _for(k, 0, 2) _rep(i, 1, n) {
        int x = ord[i];
        _for(j, 0, G[x].size()) {
            const Edge& e = edges[G[x][j]];
            int y = e.to;
            if(D[y] == D[x] + e.w) f[k][y] += f[k][x];
            if(k == 0 && D[y] + 1 == D[x] + e.w) f[1][y] += f[0][x];
        }
    }
}

// == dp finsiehd ==

void init() {
    _for(i, 0, maxn) G[i].clear();
    edges.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);
    while (kase--) {
        init();
        scanf("%d%d", &n, &m);

        // input data
        _for(i, 0, m) {
            int u, v, l;
            scanf("%d%d%d", &u, &v, &l);
            addEdge(u, v, l);
        }
        scanf("%d%d", &st, &ed);


        // dijkstra
        initG(st);
        dijkstra(st);

        // then dp
        initDp();
        dp();

        printf("%lld\n", f[0][ed] + f[1][ed]);
    }
}