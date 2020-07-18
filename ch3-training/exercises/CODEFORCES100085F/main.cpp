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

const int maxn = 50000 + 10;
const int maxm = 8000000;
const int inf = 0x3f3f3f3f;
const double eps = 1e-6;
int n, m;
int mx = 0;


class Parabola {
public:
    double a;
    int p, h, x1, x2;

    void read() {
        scanf("%d%d%d", &x1, &p, &h);

        x2 = x1 + 2 * (p - x1);
        a = h * 1.0 / ((p-x1) * (p-x2) * 1.0);

        mx = max(mx, x2);
    }
} parabo[maxn];

void getpara() {
    scanf("%d", &n);
    _rep(i, 1, n) {
        parabo[i].read();
    }
}

double cal(int id, int x) {
    const Parabola& p = parabo[id];
    return p.a * (x - p.x1) * (x - p.x2);
}

double getmaxh(int id, int xl, int xr) {
    // for particular parabola[id], maxh in [xl, xr]
    const Parabola& P = parabo[id];
    if(xr <= P.x1) return 0;
    if(xl >= P.x2) return 0;

    if(P.x1 < xr && xr < P.p) return cal(id, xr);
    if(P.p < xl && xl < P.x2) return cal(id, xl);

    return P.h;
}

// == seg Tree and nested tree  ==
int tot = 0;
int rt[maxn << 2];

void init() {
    tot = 0;
    Set(rt, 0);
}

class nestTree {
public:
    int ls, rs;
    double maxh;
} nTree[maxm];
#define ls(x) nTree[x].ls
#define rs(x) nTree[x].rs
#define maxh(x) nTree[x].maxh

// usage: spread(u, 0, mx)
void spread(int& o, int id, int l, int r) {
    if(!o) o = ++tot;
    maxh(o) = getmaxh(id, l, r);
    //debug(xl(o)), debug(xr(o));

    if(l == r) return;
    int mid = (l + r) >> 1;
    if(l <= mid) spread(ls(o), id, l, mid);
    if(mid + 1 <= r) spread(rs(o), id, mid + 1, r);
    // debug(ls(o)), debug(rs(o));
}

int merge(int p, int q, int l, int r) {
    if(!p || !q) return p + q;
    if(l == r) return maxh(p) > maxh(q) ? p : q;

    int u = ++tot;
    int mid = (l + r) >> 1;
    ls(u) = merge(ls(p), ls(q), l, mid);
    rs(u) = merge(rs(p), rs(q), mid + 1, r);
    maxh(u) = max(maxh(ls(u)), maxh(rs(u)));

    return u;
}

/*
class segTree {
public:
    int l, r;
} tree[maxn << 2];
#define l(x) tree[x].l
#define r(x) tree[x].r
*/

void build(int p, int l, int r) {
    if(l == r) {
        int id = l;
        spread(rt[p], id, 0, mx);
        return;
    }

    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid + 1, r);
    rt[p] = merge(rt[p<<1], rt[p<<1|1], 0, mx);
}

double querysub(int o, int l, int r, int ql, int qr) {
    if(!o || l > qr || r < ql) return 0;
    //debug(ls(o));
    //debug(rs(o));
    if(ql <= l && r <= qr) return maxh(o);

    int mid = (l + r) >> 1;
    return max(querysub(ls(o), l, mid, ql, qr), querysub(rs(o), mid + 1, r, ql, qr));
}

double query(int p, int l, int r, int tl, int tr, int xl, int xr) {
    if(tr < l || r < tl) return 0;
    if(l >= tl && r <= tr) {
        //debug(l(p));
        //debug(r(p));
        // query sub
        //debug(rt[p]);
        double ans = querysub(rt[p], 0, mx, xl, xr);
        return ans;
    }

    int mid = (l + r) >> 1;
    //debug(mid);

    return max(query(p<<1, l, mid, tl, tr, xl, xr), query(p<<1|1, mid + 1, r, tl, tr, xl, xr));
}

// == seg Tree and nested tree finsihed ==

// == solve the problem ==
void solve() {
    build(1, 1, n);

    scanf("%d", &m);
    _rep(i, 1, m) {
        int t1, t2, x1, x2;
        scanf("%d%d%d%d", &t1, &t2, &x1, &x2);

        // double ans = 0.0;
        double ans = query(1, 1, n, t1, t2, x1, x2);
        printf("%lf\n", ans);
    }
}
// == solve finsihed ==

/*
void solve2() {
    scanf("%d", &m);
    _rep(i, 1, m) {
        int t1, t2, x1, x2;
        scanf("%d%d%d%d", &t1, &t2, &x1, &x2);

        double ans = 0.0;
        _rep(k, t1, t2) {
            double val = getmaxh(k, x1, x2);
            ans = max(ans, val);
        }
        printf("%lf\n", ans);
    }
}
*/

int main() {
    // freopen("input.txt", "r", stdin);
    freopen("flights.in", "r", stdin);
    //freopen("flights.out", "w", stdout);
    init();
    getpara();

    solve();
}


