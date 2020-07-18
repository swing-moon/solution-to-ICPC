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

// ============================================================================= //

const int maxn = 1e5 + 10;
const int inf = 1e9;
int N, M;
int n = 0, tot = 0;
int ans[maxn];

// == discrete ==
int a[maxn], b[maxn];

void discrete() {
    sort(b + 1, b + 1 + N);
    n = unique(b + 1, b + 1 + N) - b - 1;
    _rep(i, 1, N) a[i] = lower_bound(b + 1, b + 1 + n, a[i]) - b;
}
// original: b[a[i]], a in [1, n]
// == discrete finished ==

class Qry {
public:
    int x, y, z;
    int op;
    Qry() {}
    Qry(int x, int y, int z) : x(x), y(y), z(z) {}
    Qry(int x, int y) : x(x), y(y) {}
} qry[maxn << 1], lqry[maxn << 1], rqry[maxn << 1];

class Fwick {
public:
    int C[maxn];
    int n;
    void _init(int n) {
        this->n = n;
        memset(C, 0, sizeof(C));
    }

    void add(int x, int y) {
        for(; x <= n; x += lowbit(x)) C[x] += y;
    }

    int ask(int x) {
        int ret = 0;
        for(; x; x -= lowbit(x)) ret += C[x];
        return ret;
    }
} fwick;

void solve(int lval, int rval, int st, int ed) {
    if(st > ed) return;
    if(lval == rval) {
        _rep(i, st, ed) {
            if(qry[i].op > 0) ans[qry[i].op] = b[lval];
        }
        return;
    }

    int mid = (lval + rval) >> 1;

    int lt = 0, rt = 0;
    _rep(i, st, ed) {
        if(qry[i].op == 0) {
            // x -> y
            if(qry[i].y <= mid) {
                fwick.add(qry[i].x, 1);
                lqry[++lt] = qry[i];
            }
            else rqry[++rt] = qry[i];
        }
        else {
            int cnt = fwick.ask(qry[i].y) - fwick.ask(qry[i].x - 1);
            if(cnt >= qry[i].z) lqry[++lt] = qry[i];
            else {
                qry[i].z -= cnt;
                rqry[++rt] = qry[i];
            }
        }
    }

    _rep(i, st, ed) {
        if(qry[i].op == 0 && qry[i].y <= mid) fwick.add(qry[i].x, -1);
    }

    _rep(i, 1, lt) qry[st + i - 1] = lqry[i];
    _rep(i, 1, rt) qry[st + lt + i - 1] = rqry[i];

    solve(lval, mid, st, st + lt - 1);
    solve(mid + 1, rval, st + lt, ed);
}

void init() {
    n = 0;
    tot = 0;
    memset(ans, 0, sizeof(ans));
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> N >> M;
    init();

    // == get data ==
    _rep(i, 1, N) {
        scanf("%d", &a[i]);
        b[i] = a[i];
    }
    discrete();
    // == get data finished ==

    // == get query ==
    _rep(i, 1, N) {
        qry[++tot] = Qry(i, a[i]);
        qry[tot].op = 0;
    }

    _rep(i, 1, M) {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        qry[++tot] = Qry(l, r, k);
        qry[tot].op = i;
    }
    // == query finished ==

    // then solve the problem
    fwick._init(n + 1);
    solve(1, n, 1, tot);

    _rep(i, 1, M) printf("%d\n", ans[i]);
}