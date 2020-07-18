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
const int inf = 0x3f3f3f3f;
const int mod = 3;
int n;

inline ll gcd(ll a, ll b) {
    return b == 0 ? a : gcd(b, a % b);
}

class Edge {
public:
    int to, w;
    Edge* next;
    Edge() {}
    Edge(int to, int w) : to(to), w(w) {
        next = NULL;
    }
} edges[maxn << 1], *head[maxn];

int M = 0;

void initG() {
    M = 0;
    memset(head, 0, sizeof(head));
}

void add(int u, int v, int w) {
    edges[++M] = Edge(v, w);
    edges[M].next = head[u];
    head[u] = &edges[M];
}

// == gravity ==
int root = 0;
int sz[maxn];
int vis[maxn];
int sn = n;

void getRoot(int x, int pa, int& res) {
    sz[x] = 1;
    int maxpart = 0;
    for(const Edge* e = head[x]; e; e = e->next) {
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
// == gravity finished ==

ll cnt[mod + 3];

void dfs(int x, int pa, int dep) {
    ++cnt[dep % mod];
    for(const Edge* e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->w;

        if(vis[y] || y == pa) continue;
        int dep2 = (dep + w) % mod;
        dfs(y, x, dep2);
    }
}


inline ll cal(int x, int dep) {
    memset(cnt, 0, sizeof(cnt));
    dfs(x, 0, dep);

    ll ans = 1ll * cnt[0] * cnt[0] + 1ll * 2 * cnt[1] * cnt[2];
    return ans;
}



// == work ==
void work(int x, ll& ans) {
    vis[x] = 1;
    ans += cal(x, 0);

    for(const Edge* e = head[x]; e; e = e->next) {
        int y = e->to;
        int w = e->w;

        if(vis[y]) continue;

        ans -= cal(y, w);

        int res = inf;
        sn = sz[y];
        root = 0;
        getRoot(y, 0, res);

        work(root, ans);
    }
}
// == work finished ==

void init() {
    memset(sz, 0, sizeof(sz));
    memset(vis, 0, sizeof(vis));
    sn = n;

    memset(cnt, 0, sizeof(cnt));
}


int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    init();
    initG();

    _for(i, 0, n - 1) {
        int x, y, z;
        scanf("%d%d%d", &x, &y, &z);
        add(x, y, z % mod);
        add(y, x, z % mod);
    }

    // then solve
    int res = inf;
    getRoot(1, 0, res);

    ll ans = 0;
    work(root, ans);

    ll p = n * n;
    ll g = gcd(ans, p);

    ans /= g, p /= g;
    printf("%lld/%lld\n", ans, p);
}