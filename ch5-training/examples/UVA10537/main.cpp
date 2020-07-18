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

const int maxn = 100 + 5;
const ll inf = 0x3f3f3f3f3f3f3f3f;
int n, P, st, ed;

// == Graph definition ==
vector<int> G[maxn];

class Edge {
public:
    int from, to, isUp;
    Edge() {}
    Edge(int f, int t, int w) : from(f), to(t), isUp(w) {}
};

vector<Edge> edges;

class Node {
public:
    int u;
    ll dist;
    Node() {}
    Node(int u, ll d) : u(u), dist(d) {}
    bool operator< (const Node& rhs) const {
        return dist > rhs.dist;
    }
};

void initG() {
    edges.clear();
    _for(i, 0, maxn) G[i].clear();
}

void addEdge(int u, int v, int isUp) {
    edges.push_back(Edge(u, v, isUp));
    G[u].push_back(edges.size() - 1);
}
// == Graph finsihed ==

inline int read() {
    char ch[9];
    scanf("%s", ch);
    if(isupper(ch[0])) return ch[0] - 'A';
    else return ch[0] - 'a' + 26;
}

inline char format(int u) {
    return u < 26 ? 'A' + u : 'a' + (u - 26);
}

inline bool isUp(int u) {
    return u < 26 ? 1 : 0;
}

// == dijkstra ==
ll D[maxn];
int vis[maxn];
int pid[maxn];

void initDij(ll P, int st) {
    _for(i, 0, maxn) D[i] = inf;
    D[st] = P;
    Set(vis, 0);
    Set(pid, 0);
    pid[st] = -1;
}

void dijkstra(ll P, int st) {
    initDij(P, st);
    priority_queue<Node> que;
    que.push(Node(st, P));

    while (!que.empty()) {
        int x = que.top().u;
        que.pop();
        //debug(D[x]);
        if(vis[x]) continue;
        vis[x] = 1;

        _for(i, 0, G[x].size()) {
            const Edge& e = edges[G[x][i]];
            int y = e.to;

            ll d_to;
            if(e.isUp) d_to = (ll)ceil(D[x] * 1.0 / 19 * 20);
            else d_to = D[x] + 1;
            //debug(d_to);

            if(D[y] > d_to || (D[y] == d_to && format(x) < format(edges[pid[y]].from))) {
                D[y] = d_to;
                pid[y] = G[x][i];
                que.push(Node(y, D[y]));
            }
        }
    }
}

void print(int u) {
    if(pid[u] == -1) {
        printf("%c\n", format(u));
        return;
    }
    printf("%c-", format(u));
    print(edges[pid[u]].from);
}
// == dijkstra finsihed ==

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while (scanf("%d", &n) == 1 && n >= 0) {
        initG();
        printf("Case %d:\n", ++kase);

        // build graph
        _for(i, 0, n) {
            int u = read();
            int v = read();

            if(u != v) {
                addEdge(u, v, isUp(u));
                addEdge(v, u, isUp(v));
            }
        }
        // graph finished

        // then dijkstra
        scanf("%d", &P);
        st = read();
        ed = read();
        //debug(ed);

        dijkstra(P, ed);
        printf("%lld\n", D[st]);
        print(st);
    }
}
