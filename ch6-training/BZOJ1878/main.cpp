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

const int maxn = 200000 + 10;
int a[maxn], inp[maxn];
int n, m, N;

class Qry {
public:
    int l, r, id;
};
Qry qry[maxn];

// == discrete ==
void discrete() {
    sort(inp + 1, inp + 1 + n);
    N = unique(inp + 1, inp + 1 + n) - inp - 1;
    _rep(i, 1, n) a[i] = lower_bound(inp + 1, inp + 1 + N, a[i]) - inp;
}
// == discrete finished ==

// == block ==
int belong[maxn];
int sz, t;
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
// == block finshed ==

// == Mo algo ==
int CNT[maxn], ANS[maxn];
int res = 0;

void initMo() {
    Set(CNT, 0);
    Set(ANS, 0);
    res = 0;
}

inline void add(int x, int& ans) {
    if(++CNT[x] == 1) ans++;
}

inline void del(int x, int& ans) {
    if(--CNT[x] == 0) ans--;
}

void solve() {
    sort(qry + 1, qry + 1 + m, cmp);

    int l = 1, r = 0;
    assert(res == 0);
    _rep(i, 1, m) {
        int ql = qry[i].l, qr = qry[i].r;
        while (l < ql) del(a[l++], res);
        while (l > ql) add(a[--l], res);
        while (r < qr) add(a[++r], res);
        while (r > qr) del(a[r--], res);

        ANS[qry[i].id] = res;
    }
}
// == Mo algo finshed ==

int main() {
    freopen("input.txt", "r", stdin);

    // == input ==
    scanf("%d", &n);
    _rep(i, 1, n) {
        scanf("%d", &a[i]);
        inp[i] = a[i];
    }

    scanf("%d", &m);
    _rep(i, 1, m) {
        int l, r;
        scanf("%d%d", &l, &r);
        qry[i].l = l;
        qry[i].r = r;
        qry[i].id = i;
    }
    // == input finished ==

    // == discrete ==
    discrete();
    // == discrete finished ==

    // == block ==
    block();
    // == block finished ==

    // == Mo algorithm ==
    initMo();
    solve();
    // == Mo finished ==

    _rep(i, 1, m) printf("%d\n", ANS[i]);
}