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

const int maxn = 1000000 + 5;
int n, m, t, sz;
int CNT[maxn];
int clr[maxn];
int cntq = 0, cntc = 0;
int ANS[maxn];

void init() {
    cntq = cntc = 0;
}

class Query {
public:
    int l, r, id, time;
};

Query qry[maxn];

inline void add(int x, int& ans) {
    if(++CNT[x] == 1) ans++;
}

inline void del(int x, int& ans) {
    if(--CNT[x] == 0) ans--;
}


// == init block ==
int tans = 0;
void initBlk() {
    tans = 0;
}
// == init block finished ==

class Modify {
public:
    int pos, curC;
    void apply(int curL, int curR) {
        if(curL <= pos && pos <= curR) {
            int oldC = clr[pos];
            del(oldC, tans);
            add(curC, tans);
        }
        swap(curC, clr[pos]);
    }
};
Modify mdfy[maxn];

// === block() by n ===
int belong[maxn];
void block() {
    Set(belong, 0);
    sz = pow(n, 2.0 / 3.0);
    t = n / sz;

    _rep(i, 1, t) {
        _rep(k, (i - 1) * sz + 1, i * sz) belong[k] = i;
    }
    if(t * sz < n) {
        t++;
        _rep(k, (t - 1) * sz + 1, n) belong[k] = t;
    }
    // debug(t);
}

// == solve() ==
bool cmp(const Query& a, const Query& b) {
    if(belong[a.l] ^ belong[b.l]) return belong[a.l] < belong[b.l];
    if(belong[a.r] ^ belong[b.r]) return belong[a.r] < belong[b.r];
    return a.time < b.time;
}

void solve() {
    sort(qry + 1, qry + 1 + cntq, cmp);
    initBlk();
    assert(tans == 0);

    // get started ptime and [l, r]
    int ptime = 0, l = 0, r = 0;

    // then expand to other query by recursion
    _rep(i, 1, cntq) {
        int ql = qry[i].l, qr = qry[i].r, qt = qry[i].time;
        while (l < ql) del(clr[l++], tans);
        while (l > ql) add(clr[--l], tans);
        while (r < qr) add(clr[++r], tans);
        while (r > qr) del(clr[r--], tans);

        while (ptime < qt) mdfy[++ptime].apply(l, r);
        while (ptime > qt) mdfy[ptime--].apply(l, r);

        ANS[qry[i].id] = tans;
        //debug(clr[1]);
    }

}

// == solve fnished ==

// === block() finished ===

int main() {
    freopen("input.txt", "r", stdin);
    init();

    // == input ==
    scanf("%d%d", &n, &m);
    _rep(i, 1, n) {
        scanf("%d", &clr[i]);
    }

    assert(cntq == 0 && cntc == 0);
    _rep(i, 1, m) {
        char op[2];
        scanf("%s", op);
        if(op[0] == 'Q') {
            Query& curq = qry[++cntq];
            scanf("%d%d", &curq.l, &curq.r);
            curq.id = cntq;
            curq.time = cntc;

            //debug(curq.time);
        }
        else {
            Modify& md = mdfy[++cntc];
            scanf("%d%d", &md.pos, &md.curC);
            // mdfy[] as a tag, we not really change here
        }
    }
    // == input finished ==

    // == block ==
    block();
    // == block finished ==

    solve();
    _rep(i, 1, cntq) printf("%d\n", ANS[i]);
}