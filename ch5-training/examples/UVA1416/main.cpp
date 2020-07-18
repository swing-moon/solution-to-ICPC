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
int n, m, L;

vector<int> W[maxn][maxn];
int used[maxn][maxn][maxn];
int idx[maxn][maxn];

// == Graph definition ==
vector<int> G[maxn];

class Edge {
public:
    int from, to, weight;
    Edge() {}
    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
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
    _for(i, 0, maxn) G[i].clear();
    edges.clear();
}

void addEdge(int u, int v, int w) {
    edges.push_back(Edge(u, v, w));
    G[u].push_back(edges.size() - 1);
    idx[u][v] = edges.size() - 1;
}
// == Graph finished ==

// == Dijkstra ==
int p[maxn];
int D[maxn], vis[maxn];

void initDij(int st) {
    Set(p, 0);
    Set(vis, 0);
    Set(D, inf);
    D[st] = 0;
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

            if(e.weight > 0 && D[y] > D[x] + e.weight) {
                D[y] = D[x] + e.weight;
                p[y] = G[x][i];
                que.push(Node(y, D[y]));
            }
        }
    }
}
// == Dijkstra finished ==

// == solver ==
int C[maxn];

void initCal() {
    Set(C, 0);
}

int cal() {
    initCal();

    int ans = 0;
    _rep(st, 1, n) {
        dijkstra(st);
        _rep(v, 1, n) {
            if(v != st) {
                int u = edges[p[v]].from;
                used[st][u][v] = used[st][v][u] = 1;
            }
            C[st] += (D[v] == inf ? L : D[v]);
        }
        ans += C[st];
    }
    return ans;
}


int del(int u, int v) {
    Edge& e1 = edges[idx[u][v]];
    Edge& e2 = edges[idx[v][u]];;

    if(W[u][v].size() == 1) e1.weight = e2.weight = 0;
    else if(W[u][v].size() > 1) e1.weight = e2.weight = W[u][v][1];

    int ans = 0;
    _rep(st, 1, n) {
        if(used[st][u][v] == 0) ans += C[st];
        else {
            dijkstra(st);
            _rep(i, 1, n) ans += (D[i] == inf ? L : D[i]);
        }
    }

    e1.weight = e2.weight = W[u][v][0];
    return ans;
}
// == solver finsihed ==

void init() {
    _for(i, 0, maxn) _for(j, 0, maxn) W[i][j].clear();
    Set(used, 0);
    Set(idx, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d%d", &n, &m, &L) == 3) {
        init();
        initG();

        // build graph
        _for(i, 0, m) {
            int u, v, s;
            scanf("%d%d%d", &u, &v, &s);
            W[u][v].push_back(s);
            W[v][u].push_back(s);
        }
        _rep(i, 1, n) _rep(j, i + 1, n) {
            if(W[i][j].size()) {
                sort(W[i][j].begin(), W[i][j].end());

                addEdge(i, j, W[i][j][0]);
                addEdge(j, i, W[i][j][0]);
            }
        }
        // build finished

        // solve the problem
        int c1 = cal();
        int c2 = -1;
        _rep(i, 1, n) _rep(j, i + 1, n) if(W[i][j].size()) {
            c2 = max(c2, del(i, j));
        }

        printf("%d %d\n", c1, c2);
    }
}