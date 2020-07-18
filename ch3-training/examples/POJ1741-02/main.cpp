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

const int maxn = 1e5 + 10;
const int MAXN = maxn << 5;
const int inf = 0x3f3f3f3f;
int N, K;

// == Fenwick ==
class Fwick {
public:
    vector<int> C;
    int n;

    void resize(int n) {
        this->n = n;
        C.resize(n);
    }

    void clear() {
        fill(C.begin(), C.end(), 0);
    }

    int ask(int x) {
        x++;
        int ans = 0;
        for(; x > 0; x -= lowbit(x)) ans += C[x];
        return ans;
    }

    void add(int x, int d) {
        x++;
        for(; x <= K + 10; x += lowbit(x)) C[x] += d;
    }

    int find(int l, int r, int val) {
        while (l < r) {
            int mid = (l + r) >> 1;
            if(ask(mid) < val) l = mid + 1;
            else r = mid;
        }
        return l;
    }
} fwick;
// == Fenwick finished ==

// == Graph definition ==
int m = 0;

class Edge {
public:
    int to, weight;
    Edge *next;

    Edge() {}
    Edge(int to, int w) : to(to), weight(w) {
        next = NULL;
    }
} edges[maxn << 1], *head[maxn];

void add(int u, int v, int w) {
    edges[++m] = Edge(v, w);
    edges[m].next = head[u];
    head[u] = &edges[m];
}

void initG() {
    m = 0;
    memset(head, 0, sizeof(head));
}
// == Graph finished ==

int sz[maxn];
int dep[maxn];
int vis[maxn];
int sn = N;
int root = 0;

// == get gravity as root ==
void getRoot(int x, int pa, int &res) {
    sz[x] = 1;
    int maxpart = 0;
    for(const Edge *e = head[x]; e; e = e->next) {
        int y = e->to;
        if(vis[y] || y == pa) continue;

        getRoot(y, x, res);
        sz[x] += sz[y];
        maxpart = max(maxpart, sz[y]);
    }
    maxpart = max(maxpart, sn - sz[x]);
    if(maxpart < res) {
        res = maxpart;
        root = x;
    }
}
// == get root finished ==

// == get dep and calculate ==
void getDep(int x, int pa, vector<int> &vec) {
    vec.push_back(dep[x]);
    for(const Edge *e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->weight;

        if(vis[y] || y == pa) continue;
        dep[y] = dep[x] + w;

        if(dep[y] <= K) getDep(y, x, vec);
    }
}

queue<int> buf;
inline void cal(int x, int &ans) {
    fwick.add(dep[x], 1);

    for(const Edge *e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->weight;
        if(vis[y]) continue;

        dep[y] = dep[x] + w;
        vector<int> vec;
        getDep(y, x, vec);

        _for(i, 0, vec.size()) if(K >= vec[i]) {
            ans += fwick.ask(K - vec[i]);
        }

        _for(i, 0, vec.size()) {
            fwick.add(vec[i], 1);
            buf.push(vec[i]);
        }
    }

    while (buf.size()) {
        fwick.add(buf.front(), -1);
        buf.pop();
    }
    fwick.add(dep[x], -1);
}
// == get dep finsihed ==

// == solve ==
void solve(int x, int &ans) {
    dep[x] = 0;
    vis[x] = 1;
    cal(x, ans);

    for(const Edge *e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->weight;

        if(vis[y]) continue;

        sn = sz[y];
        root = 0;
        int res = inf;
        getRoot(y, -1, res);

        solve(root, ans);
    }
}
// == solve finished ==

void init() {
    Set(sz, 0);
    Set(dep, 0);
    Set(vis, 0);
    sn = N;
    root = 0;

    fwick.resize(MAXN);
    fwick.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &N, &K) == 2 && N) {
        init();
        initG();

        // get data
        _for(i, 1, N) {
            int u, v, w;
            scanf("%d%d%d", &u, &v, &w);
            add(u, v, w);
            add(v, u, w);
        }
        // data finished

        int res = inf;
        getRoot(1, -1, res);

        int ans = 0;
        solve(root, ans);
        printf("%d\n", ans);
    }
}