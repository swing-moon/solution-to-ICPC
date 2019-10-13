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

const int maxn = 500000 + 2;
const int inf = maxn;
int n, m;
int A[maxn];

class SegTree {
public:
    int l, r, dat;
    int sum, lmax, rmax;
};

typedef SegTree Node;

SegTree t[maxn * 4];

void build(int p, int l, int r) {
    t[p].l = l;
    t[p].r = r;

    if(l == r) {
        t[p].dat = t[p].sum = t[p].lmax = t[p].rmax = A[l];
        return;
    }

    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);

    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
    t[p].lmax = max(t[p << 1].lmax, t[p << 1].sum + t[p << 1 | 1].lmax);
    t[p].rmax = max(t[p << 1 | 1].rmax, t[p << 1 | 1].sum + t[p << 1].rmax);
    t[p].dat = max(max(t[p << 1].dat, t[p << 1 | 1].dat), t[p << 1].rmax + t[p << 1 | 1].lmax);
}

void change(int p, int x, int v) {
    if(t[p].l == t[p].r) {
        t[p].sum = t[p].dat = t[p].lmax = t[p].rmax = v;
        return;
    }
    int mid = (t[p].l + t[p].r) >> 1;
    if(x <= mid) change(p << 1, x, v);
    else change(p << 1 | 1, x, v);

    t[p].sum = t[p << 1].sum + t[p << 1 | 1].sum;
    t[p].lmax = max(t[p << 1].lmax, t[p << 1].sum + t[p << 1 | 1].lmax);
    t[p].rmax = max(t[p << 1 | 1].rmax, t[p << 1 | 1].sum + t[p << 1].rmax);
    t[p].dat = max(max(t[p << 1].dat, t[p << 1 | 1].dat), t[p << 1].rmax + t[p << 1 | 1].lmax);
}

Node ask(int p, int x, int y) {
    // ask [x, y] dat
    if(x <= t[p].l && t[p].r <= y) return t[p];

    Node nl, nr, ans;
    nl.lmax = nl.rmax = nl.sum = nl.dat = nr.lmax = nr.rmax = nr.dat = nr.sum = -inf;
    ans.sum = 0;

    int mid = (t[p].l + t[p].r) >> 1;
    if(x <= mid) {
        nl = ask(p << 1, x, y);
        ans.sum += nl.sum;
    }
    if(y > mid) {
        nr = ask(p << 1 | 1, x, y);
        ans.sum += nr.sum;
    }

    ans.dat = max(max(nl.dat, nr.dat), nl.rmax + nr.lmax);
    ans.lmax = max(nl.lmax, nl.sum + nr.lmax);
    ans.rmax = max(nr.rmax, nr.sum + nl.rmax);

    if(x > mid) ans.lmax = max(ans.lmax, nr.lmax);
    if(y <= mid) ans.rmax = max(ans.rmax, nl.rmax);

    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &n);
    _rep(i, 1, n) scanf("%d", &A[i]);
    build(1, 1, n);

    scanf("%d", &m);
    while (m--) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);

        if(op == 1) {
            if(x > y) swap(x, y);
            cout << ask(1, x, y).dat << endl;
        }
        if(op == 0) change(1, x, y);
    }
}