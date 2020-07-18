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

const int maxn = 1000 + 10;
const int inf = 0x3f3f3f3f;
int n, m;

// == Graph definition ==
vector<int> G[maxn];

class Edge {
public:
    int to, weight;
    Edge() {}
    Edge(int t, int w) : to(t), weight(w) {}
};

vector<Edge> edges;

void initG() {
    _for(i, 0, maxn) G[i].clear();
    edges.clear();
}

void addEdge(int u, int v, int w) {
    edges.push_back(Edge(v, w));
    G[u].push_back(edges.size() - 1);
}

class Node {
public:
    int u, dist;
    bool operator< (const Node& rhs) const {
        return dist > rhs.dist;
    }
    Node() {}
    Node(int u, int d) : u(u), dist(d) {}
};
// == Graph finished ==

// == dijkstra ==
int D[maxn], vis[maxn];

void initDij(int st) {
    Set(D, inf);
    D[st] = 0;
    Set(vis, 0);
}

void dijkstra(int st) {
    initDij(st);
    priority_queue<Node> que;
    que.push(Node(st, 0));

    while (!que.empty()) {
        int x = que.top().u;
        que.pop();
        if(vis[x]) continue;
        vis[x] = 1;

        _for(i, 0, G[x].size()) {
            const Edge& e = edges[G[x][i]];
            int y = e.to;

            if(D[y] > D[x] + e.weight) {
                D[y] = D[x] + e.weight;
                que.push(Node(y, D[y]));
            }
        }
    }
}
// == dijkstra finished ==

// == dp ==
inline bool cmp(int a, int b) {
    return D[a] < D[b];
}
int ord[maxn];
int f[maxn];
void initDP(const int ed) {
    _rep(i, 1, n) ord[i] = i;
    sort(ord + 1, ord + 1 + n, cmp);
    //assert(ed == ord[1]);

    Set(f, 0);
    f[ed] = 1;
}

void dp(const int st) {
    _rep(i, 1, n) {
        int x = ord[i];
        _for(j, 0, G[x].size()) {
            int y = edges[G[x][j]].to;
            if(D[y] > D[x]) f[y] += f[x];
        }
    }
    printf("%d\n", f[st]);
}

void initDP() {
    Set(f, -1);
}
int dp(int x, const int ed) {
    if(x == ed) return 1;
    if(f[x] >= 0) return f[x];

    f[x] = 0;
    _for(i, 0, G[x].size()) {
        int y = edges[G[x][i]].to;
        if(D[y] < D[x]) f[x] += dp(y, ed);
    }
    return f[x];
}
// == dp finsiehd ==

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) == 2 && n) {
        initG();
        _for(i, 0, m) {
            int x, y, z;
            scanf("%d%d%d", &x, &y, &z);
            addEdge(x, y, z);
            addEdge(y, x, z);
        }

        // run dijkstra
        dijkstra(2);

        // then dp
        initDP(2);
        dp(1);

        //initDP();
        //printf("%d\n", dp(1, 2));
    }
}