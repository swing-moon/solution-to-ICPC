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

const int maxn = 200200;
int n, m, N;
int a[maxn], buf[maxn];

// == Graph structure ==
int head[maxn], nxt[maxn], ver[maxn];
int tot = 0;
void init() {
    Set(head, 0);
    Set(nxt, 0);
    Set(ver, 0);
    tot = 0;
}

void add(int x, int y) {
    ver[++tot] = y; nxt[tot] = head[x]; head[x] = tot;
}
// == Graph structure finished ==

// == discrete ==
void discrete() {
    sort(buf + 1, buf + 1 + n);
    N = unique(buf + 1, buf + 1 + n) - buf - 1;
    _rep(i, 1, n) a[i] = lower_bound(buf + 1, buf + 1 + N, a[i]) - buf;
}
// == dicrete finsihed ==


// == dfs order and lca ==
int f[maxn][30], dep[maxn];
int h = 0;

int fst[maxn], lst[maxn];
int ord[maxn], dfsn;
void initdfs() {
    Set(dep, 0);
    Set(fst, 0);
    Set(lst, 0);
    Set(ord, 0);
    dfsn = 0;

    dep[1] = 1;
    h = 20 + 5;
}

void dfs(int x) {
    assert(dep[1] == 1);
    ord[++dfsn] = x;
    fst[x] = dfsn;
    for(int i = head[x]; i; i = nxt[i]) {
        int y = ver[i];
        if(dep[y]) continue;

        dep[y] = dep[x] + 1;
        f[y][0] = x;
        _rep(k, 1, h) f[y][k] = f[f[y][k - 1]][k - 1];
        dfs(y);
    }
    ord[++dfsn] = x;
    lst[x] = dfsn;
}

int LCA(int x, int y) {
    if(dep[x] > dep[y]) swap(x, y);
    _forDown(i, h, 0) if(dep[f[y][i]] >= dep[x]) y = f[y][i];

    if(x == y) return x;

    _forDown(i, h, 0) if(f[y][i] != f[x][i]) {
            x = f[x][i], y = f[y][i];
        }
    return f[x][0];
}
// == dfs order and lca finshed ==

// == query and block ==
class Qry {
public:
    int l, r, lca, id;
};
Qry qry[maxn];

int belong[maxn];
int sz, t;

bool cmp(const Qry& a, const Qry& b) {
    if(belong[a.l] ^ belong[b.l]) return belong[a.l] < belong[b.l];
    if(belong[a.l] & 1) return a.r < b.r;
    return a.r > b.r;
}

// [1, dfsn]
void block() {
    sz = sqrt(dfsn);
    t = dfsn / sz;
    _rep(i, 1, t) _rep(k, (i - 1) * sz + 1, i * sz) belong[k] = i;
    if(t * sz < n) {
        t++;
        _rep(k, (t - 1) * sz + 1, n) belong[k] = t;
    }
}

// == query and block finsihed ==

// == Mo's algorithm ==
int CNT[maxn];
int visMo[maxn];

void initMo() {
    Set(CNT, 0);
    Set(visMo, 0);
}

inline void work(int pos, int& ans) {
    if(visMo[pos] == 0) if(++CNT[a[pos]] == 1) ans++;
    if(visMo[pos]) if(--CNT[a[pos]] == 0) ans--;
    visMo[pos] ^= 1;
}

int ANS[maxn];
int l = 1, r = 0, res = 0;
void solve() {
    sort(qry + 1, qry + 1 + m, cmp);

    _rep(i, 1, m) {
        int ql = qry[i].l, qr = qry[i].r, qlca = qry[i].lca;
        // printf("%d %d\n", ql, qr);
        while (l < ql) work(ord[l++], res);
        while (l > ql) work(ord[--l], res);
        while (r < qr) work(ord[++r], res);
        while (r > qr) work(ord[r--], res);

        if(qlca) work(qlca, res);
        ANS[qry[i].id] = res;
        if(qlca) work(qlca, res);
    }
}
// == Mo;s algo finished ==

int main() {
    freopen("input.txt", "r", stdin);
    init();

    // == input data ==
    scanf("%d%d", &n, &m);
    _rep(i, 1, n) {
        scanf("%d", &a[i]);
        buf[i] = a[i];
    }
    _for(i, 1, n) {
        int x, y;
        scanf("%d%d", &x, &y);
        add(x, y);
        add(y, x);
    }
    // == input finished ==

    // == discrete ==
    discrete();
    // == discrete finished ==


    // == get dfs order and lca ==
    initdfs();
    dfs(1);
    // == dfs order finished

    // == block query ==

    // == block query finished ==
    // == check the arr ord[]
    block();

    _rep(i, 1, m) {
        int l, r;
        scanf("%d%d", &l, &r);
        int lca = LCA(l, r);
        //debug(lca);

        if(fst[l] > fst[r]) swap(l, r);
        qry[i].id = i;

        if(l == lca) {
            qry[i].l = fst[l];
            qry[i].r = fst[r];
        }
        else {
            qry[i].l = lst[l];
            qry[i].r = fst[r];
            qry[i].lca = lca;
        }
    }
    // == Mo's algorithm ==

    initMo();
    solve();

    _rep(i, 1, m) printf("%d\n", ANS[i]);
}