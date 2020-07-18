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

const int maxn = 100000 + 10;
int A[maxn], n, m;

class segTree {
public:
    int l, r;
    llong sum, tag;
#define l(x) tree[x].l
#define r(x) tree[x].r
#define sum(x) tree[x].sum
#define tag(x) tree[x].tag
} tree[maxn * 4];

void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    //debug(p);
    if(l == r) {
        sum(p) = A[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);

    sum(p) = sum(p << 1) + sum(p << 1 | 1);
}

void spread(int p) {
    if(tag(p)) {
        sum(p << 1) += tag(p) * (r(p<<1) - l(p<<1) + 1);
        sum(p << 1 | 1) += tag(p) * (r(p<<1 | 1) - l(p<<1 | 1) + 1);
        tag(p << 1) += tag(p);
        tag(p << 1 | 1) += tag(p);
        tag(p) = 0;
    }
}

void change(int p, int l, int r, int d) {
    if(l <= l(p) && r(p) <= r) {
        sum(p) += (llong)d * (r(p) - l(p) + 1);
        tag(p) += d;
        return;
    }
    spread(p);
    int mid = (l(p) + r(p)) >> 1;
    if(l <= mid) change(p<<1, l, r, d);
    if(r > mid) change(p<<1 | 1, l, r, d);

    sum(p) = sum(p<<1) + sum(p<<1 | 1);
}

llong ask(int p, int l, int r) {
    if(l <= l(p) && r(p) <= r) return sum(p);
    spread(p);

    int mid = (l(p) + r(p)) >> 1;
    llong val = 0;
    if(l <= mid) val += ask(p<<1, l, r);
    if(r > mid) val += ask(p<<1 | 1, l, r);
    return val;
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> m;
    _rep(i, 1, n) scanf("%d", &A[i]);

    build(1, 1, n);

    while (m--) {
        char op[2];
        int l, r;
        scanf("%s%d%d", op, &l, &r);
        if(op[0] == 'C') {
            int d;
            scanf("%d", &d);
            change(1, l, r, d);
        }
        else printf("%lld\n", ask(1, l, r));
    }
}