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

const int maxn = 5000 + 6;
const int maxv = 20000 + 7;
const int inf = 0x3f3f3f3f;
int n, tot;
int Max = -inf, Min = inf;

void init() {
    tot = 0;
    Max = -inf;
    Min = inf;
}

class L {
public:
    int x1, x2;
    int y;
    int st;
    bool operator< (const L& rhs) const {
        return y < rhs.y;
    }
};
L a[maxn << 1];

class segTree{
public:
    int l, r;
    bool lc, rc;
    int len;
    int cover;
    int cnt;
    // cnt: cover by discrete segment
} t[maxv << 2];

void build(int p, int l, int r) {
    t[p].l = l;
    t[p].r = r;
    t[p].lc = t[p].rc = 0;
    t[p].len = t[p].cnt = t[p].cover = 0;

    if(l == r) return;
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

void check(int p) {
    if(t[p].cover) {
        t[p].len = t[p].r + 1 - t[p].l;
        t[p].lc = t[p].rc = 1;
        t[p].cnt = 1;
    }
    else if(t[p].l == t[p].r) {
        t[p].len = 0;
        t[p].lc = t[p].rc = 0;
        t[p].cnt = 0;
    }
    else {
        t[p].len = t[p<<1].len + t[p<<1 | 1].len;
        t[p].cnt = t[p<<1].cnt + t[p<<1 | 1].cnt;
        t[p].lc = t[p<<1].lc;
        t[p].rc = t[p<<1 | 1].rc;

        if(t[p<<1].rc && t[p<<1 | 1].lc) t[p].cnt--;
    }
}

void change(int p, int l, int r, int d) {
    if(l <= t[p].l && t[p].r <= r) {
        t[p].cover += d;
        check(p);
        return;
    }

    int mid = (t[p].l + t[p].r) >> 1;
    if(r <= mid) change(p << 1, l, r, d);
    else if(l > mid) change(p << 1 | 1, l, r, d);
    else {
        change(p << 1, l, mid, d);
        change(p << 1 | 1, mid + 1, r, d);
    }
    check(p);
}

void picture() {
    sort(a, a + tot);
    build(1, Min, Max - 1);

    int ans = 0, preOverlap = 0;
    _for(i, 0, tot) {
        change(1, a[i].x1, a[i].x2 - 1, a[i].st);
        ans += abs(preOverlap - t[1].len);
        ans += 2 * t[1].cnt * (a[i + 1].y - a[i].y);

        preOverlap = t[1].len;
    }
    cout << ans << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    init();
    int x1, y1, x2, y2;
    _for(i, 0, n) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        Max = max(Max, max(x1, x2));
        Min = min(Min, min(x1, x2));

        L& a1 = a[tot];
        L& a2 = a[tot + 1];

        a1.x1 = a2.x1 = x1;
        a1.x2 = a2.x2 = x2;

        a1.y = y1;
        a2.y = y2;

        a1.st = 1;
        a2.st = -1;

        tot += 2;
    }

    picture();
}