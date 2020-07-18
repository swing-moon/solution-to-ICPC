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
#define Cpy(a, b) memcpy(a, b, sizeof(b))
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

pair<int, int> crack(int n) {
    int st = sqrt(n);
    int fac = n / st;
    while (n % st) {
        st += 1;
        fac = n / st;
    }

    return make_pair(st, fac);
}

inline ll qpow(ll a, int n) {
    ll ans = 1;
    for(; n; n >>= 1) {
        if(n & 1) ans *= 1ll * a;
        a *= a;
    }
    return ans;
}

// ============================================================================= //
#pragma GCC optimize(2)
const int maxn = 1e6 + 5;
const int inf = 0x3f3f3f3f;

int n, m, maxy = -inf;
int ans[maxn];

class Node {
public:
    int x, y;
    int tp;

    Node() {}
    Node(int x, int y, int tp) : x(x), y(y), tp(tp) {}

    bool operator< (const Node& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
} a[maxn], buf[maxn];

// == fenwick definition ==
class Fwick {
public:
    int C[maxn];
    int n;

    void _init(int n) {
        Set(C, -inf);
        this->n = n;
    }

    void add(int y, int val) {
        for(; y < n; y += lowbit(y)) C[y] = max(C[y], val);
    }

    int ask(int y) {
        int ret = -inf;
        for(; y > 0; y -= lowbit(y)) ret = max(ret, C[y]);

        return ret;
    }

    void reset(int y) {
        for(; y < n; y += lowbit(y)) C[y] = -inf;
    }
} fwick;
// == fenwick finished ==

// == CDQ ==
inline void work(int st, int ed, int w, int dx, int dy) {
    for(int i = st; i != ed; i += w) {
        int num = dx * buf[i].x + dy * buf[i].y;

        int y = dy == -1 ? maxy - buf[i].y : buf[i].y;

        if(a[buf[i].tp].tp == 1) fwick.add(y, num);
        else ans[buf[i].tp] = min(ans[buf[i].tp], abs(num - fwick.ask(y)));

        //debug(ans[buf[i].tp]);
    }

    for(int i = st; i != ed; i += w) {
        int y = dy == -1 ? maxy - buf[i].y : buf[i].y;
        if(a[buf[i].tp].tp == 1) fwick.reset(y);
    }
}

void CDQ(int l, int r) {
    int mid = (l + r) >> 1;
    if(l < mid) CDQ(l, mid);
    if(mid + 1 < r) CDQ(mid + 1, r);

    int tot = 0;
    _rep(i, l, r) {
        if((i <= mid && a[i].tp == 1) || (i > mid && a[i].tp == 2)) {
            buf[++tot] = a[i];
            buf[tot].tp = i;
        }
    }

    sort(buf + 1, buf + 1 + tot);
    work(1, tot + 1, 1, 1, 1);
    work(1, tot + 1, 1, 1, -1);
    work(tot, 0, -1, -1, 1);
    work(tot, 0, -1, -1, -1);
}
// == CDQ finished ==

void init() {
    Set(ans, inf);

    fwick._init(maxy);
}


int main() {
    freopen("input.txt", "r", stdin);
    cin >> n >> m;

    // get data
    _rep(i, 1, n) {
        scanf("%d%d", &a[i].x, &a[i].y);
        a[i].tp = 1;
        maxy = max(maxy, a[i].y);
    }
    _rep(i, 1, m) {
        scanf("%d%d%d", &a[n+i].tp, &a[n+i].x, &a[n+i].y);
        maxy = max(maxy, a[n+i].y);
    }
    maxy++;
    //debug(maxy);

    // get data finished
    init();
    CDQ(1, n + m);

    _rep(i, 1, n + m) if(a[i].tp == 2) printf("%d\n", ans[i]);
}