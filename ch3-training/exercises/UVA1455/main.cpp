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

const int maxn = 1000000 + 10;
const int maxm = maxn * 2;

int n, m;

struct _A {
    int x, y;
} A[maxn];

int pa[maxn], miny[maxn], maxy[maxn], cnt[maxn];
int top = 0;

int findset(int x) {
    return x == pa[x] ? x : pa[x] = findset(pa[x]);
}

void init() {
    _rep(i, 0, n) pa[i] = i;
    Set(miny, 0);
    Set(maxy, 0);
    Set(cnt, 0);
    top = 0;
}

// == seg Tree ==
class segTree {
public:
    int l, r;
    int num, city;
    int tag1, tag2;
} tree[maxm << 2];
#define l(x) tree[x].l
#define r(x) tree[x].r
#define num(x) tree[x].num
#define city(x) tree[x].city
#define tag1(x) tree[x].tag1
#define tag2(x) tree[x].tag2

void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    num(p) = city(p) = 0;
    tag1(p) = tag2(p) = 0;

    if(l == r) return;
    int mid = (l + r) >> 1;
    build(p<<1, l, mid);
    build(p<<1|1, mid + 1, r);
}

void pushdown(int p) {
    if(tag1(p) && l(p) != r(p)) {
        // deal with tag1, num
        tag1(p<<1) += tag1(p);
        num(p<<1) += (r(p<<1) - l(p<<1) + 1) * tag1(p);

        tag1(p<<1|1) += tag1(p);
        num(p<<1|1) += (r(p<<1|1) - l(p<<1|1) + 1) * tag1(p);

        tag1(p) = 0;
    }

    if(tag2(p) && l(p) != r(p)) {
        // deal with tag2, city
        tag2(p<<1) += tag2(p);
        city(p<<1) += (r(p<<1) - l(p<<1) + 1) * tag2(p);

        tag2(p<<1|1) += tag2(p);
        city(p<<1|1) += (r(p<<1|1) - l(p<<1|1) + 1) * tag2(p);

        tag2(p) = 0;
    }
}

void pushup(int p) {
    num(p) = num(p<<1) + num(p<<1|1);
    city(p) = city(p<<1) + city(p<<1|1);
}

void change(int p, int l, int r, int a, int b) {
    if(l(p) == l && r(p) == r) {
        tag1(p) += a;
        num(p) += (r(p) - l(p) + 1) * a;

        tag2(p) += b;
        city(p) += (r(p) - l(p) + 1) * b;

        return;
    }

    pushdown(p);

    int mid = (l(p) + r(p)) >> 1;
    if(r <= mid) change(p<<1, l, r, a, b);
    else if(l > mid) change(p<<1|1, l, r, a, b);
    else {
        change(p<<1, l, mid, a, b);
        change(p<<1|1, mid + 1, r, a, b);
    }

    pushup(p);
}

int query(int p, int C) {
    if(l(p) == r(p)) return p;

    pushdown(p);
    int mid = (l(p) + r(p)) >> 1;
    if(C <= mid) return query(p<<1, C);
    else return query(p<<1|1, C);
}
// == seg Tree finished ==

void inp() {
    scanf("%d", &n);
    init();

    _for(i, 0, n) {
        scanf("%d%d", &A[i].x, &A[i].y);
        A[i].y <<= 1;

        top = max(top, A[i].y);
        maxy[i] = miny[i] = A[i].y;
        cnt[i] = 1;
    }

    build(1, 0, top);
    _for(i, 0, n) change(1, A[i].y, A[i].y, 1, 1);
}

void solve() {
    scanf("%d", &m);
    while (m--) {
        char cmd[10];
        scanf("%s", cmd);

        if(cmd[0] == 'r') {
            int a, b;
            scanf("%d%d", &a, &b);

            a = findset(a);
            b = findset(b);

            if(a == b) continue;

            change(1, miny[a], maxy[a], -1, -cnt[a]);
            change(1, miny[b], maxy[b], -1, -cnt[b]);

            pa[b] = a;
            cnt[a] += cnt[b];
            miny[a] = min(miny[a], miny[b]);
            maxy[a] = max(maxy[a], maxy[b]);

            change(1, miny[a], maxy[a], 1, cnt[a]);
        }
        else {
            double c;
            scanf("%lf", &c);
            int C = c * 2 + 0.5;

            if(C > top) puts("0 0");
            else {
                int ans = query(1, C);
                printf("%d %d\n", num(ans), city(ans));
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);

    while (kase--) {
        inp();
        solve();
    }
}