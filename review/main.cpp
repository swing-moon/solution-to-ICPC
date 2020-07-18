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
typedef long long ll;
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

const int maxn = 2e5 + 5;

// == Graph structure ==
class Edge {
public:
    int to;
    Edge() {}
    Edge(int to) : to(to) {}
};
vector<int> G[maxn];
vector<Edge> edges;

void addEdge(int x, int y) {
    edges.push_back(Edge(y));
    G[x].push_back(edges.size() - 1);
}
// == Graph finished ==

// == input 1 ==
int n, m, q;
int V[maxn], W[maxn], C[maxn];

void inp1() {
    scanf("%d%d%d", &n, &m, &q);
    _rep(i, 1, m) scanf("%d", &V[i]);
    _rep(i, 1, n) scanf("%d", &W[i]);

    _for(i, 1, n) {
        int u, v;
        scanf("%d%d", &u, &v);
        addEdge(u, v);
        addEdge(v, u);
    }

    _rep(i, 1, n) scanf("%d", &C[i]);
}
// == input 1 finished ==

// == dfs order and lca ==
const int maxt = 25;
int fst[maxn], lst[maxn], dep[maxn], f[maxn][maxt + 5], ord[maxn];
int dfn = 0;

void dfs(int x) {
    assert(dep[1] == 1);

    ord[++dfn] = x;
    fst[x] = dfn;

    // dfs main
    _for(i, 0, G[x].size()) {
        int y = edges[G[x][i]].to;
        if(dep[y]) continue;

        dep[y] = dep[x] + 1;
        f[y][0] = x;
        _rep(k, 1, maxt) f[y][k] = f[f[y][k - 1]][k - 1];

        dfs(y);
    }

    ord[++dfn] = x;
    lst[x] = dfn;
}

int LCA(int x, int y) {
    if(dep[x] > dep[y]) swap(x, y);
    _forDown(i, maxt, 0) if(dep[x] <= dep[f[y][i]]) y = f[y][i];

    if(x == y) return x;

    _forDown(i, maxt, 0) if(f[y][i] != f[x][i]) {
            x = f[x][i], y = f[y][i];
        }
    return f[x][0];
}
// == dfs finsihed ==

// == Query definition ==
class Qry {
public:
    int l, r, id, time, lca;
} qry[maxn];

class Ch {
public:
    int pos, val;
} ch[maxn];

int qn = 0, cn = 0;
// == Query finsihed ==

// == inp2, after get dfs order ord[]  ==
void inp2() {
    _rep(i, 1, q) {
        int op, x, y;
        scanf("%d%d%d", &op, &x, &y);

        if(op) {
            // ask command
            int lca = LCA(x, y);
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
// == inp2 finsihed ==

// == Mo algorithm ==
int vis[maxn], cnt[maxn];
inline void add(int x, ll& ans) {
    ans += (ll)1 * V[C[x]] * W[++cnt[C[x]]];
}
inline void del(int x, ll& ans) {
    ans -= (ll)1 * V[C[x]] * W[cnt[C[x]]--];
}

// x means the place ID number, xth viewpoint
inline void work(int x, ll& ans) {
    vis[x] ? del(x, ans) : add(x, ans);
    vis[x] ^= 1;
}

void apply(int t, ll& ans) {
    if(vis[ch[t].pos]) {
        work(ch[t].pos, ans);
        swap(ch[t].val, C[ch[t].pos]);
        work(ch[t].pos, ans);
    }
    else {
        swap(ch[t].val, C[ch[t].pos]);
    }
}
// == Mo algo finished ==

// == block ==
int SZ, T;
int belong[maxn];
void block() {
    SZ = pow(n, 2.0 / 3.0);
    T = dfn / SZ;

    _rep(i, 1, T) _rep(k, (i - 1) * SZ + 1, i * SZ) belong[k] = i;
    if(T * SZ < dfn) {
        T++;
        _rep(k, (T - 1) * SZ + 1, dfn) belong[k] = T;
    }
}

int cmp(const Qry& a, const Qry& b) {
    if(belong[a.l] ^ belong[b.l]) return belong[a.l] < belong[b.l];
    if(belong[a.r] ^ belong[b.r]) return belong[a.l] & 1 ? a.r < b.r : a.r > b.r;
    return a.time < b.time;
}
// == block finsihed ==

// == solve the problem ==
ll ANS[maxn];

void solve() {
    sort(qry + 1, qry + 1 + qn, cmp);

    int pl = 1, pr = 0, pt = 0;
    ll res = 0;
    _rep(i, 1, qn) {
        int ql = qry[i].l, qr = qry[i].r, qt = qry[i].time, lca = qry[i].lca;

        while (pl < ql) work(ord[pl++], res);
        while (pl > ql) work(ord[--pl], res);
        while (pr < qr) work(ord[++pr], res);
        while (pr > qr) work(ord[pr--], res);

        while (pt < qt) apply(++pt, res);
        while (pt > qt) apply(pt--, res);

        if(lca) work(lca, res);
        ANS[qry[i].id] = res;
        if(lca) work(lca, res);
    }
}
// == solve finished ==

void init() {
    Set(dep, 0);
    dep[1] = 1;
    dfn = 0;
    Set(f, 0);

    qn = cn = 0;

    Set(vis, 0);
    Set(cnt, 0);
}

void dbg() {
    _rep(i, 0, dfn) printf("%d ", ord[i]);
    puts("");
}

int main() {
    freopen("P4074_10.in", "r", stdin);
    //freopen("ans.out", "w", stdout);

    init();
    inp1();

    dfs(1);
    inp2();

    //dbg();
    block();
    solve();
    _rep(i, 1, qn) printf("%lld\n", ANS[i]);

    /*
    if(system("diff ans.out P4074_10.out")) {
        printf("Wrong Answer\n");
        return 0;
    }
    else {
        printf("Accepted\n");
    }
    */
}