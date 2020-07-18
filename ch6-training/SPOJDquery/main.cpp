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
int n, m, t, sz;
int A[maxn];

class Qry {
public:
    int l, r, id;
};

Qry qry[maxn];

int belong[maxn];

bool cmp(const Qry& a, const Qry& b) {
    if(belong[a.l] ^ belong[b.l]) return belong[a.l] < belong[b.l];
    if(belong[a.l] & 1) return a.r < b.r;
    return a.r > b.r;
}

// == block ==
void block() {
    sz = sqrt(1.0 * n);
    t = n / sz;

    _rep(i, 1, t) _rep(k, (i - 1) * sz + 1, i * sz) {
        belong[k] = i;
    }
    if(t * sz < n) {
        t++;
        _rep(k, (t - 1) * sz + 1, n) belong[k] = t;
    }
}
// == block finished ==


// == solve the problem ==
int num[maxn];
int tans = 0;
int ANS[maxn];

void initBlk() {
    Set(num, 0);
    tans = 0;
}

inline void add(int x, int& ans) {
    if(++num[x] == 1) ans++;
}

inline void del(int x, int& ans) {
    if(--num[x] == 0) ans--;
}

void solve() {
    sort(qry + 1, qry + 1 + m, cmp);
    initBlk();
    assert(tans == 0);
    assert(num[A[1]] == 0);

    // brute force for the first query in the block
    int l = 1, r = 0;

    // then get other query by recursion
    _rep(i, 1, m) {
        while (l < qry[i].l) del(A[l++], tans);
        while (l > qry[i].l) add(A[--l], tans);
        while (r < qry[i].r) add(A[++r], tans);
        while (r > qry[i].r) del(A[r--], tans);

        ANS[qry[i].id] = tans;
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