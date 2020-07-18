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
const int maxn = 1000;
const double eps = 1e-3;
int n, m;

// == Graph definition ==
vector<int> G[maxn];
class Edge {
public:
    int to;
    double weight;
    Edge() {}
    Edge(int t, double w) : to(t), weight(w) {}
};
vector<Edge> edges;

void initG() {
    _for(i, 0, maxn) G[i].clear();
    edges.clear();
}

void addEdge(int u, int v, double w) {
    edges.push_back(Edge(v, w));
    G[u].push_back(edges.size() - 1);
}
// == Graph finished ==
// node ID [0, 1, ...)

// == bellman ford algorithm ==
bool inq[maxn];
int cnt[maxn], p[maxn];
double dist[maxn];

void initBellman() {
    Set(inq, 0);
    Set(cnt, 0);
    Set(p, 0);
}


bool bellmanFord() {
    initBellman();

    queue<int> que;
    _for(i, 0, n) {
        dist[i] = 0;
        que.push(i);
        inq[i] = true;
    }

    while (!que.empty()) {
        int x = que.front();
        inq[x] = false;
        que.pop();

        _for(i, 0, G[x].size()) {
            int y = edges[G[x][i]].to;
            double z = edges[G[x][i]].weight;

            if(dist[y] > dist[x] + z) {
                dist[y] = dist[x] + z;
                p[y] = G[x][i];

                if(!inq[y]) {
                    inq[y] = true;
                    que.push(y);
                    if(++cnt[y] > n) return true;
                }
            }
        }
    }
    return false;
}
// == bellman finished ==

// == test ==
bool test(double x) {
    _for(i, 0, edges.size()) edges[i].weight -= x;
    bool ans = bellmanFord();

    _for(i, 0, edges.size()) edges[i].weight += x;

    return ans;
}
// == test finsihed ==

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);

    for(int _ = 1; _ <= kase; _++) {
        printf("Case #%d: ", _);

        scanf("%d%d", &n, &m);
        initG();
        double maxv = 0;
        while (m--) {
            int u, v;
            double w;
            scanf("%d%d%lf", &u, &v, &w);
            u--; v--; maxv = max(maxv, w);

            addEdge(u, v, w);
        }

        // bellman ford judge cycle
        if(!test(maxv + 1)) printf("No cycle found.\n");
        else {
            double L = 0, R = maxv;
            while (R - L > 1e-3) {
                double mid = L + (R - L) / 2;
                if(test(mid)) R = mid;
                else L = mid;
            }
            printf("%.2lf\n", L);
        }
    }
}