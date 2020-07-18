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

const int maxn = 25000 + 10;
const int inf = 0x3f3f3f3f;
const int INF = 0x7f;
int N, R, P, S;

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
// == Graph finished ==

// == prework ==
// usage: prework(N) to calculate connect component
int cnt = 0;
int belong[maxn];
void dfs(int x, int cnt) {
    belong[x] = cnt;
    _for(i, 0, G[x].size()) {
        int y = edges[G[x][i]].to;
        if(belong[y]) continue;
        dfs(y, cnt);
    }
}

void prework(int N) {
    _rep(i, 1, N) {
        if(!belong[i]) {
            ++cnt;
            dfs(i, cnt);
        }
    }
}
// == prework finished ==

// == use for topo sort ==
int deg[maxn];
// == topo finsihed ==

// == dijkstra with top ==
int dist[maxn];
bool vis[maxn];
typedef pair<int, int> PII;
priority_queue<PII, vector<PII>, greater<PII> > pque;
queue<int> que;

void initDij() {
    Set(vis, 0);
    Set(dist, INF);
    dist[S] = 0;
    que.push(belong[S]);
}

void dijkstra() {
    initDij();
    _rep(i, 1, cnt) if(deg[i] == 0) que.push(i);

    while (!que.empty()) {
        int c = que.front();
        que.pop();
        _rep(i, 1, N) if(belong[i] == c) pque.push(MPR(dist[i], i));

        while (!pque.empty()) {
            int x = pque.top().second;
            pque.pop();
            if(vis[x]) continue;
            vis[x] = true;

            _for(i, 0, G[x].size()) {
                int y = edges[G[x][i]].to;
                int z = edges[G[x][i]].weight;
                if(dist[y] > dist[x] + z) {
                    dist[y] = dist[x] + z;
                    if(belong[x] == belong[y]) pque.push(MPR(dist[y], y));
                }

                if(belong[x] != belong[y] && --deg[belong[y]] == 0) que.push(belong[y]);
            }
        }
    }
}
// == dijkstra finsiehd ==

void init() {
    cnt = 0;
    Set(belong, 0);
    Set(deg, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    init();
    cin >> N >> R >> P >> S;

    // build Graph
    initG();
    _rep(i, 1, R) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addEdge(x, y, z);
        addEdge(y, x, z);
    }
    prework(N);
    // build negative Graph
    _rep(i, 1, P) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addEdge(x, y, z);
        if(belong[x] != belong[y]) ++deg[belong[y]];
    }

    // topo and dijkstra
    dijkstra();
    _rep(i, 1, N) {
        if(dist[i] >= inf) puts("NO PATH");
        else printf("%d\n", dist[i]);
    }
}

