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
#include <unordered_map>

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

pair<int, int> crack(int n) {
    int st = sqrt(n);
    int fac = n / st;
    while (n % st) {
        st += 1;
        fac = n / st;
    }

    return make_pair(st, fac);
}

inline ll qpow(ll a, int n) {
    ll ans = 1;
    for(; n; n >>= 1) {
        if(n & 1) ans *= 1ll * a;
        a *= a;
    }
    return ans;
}

template <class T>
inline bool chmax(T& a, T b) {
    if(a < b) {
        a = b;
        return true;
    }
    return false;
}

template <class T>
inline bool chmin(T& a, T b) {
    if(a > b) {
        a = b;
        return true;
    }
    return false;
}

// ============================================================== //

const int maxn = 1e5 + 10;
const int Maxn = 1e7 + 3;
const int inf = 0x3f3f3f3f;
int n, m;

int ans[maxn];
int qry[maxn];

class Edge {
public:
    int to, w;
    Edge* next;
    Edge() {}
    Edge(int to, int w) : to(to), w(w) {}
} edges[maxn << 1], *head[maxn];

int M = 0;
int K;

void initG() {
    M = 0;
    memset(head, 0, sizeof(head));
}

void add(int u, int v, int w) {
    edges[++M] = Edge(v, w);
    edges[M].next = head[u];
    head[u] = &edges[M];
}

int root = 0;
int sz[maxn];
int vis[maxn];
int sn = n;

void getRoot(int x, int pa, int& res) {
    sz[x] = 1;
    int maxpart = 0;
    for(const Edge* e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->w;

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

int dep[maxn];
int C[Maxn << 1];

void dfs(int x, int pa, vector<int>& vec) {
    vec.push_back(dep[x]);
    for(const Edge* e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->w;

        if(vis[y] || y == pa) continue;
        dep[y] = dep[x] + w;
        dfs(y, x, vec);
    }
}

queue<int> buf;
inline void cal(int x) {
    assert(dep[x] == 0);
    C[dep[x]] = 1;
    for(const Edge* e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->w;

        if(vis[y]) continue;
        dep[y] = dep[x] + w;
        vector<int> vec;
        dfs(y, x, vec);

        for(auto v : vec) _rep(k, 1, m) {
            //debug(v);
            if(qry[k] >= v) ans[k] |= C[qry[k] - v];
        }
        for(auto v : vec) {
            buf.push(v);
            C[v] = 1;
        }
    }
    while (buf.size()) {
        int x = buf.front();
        buf.pop();

        C[x] = 0;
    }
    C[dep[x]] = 0;
}

void solve(int x) {
    vis[x] = 1;
    dep[x] = 0;

    cal(x);

    for(const Edge *e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->w;

        if(vis[y]) continue;

        sn = sz[y];
        root = 0;
        int res = inf;
        getRoot(y, 0, res);

        solve(root);
    }
}


void init() {
    memset(sz, 0, sizeof(sz));
    memset(vis, 0, sizeof(vis));
    sn = n;
    memset(dep, 0, sizeof(dep));
    memset(ans, 0, sizeof(ans));
    memset(C, 0, sizeof(C));
}


int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    init();
    initG();

    _for(i, 1, n) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add(u, v, w);
        add(v, u, w);
    }

    _rep(k, 1, m) scanf("%d", &qry[k]);

    // then solve
    int res = inf;
    getRoot(1, 0, res);
    solve(root);


    _rep(k, 1, m) {
        if(ans[k]) printf("AYE\n");
        else printf("NAY\n");
    }

}