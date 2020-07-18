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
int n;
int M = 0;

class Edge {
public:
    int to;
    Edge* next;
    Edge() {}
    Edge(int to) : to(to) {
        next = NULL;
    }
} edges[maxn << 1], *head[maxn];

void add(int u, int v) {
    edges[++M] = Edge(v);
    edges[M].next = head[u];
    head[u] = &edges[M];
}

void initG() {
    M = 0;
    memset(head, 0, sizeof(head));
}

ll ans[maxn];
int color[maxn];

int sz[maxn];
int root = -1;
int sn = n;
int vis[maxn];

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

ll num[maxn];
int cnt[maxn];

void clear(int x, int pa) {
    cnt[color[x]] = num[color[x]] = 0;
    sz[x] = 1;

    for(const Edge* e = head[x]; e; e = e->next) {
        int y = e->to;
        if(vis[y] || y == pa) continue;

        clear(y, x);
        sz[x] += sz[y];
    }
}

void calculate1(int x, int pa, ll& sum) {
    if(++cnt[color[x]] == 1) {
        sum += sz[x];
        num[color[x]] += sz[x];
    }

    for(const Edge* e = head[x]; e; e = e->next) {
        int y = e->to;
        if(vis[y] || y == pa) continue;

        calculate1(y, x, sum);
    }

    --cnt[color[x]];
}

void change(int x, int pa, int sgn, ll& sum) {
    if(++cnt[color[x]] == 1) {
        sum += sgn * sz[x];
        num[color[x]] += sgn * sz[x];
    }

    for(const Edge* e = head[x]; e; e = e->next) {
        int y = e->to;
        if(vis[y] || y == pa) continue;

        change(y, x, sgn, sum);
    }

    --cnt[color[x]];
}

void calculate2(int x, int pa, int tot2, int other, ll& sum) {
    if(++cnt[color[x]] == 1) {
        tot2++;
        sum -= num[color[x]];
    }

    ans[x] += sum + 1ll * other * tot2;

    for(const Edge* e = head[x]; e; e = e->next) {
        int y = e->to;
        if(vis[y] || y == pa) continue;

        calculate2(y, x, tot2, other, sum);
    }

    if(--cnt[color[x]] == 0) {
        tot2--;
        sum += num[color[x]];
    }
}

void work(int x, ll& sum) {
    vis[x] = 1;

    clear(x, -1);
    sum = 0;
    calculate1(x, -1, sum);
    ans[x] += 1ll * sum;

    for(const Edge* e = head[x]; e; e = e->next) {
        int y = e->to;
        if(vis[y]) continue;

        cnt[color[x]]++;
        change(y, x, -1, sum);
        sum -= sz[y];
        num[color[x]] -= sz[y];

        calculate2(y, x, 0, sz[x] - sz[y], sum);

        change(y, x, 1, sum);
        sum += sz[y];
        num[color[x]] += sz[y];
        cnt[color[x]]--;
    }

    for(const Edge* e = head[x]; e; e = e->next) {
        int y = e->to;
        if(vis[y]) continue;

        sn = sz[y];
        root = -1;
        int res = inf;
        getRoot(y, -1, res);

        work(root, sum);
    }
}

void init() {
    memset(sz, 0, sizeof(sz));
    memset(vis, 0, sizeof(vis));
    memset(ans, 0, sizeof(ans));
    sn = n;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    init();
    initG();

    _rep(i, 1, n) scanf("%d", &color[i]);
    _for(i, 1, n) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }

    // then solve

    ll sum = 0;
    int res = inf;
    getRoot(1, -1, res);
    work(root, sum);

    _rep(i, 1, n) printf("%lld\n", ans[i]);
}