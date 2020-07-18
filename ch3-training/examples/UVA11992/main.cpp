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

const int maxn = 1e6 + 5;
const int inf = 1e9 + 1;
int r, c, m;
const int maxr = 20 + 5;
int Min = inf, Max = -inf, Sum = 0;

void initQry() {
    Min = inf;
    Max = -inf;
    Sum = 0;
}

class segTree {
public:
    int l, r;
    int sum, maxv, minv;
    int tagAdd, tagSet;
#define l(x) tree[x].l
#define r(x) tree[x].r
#define sum(x) tree[x].sum
#define maxv(x) tree[x].maxv
#define minv(x) tree[x].minv
#define tagAdd(x) tree[x].tagAdd
#define tagSet(x) tree[x].tagSet

    void clear() {
        l = r = 0;
        sum = maxv = minv = 0;
        tagAdd = 0;
        tagSet = -1;
    }
} tree[maxn * 4];

void spread(int p) {
    if(tagSet(p) >= 0) {
        tagSet(p << 1) = tagSet(p << 1 | 1) = tagSet(p);
        tagAdd(p << 1) = tagAdd(p << 1 | 1) = 0;
        maxv(p << 1) = maxv(p << 1 | 1) = tagSet(p);
        minv(p << 1) = minv(p << 1 | 1) = tagSet(p);
        sum(p << 1) = tagSet(p) * (r(p << 1) - l(p << 1) + 1);
        sum(p << 1 | 1) = tagSet(p) * (r(p << 1 | 1) - l(p << 1 | 1) + 1);
        tagSet(p) = -1;
    }
    if(tagAdd(p) > 0) {
        tagAdd(p << 1) += tagAdd(p);
        tagAdd(p << 1 | 1) += tagAdd(p);

        maxv(p << 1) += tagAdd(p);
        maxv(p << 1 | 1) += tagAdd(p);

        minv(p << 1) += tagAdd(p);
        minv(p << 1 | 1) += tagAdd(p);

        sum(p << 1) += tagAdd(p) * (r(p << 1) - l(p << 1) + 1);
        sum(p << 1 | 1 ) += tagAdd(p) * (r(p << 1 | 1) - l(p << 1 | 1) + 1);

        tagAdd(p) = 0;
    }
}

void update(int p) {
    sum(p) = sum(p << 1) + sum(p << 1 | 1);
    maxv(p) = max(maxv(p << 1), maxv(p << 1 | 1));
    minv(p) = min(minv(p << 1), minv(p << 1 | 1));
}

void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    sum(p) = 0;
    maxv(p) = minv(p) = 0;
    tagAdd(p) = 0;
    tagSet(p) = -1;

    if(l == r) return;

    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

void opSet(int p, int l, int r, int v) {
    if(l <= l(p) && r(p) <= r) {
        sum(p) = v * (r(p) - l(p) + 1);
        maxv(p) = minv(p) = v;

        tagSet(p) = v;
        tagAdd(p) = 0;
        return;
    }

    spread(p);

    int mid = (l(p) + r(p)) >> 1;
    if(l <= mid) opSet(p << 1, l, r, v);
    if(r > mid) opSet(p << 1 | 1, l, r, v);

    update(p);
}

void opAdd(int p, int l, int r, int v) {
    if(l <= l(p) && r(p) <= r) {
        sum(p) += v * (r(p) - l(p) + 1);
        maxv(p) += v;
        minv(p) += v;
        tagAdd(p) += v;
        return;
    }

    spread(p);

    int mid = (l(p) + r(p)) >> 1;
    if(l <= mid) opAdd(p << 1, l, r, v);
    if(r > mid) opAdd(p << 1 | 1, l, r, v);

    update(p);
}

void query(int p, int l, int r) {
    if(l <= l(p) && r(p) <= r) {
        Sum += sum(p);
        Min = min(Min, minv(p));
        Max = max(Max, maxv(p));
        return;
    }

    spread(p);

    int mid = (l(p) + r(p)) >> 1;
    if(l <= mid) query(p << 1, l, r);
    if(r > mid) query(p << 1 | 1, l, r);

    update(p);
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d%d", &r, &c, &m) == 3) {
        int op, x1, x2, y1, y2, v;

        build(1, 1, r * c);

        while (m--) {
            scanf("%d", &op);
            if(op == 1) {
                scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
                _rep(i, x1, x2) {
                    opAdd(1, (i - 1) * c + y1, (i - 1) * c + y2, v);
                }
            }
            if(op == 2) {
                scanf("%d%d%d%d%d", &x1, &y1, &x2, &y2, &v);
                _rep(i, x1, x2) {
                    opSet(1, (i - 1) * c + y1, (i - 1) * c + y2, v);
                }
            }
            if(op == 3) {
                scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
                initQry();
                _rep(i, x1, x2) {
                    query(1, (i - 1) * c + y1, (i - 1) * c + y2);
                }
                printf("%d %d %d\n", Sum, Min, Max);
            }
        }
    }
}