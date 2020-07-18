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

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, -1, 0, 1};
const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;
const int inv[] = {2, 3, 0, 1};

const int maxn = 100 + 5;
int R, C, r1, c1, r2, c2;
int cost[maxn][maxn][4];
int N;
const int maxN = maxn * maxn * 8 + 5;
const int inf = 0x3f3f3f3f;

inline int read() {
    int x;
    scanf("%d", &x);
    return x;
}

// == Graph defintion ==
vector<int> G[maxN];

class Edge {
public:
    int from, to, weight;
    Edge() {}
    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
};

vector<Edge> edges;

class Node {
public:
    int u, dist;
    bool operator< (const Node& rhs) const {
        return dist > rhs.dist;
    }

    Node() {}
    Node(int u, int d) : u(u), dist(d) {}
};

void initG() {
    edges.clear();
    _for(i, 0, maxN) G[i].clear();
}

void addEdge(int u, int v, int w) {
    edges.push_back(Edge(u, v, w));
    G[u].push_back(edges.size() - 1);
}
// == Graph finsihed ==

// == build data ==
int id[maxn][maxn][4][2];
int tot = 0;

inline int ID(int r, int c, int dir, int doubled) {
    int& x = id[r][c][dir][doubled];
    if(x != 0) return x;
    x = ++tot;
    return x;
}

void init() {
    tot = 0;
    Set(id, 0);
}
// [1, R], [1, C]
inline bool valid(int r, int c, int dir) {
    if(r <= 0 || r > R || c <= 0 || c > C) return false;
    return cost[r][c][dir] > 0;
}
// == data finished ==

// == build graph ==
void build() {
    _for(dir, 0, 4) if(valid(r1, c1, dir)) {
        int u = ID(r1+dr[dir], c1+dc[dir], dir, 1);
        assert(u >= 1);
        int w = cost[r1][c1][dir] * 2;
        addEdge(0, u, w);
    }

    _rep(r, 1, R) _rep(c, 1, C) _for(dir, 0, 4) if(valid(r, c, inv[dir])) {
        _for(nDir, 0, 4) if(valid(r, c, nDir)) {
            _for(doubled, 0, 2) {
                int nr = r + dr[nDir];
                int nc = c + dc[nDir];
                int w = cost[r][c][nDir];
                int nDoubled = 0;

                if(nDir != dir) {
                    nDoubled = 1;
                    if(!doubled) w += cost[r][c][inv[dir]];
                    w += cost[r][c][nDir];
                }

                addEdge(ID(r, c, dir, doubled), ID(nr, nc, nDir, nDoubled), w);
            }
        }
    }
}
// == build finsihed ==

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

// == solve ==
void solve(int& ans) {
    _for(dir, 0, 4) _for(doubled, 0, 2) {
        int ed = ID(r2, c2, dir, doubled);
        int res = D[ed];
        if(!doubled) res += cost[r2][c2][inv[dir]];
        ans = min(ans, res);
    }
}
// == solve finsihed ==

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while (scanf("%d%d%d%d%d%d", &R, &C, &r1, &c1, &r2, &c2) == 6 && R) {
        init();
        initG();

        // input grid data
        _rep(r, 1, R) {
            _rep(c, 1, C - 1) cost[r][c][RIGHT] = cost[r][c+1][LEFT] = read();
            if(r != R) {
                _rep(c, 1, C)  cost[r][c][DOWN] = cost[r+1][c][UP] = read();
            }
        }
        N = R*C*8 + 1;

        // build graph
        build();

        // run dijkstra
        dijkstra(0);

        // solve
        int ans = inf;
        solve(ans);

        printf("Case %d: ", ++kase);
        if(ans == inf) printf("Impossible\n");
        else printf("%d\n", ans);
    }
}