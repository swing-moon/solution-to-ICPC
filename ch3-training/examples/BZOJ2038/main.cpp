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
int n, m, t;
int color[maxn];
llong Ans[maxn][2];

class Q {
public:
    int l, r, id;
};

Q qry[maxn];

class Blk {
public:
    int L, R;
};

Blk blk[maxn];

bool cmp1(const Q& lhs, const Q& rhs) {
    return lhs.l < rhs.l || (lhs.l == rhs.l && lhs.r < rhs.r);
}

bool cmp2(const Q& lhs, const Q& rhs) {
    return lhs.r < rhs.r;
}

void block() {
    sort(qry + 1, qry + 1 + m, cmp1);
    t = sqrt(m);

    _rep(i, 1, t) {
        blk[i].L = (i - 1) * t + 1;
        blk[i].R = i * t;
    }
    if(blk[t].R < n) {
        t++;
        blk[t].L = blk[t - 1].R + 1;
        blk[t].R = n;
    }
}


// == then solve the problem ==

inline llong gcd(llong a, llong b) {
    return b ? gcd(b, a % b) : a;
}

int num[maxn];
llong tans = 0;
// tans used for temp ans in the block

void initBlk(int i) {
    tans = 0;
    Set(num, 0);

    sort(qry + blk[i].L, qry + blk[i].R + 1, cmp2);
}

void maintain(int x, int d, llong& tans) {
    tans -= num[x] * (num[x] - 1);
    num[x] += d;
    tans += num[x] * (num[x] - 1);
}

void solve() {
    _rep(i, 1, t) {
        initBlk(i);

        // brute force for the first elem
        int l = qry[blk[i].L].l, r = qry[blk[i].L].r;
        _rep(k, l, r) maintain(color[k], 1, tans);
        int qid = blk[i].L;
        Ans[qry[qid].id][0] = tans;
        Ans[qry[qid].id][1] = (llong)(r - l + 1) * (r - l);
        int g = gcd(Ans[qry[qid].id][0], Ans[qry[qid].id][1]);
        if(g == 0) Ans[qry[qid].id][1] = 1;
        else {
            Ans[qry[qid].id][0] /= g;
            Ans[qry[qid].id][1] /= g;
        }

        // then get [blk[i].L + 1, blk[i].R] by recursion
        _rep(k, blk[i].L + 1, blk[i].R) {
            // now qid = k;
            while (r < qry[k].r) maintain(color[++r], 1, tans);
            while (r > qry[k].r) maintain(color[r--], -1, tans);
            while (l < qry[k].l) maintain(color[l++], -1, tans);
            while (l > qry[k].l) maintain(color[--l], 1, tans);

            if(qry[k].l == qry[k].r) {
                Ans[qry[k].id][0] = 0;
                Ans[qry[k].id][1] = 1;
            }
            else {
                Ans[qry[k].id][0] = tans;
                Ans[qry[k].id][1] = (llong)(qry[k].r - qry[k].l + 1) * (qry[k].r - qry[k].l);

                int g = gcd(Ans[qry[k].id][0], Ans[qry[k].id][1]);
                if(!g) Ans[qry[k].id][1] = 1;
                else {
                    Ans[qry[k].id][0] /= g;
                    Ans[qry[k].id][1] /= g;
                }
            }
        }
    }
}

// === solve finished ==

int main() {
    freopen("input.txt", "r", stdin);

    Set(Ans, 0);
    cin >> n >> m;
    _rep(i, 1, n) scanf("%d", &color[i]);
    _rep(i, 1, m) {
        scanf("%d%d", &qry[i].l, &qry[i].r);
        qry[i].id = i;
    }

    // == input finished==

    // === then split query into block ==
    block();
    // === blocked ===


    // == then query in each blocked sorted by cmp2
    solve();
    // === sorted finished

    _rep(i, 1, m) {
        printf("%lld/%lld\n", Ans[i][0], Ans[i][1]);
    }
}