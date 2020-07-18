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

const int maxn = 50 + 5;
const int mod = 1e9+7;

// == calculate C() ==
ll power(ll a, int b) {
    ll ans = 1;
    for(; b; b >>= 1) {
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
    }
    return ans;
}

ll jc[maxn*2], jcinv[maxn*2];
void initC() {
    Set(jc, 0), Set(jcinv, 0);
    jc[0] = 1, jcinv[0] = 1;

    assert(jc[0] == 1);
    assert(jcinv[0] == 1);
    _rep(i, 1, maxn * 2) {
        jc[i] = jc[i - 1] * i % mod;
        jcinv[i] = power(jc[i], mod - 2);
    }
}

inline int C(int n, int m) {
    return jc[n] * jcinv[m] % mod * jcinv[n-m] % mod;
}
// == C() finsihed, usage initC() and C(x, y) ==

// == first get table and list H[] ==
ll H[maxn];

void initH() {
    Set(H, 0);
    H[1] = 1;
}

void table() {
    initH();
    _rep(i, 2, maxn) {
        H[i] = power(2, i*(i-1)/2);
        _for(j, 1, i) {
            H[i] = (H[i] - (H[j] * C(i-1, j-1) % mod * power(2, (i-j)*(i-j-1)/2) % mod) + mod) % mod;
        }
    }
}
// == table finished ==

const int maxm = 1250;

// == first part, init f(i,j) ==
ll f[maxn][maxm];

void initf() {
    Set(f, -1);
    f[0][0] = 0;
    f[1][0] = 1;
    f[1][1] = 0;
    f[2][0] = 0;
    f[2][1] = 1;
    f[2][2] = 0;

    _for(i, 3, maxn) f[i][0] = 0;
}
// == f(i, j) finished ==

// == second part, init g(i,j,k) ==
ll g[maxn][maxn][maxm];

void initg() {
    Set(g, -1);
    _for(i, 0, maxn) _for(j, 0, maxm) g[0][i][j] = 0;

    _for(k, 0, maxm) g[1][0][k] = 0;

    g[1][1][0] = 1;
    _for(k, 1, maxm) g[1][1][k] = 0;
}
// == g(i,j,k) finished ==

// == function G(i,j,k) ==
ll G(int i, int j, int k) {
    if(g[i][j][k] >= 0) return g[i][j][k];

    ll res = 0;
    _rep(p, 1, i) _rep(q, 0, k) {
            //debug(p);
            //debug(q);
            //debug(f[p][q]);
            if(q >= p) continue;
            assert(f[p][q] >= 0);
            //debug(f[p][q]);

            ll S = G(i-p, j-1, k-q);
            assert(S >= 0);

            res += (f[p][q] * C(i-1, p-1) % mod * p % mod * S) % mod;
            res %= mod;
        }
    return g[i][j][k] = res;
}
// == G(i,j,k) finished ==

// == function cal(i, j, k) ==
ll cal(int i, int j, int k) {
    assert(f[k][0] >= 0);
    ll S1 = f[k][0] * C(i-1, k-1) % mod;

    ll S2 = 0;
    _rep(x, 1, min(i-k, j)) {
        S2 += (G(i-k, x, j-x) * power(k, x)) % mod;
        S2 %= mod;
    }
    return S1 * S2 % mod;
}
// == cal(i, j, k) finsihed ==

// == then solve ==
const int N = 50;
const int M = 1250;

void solve() {
    _rep(i, 3, N) {
        f[i][0] = H[i];
        _for(j, 1, i) {
            //assert(f[i][j] <= 0);

            f[i][j] = 0;
            _rep(k, 1, i - 1) f[i][j] = (f[i][j] + cal(i, j, k)) % mod;

            f[i][0] = (f[i][0] - f[i][j] + mod) % mod;
        }
    }
}
// == solve finished ==

int main() {
    //freopen("sol.txt", "w", stdout);

    // == get H[] and pass test ==
    initC();
    // initH();
    table();

    _rep(i, 1, 50) printf("%d\n", H[i]);
    // == H[] table() and finished ==


    cout << "\n========================\n" << endl;

    // == init f and init g ==
    initf();
    initg();
    solve();
    // == init finished ==

    _rep(i, 1, N) {
        cout << i << ": ";
        _rep(j, 0, 10) printf("%lld ", f[i][j]);
        puts("");
    }
}