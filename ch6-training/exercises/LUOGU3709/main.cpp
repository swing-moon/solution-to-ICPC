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
const int maxt = 40;
int n, m, tot = 0;

// == input and discrete ==
int buf[maxn], A[maxn];
void discrete() {
    Cpy(buf, A);
    sort(buf + 1, buf + 1 + n);
    tot = unique(buf + 1, buf + 1 + n) - buf - 1;

    _rep(i, 1, n) {
        A[i] = lower_bound(buf + 1, buf + 1 + tot, A[i]) - buf;
    }

    // use buf[A[i]] to output
}
// == input and discrete finshed ==


// == block ==
int t, sz;
int belong[maxn], bl[maxn], br[maxn];
void block() {
    t = sqrt(n);
    sz = t ? n / t : n;

    _rep(i, 1, t) {
        bl[i] = (i - 1) * sz + 1;
        br[i] = i * sz;

        _rep(k, bl[i], br[i]) belong[k] = i;
    }

    if(t * sz < n) {
        t++;
        bl[t] = (t - 1) * sz + 1;
        br[t] = n;

        _rep(k, (t - 1) * sz + 1, n) belong[k] = t;
    }
}
// == block finished ==

// == query data structure ==
class Qry {
public:
    int l, r;
    int id;
};
Qry qry[maxn];

int cmp(const Qry& a, const Qry& b) {
    if(belong[a.l] ^ belong[b.l]) return belong[a.l] < belong[b.l];
    if(belong[a.l] & 1) return a.r < b.r;
    return a.r > b.r;
}
// == query finished ==

// == Mo algorithm ==
int cur = 0;
int num[maxn], kind[maxn];
int ANS[maxn];

void init() {
    Set(num, 0);
    Set(kind, 0);
    Set(ANS, 0);
}

inline void add(int x, int& ans) {
    if(num[x] == ans) ans++;
    kind[num[x]]--;
    kind[++num[x]]++;
}

inline void del(int x, int& ans) {
    if(num[x] == ans && kind[num[x]] == 1) ans--;
    kind[num[x]]--;
    kind[--num[x]]++;
}

void solve() {
    sort(qry + 1, qry + 1 + m, cmp);
    int l = 1, r = 0, ans = 0;

    _rep(i, 1, m) {
        int ql = qry[i].l, qr = qry[i].r;
        while (l < ql) del(A[l++], ans);
        while (l > ql) add(A[--l], ans);
        while (r < qr) add(A[++r], ans);
        while (r > qr) del(A[r--], ans);

        ANS[qry[i].id] = ans;
    }
}

// == Mo algo finished ==

int main() {
    freopen("input.txt", "r", stdin);
    init();

    // == input ==
    scanf("%d%d", &n, &m);
    _rep(i, 1, n) scanf("%d", &A[i]);

    _rep(i, 1, m) {
        scanf("%d%d", &qry[i].l, &qry[i].r);
        qry[i].id = i;
    }
    // == input finished ==

    // == discrete ==
    discrete();
    // == discrete finished ==

    // == init block ==
    block();
    // == block finished ==

    solve();

    _rep(i, 1, m) printf("%d\n", -ANS[i]);

}