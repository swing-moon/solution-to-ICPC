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

const int N = 1000 + 5;
const int P = 10000 + 5;
const int maxn = N * N;
const int inf = 0x3f3f3f3f;
int n, p, k;

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

inline int _hash(int x, int p) {
    return x + p * n;
}
// == Graph finished ==

// == spfa ==
int d[maxn];
bool inq[maxn];
int cnt[maxn];
queue<int> que;

void initSpfa() {
    Set(d, inf);
    d[1] = 0;
    Set(inq, 0);
    Set(cnt, 0);
}

bool spfa() {
    initSpfa();

    que.push(1);
    inq[1] = true;

    while (!que.empty()) {
        int x = que.front();
        que.pop();
        inq[x] = false;

        _for(i, 0, G[x].size()) {
            int y = edges[G[x][i]].to;
            int z = edges[G[x][i]].weight;

            if(d[y] > max(d[x], z)) {
                d[y] = max(d[x], z);

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
// == spfa finsihed ==

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> p >> k;
    initG();

    _rep(i, 1, p) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);

        _rep(j, 0, k) {
            addEdge(_hash(x, j), _hash(y, j), z);
            addEdge(_hash(y, j), _hash(x, j), z);
        }
        _for(j, 0, k) {
            addEdge(_hash(x, j), _hash(y, j + 1), 0);
            addEdge(_hash(y, j), _hash(x, j + 1), 0);
        }
    }

    // bellman ford
    spfa();
    if(d[n + k * n] == inf) puts("-1");
    else cout << d[n + k * n] << endl;
}