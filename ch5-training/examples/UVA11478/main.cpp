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

const int maxn = 500 + 10;
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
    edges.clear();
    _for(i, 0, maxn) G[i].clear();
}

void addEdge(int u, int v, int w) {
    edges.push_back(Edge(v, w));
    G[u].push_back(edges.size() - 1);
}
// == Graph finished ==
int cnt[maxn], inq[maxn];
int D[maxn];

void initSPFA() {
    Set(cnt, 0);
    Set(inq, 0);
    Set(D, inf);
}

// true: nega-cycle
// false: non-negaCycle
int spfa() {
    initSPFA();
    queue<int> que;
    _rep(i, 1, n) {
        D[i] = 0;
        que.push(i);
        inq[i] = true;
    }

    while (!que.empty()) {
        int x = que.front();
        que.pop();
        inq[x] = 0;

        _for(i, 0, G[x].size()) {
            const Edge& e = edges[G[x][i]];
            int y = e.to;

            if(D[y] > D[x] + e.weight) {
                D[y] = D[x] + e.weight;
                if(!inq[y]) {
                    que.push(y);
                    inq[y] = true;

                    if(++cnt[y] > n) return true;
                }
            }
        }
    }
    return false;
}

bool check(int x) {
    _for(i, 0, edges.size()) {
        edges[i].weight -= x;
    }
    bool ret = spfa();
    _for(i, 0, edges.size()) {
        edges[i].weight += x;
    }

    return !ret;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &n, &m) == 2) {
        initG();

        // build graph
        int ud = 0;
        _for(i, 0, m) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            addEdge(u, v, d);
            ud = max(ud, d);
        }
        // build finished
        // x in [1, ud]
        //debug(ud);

        if(check(ud + 1)) printf("Infinite\n");
        else if(!check(1)) printf("No Solution\n");
        else {
            int ans = 1;
            int L = 2, R = ud;

            while (L <= R) {
                int mid = (L + R) >> 1;
                //debug(mid);
                if(check(mid)) {
                    ans = mid;
                    L = mid + 1;
                }
                else R = mid - 1;
            }
            printf("%d\n", ans);
        }
    }
}
