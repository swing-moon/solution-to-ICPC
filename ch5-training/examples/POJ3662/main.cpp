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

const int maxn = 1000 + 5;
const int inf = 0x3f3f3f3f;
int n, P, K;

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
// == Graph finsihed ==

// == bfs shortest path ==
deque<int> que;
int dist[maxn];
bool vis[maxn];

void initbfs() {
    Set(dist, inf);
    dist[1] = 0;
    Set(vis, 0);
}

int bfs(int mid) {
    initbfs();
    que.push_back(1);

    while (!que.empty()) {
        int x = que.front();
        que.pop_front();

        if(vis[x]) continue;
        vis[x] = 1;

        _for(i, 0, G[x].size()) {
            int y = edges[G[x][i]].to;
            int z = edges[G[x][i]].weight;

            if(vis[y]) continue;
            if(z > mid) {
                // weight count as 1
                if(dist[y] > dist[x] + 1) {
                    dist[y] = dist[x] + 1;
                    que.push_back(y);
                }
            }
            else {
                // weight count as 0
                if(dist[y] > dist[x]) {
                    dist[y] = dist[x];
                    que.push_front(y);
                }
            }
        }
    }
    return dist[n];
}
// == bfs finished ==

int main() {
    freopen("input.txt", "r", stdin);
    initG();
    cin >> n >> P >> K;

    int maxl = -1;
    _rep(i, 1, P) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        addEdge(x, y, z);
        addEdge(y, x, z);
        maxl = max(maxl, z);
    }

    // deque bfs to solve shortest path
    if(bfs(maxl + 1) > K) {
        puts("-1");
        return 0;
    }

    int l = 0, r = maxl;
    while (l < r) {
        int mid = (l + r) >> 1;
        if(bfs(mid) > K) l = mid + 1;
        else r = mid;
    }
    cout << l << endl;
}