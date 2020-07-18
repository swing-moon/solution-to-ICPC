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
const int maxN = 4000000;
int cost[maxn][maxn][3];
int n, m;

// == Graph definition ==
vector<int> G[maxN];
class Edge {
public:
    int to, weight;
    Edge() {}
    Edge(int to, int w) : to(to), weight(w) {}
};

class Node {
public:
    int u, dist;
    Node() {}
    Node(int u, int d) : u(u), dist(d) {}
    bool operator< (const Node& rhs) const {
        return dist > rhs.dist;
    }
};
vector<Edge> edges;

void initG() {
    _for(i, 0, maxN) G[i].clear();
    edges.clear();
}

void addEdge(int u, int v, int w) {
    edges.push_back(Edge(v, w));
    G[u].push_back(edges.size() - 1);
}
// == Graph finished ==

// == dijkstra ==
int D[maxN], vis[maxN];

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
// == dijkstra finsihed ==

inline int ID(int i, int j, int dir) {
    return i*m+j+1 + dir*n*m;
}

inline int read() {
    int x;
    scanf("%d", &x);
    return x;
}

// == build graph ==
void getEdge(int *e1, int *e2, int *e3) {
    int *edges[3] = {e1, e2, e3};
    // edges[i]:= (i, j, dir)
    _for(i, 0, 3) _for(j, 0, 3) if(i != j) {
        int u = ID(edges[i][0], edges[i][1], edges[i][2]);
        int v = ID(edges[j][0], edges[j][1], edges[j][2]);
        int w = cost[edges[j][0]][edges[j][1]][edges[j][2]];

        addEdge(u, v, w);
    }
}

void build() {
    _for(i, 0, n - 1) _for(j, 0, m - 1) {
        int top[] = {i, j, 0};
        int bottom[] = {i + 1, j, 0};
        int left[] = {i, j, 1};
        int right[] = {i, j + 1, 1};
        int slash[] = {i, j, 2};

        getEdge(top, right, slash);
        getEdge(bottom, left, slash);
    }

    _for(i, 0, n - 1) {
        int u = ID(i, 0, 1);
        int w = cost[i][0][1];
        addEdge(0, u, w);
    }
    _for(i, 0, m - 1) {
        int u = ID(n - 1, i, 0);
        int w = cost[n - 1][i][0];
        addEdge(0, u, w);
    }
}
// == build finsiehd ==

void init() {
    Set(cost, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while (scanf("%d%d", &n, &m) == 2 && n) {
        init();
        initG();

        // get data
        _for(i, 0, n) _for(j, 0, m-1) cost[i][j][0] = read();
        _for(i, 0, n - 1) _for(j, 0, m) cost[i][j][1] = read();
        _for(i, 0, n - 1) _for(j, 0, m - 1) cost[i][j][2] = read();

        // build graph
        build();

        // dijkstra
        dijkstra(0);

        // get ans
        int ans = inf;
        _for(i, 0, n - 1) ans = min(ans, D[ID(i, m - 1, 1)]);
        _for(i, 0, m - 1) ans = min(ans, D[ID(0, i, 0)]);

        //debug(ans);

        printf("Case %d: Minimum = %d\n", ++kase, ans);
    }
}