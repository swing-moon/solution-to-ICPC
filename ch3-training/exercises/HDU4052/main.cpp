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

const int maxn = 100000 + 10;
const int inf = 0x3f3f3f3f;

class Node {
public:
    int x;
    int y1, y2;
    int k;

    Node() {}
    Node(int x, int y1, int y2, int k) : x(x), y1(y1), y2(y2), k(k) {}

    bool operator< (const Node& rhs) const {
        return x < rhs.x;
    }
} node[maxn];

struct Rec {
    int x1, y1, x2, y2;
    void read() {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        if(x1 > x2) swap(x1, x2);
        if(y1 > y2) swap(y1, y2);
    }
} rec[maxn];

map<int, int> ny;
int raw[maxn];

void init() {
    ny.clear();
    Set(raw, 0);
}

// == seg Tree ==
class segTree {
public:
    int l, r, cover;
    int len;
} tree[maxn << 2];

#define l(x) tree[x].l
#define r(x) tree[x].r
#define cover(x) tree[x].cover
#define len(x) tree[x].len

void build(int p, int l, int r) {
    cover(p) = len(p) = 0;
    l(p) = l, r(p) = r;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid + 1, r);
}

inline void pushup(int p) {
    if(cover(p)) len(p) = (raw[r(p)] - raw[l(p) - 1]);
    else if (l(p) == r(p)) len(p) = 0;
    else len(p) = len(p<<1) + len(p<<1|1);
}

void change(int p, int l, int r, int d) {
    if(l <= l(p) && r(p) <= r) {
        cover(p) += d;
        pushup(p);
        return;
    }

    int mid = (l(p) + r(p)) >> 1;
    //debug(l(1)), debug(r(1));
    //debug(mid);
    if(l <= mid) change(p<<1, l, r, d);
    if(r > mid) change(p<<1|1, l, r, d);

    pushup(p);
}
// == seg Tree finished ==


// == solve the problem ==
int w, h, m;
int N, n;

void discrete(int _n) {
    sort(raw + 1, raw + 1 + _n);
    sort(node + 1, node + 1 + _n);
    N = unique(raw + 1, raw + 1 + _n) - raw - 1;

    _rep(i, 1, N) ny[raw[i]] = i;
}

ll solve(int _n) {
    if(m > h) return 0;
    ny.clear();

    int L, R;
    _rep(i, 1, _n) {
        int k = i << 1;
        L = raw[k - 1] = rec[i].y1;
        R = raw[k] = min(h, rec[i].y2 + m - 1) + 1;

        node[k - 1] = Node(rec[i].x1, L, R, 1);
        node[k] = Node(rec[i].x2 + 1, L, R, -1);
    }
    _n <<= 1;
    L = 1, R = 1 + min(h, m - 1);

    node[_n + 1] = Node(1, L, R, 1);
    raw[_n + 1] = L;
    node[_n + 2] = Node(1 + w, L, R, -1);
    raw[_n + 2] = R;

    _n += 2;

    discrete(_n);

    ll ans = 0;
    // == main solve() ==
    if(N) build(1, 1, N);
    _rep(i, 1, _n - 1) {
        int L = ny[node[i].y1] + 1, R = ny[node[i].y2];
        assert(L != 0 && R != 0);

        //debug(node[i].y1), debug(node[i].y2), debug(node[i].x), debug(node[i].k);
        //cout << endl;

        if(L <= R) change(1, L, R, node[i].k);
        ans += (ll) len(1) * (node[i + 1].x - node[i].x);
    }

    ans = (ll) w * h - ans;
    return ans;
    // == finished ==
}
// == solve finsihed ==


int main() {
    freopen("input.txt", "r", stdin);
    while (~scanf("%d%d%d%d", &w, &h, &n, &m)) {
        init();
        int n2 = n;

        _rep(i, 1, n) {
            rec[i].read();
        }

        ll ans = solve(n);

        _rep(i, 1, n2) {
            swap(rec[i].y1, rec[i].x1);
            swap(rec[i].y2, rec[i].x2);
        }
        swap(w, h);

        ans += solve(n2);

        if(m == 1) ans /= 2;
        printf("%lld\n", ans);

    }
}