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
int n, m, A[maxn];

// == block ==
int belong[maxn], sz, t;

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
// == block finished ==

inline llong gcd(llong a, llong b) {
    return b ? gcd(b, a % b) : a;
}

// == query structure ==
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

// == Mo's algotithm ==
llong num[maxn];

void maintain(int x, int d, llong& ans) {
    ans -= num[x] * (num[x] - 1);
    num[x] += d;
    ans += num[x] * (num[x] - 1);
}

llong ANS[maxn][2];
void solve() {
    int l = 1, r = 0;
    llong res = 0;

    _rep(i, 1, m) {
        int ql = qry[i].l, qr = qry[i].r;

        if(ql == qr) {
            ANS[qry[i].id][0] = 0;
            ANS[qry[i].id][1] = 1;
            continue;
        }

        while (l < ql) maintain(A[l++], -1, res);
        while (l > ql) maintain(A[--l], 1, res);
        while (r < qr) maintain(A[++r], 1, res);
        while (r > qr) maintain(A[r--], -1, res);

        llong D = (llong)(qry[i].r - qry[i].l + 1) * (qry[i].r - qry[i].l);
        llong g = gcd(D, res);

        ANS[qry[i].id][0] = res;
        ANS[qry[i].id][1] = D;

        if(!g) ANS[qry[i].id][1] = 1;
        else {
            ANS[qry[i].id][0] /= g;
            ANS[qry[i].id][1] /= g;
        }
    }
}
// == Mo finished ==

void init() {
    Set(num, 0);
    Set(ANS, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    //freopen("output.txt", "w", stdout);
    init();

    // == get input ==
    scanf("%d%d", &n, &m);
    _rep(i, 1, n) scanf("%d", &A[i]);

    _rep(i, 1, m) {
        scanf("%d%d", &qry[i].l, &qry[i].r);
        qry[i].id = i;
    }
    // == input finished ==

    // == block ==
    block();
    // == block finsihed ==

    // == solve the problem ==
    sort(qry + 1, qry + 1 + m, cmp);
    solve();

    _rep(i, 1, m) printf("%lld/%lld\n", ANS[i][0], ANS[i][1]);
}