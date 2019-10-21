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

const int maxn = 500000 + 10;
int n, m;

llong A[maxn], B[maxn];
llong fwick[maxn];

llong gcd(llong a, llong b) {
    return b ? gcd(b, a % b) : a;
}

void add(int x, llong d) {
    for(; x <= n; x += lowbit(x)) fwick[x] += d;
}

llong sum(int x) {
    llong ret = 0;
    for(; x > 0; x -= lowbit(x)) ret += fwick[x];
    return ret;
}

void init() {
    Set(A, 0);
    Set(B, 0);
    Set(fwick, 0);
}

class SegTree {
public:
    int l, r;
    llong dat;
};

SegTree t[maxn * 4];
typedef SegTree Node;

void build(int p, int l, int r) {
    t[p].l = l; t[p].r = r;
    if(l == r) {
        t[p].dat = B[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);

    t[p].dat = gcd(t[p << 1].dat, t[p << 1 | 1].dat);
}

void change(int p, int x, llong v) {
    if(t[p].l == t[p].r) {
        t[p].dat += v;
        return;
    }

    int mid = (t[p].l + t[p].r) >> 1;
    if(x <= mid) change(p << 1, x, v);
    else change(p << 1 | 1, x, v);

    t[p].dat = gcd(t[p << 1].dat, t[p << 1 | 1].dat);
}

llong ask(int p, int l, int r) {
    if(l <= t[p].l && t[p].r <= r) {
        return abs(t[p].dat);
    }

    int mid = (t[p].l + t[p].r) >> 1;

    llong ret = 0;

    if(l <= mid) ret = gcd(ret, ask(p << 1, l, r));
    if(r > mid) ret = gcd(ret, ask(p << 1 | 1, l, r));

    return abs(ret);
}

int main() {
    freopen("input.txt", "r", stdin);
    init();
    scanf("%d%d", &n, &m);

    _rep(i, 1, n) {
        scanf("%lld", &A[i]);
        B[i] = A[i] - A[i - 1];
    }

    // then build segTree
    build(1, 1, n);

    _for(i, 0, m) {
        // query
        char str[2];
        scanf("%s", str);
        int l, r;
        scanf("%d%d", &l, &r);

        if(str[0] == 'Q') {
            //
            llong al = A[l] + sum(l);
            llong val = l < r ? ask(1, l + 1, r) : 0;
            printf("%lld\n", gcd(al, val));
        }

        if(str[0] == 'C') {
            //
            llong d;
            scanf("%lld", &d);
            change(1, l, d);
            if(r < n) change(1, r + 1, -d);

            add(l, d);
            add(r + 1, -d);
        }
    }
}