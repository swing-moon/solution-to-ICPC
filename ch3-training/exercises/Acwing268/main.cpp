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

const int maxn = 3 * 1e5 + 10;
const int inf = 0x3f3f3f3f;
int n, m;
int K = 0;
vector<int> vec[maxn];

class BIU {
public:
    int id;
    ll val;
    BIU() {}
    BIU(int id, ll val) : id(id), val(val) {}
} P[maxn], pl[maxn], pr[maxn];

class Met {
public:
    int l, r;
    ll a;
    Met() {}
    Met(int l, int r, ll a) : l(l), r(r), a(a) {}
} A[maxn];

class Fwick {
public:
    ll C[maxn];
    int n;

    void _init(int n) {
        this->n = n;
        memset(C, 0, sizeof(C));
    }

    void add(int x, ll d) {
        for(; x <= m; x += lowbit(x)) C[x] += d;
    }

    ll ask(int x) {
        ll ret = 0;
        for(; x; x -= lowbit(x)) ret += C[x];
        return ret;
    }
} fwick;

void get(int k, int sgn) {
    ll val = sgn * A[k].a;

    if(A[k].l <= A[k].r) {
        fwick.add(A[k].l, val);
        fwick.add(A[k].r + 1, -val);
    }
    else {
        fwick.add(1, val);
        fwick.add(A[k].l, val);
        fwick.add(A[k].r + 1, -val);
    }
}

ll ans[maxn];

void solve(int lval, int rval, int st, int ed) {
    if(st > ed) return;
    if(lval == rval) {
        _rep(i, st, ed) ans[P[i].id] = lval;
        return;
    }

    int mid = (lval + rval) >> 1;
    int lt = 0, rt = 0;

    _rep(i, lval, mid) get(i, 1);
    _rep(i, st, ed) {
        // P[i].id is cur BIU
        ll tot = 0;
        for(auto x : vec[P[i].id]) {
            tot += fwick.ask(x);
            if(tot > P[i].val) break;
        }

        if(tot >= P[i].val) pl[++lt] = P[i];
        else {
            P[i].val -= tot;
            pr[++rt] = P[i];
        }
    }

    _rep(i, lval, mid) get(i, -1);

    _rep(i, 1, lt) P[st + i - 1] = pl[i];
    _rep(i, 1, rt) P[st + lt + i - 1] = pr[i];

    solve(lval, mid, st, st + lt - 1);
    solve(mid + 1, rval, st + lt, ed);
}

void init() {
    //
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d%d", &n, &m);

    init();
    // get data
    _rep(i, 1, m) {
        int o;
        scanf("%d", &o);
        vec[o].push_back(i);
    }
    _rep(i, 1, n) {
        P[i].id = i;
        scanf("%lld", &P[i].val);
    }
    scanf("%d", &K);
    _rep(i, 1, K) {
        int l, r;
        ll a;
        scanf("%d%d%lld", &l, &r, &a);
        A[i] = Met(l, r, a);
    }
    A[++K] = Met(1, m, inf);

    // then solve the problem
    fwick._init(maxn);

    solve(1, K, 1, n);

    _rep(i, 1, n) ans[i] == K ? puts("NIE") : printf("%lld\n", ans[i]);
}