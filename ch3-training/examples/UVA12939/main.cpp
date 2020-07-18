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

const int maxn = 200000 + 10;
const int NIL = 0;
int n, d, m;

// == Point definition ==
class Point {
public:
    int x, y;
} PO[maxn];
// == Point finsihed ==

// == Node definition ==
int ID[maxn];
     /* used for mapping ID */

int K = 2, cd;

class KDTree {
public:
    int xy[2], xymin[2], xymax[2];
    int cld[2];
    int sum, fa, num;

    bool operator< (const KDTree& rhs) const {
        return xy[cd] < rhs.xy[cd];
    }
    inline void update();
    inline void _init(int i);
} T[maxn];

inline void KDTree::_init(int i) {
    ID[fa] = i;
    _for(j, 0, K) xymax[j] = xymin[j] = xy[j];
    num = sum = 0;
    cld[0] = cld[1] = NIL;
}

inline void KDTree::update() {
    _for(i, 0, K) if(cld[i]) _for(j, 0, K) {
        xymin[j] = min(xymin[j], T[cld[i]].xymin[j]);
        xymax[j] = max(xymax[j], T[cld[i]].xymax[j]);
    }
}

int build(int l, int r, int dep, int _fa) {
    if(l > r) return NIL;
    int mid = (l + r) >> 1;

    cd = dep % K;
    nth_element(T + l, T + mid, T + r + 1);
    KDTree& cur = T[mid];
    //assert(cur.fa != 0);

    cur._init(mid);
    assert(ID[cur.fa] == mid);
    cur.fa = _fa;

    if(l < mid) cur.cld[0] = build(l, mid - 1, dep + 1, mid);
    if(r > mid) cur.cld[1] = build(mid + 1, r, dep + 1, mid);
    cur.update();

    return mid;
}

int root;
// == Node definition finished ==

// == KDTree query ==
ll ANS[maxn];

inline bool inRange(int x, int l, int r) {
    return l <= x && x <= r;
}
int query(int u, int x1, int x2, int y1, int y2) {
    int res = 0;

    const KDTree& cur = T[u];
    if(cur.xymin[0] > x2 || cur.xymax[0] < x1 || cur.xymin[1] > y2 || cur.xymax[1] < y1 || cur.sum == 0) {
        return 0;
    }
    if(x1 <= cur.xymin[0] && cur.xymax[0] <= x2 && y1 <= cur.xymin[1] && cur.xymax[1] <= y2) {
        return cur.sum;
    }

    if(inRange(cur.xy[0], x1, x2) && inRange(cur.xy[1], y1, y2)) res += cur.num;
    _for(i, 0, K) if(cur.cld[i]) {
        res += query(cur.cld[i], x1, x2, y1, y2);
    }

    return res;
}
// == KDTree query finished ==

// == Mo algo ==
int belong[maxn];
int sz, t;

class Qry {
public:
    int l, r, id;
} qry[maxn];

void block() {
    sz = sqrt(n);
    t = n / sz;
    _rep(i, 1, t) _rep(k, (i - 1) * sz + 1, i * sz) belong[k] = i;
    if(t * sz < n) {
        t++;
        _rep(k, (t - 1) * sz + 1, n) belong[k] = t;
    }
}

bool cmp(const Qry& a, const Qry& b) {
    if(belong[a.l] ^ belong[b.l]) return belong[a.l] < belong[b.l];
    return a.r < b.r;
}

void add(int pos, ll& ans) {
    ans += query(root, PO[pos].x - d, PO[pos].x + d, PO[pos].y - d, PO[pos].y + d);
    int ti = ID[pos];
    T[ti].num = 1;
    while (ti) T[ti].sum++, ti = T[ti].fa;
}

void del(int pos, ll& ans) {
    int ti = ID[pos];
    T[ti].num = 0;
    while (ti) T[ti].sum--, ti = T[ti].fa;
    ans -= query(root, PO[pos].x - d, PO[pos].x + d, PO[pos].y - d, PO[pos].y + d);
}
// == Mo algo finished ==

void init() {
    Set(ID, 0);
    Set(belong, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    for(int t = 1, x, y; scanf("%d%d%d", &n, &d, &m) == 3; t++) {
        init();
        printf("Case %d:\n", t);

        // input point data
        _rep(i, 1, n) {
            KDTree& cur = T[i];
            scanf("%d%d", &x, &y);
            cur.xy[0] = PO[i].x = x + y;
            cur.xy[1] = PO[i].y = x - y;
            cur.fa = i;
        }

        // build tree
        root = build(1, n, 0, 0);

        // block for Mo algorithm
        // remember sort query then Mo algorithm
        _rep(i, 1, m) {
            scanf("%d%d", &qry[i].l, &qry[i].r);
            qry[i].id = i;
        }
        block();
        sort(qry + 1, qry + 1 + m, cmp);

        // use Mo algo and KDTree query
        int l = 1, r = 0;
        ll ans = 0;
        _rep(i, 1, m) {
            int ql = qry[i].l, qr = qry[i].r;
            while (r < qr) add(++r, ans);
            while (r > qr) del(r--, ans);
            while (l < ql) del(l++, ans);
            while (l > ql) add(--l, ans);

            ANS[qry[i].id] = ans;
        }

        _rep(i, 1, m) printf("%lld\n", ANS[i]);
    }
}