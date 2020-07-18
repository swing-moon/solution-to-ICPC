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

const int maxn = 100000 + 10;
int ans = 0;

// == Graph definition ==
vector<int> G[maxn];

class Edge {
public:
    int to, weight;
    Edge() {}
    Edge(int v, int w) : to(v), weight(w) {}
};

vector<Edge> edges;
int deg[maxn];

void initG() {
    Set(deg, 0);
    _for(i, 0, maxn) G[i].clear();
    edges.clear();
}

void addEdge(int u, int v, int w) {
    edges.push_back(Edge(v, w));
    G[u].push_back(edges.size() - 1);
    deg[v]++;
}

int n, m;
// == Graph finished ==

int D[maxn];
void initdp() {
    ans = 0;
    Set(D, 0);
}

void dp() {
    queue<int> que;
    _rep(i, 1, n) if(deg[i] == 0) que.push(i);

    while (que.size()) {
        int x = que.front();
        que.pop();

        if(G[x].size() == 0) ans = max(ans, D[x]);

        _for(i, 0, G[x].size()) {
            const Edge& e = edges[G[x][i]];
            int y = e.to;

            if(D[y] < D[x] + e.weight) D[y] = D[x] + e.weight;
            if(--deg[y] == 0) que.push(y);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);

    while (kase--) {
        initG();
        scanf("%d%d", &n, &m);
        _rep(i, 1, m) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            addEdge(u, v, w);
        }


        initdp();
        dp();
        printf("%d\n", ans);
    }
}