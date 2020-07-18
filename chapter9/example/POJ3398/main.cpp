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
vector<int> G[maxn];

inline void add(int u, int v) {
    G[u].push_back(v);
}

// == dp ==
int d[maxn][3];

void initdp() {
    memset(d, -1, sizeof(d));

    vector<int> ed;
    _rep(i, 1, n) if(G[i].size() == 0) ed.push_back(i);

    for(auto x : ed) {
        d[x][0] = 1;
        d[x][1] = 0;
        d[x][2] = inf;
    }
}

int dp(int u, int pa, int k) {
    if(d[u][k] != -1) {
        return d[u][k];
    }

    d[u][0] = 1;
    d[u][1] = 0;

    for(auto v : G[u]) {
        if(v == pa) continue;

        d[u][0] += min(dp(v, u, 0), dp(v, u, 1));
        d[u][1] += dp(v, u, 2);

        if (d[u][0] > inf) d[u][0] = inf;
        if (d[u][1] > inf) d[u][1] = inf;

    }

    d[u][2] = inf;
    for(auto v : G[u]) {
        if(v == pa) continue;

        d[u][2] = min(d[u][2], d[u][1] - dp(v, u, 2) + dp(v, u, 0));
    }

    return d[u][k];
}

// == dp finished ==

void init() {
    _for(i, 0, maxn) G[i].clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) == 1) {
        init();

        // get data
        _for(i, 0, n - 1) {
            int u, v;
            scanf("%d%d", &u, &v);
            add(u, v);
            add(v, u);
        }
        // get data finished

        initdp();
        int ans = min(dp(1, 0, 0), dp(1, 0, 2));
        printf("%d\n", ans);
        scanf("%d", &n);
    }
}