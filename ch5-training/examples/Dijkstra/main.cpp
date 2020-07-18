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

const int inf = 0x3f3f3f3f;
const int maxn = 1e6 + 5;

// == Graph definition ==
vector<int> G[maxn];
class Edge {
public:
    int to, weight;
    Edge() {}
    Edge(int to, int w) : to(to), weight(w) {}
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

int st[maxn], ed[maxn], w[maxn];
typedef pair<int, int> PII;
int n, m;

// == Dijkstra ==
int vis[maxn], dist[maxn];

void initDij() {
    Set(dist, inf);
    Set(vis, 0);
    dist[1] = 0;
}

void dijkstra() {
    priority_queue<PII, vector<PII>, greater<PII> > que;
    que.push(MPR(0, 1));

    while (!que.empty()) {
        int x = que.top().second; que.pop();
        if(vis[x]) continue;
        vis[x] = 1;

        _for(i, 0, G[x].size()) {
            int y = edges[G[x][i]].to;
            int z = edges[G[x][i]].weight;

            if(dist[y] > dist[x] + z) {
                dist[y] = dist[x] + z;
                que.push(MPR(dist[y], y));
            }
        }
    }
}
// == Dijkstra finished ==

int main() {
    freopen("input.txt", "r", stdin);

    int kase;
    scanf("%d", &kase);
    while (kase--) {
        scanf("%d%d", &n, &m);

        initG();
        _rep(i, 1, m) {
            scanf("%d%d%d", &st[i], &ed[i], &w[i]);
            addEdge(st[i], ed[i], w[i]);
        }

        initDij();
        dijkstra();

        ll sum = 0;
        _rep(i, 1, n) sum += dist[i];

        initG();
        _rep(i, 1, m) addEdge(ed[i], st[i], w[i]);

        initDij();
        dijkstra();

        _rep(i, 1, n) sum += dist[i];

        printf("%lld\n", sum);
    }
}