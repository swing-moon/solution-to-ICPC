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

const int maxn = 100000 + 5;
int n, m;
llong a[maxn];
int t;

int pos[maxn];
llong add[maxn], sum[maxn];
// add[i] is tot segment[i] is added d

void init() {
    Set(pos, 0);
    Set(add, 0);
    Set(sum, 0);
}

class Seg {
public:
    int l, r;
} seg[maxn];

inline void cal() {
    t = sqrt(n);
    _rep(i, 1, t) {
        seg[i].l = (i - 1) * sqrt(n) + 1;
        seg[i].r = i * sqrt(n);
    }
    if(seg[t].r < n) {
        t++;
        seg[t].l = seg[t - 1].r + 1;
        seg[t].r = n;
    }

    _rep(i, 1, t) {
        _rep(k, seg[i].l, seg[i].r) {
            pos[k] = i;
            sum[i] += a[k];
        }
    }
}

void change(int l, int r, llong d) {
    int p = pos[l], q = pos[r];
    if(p == q) {
        _rep(i, l, r) a[i] += d;
        sum[p] += d * (r - l + 1);
    }
    else {
        _rep(i, p + 1, q - 1) add[i] += d;

        _rep(i, l, seg[p].r) a[i] += d;
        sum[p] += d * (seg[p].r - l + 1);

        _rep(i, seg[q].l, r) a[i] += d;
        sum[q] += d * (r - seg[q].l + 1);
    }
}

llong ask(int l, int r) {
    int p = pos[l], q = pos[r];
    llong ans = 0;

    if(p == q) {
        _rep(i, l, r) ans += a[i];
        ans += add[p] * (r - l + 1);
    }
    else {
        _rep(i, p + 1, q - 1) {
            ans += sum[i] + add[i] * (seg[i].r - seg[i].l + 1);
        }

        _rep(i, l, seg[p].r) ans += a[i];
        ans += add[p] * (seg[p].r - l + 1);

        _rep(i, seg[q].l, r) ans += a[i];
        ans += add[q] * (r - seg[q].l + 1);
    }
    return ans;
}


int main() {
    freopen("input.txt", "r", stdin);
    init();
    cin >> n >> m;
    _rep(i, 1, n) scanf("%lld", &a[i]);

    // init calculate
    cal();
    while (m--) {
        char op[3];
        int l, r, d;

        scanf("%s", op);
        scanf("%d%d", &l, &r);

        if(op[0] == 'C') {
            scanf("%d", &d);
            change(l, r, d);
        }
        else printf("%lld\n", ask(l, r));
    }
}