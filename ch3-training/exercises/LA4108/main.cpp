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

class segTree {
public:
    int l, r;
    int maxv, minv, tag;
} tree[maxn << 2];

#define l(x) tree[x].l
#define r(x) tree[x].r
#define maxv(x) tree[x].maxv
#define minv(x) tree[x].minv
#define tag(x) tree[x].tag

void pushup(int p) {
    maxv(p) = max(maxv(p<<1), maxv(p<<1 | 1));
    minv(p) = min(minv(p<<1), minv(p<<1 | 1));
}

void pushdown(int p) {
    if(tag(p) && l(p) != r(p)) {
        tag(p<<1) = tag(p);
        maxv(p<<1) = minv(p<<1) = tag(p);

        tag(p<<1 | 1)= tag(p);
        maxv(p<<1 | 1) = minv(p<<1 | 1) = tag(p);

        tag(p) = 0;
    }
}

void build(int p, int l, int r) {
    l(p) = l, r(p) = r;
    tag(p) = 0;
    minv(p) = maxv(p) = 0;

    if(l == r) return;
    int mid = (l + r) >> 1;
    build(p << 1, l, mid);
    build(p << 1 | 1, mid + 1, r);
}

int change(int p, int l, int r, int val) {
    if(l(p) == l && r(p) == r && minv(p) > val) return 0;
    if(l(p) == l && r(p) == r && maxv(p) <= val) {
        // update segment node
        if(maxv(p) < val) {
            tag(p) = val;
            maxv(p) = minv(p) = val;
        }
        //debug(r - l + 1);
        return r - l + 1;
    }

    pushdown(p);

    int ans = 0;
    int mid = (l(p) + r(p)) >> 1;
    if(r <= mid) ans = change(p << 1, l, r, val);
    else if(l > mid) ans = change(p << 1 | 1, l, r, val);
    else ans = change(p << 1, l, mid, val) + change(p << 1 | 1, mid + 1, r, val);

    pushup(p);
    return ans;
}


int n, li, ri, h;

void solve() {
    int ans = 0;
    build(1, 1, maxn);
    scanf("%d", &n);
    _for(i, 0, n) {
        scanf("%d%d%d", &li, &ri, &h);
        ans += change(1, li, ri - 1, h);
    }
    printf("%d\n", ans);
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    while (true) {
        scanf("%d", &kase);
        if(kase == 0) break;

        while (kase--) {
            solve();
        }
    }

}