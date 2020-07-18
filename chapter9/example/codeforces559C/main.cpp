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

const int SZ = 2000 + 10;
const int maxn = 200000 + 10;
const ll mod = 1000000000 + 7;
int h, w, n;

ll jc[maxn], jcinv[maxn];
int f[SZ];

struct A {
    int x, y;
    bool operator< (const A& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};
A a[SZ];

// == init jc ==
inline ll power(ll a, int b) {
    ll ans = 1;
    for(; b; b >>= 1) {
        if(b & 1) ans = ans * a % mod;
        a = a * a % mod;
    }
    return ans;
}

void init() {
    Set(f, 0);
    jc[0] = 1;
    jcinv[0] = 1;

    _rep(i, 1, maxn) {
        jc[i] = jc[i - 1] * i % mod;
        jcinv[i] = power(jc[i], mod - 2);
    }
}
// == init finished ==

// == calculate C ==
int C(int n, int m) {
    return jc[n] * jcinv[m] % mod * jcinv[n - m] % mod;
}
// == calculate finished ==

// == input files ==
void inp() {
    cin >> h >> w >> n;
    _rep(i, 1, n) {
        scanf("%d%d", &a[i].x, &a[i].y);
    }
    sort(a + 1, a + 1 + n);
    a[n + 1].x = h, a[n + 1].y = w;
}
// == input finsihed ==

// == dp ==
void dp() {
    _rep(i, 1, n + 1) {
        f[i] = C(a[i].x + a[i].y - 2, a[i].x - 1);
        //debug(f[i]);
        _for(j, 1, i) {
            if(a[j].x > a[i].x || a[j].y > a[i].y) continue;
            f[i] = (f[i] - (ll)f[j] * C(a[i].x - a[j].x + a[i].y - a[j].y, a[i].x - a[j].x)) % mod;
        }
    }
    cout << (f[n + 1] + mod) % mod << endl;
}
// == dp finished ==

int main() {
    freopen("input.txt", "r", stdin);

    init();
    //debug(jc[2000]);
    // debug(jcinv[2000]);
    inp();
    dp();
}