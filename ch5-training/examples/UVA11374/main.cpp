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

const int maxn = 1000 + 10;
const int inf = 0x3f3f3f3f;
int N, S, E, K, M;

// == Graph definition ==
vector<int> G[maxn];
class Edge {
public:
    int from, to, weight;
    Edge() {}
    Edge(int f, int t, int w) : from(f), to(t), weight(w) {}
};
vector<Edge> edges;

void initG(int N) {
    _rep(i, 0, N) G[i].clear();
    edges.clear();
}

void addEdge(int u, int v, int w) {
    edges.push_back(Edge(u, v, w));
    G[u].push_back(edges.size() - 1);
}
// == Graph finished ==

// == dijkstra ==
int dist[maxn], p[maxn];
bool vis[maxn];
typedef pair<int, int> PII;

void initDij(int s) {
    Set(vis, 0);
    Set(dist, inf);
    dist[s] = 0;
}
void dijkstra(int s) {
    initDij(s);
    priority_queue<PII, vector<PII>, greater<PII> > que;
    que.push(MPR(0, s));

    while (!que.empty()) {
        int x = que.top().second;
        que.pop();
        if(vis[x]) continue;
        vis[x] = true;

        _for(i, 0, G[x].size()) {
            int y = edges[G[x][i]].to;
            int z = edges[G[x][i]].weight;

            if(dist[y] > dist[x] + z) {
                dist[y] = dist[x] + z;
                p[y] = G[x][i];
                que.push(MPR(dist[y], y));
            }
        }
    }
}
// == dijkstra finished ==

// == get path ==
vector<int> path1[maxn], path2[maxn];
int d1[maxn], d2[maxn];

// (s, a0, ..., a) <- (a, ak, ak-1, ..., a0, s)
void prework(int s, vector<int> path[], int d[]) {
    dijkstra(s);
    _rep(i, 1, N) {
        d[i] = dist[i];

        for(int t = i; t != s; t = edges[p[t]].from) path[i].push_back(t);
        path[i].push_back(s);
        reverse(path[i].begin(), path[i].end());
    }
}
// == prework finsihed ==

// == solve the problem ==
void solve() {
    int ans = d1[E];
    vector<int> path = path1[E];
    int mid = -1;

    scanf("%d", &K);
    _for(i, 0, K) {
        int X, Y, Z;
        scanf("%d%d%d", &X, &Y, &Z);

        _for(_, 0, 2) {
            if(ans > d1[X] + d2[Y] + Z) {
                ans = d1[X] + d2[Y] + Z;

                path = path1[X];
                _forDown(j, path2[Y].size() - 1, 0) {
                    path.push_back(path2[Y][j]);
                }

                mid = X;
            }
            swap(X, Y);
        }
    }

    _for(i, 0, path.size() - 1) printf("%d ", path[i]);
    printf("%d\n", E);

    if(mid == -1) printf("Ticket Not Used\n");
    else printf("%d\n", mid);

    printf("%d\n", ans);
}
// == solve finsihed ==

// init ans
void init(int n) {
    _rep(i, 0, n) {
        path1[i].clear();
        path2[i].clear();
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while (scanf("%d%d%d", &N, &S, &E) == 3) {
        scanf("%d", &M);
        init(N);

        // build graph
        initG(N);
        _for(i, 0, M) {
            int X, Y, Z;
            scanf("%d%d%d", &X, &Y, &Z);
            addEdge(X, Y, Z);
            addEdge(Y, X, Z);
        }

        // prework
        prework(S, path1, d1);
        prework(E, path2, d2);

        // solve the problem
        if(kase != 0) printf("\n");
        kase++;

        solve();
    }
}