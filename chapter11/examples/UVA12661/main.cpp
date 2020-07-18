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

const int maxn = 300 + 10;
const int inf = 0x3f3f3f3f;
int n, m, s, t;
int D[maxn], vis[maxn];

// == Graph definition ==
vector<int> G[maxn];

class Edge {
public:
    int from, to, a, b, t;
    Edge(int from, int to, int a, int b, int t) : from(from), to(to), a(a), b(b), t(t) {}
    Edge() {}
};

vector<Edge> edges;

void addEdge(int u, int v, int a, int b, int t) {
    edges.push_back(Edge(u, v, a, b, t));
    G[u].push_back(edges.size() - 1);
}

void initG(int s) {
    Set(D, inf);
    D[s] = 0;
    Set(vis, 0);
}
// == Graph finished ==

// == Dijkstra ==
struct Node {
    int u, dist;
    Node(int u, int d) : u(u), dist(d) {}
    Node() {}
    bool operator< (const Node& rhs) const {
        return dist > rhs.dist;
    }
};

void dijkstra(int s) {
    priority_queue<Node> que;
    que.push(Node(s, 0));

    while (!que.empty()) {
        int x = que.top().u;
        que.pop();
        if(vis[x]) continue;
        vis[x] = true;

        _for(i, 0, G[x].size()) {
            const Edge& e = edges[G[x][i]];
            int y = e.to;
            if(e.t > e.a) continue;

            int w, r = D[x] % (e.a + e.b);
            if(r + e.t <= e.a) w = e.t;
            else w = e.a + e.b - r + e.t;

            if(D[y] > D[x] + w) {
                D[y] = D[x] + w;
                que.push(Node(y, D[y]));
            }
        }
    }
}
// == Dijkstra finished ==

void init() {
    _rep(i, 0, n) G[i].clear();
    edges.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while (~scanf("%d%d%d%d", &n, &m, &s, &t)) {
        init();
        printf("Case %d: ", ++kase);

        // get data
        _for(i, 0, m) {
            int u, v, a, b, t;
            scanf("%d%d%d%d%d", &u, &v, &a, &b, &t);
            addEdge(u, v, a, b, t);
        }

        // then dijkstra
        initG(s);
        dijkstra(s);
        printf("%d\n", D[t]);
    }
}