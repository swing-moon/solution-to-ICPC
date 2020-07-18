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
typedef long long llong;
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

const int maxn = 10000 + 6;
unsigned int n, W, H;
int m;
// discrete n -> m

class R {
public:
    llong x;
    llong y1, y2;
    int c;
    bool operator< (const R& rhs) const {
        return x < rhs.x || (x == rhs.x && c < rhs.c);
    }
};

R a[maxn << 1];
llong raw[maxn << 1];
map<llong, int> ny;

void init() {
    //
    Set(raw, 0);
    ny.clear();
}

void discrete() {
    sort(raw + 1, raw + 1 + n);
    m = unique(raw + 1, raw + 1 + n) - raw - 1;

    _rep(i, 1, m) {
        ny[raw[i]] = i;
    }
}

class segTree {
public:
    int l, r, dat, tag;
#define l(p) t[p].l
#define r(p) t[p].r
#define dat(p) t[p].dat
#define tag(p) t[p].tag
} t[maxn << 3];

void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    dat(p) = tag(p) = 0;
    if(l == r) return;
    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1 | 1, mid + 1, r);
}

void spread(int p) {
    tag(p<<1) += tag(p);
    dat(p<<1) += tag(p);;

    tag(p<<1 | 1) += tag(p);
    dat(p<<1 | 1) += tag(p);

    tag(p) = 0;
}

void change(int p, int l, int r, int c) {
    if(l <= l(p) && r(p) <= r) {
        dat(p) += c;
        tag(p) += c;
        return;
    }

    if(tag(p)) spread(p);

    int mid = (l(p) + r(p)) >> 1;
    if(l <= mid) change(p<<1, l, r, c);
    if(r > mid) change(p<<1 | 1, l, r, c);

    dat(p) = max(dat(p<<1), dat(p<<1 | 1));
}

void starsWindow() {
    sort(a + 1, a + 1 + n);
    build(1, 1, m);

    int ans = 0;
    _rep(i, 1, n) {
        int y1 = ny[a[i].y1], y2 = ny[a[i].y2];
        change(1, y1, y2, a[i].c);
        ans = max(ans, dat(1));
    }
    cout << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (cin >> n >> W >> H) {
        init();

        _rep(i, 1, n) {
            int k = (i<<1);
            cin >> a[k-1].x >> a[k-1].y1 >> a[k-1].c;
            a[k].x = a[k-1].x + W;
            raw[k-1] = a[k].y1 = a[k-1].y1;
            raw[k] = a[k].y2 = a[k-1].y2 = a[k-1].y1 + H - 1;
            a[k].c = -a[k-1].c;
        }
        // input finished
        n <<= 1;
        discrete();

        starsWindow();
    }
}