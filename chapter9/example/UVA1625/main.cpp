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

const int maxn = 5000 + 10;
const int inf = 0x3f3f3f3f;
const int maxs = 256;
char p[maxn], q[maxn];
int n, m;

int sp[maxs+1], ep[maxs+1];
int sq[maxs+1], eq[maxs+1];

void prework() {
    _rep(i, 1, n) {
        sp[p[i]] = min(sp[p[i]], i);
        ep[p[i]] = i;
    }
    _rep(i, 1, m) {
        sq[q[i]] = min(sq[q[i]], i);
        eq[q[i]] = i;
    }
}

int f[2][maxn], cnt[2][maxn];
int k = 0;

void initdp() {
    memset(f, 0, sizeof(f));
    memset(cnt, 0, sizeof(cnt));
    k = 0;
}

void update(int i, int j) {
    if(i) {
        cnt[k][j] = cnt[k^1][j];
        if(i == sp[p[i]] && j < sq[p[i]]) cnt[k][j]++;
        if(i == ep[p[i]] && j >= eq[p[i]]) cnt[k][j]--;
        //debug(cnt[k][j]);
    }
    if(j) {
        cnt[k][j] = cnt[k][j - 1];
        if(j == sq[q[j]] && i < sp[q[j]]) cnt[k][j]++;
        if(j == eq[q[j]] && i >= ep[q[j]]) cnt[k][j]--;
    }
}

void dp() {
    _rep(i, 0, n) {
        _rep(j, 0, m) {
            if(i == 0 && j == 0) continue;

            int v1 = inf, v2 = inf;
            if(i) v1 = f[k^1][j] + cnt[k^1][j];
            if(j) v2 = f[k][j - 1] + cnt[k][j - 1];
            f[k][j] = min(v1, v2);

            update(i, j);
        }
        k ^= 1;
    }
}


void init() {
    Set(sp, inf);
    Set(ep, 0);
    Set(sq, inf);
    Set(eq, 0);

    n = strlen(p + 1);
    m = strlen(q + 1);
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    cin >> kase;

    while (kase--) {
        scanf("%s", p + 1);
        scanf("%s", q + 1);

        // prework
        init();
        prework();

        // dp
        initdp();
        dp();
        printf("%d\n", f[k^1][m]);
    }
}
