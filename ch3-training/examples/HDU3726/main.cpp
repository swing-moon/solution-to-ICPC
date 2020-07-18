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

const int maxn = 20000 + 5;
const int maxm = 60000 + 5;
const int inf = 0x3f3f3f3f;
int n, m;
int weight[maxm], rmved[maxm];

// === treap tree ===

class Treap {
public:
    Treap* l;
    Treap* r;

    int val, dat;
    int sz;

    Treap(int val) : val(val) {
        l = r = NULL;
        dat = rand();
        sz = 1;
    }

    void update() {
        sz = 1;
        if(l != NULL) sz += l->sz;
        if(r != NULL) sz += r ->sz;
    }
};

typedef Treap* T;
T a[maxn];

void zig(T& p) {
    T q = p->l;
    p->l = q->r; q->r = p; p = q;

    p->r->update();
    p->update();
}

void zag(T& p) {
    T q = p->r;
    p->r = q->l; q->l = p; p = q;

    p->l->update();
    p->update();
}

void insert(T& p, int val) {
    if(p == NULL) {
        p = new Treap(val);
        return;
    }

    if(val < p->val) {
        insert(p->l, val);
        if(p->dat < p->l->dat) zig(p);
    }
    else {
        insert(p->r, val);
        if(p->dat < p->r->dat) zag(p);
    }
    p->update();
}


void remove(T& p, int val) {
    if(val == p->val) {
        T u = p;
        if(p->l && p->r) {
            if(p->l->dat > p->r->dat) {
                zig(p);
                remove(p->r, val);
            }
            else {
                zag(p);
                remove(p->l, val);
            }
        }
        else {
            if(p->l == NULL) p = p->r;
            else p = p->l;
            delete u;
        }
    }
    else {
        val < p->val ? remove(p->l, val) : remove(p->r, val);
    }
    if(p != NULL) p->update();
}


// pre is the max of min{}
int getPre(const T& root, int val) {
    int ans = -inf;
    T p = root;

    while (p) {
        if(val == p->val) {
            if(p->l != NULL) {
                p = p->l;
                while (p->r != NULL) p = p->r;
                ans = p->val;
            }
            break;
        }
        if(p->val < val && p->val > ans) ans = p->val;
        p = val < p->val ? p->l : p->r;
    }
    return ans;
}

// next is the min of max{}

int getNxt(const T& root, int val) {
    int ans = inf;
    T p = root;

    while (p) {
        if(val == p->val) {
            if(p->r != NULL) {
                p = p->r;
                while (p->l != NULL) p = p->l;
                ans = p->val;
            }
            break;
        }
        if(p->val > val && p->val < ans) ans = p->val;
        p = val < p->val ? p->l : p->r;
    }
    return ans;
}

int rankByVal(T p, int val) {
    if(p == NULL) return 0;
    if(val == p->val) return p->l->sz + 1;
    if(val < p->val) return rankByVal(p->l, val);
    return p->l->sz + 1 + rankByVal(p->r, val);
}

int valByRank(T p, int rank) {
    if(p == NULL || rank <= 0 || rank > p->sz) return 0;
    int s = p->r == NULL ? 0 : p->r->sz;

    if(rank == s + 1) return p->val;
    else if(rank <= s) return valByRank(p->r, rank);
    else return valByRank(p->l, rank - 1 - s);
}

// === treap tree finished ===


// === algorithm about forest
void mergeto(T& src, T& dest) {
    if(src->l != NULL) mergeto(src->l, dest);
    if(src->r != NULL) mergeto(src->r, dest);
    insert(dest, src->val);

    delete src;
    src = NULL;
}

void rmvTree(T& p) {
    if(p->l != NULL) rmvTree(p->l);
    if(p->r != NULL) rmvTree(p->r);
    delete p;
    p = NULL;
}

// === forest algorithm finished


class Edge {
public:
    int from, to;
};
Edge edges[maxm];


// === Union Find ===
int pa[maxn];
int findset(int x) {
    return pa[x] != x ? pa[x] = findset(pa[x]) : x;
}

void initpa(int n) {
    _rep(i, 1, n) pa[i] = i;
}

// === Union Find finished ===


// == main algorithm ==
void addEdge(int x) {
    int u = findset(edges[x].from), v = findset(edges[x].to);

    if(u != v) {
        if(a[u]->sz < a[v]->sz) {
            pa[u] = v;
            mergeto(a[u], a[v]);
        }
        else {
            pa[v] = u;
            mergeto(a[v], a[u]);
        }
    }
}

void changeWeight(int x, int v) {
    int u = findset(x);
    remove(a[u], weight[x]);
    insert(a[u], v);
    weight[x] = v;
}


llong ans = 0;
int qcnt = 0;

void query(int x, int k) {
    qcnt++;
    //debug(a[findset(x)]->val);
    //debug(valByRank(a[findset(x)], k));
    //cout << endl;
    ans += valByRank(a[findset(x)], k);
}

// == main algorithm finished ==

// === get input ===
class CMD {
public:
    char type;
    int x, p;
};

vector<CMD> cmds;

void init() {
    Set(weight, 0);
    Set(rmved, 0);
    cmds.clear();

    ans = qcnt = 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while (scanf("%d%d", &n, &m) == 2 && n) {
        init();
        _rep(i, 1, n) scanf("%d", &weight[i]);
        _rep(i, 1, m) scanf("%d%d", &edges[i].from, &edges[i].to);

        // then read cmds
        for(;;) {
            char type;
            int x = 0, p = 0, v = 0;
            cin >> type;

            if(type == 'E') break;
            scanf("%d", &x);
            if(type == 'D') rmved[x] = 1;
            if(type == 'Q') scanf("%d", &p);
            if(type == 'C') {
                scanf("%d", &v);
                p = weight[x];
                weight[x] = v;
            }

            cmds.push_back((CMD) { type, x, p });
        }

        // read finished

        //initpa(n);

        // then build the last Graph

        _rep(i, 1, n) {
            pa[i] = i;
            if(a[i] != NULL) rmvTree(a[i]);
            a[i] = new Treap(weight[i]);
        }

        _rep(i, 1, m) if(!rmved[i]) addEdge(i);

        _forDown(i, cmds.size() - 1, 0) {
            if(cmds[i].type == 'D') addEdge(cmds[i].x);
            if(cmds[i].type == 'Q') query(cmds[i].x, cmds[i].p);
            if(cmds[i].type == 'C') changeWeight(cmds[i].x, cmds[i].p);
        }

        if(qcnt) printf("Case %d: %.6lf\n", ++kase, ans / (double)qcnt);
        else printf("Case %d: 0\n", ++kase);

    }
}