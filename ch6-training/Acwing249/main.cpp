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

const int maxn = 40000 + 10;
const int maxt = 35 + 5;

class Mode {
public:
    int CNT, pos;
    void clear() {
        CNT = pos = 0;
    }
};
Mode f[maxt][maxt], cur;

int belong[maxn], c[maxt][maxt][maxn];

void init() {
    Set(belong, 0);
    Set(c, 0);
}

int a[maxn], buf[maxn];
int n, m, tot, t, sz;

void discrete() {
    Cpy(buf, a);
    sort(buf + 1, buf + 1 + n);
    tot = unique(buf + 1, buf + 1 + n) - buf - 1;
    _rep(i, 1, n) {
        a[i] = lower_bound(buf + 1, buf + 1 + tot, a[i]) - buf;
    }
}

// == block ==
class Blk {
public:
    int L, R;
};
Blk blk[maxn];

void block() {
    t = pow((double)n, 1.0 / 3.0);
    sz = t ? n / t : n;

    _rep(i, 1, t) {
        blk[i].L = (i - 1) * sz + 1;
        blk[i].R = i * sz;
    }
    if(blk[t].R < n) {
        t++;
        blk[t].L = blk[t - 1].R + 1;
        blk[t].R = n;
    }

    _rep(i, 1, t) _rep(k, blk[i].L, blk[i].R) {
        belong[k] = i;
    }
}

// == blocked finished ==

// == init seg ==
void initseg() {
    cur.clear();
    _for(i, 0, maxt) _for(j, 0, maxt) f[i][j].clear();

    _rep(i, 1, t) _rep(j, i, t) {
        _rep(k, blk[i].L, blk[j].R) {
            ++c[i][j][a[k]];
        }

        _rep(x, 1, tot) {
            if(f[i][j].CNT < c[i][j][x]) {
                f[i][j].CNT = c[i][j][x];
                f[i][j].pos = x;
            }
        }
    }
}

// == init seg finished ==
inline void maintain(int x, int y, int val) {
    ++c[x][y][val];
    if(c[x][y][val] > cur.CNT || (c[x][y][val] == cur.CNT && val < cur.pos)) {
        cur.CNT = c[x][y][val];
        cur.pos = val;
    }
}
// == query ==
int query(int l, int r) {
    int p = belong[l], q = belong[r];
    int x = 0, y = 0;
    if(p + 1 <= q - 1) {
        x = p + 1; y = q - 1;
    }

    cur = f[x][y];

    if(p == q) {
        // at the same block
        _rep(i, l, r) maintain(x, y, a[i]);
        _rep(i, l, r) --c[x][y][a[i]];
    }
    else {
        _rep(i, l, blk[p].R) maintain(x, y, a[i]);
        _rep(i, blk[q].L, r) maintain(x, y, a[i]);
        _rep(i, l, blk[p].R) --c[x][y][a[i]];
        _rep(i, blk[q].L, r) --c[x][y][a[i]];
    }

    return buf[cur.pos];
}
// == query finished ==

int main() {
    freopen("input.txt", "r", stdin);
    init();

    // == input ==
    cin >> n >> m;
    _rep(i, 1, n) scanf("%d", &a[i]);
    // == input finished ==

    // == discrete ==
    discrete();
    // == discrete finished ==


    // == block ==
    block();
    // == block finished ==

    // == then init Segment ==
    initseg();
    // == init segment finished ==

    // == then solve() ==

    int x = 0;
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        l = (l + x - 1) % n + 1;
        r = (r + x - 1) % n + 1;
        if(l > r) swap(l, r);

        x = query(l, r);
        printf("%d\n", x);
    }
}