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

typedef pair<int, int> PII;
const int maxn = 500000 + 2;
llong sum[maxn];
int n, m;

void init() {
    Set(sum, 0);
}

llong cal(const PII x) {
    return sum[x.second] - sum[x.first - 1];
}

PII better(const PII& lhs, const PII& rhs) {
    llong suml = cal(lhs), sumr = cal(rhs);
    if(suml != sumr) return suml > sumr ? lhs : rhs;
    return lhs < rhs ? lhs : rhs;
}


class SegTree {
public:
    int l, r;

    PII dat;
    int lx, rx;
};

SegTree t[maxn * 4];
typedef SegTree Node;

Node combine(const Node& lhs, const Node& rhs) {
    Node ret;
    ret.l = lhs.l; ret.r = rhs.r;

    ret.lx = better(PII(lhs.l, lhs.lx), PII(lhs.l, rhs.lx)).second;
    ret.rx = better(PII(rhs.rx, rhs.r), PII(lhs.rx, rhs.r)).first;
    // then ret.dat = cross
    ret.dat = better(better(lhs.dat, rhs.dat), PII(lhs.rx, rhs.lx));

    return ret;
}

void build(int p, int l, int r) {
    t[p].l = l;
    t[p].r = r;

    if(l == r) {
        t[p].lx = t[p].rx = l;
        t[p].dat = PII(l, l);
        return;
    }

    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);

    t[p].lx = better(PII(t[p << 1].l, t[p << 1].lx), PII(t[p << 1].l, t[p << 1 | 1].lx)).second;
    t[p].rx = better(PII(t[p << 1 | 1].rx, t[p << 1 | 1].r), PII(t[p << 1].rx, t[p << 1 | 1].r)).first;
    t[p].dat = better(better(t[p << 1].dat, t[p << 1 | 1].dat), PII(t[p << 1].rx, t[p << 1 | 1].lx));
}

Node ask(int p, int x, int y) {
    if(x <= t[p].l && t[p].r <= y) return t[p];

    int mid = (t[p].l + t[p].r) >> 1;
    Node ans;

    if(x <= mid && mid < y) {
        // both left tree and right tree
        ans = combine(ask(p << 1, x, y), ask(p << 1 | 1, x, y));
    }
    else if(x <= mid) {
        // only left
        ans = ask(p << 1, x, y);
    }
    else if(mid < y) {
        ans = ask(p << 1 | 1, x, y);
    }

    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 1;
    while (scanf("%d%d", &n, &m) != EOF) {
        init();
        _rep(i, 1, n) {
            llong x;
            scanf("%lld", &x);
            sum[i] = sum[i - 1] + x;
        }

        build(1, 1, n);
        printf("Case %d:\n", kase++);

        _rep(i, 1, m) {
            int x, y;
            scanf("%d%d", &x, &y);
            PII res = ask(1, x, y).dat;
            printf("%d %d\n", res.first, res.second);
        }
    }
}