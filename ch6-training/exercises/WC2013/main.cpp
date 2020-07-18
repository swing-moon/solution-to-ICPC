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

// == Graph structure ==
int head[maxn], nxt[maxn], ver[maxn];
int tot = 0;

void initG() {
    Set(head, 0);
    Set(nxt, 0);
    Set(ver, 0);
    tot = 0;
}
void add(int x, int y) {
    ver[++tot] = y;
    nxt[tot] = head[x];
    head[x] = tot;
}
// == Graph structure finished ==

// == get input ==
int V[maxn], W[maxn], C[maxn];
int cnt[maxn];
int n, m, q;

void init() {
    Set(cnt, 0);
}
void getinp() {
    scanf("%d%d%d", &n, &m, &q);
    _rep(i, 1, m) scanf("%d", &V[i]);
    _rep(i, 1, n) scanf("%d", &W[i]);
    _for(i, 1, n) {
        int u, v;
        scanf("%d%d", &u, &v);
        add(u, v);
        add(v, u);
    }

    _rep(i, 1, n) scanf("%d", &C[i]);
}
// == input finished ==

// == get dfs order and lca ==
int fst[maxn], lst[maxn], dep[maxn], ord[maxn];
int f[maxn][30];
const int H = 25;
int dfn = 0;

void initdfs() {
    Set(dep, 0);
    Set(f, 0);
    dep[1] = 1;
    dfn = 0;
}

void dfs(int x) {
    assert(dep[1] == 1);

    ord[++dfn] = x;
    fst[x] = dfn;

    for(int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if(dep[y]) continue;

        dep[y] = dep[x] + 1;
        f[y][0] = x;
        _rep(k, 1, H) f[y][k] = f[f[y][k - 1]][k - 1];
        dfs(y);
    }

    ord[++dfn] = x;
    lst[x] = dfn;
}

int getlca(int x, int y) {
    if(dep[x] > dep[y]) swap(x, y);
    _forDown(i, H, 0) if(dep[f[y][i]] >= dep[x]) y = f[y][i];

    if(x == y) return x;

    _forDown(i, H, 0) if(f[y][i] != f[x][i]) {
        x = f[x][i], y = f[y][i];
    }

    return f[x][0];
}
// == dfs order and lca finished ==

// == get qry and change ==
class Qry {
public:
    int l, r, id, time, lca;
};
Qry qry[maxn];

class Ch {
public:
    int val, pos;
};
Ch ch[maxn];

int qn = 0, cn = 0;
void getinp2() {
    _rep(i, 1, q) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);
        if(op) {
            int lca = getlca(x, y);
            qry[++qn].time = cn;
            qry[qn].id = qn;

            if(fst[x] > fst[y]) swap(x, y);
            if(x == lca) {
                qry[qn].l = fst[x];
                qry[qn].r = fst[y];
            }
            else {
                qry[qn].l = lst[x];
                qry[qn].r = fst[y];
                qry[qn].lca = lca;
            }
        }
        else {
            ch[++cn].pos = x;
            ch[cn].val = y;
        }
    }
}
// == qry and change finished ==

// == block ==
int belong[maxn];
int sz, t;

void block() {
    sz = sqrt(dfn);
    t = dfn / sz;

    _rep(i, 1, t) _rep(k, (i - 1) * sz + 1, i * sz) belong[k] = i;

    if(t * sz < dfn) {
        t++;
        _rep(k, (t - 1) * sz + 1, dfn) belong[k] = t;
    }
}

int cmp(const Qry& a, const Qry& b) {
    if(belong[a.l] ^ belong[b.l]) return belong[a.l] < belong[b.l];
    if(belong[a.l] ^ belong[b.r]) return belong[a.r] < belong[b.r];
    return a.time < b.time;
}
// == block finsihed ==

// == Mo algorithm ==
int visMo[maxn];
void push(int x, llong& ans) {
    ans += (llong)1 * V[C[x]] * W[++cnt[C[x]]];
}
void del(int x, llong& ans) {
    ans -= (llong)1 * V[C[x]] * W[cnt[C[x]]--];
}

void work(int x, llong& ans) {
    visMo[x] ? del(x, ans) : push(x, ans);
    visMo[x] ^= 1;
}

void apply(int t, llong& ans) {
    if(visMo[ch[t].pos]) {
        work(ch[t].pos, ans);
        swap(ch[t].val, C[ch[t].pos]);
        assert(visMo[ch[t].pos] == 0);
        work(ch[t].pos, ans);
    }
    else swap(ch[t].val, C[ch[t].pos]);
}

llong ANS[maxn];

void solve() {
    sort(qry + 1, qry + 1 + qn, cmp);
    int l = 1, r = 0, ptime = 0;
    llong ans = 0;

    _rep(i, 1, qn) {
        int ql = qry[i].l, qr = qry[i].r, qt = qry[i].time, qlca = qry[i].lca;

        while (l < ql) work(ord[l++], ans);
        while (l > ql) work(ord[--l], ans);
        while (r < qr) work(ord[++r], ans);
        while (r > qr) work(ord[r--], ans);

        while (ptime < qt) apply(++ptime, ans);
        while (ptime > qt) apply(ptime--, ans);

        if(qlca) work(qlca, ans);
        ANS[qry[i].id] = ans;
        if(qlca) work(qlca, ans);
    }
}
// == Mo algorithm finished ==

int main() {
    freopen("input.txt", "r", stdin);
    initG();
    init();

    getinp();

    initdfs();
    dfs(1);


    getinp2();
    block();
    solve();

    _rep(i, 1, qn) printf("%lld\n", ANS[i]);
}