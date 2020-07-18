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

const int maxn = 50000 + 10;
int a[maxn];
int n, m, k;

class Qry {
public:
    int l, r, id;
};
Qry qry[maxn];

// == block ==
int sz, t;
int belong[maxn];

void block() {
    sz = sqrt(n);
    t = n / sz;

    _rep(i, 1, t) {
        _rep(k, (i - 1) * sz + 1, i * sz) belong[k] = i;
    }

    if(t * sz < n) {
        t++;
        _rep(k, (t - 1) * sz + 1, n) belong[k] = t;
    }
}

bool cmp(const Qry& a, const Qry& b) {
    if(belong[a.l] ^ belong[b.l]) return belong[a.l] < belong[b.l];
    if(belong[a.l] & 1) return a.r < b.r;
    return a.r > b.r;
}
// == block finished ==

// == Mo algorithm ==
int CNT[maxn], res = 0;
int ANS[maxn];

void initMo() {
    Set(CNT, 0);
    Set(ANS, 0);
    res = 0;
}

inline void work(int x, int d, int& ans) {
    ans -= CNT[x] * CNT[x];
    CNT[x] += d;
    ans += CNT[x] * CNT[x];
}

void solve() {
    sort(qry + 1, qry + 1 + m, cmp);
    assert(res == 0);

    int l = 1, r = 0;
    _rep(i, 1, m) {
        int ql = qry[i].l, qr = qry[i].r;
        while (l < ql) work(a[l++], -1, res);
        while (l > ql) work(a[--l], 1, res);
        while (r < qr) work(a[++r], 1, res);
        while (r > qr) work(a[r--], -1, res);

        ANS[qry[i].id] = res;
    }
}
// == Mo algorithm finished ==

int main() {
    freopen("input.txt", "r", stdin);

    // == input data ==
    scanf("%d%d%d", &n, &m, &k);
    _rep(i, 1, n) scanf("%d", &a[i]);

    _rep(i, 1, m) {
        int l, r;
        scanf("%d%d", &l, &r);
        qry[i].l = l;
        qry[i].r = r;
        qry[i].id = i;
    }
    // == input finished ==

    // == block ==
    block();
    // == block finished ==
    initMo();
    solve();
    // == Mo algorithm ==
    _rep(i, 1, m) printf("%d\n", ANS[i]);

}