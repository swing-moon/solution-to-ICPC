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

const int maxn = 2e6 + 10;
int n, m, t;
int A[maxn];

class Blk {
public:
    int L, R;
};

Blk blk[maxn];

class Qry {
public:
    int l, r, id;
};

Qry qry[maxn];

bool cmp1(const Qry& a, const Qry& b) {
    return a.l < b.l || (a.l == b.l && a.r < b.r);
}

bool cmp2(const Qry& a, const Qry& b) {
    return a.r < b.r;
}

// == block ==
void block() {
    sort(qry + 1, qry + 1 + m, cmp1);
    t = sqrt(m);

    _rep(i, 1, t) {
        blk[i].L = (i - 1) * t + 1;
        blk[i].R = i * t;
    }

    if(blk[t].R < m) {
        t++;
        blk[t].L = blk[t - 1].R + 1;
        blk[t].R = m;
    }
}
// == block finished ==


// == solve the problem ==
int num[maxn];
int tans;
int ANS[maxn];

void initBlk(int i) {
    Set(num, 0);
    tans = 0;

    sort(qry + blk[i].L, qry + blk[i].R + 1, cmp2);
}

inline void add(int p, int& ans) {
    if(++num[A[p]] == 1) ans++;
}

inline void del(int p, int& ans) {
    if(--num[A[p]] == 0) ans--;
}


void solve() {
    _rep(i, 1, t) {
        initBlk(i);

        // brute force for the first query
        int qid = blk[i].L;
        int l = qry[qid].l, r = qry[qid].r;
        _rep(k, l, r) add(k, tans);
        ANS[qry[qid].id] = tans;

        // then get other query by recursion
        _rep(k, blk[i].L + 1, blk[i].R) {
            // now qid = k
            while (r < qry[k].r) add(++r, tans);
            while (r > qry[k].r) del(r--, tans);
            while (l < qry[k].l) del(l++, tans);
            while (l > qry[k].l) add(--l, tans);

            if(qry[k].l == qry[k].r) {
                ANS[qry[k].id] = 1;
            }
            else {
                ANS[qry[k].id] = tans;
            }
        }
    }
}

// == solved finished ==

int main() {
    freopen("input.txt", "r", stdin);

    // == input ==
    scanf("%d", &n);
    _rep(i, 1, n) scanf("%d", &A[i]);
    scanf("%d", &m);
    _rep(i, 1, m) {
        scanf("%d%d", &qry[i].l, &qry[i].r);
        qry[i].id = i;
    }
    // == input finished ==

    // == then block() ==
    block();
    // == block finished ==

    // == then solve the problem;
    solve();
    // == solved

    _rep(i, 1, m) {
        printf("%d\n", ANS[i]);
    }
}