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

const int maxn = 100000 + 10;
const int maxb = 5000;
int n, m, N;

int a[maxn], typ[maxn], inp[maxn];

class Qry {
public:
    int l, r, id;
};
Qry qry[maxn];

// == discrete ==
void discrete() {
    sort(inp + 1, inp + 1 + n);
    N = unique(inp + 1, inp + 1 + n) - inp - 1;
    _rep(i, 1, n) typ[i] = lower_bound(inp + 1, inp + 1 + N, a[i]) - inp;
}
// == discrete finished ==

// == block ==
int bl[maxn], br[maxn];
int belong[maxn];
int sz, t;

void block() {
    sz = sqrt(n);
    t = n / sz;
    _rep(i, 1, t) {
        bl[i] = (i - 1) * sz + 1;
        br[i] = i * sz;

        _rep(k, bl[i], br[i]) belong[k] = i;
    }

    if(t * sz < n) {
        t++;
        bl[t] = (t - 1) * sz + 1;
        br[t] = n;

        _rep(k, bl[t], br[t]) belong[k] = t;
    }
}

bool cmp(const Qry& a, const Qry& b) {
    if(belong[a.l] ^ belong[b.l]) return belong[a.l] < belong[b.l];
    return a.r < b.r;
}
// == block finsihed ==
int cnt[maxn];
llong ANS[maxn];

void initMo() {
    Set(ANS, 0);
    Set(cnt, 0);
}

llong force(int ql, int qr) {
    llong res = 0;
    int tcnt[maxn];

    _rep(i, ql, qr) tcnt[typ[i]] = 0;
    _rep(i, ql, qr) {
        tcnt[typ[i]]++;
        res = max(res, (llong)1 * tcnt[typ[i]] * a[i]);
        //debug(res);
    }
    return res;
}

void solve() {
    sort(qry + 1, qry + 1 + m, cmp);

    int i = 1;
    _rep(k, 1, t) {
        int l = br[k] + 1, r = br[k];
        Set(cnt, 0);
        llong res = 0;

        // brute force for seg in block
        for( ; belong[qry[i].l] == k; i++) {
            int ql = qry[i].l, qr = qry[i].r;

            if(belong[ql] == belong[qr]) {
                llong ans = force(ql, qr);
                ANS[qry[i].id] = ans;
                continue;
            }

            llong fix = 0;
            while (r < qr) {
                r++;
                ++cnt[typ[r]];
                res = max(res, (llong)1 * cnt[typ[r]] * a[r]);
                //debug(res);
            }
            fix = res;

            while (l > ql) {
                l--;
                ++cnt[typ[l]];
                res = max(res, (llong)1 * cnt[typ[l]] * a[l]);
                //debug(res);
            }

            ANS[qry[i].id] = res;
            //debug(res);

            while (l < br[k] + 1) {
                --cnt[typ[l]];
                ++l;
            }

            res = fix;
        }
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    // == input ==
    scanf("%d%d", &n, &m);
    _rep(i, 1, n) {
        scanf("%d", &a[i]);
        inp[i] = a[i];
    }
    _rep(i, 1, m) {
        int _l, _r;
        scanf("%d%d", &_l, &_r);
        qry[i].l = _l;
        qry[i].r = _r;
        qry[i].id = i;
    }
    // == input finished ==

    // == discrete ==
    discrete();
    // == discrete finished ==

    // == block ==
    block();
    // == block finished ==

    // == Mo Algorithm ==
    initMo();
    solve();
    // == Mo Algo finished ==

    _rep(i, 1, m) printf("%lld\n", ANS[i]);
}