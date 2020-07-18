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
const double eps = 1e-10;
int n, m;
int mx = 0;


class Parabola {
public:
    int x, y, p;
    double a, b, c;
    inline double cal(double x) {
        return a*x*x + b*x + c;
    }

    void read(int& mx) {
        scanf("%d%d%d", &p, &x, &y);

        a = (double)y * 1.0 / (1ll * (x - p) * (p - x) * 1.0);
        b = -2 * a * x;
        c = -a*p*p - b*p;

        mx = max(mx, 2*x-p);
    }
} para[maxn];

// == seg Tree nested seg Tree ==
int tot = 0;
int rt[maxn << 2];
double X[maxn << 2], _X[maxn << 2];

void init() {
    tot = 0;
    Set(rt, 0);
    Set(X, 0);
    Set(_X, 0);
}

class segTree {
public:
    int l, r;
} tree[maxn << 2];
#define l(x) tree[x].l
#define r(x) tree[x].r

class nestTree {
public:
    int ls, rs;
    double maxh;
} ntree[maxm];
#define ls(x) ntree[x].ls
#define rs(x) ntree[x].rs
#define maxh(x) ntree[x].maxh

void spread1(int& o, int l, int r, int x, int y) {
    if(!o) o = ++tot;
    maxh(o) = y;

    if(l == r) return;
    int mid = (l + r) >> 1;
    if(x <= mid) spread1(ls(o), l, mid, x, y);
    else spread1(rs(o), mid + 1, r, x, y);
}

int merge1(int p, int q, int l, int r) {
    if(!p || !q) return p + q;
    if(l == r) return maxh(p) > maxh(q) ? p : q;

    int u = ++tot;
    int mid = (l + r) >> 1;
    ls(u) = merge1(ls(p), ls(q), l, mid);
    rs(u) = merge1(rs(p), rs(q), mid + 1, r);
    maxh(u) = max(maxh(ls(u)), maxh(rs(u)));
    return u;
}

// usage, build1(1, 1, n)
void build1(int p, int l, int r) {
    // leaf node means lth parabola
    // spread 2D-segTree
    l(p) = l, r(p) = r;
    if(l == r) {
        spread1(rt[p], 0, mx, para[l].x, para[l].y);
        return;
    }
    int mid = (l + r) >> 1;
    build1(p<<1, l, mid);
    build1(p<<1|1, mid + 1, r);
    rt[p] = merge1(rt[p<<1], rt[p<<1|1], 0, mx);
}

// query 2D, usage, query2(rt[p], 0, mx, x1, x2)
// query interval [x1, x2]
// query2(p), query2(ls(p), ..), query2(rs(p), ...)
double query2(int p, int l, int r, int ql, int qr) {
    if(!p || ql > r || qr < l) return 0;
    if(ql <= l && r <= qr) return maxh(p);
    int mid = (l + r) >> 1;
    return max(query2(ls(p), l, mid, ql, qr), query2(rs(p), mid + 1, r, ql, qr));
}

// usage, query1(1, t1, t2, x1, x2)
double query1(int p, int tl, int tr, int xl, int xr) {
    if(r(p) < tl || l(p) > tr) return 0;
    if(tl <= l(p) && r(p) <= tr) return query2(rt[p], 0, mx, xl, xr);

    return max(query1(p<<1, tl, tr, xl, xr), query1(p<<1|1, tl, tr, xl, xr));
}
// == seg Tree nested finished ==

// == outline seg Tree, build by parabola id, solve interval endpoint ==
struct Line {
    double xl, xr;
    int id;

    Line(double _xl = 0.0, double _xr = 0.0, int _id = 0) : xl(_xl), xr(_xr), id(_id) {}

    bool operator< (const Line& rhs) const {
        return xr < rhs.xr;
    }
};

class outlineTree {
public:
    int _l, _r;
    vector<Line> lines;
} lineTree[maxn << 2];
#define _l(x) lineTree[x]._l
#define _r(x) lineTree[x]._r
#define lines(x) lineTree[x].lines

inline double intersection(int i, int j, double l, double r) {
    // find intersction of two parabola in seg [l, r]
    const Parabola& u = para[i];
    const Parabola& v = para[j];

    double A = u.a - v.a;
    double B = u.b - v.b;
    double C = u.c - v.c;

    if(fabs(A) < eps) {
        // A = 0, find solution
        // B = 0, no solution, return xr
        if(fabs(B) < eps) return r;
        double ans = -C / B;
        if(l + eps < ans && ans < r - eps) return ans;
        return r;
    }

    double D = B*B - 4*A*C;
    if(D < -eps) return r;

    D = sqrt(D);
    double ans = r;

    double x1 = (-B - D) / A / 2;
    if(l + eps < x1 && x1 < r - eps) ans = x1;
    double x2 = (-B + D) / A / 2;
    if(l + eps < x2 && x2 < r - eps) ans = min(ans, x2);

    return ans;
}

vector<Line> tmp;
inline void combine(vector<Line>& A, vector<Line>& B, vector<Line>& C) {
    sort(A.begin(), A.end());
    sort(B.begin(), B.end());

    if(A.size() == 0) {
        C = B;
        return;
    }
    if(B.size() == 0) {
        C = A;
        return;
    }

    // solve all (x, 0) to a new array _X, then unique to X
    tmp.clear();
    int tot = 0;
    _for(i, 0, A.size()) {
        _X[++tot] = A[i].xl;
        _X[++tot] = A[i].xr;
    }
    _for(i, 0, B.size()) {
        _X[++tot] = B[i].xl;
        _X[++tot] = B[i].xr;
    }
    sort(_X + 1, _X + 1 + tot);

    int sz = 0;
    for(int i = 1; i <= tot; ) {
        int j = i;
        for(; j < tot && fabs(_X[j + 1] - _X[j]) < eps; j++);
        X[++sz] = _X[j];
        i = j + 1;
    }

    // X[1,..,sz] is the sub segment
    // {l, r, paraID} construct outline
    int p1 = 0, p2 = 0;
    _for(i, 1, sz) {
        double l = X[i], r = X[i + 1];
        while (p1 < A.size() && A[p1].xr + eps < r) p1++;
        while (p2 < B.size() && B[p2].xr + eps < r) p2++;

        if(((p1 == A.size()) || (A[p1].xl > l + eps)) && ((p2 == B.size()) || (B[p2].xl > l + eps))) continue;
        if((p1 == A.size()) || (A[p1].xl > l + eps)) {
            tmp.push_back(Line(l, r, B[p2].id));
            continue;
        }
        if((p2 == B.size()) || (B[p2].xl > l + eps)) {
            tmp.push_back(Line(l, r, A[p1].id));
            continue;
        }

        // intersction [l, x1, x2, ..., r], get point
        while (l + eps < r) {
            double x = intersection(A[p1].id, B[p2].id, l, r);
            double phi = (l + x) / 2;

            if(para[A[p1].id].cal(phi) > para[B[p2].id].cal(phi)) {
                if(para[A[p1].id].cal(phi) >= 0) tmp.push_back(Line(l, x, A[p1].id));
            }
            else {
                if(para[B[p2].id].cal(phi) >= 0) tmp.push_back(Line(l, x, B[p2].id));
            }

            l = x;
        }
    }

    C.clear();
    for(int i = 0; i < tmp.size(); ) {
        int j = i;
        for(; j < tmp.size()-1 && tmp[j + 1].id == tmp[i].id; j++);
        C.push_back(Line(tmp[i].xl, tmp[j].xr, tmp[i].id));
        i = j + 1;
    }
}

void build2(int p, int l, int r) {
    _l(p) = l, _r(p) = r;
    if(l == r) {
        const Parabola& cur = para[l];
        lines(p).push_back(Line(cur.p, 2*cur.x-cur.p, l));
        return;
    }

    int mid = (l + r) >> 1;
    build2(p<<1, l, mid);
    build2(p<<1|1, mid + 1, r);
    combine(lines(p<<1), lines(p<<1|1), lines(p));
}
// == outline seg Tree finished ==

// == solve the problem ==
inline double work(int p, double x) {
    int l = 0, r = lines(p).size()-1;
    int ans = r;

    while (l <= r) {
        int mid = (l + r) >> 1;
        if(lines(p)[mid].xr >= x + eps) {
            ans = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    return para[lines(p)[ans].id].cal(x);
}

void solve(int p, int tl, int tr, int x1, int x2, double& ans) {
    if(tl > _r(p) || tr < _l(p)) return;
    if(tl <= _l(p) && _r(p) <= tr) {
        ans = max(ans, work(p, x1));
        ans = max(ans, work(p, x2));
        return;
    }

    solve(p<<1, tl, tr, x1, x2, ans);
    solve(p<<1|1, tl, tr, x1, x2, ans);
}
// == solve finished ==

int main() {
    freopen("flights.in", "r", stdin);
    freopen("flights.out", "w", stdout);

    scanf("%d", &n);
    _rep(i, 1, n) {
        para[i].read(mx);
    }

    build1(1, 1, n);
    build2(1, 1, n);

    scanf("%d", &m);
    _rep(i, 1, m) {
        int t1, t2, x1, x2;
        scanf("%d%d%d%d", &t1, &t2, &x1, &x2);
        double ans = 0.0;
        ans = query1(1, t1, t2, x1, x2);
        solve(1, t1, t2, x1, x2, ans);
        cout << ans << endl;
    }

    // debug(para[1].cal(11));
    // debug(mx);

}