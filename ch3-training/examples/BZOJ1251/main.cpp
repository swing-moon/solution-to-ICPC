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

const int inf = 0x3f3f3f3f;
const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;

// == tree structure ==
const int NIL = 0;

class Node {
public:
    int pa;
    int cld[2];

    int big, val, tag;
    int sz;
    bool rev;

    void create(int _val, int _pa) {
        pa = _pa;
        big = val = _val;
        sz = 1;
        cld[0] = cld[1] = 0;
        tag = rev = 0;
    }
} T[maxn];

int root;

inline int sgn(int u) {
    return T[T[u].pa].cld[1] == u;
}

void pushup(int u) {
    T[u].big = T[u].val;
    T[u].sz = 1;

    if(T[u].cld[0]) {
        T[u].big = max(T[u].big, T[T[u].cld[0]].big);
        T[u].sz += T[T[u].cld[0]].sz;
    }

    if(T[u].cld[1]) {
        T[u].big = max(T[u].big, T[T[u].cld[1]].big);
        T[u].sz += T[T[u].cld[1]].sz;
    }
}

void pushdown(int u) {
    if(u == NIL) return;
    if(T[u].tag) {
        _for(k, 0, 2) if(T[u].cld[k]) {
            T[T[u].cld[k]].val += T[u].tag;
            T[T[u].cld[k]].tag += T[u].tag;
            T[T[u].cld[k]].big += T[u].tag;
        }

        T[u].tag = 0;
    }

    if(T[u].rev) {
        _for(k, 0, 2) {
            if(T[u].cld[k]) T[T[u].cld[k]].rev ^= 1;
        }

        swap(T[u].cld[0], T[u].cld[1]);
        T[u].rev = 0;
    }
}

int build(int l, int r) {
    if(l > r) return NIL;
    if(l == r) return l;

    int mid = (l + r) >> 1;
    int lson, rson;

    lson = T[mid].cld[0] = build(l, mid - 1);
    rson = T[mid].cld[1] = build(mid + 1, r);
    T[lson].pa = T[rson].pa = mid;

    pushup(mid);
    return mid;
}

void buildTree(int n) {
    T[1].create(-inf, NIL), T[n + 2].create(-inf, NIL);
    _rep(i, 2, n + 1) T[i].create(0, NIL);

    root = build(1, n + 2);
    T[root].pa = NIL;

    T[NIL].cld[1] = root;
    T[NIL].pa = 0;
    T[NIL].sz = 0;

    //assert(T[1].pa != NIL);
}
// == tree structure finsihed ==

// == void rotate and splay ==
inline void setc(int q, int d, int p) {
    if(p) T[p].pa = q;
    if(q) T[q].cld[d] = p;
    if(q == NIL) root = p;
}

inline void rot(int x, int d) {
    int y = T[x].pa, z = T[y].pa;

    setc(z, sgn(y), x);
    setc(y, d, T[x].cld[d^1]);
    setc(x, d^1, y);

    pushup(y);
}

inline void rot(int x) {
    return rot(x, sgn(x));
}

int splay(int p, const int to) {
    if(p == to) return p;

    while (T[p].pa != to) {
        int y = T[p].pa, z = T[y].pa;

        if(T[p].pa == NIL) {
            root = p;
            break;
        }
        if(T[T[p].pa].pa == to) {
            rot(p);
            break;
        }
        else {
            int a = sgn(p), b = sgn(T[p].pa);
            rot((a^b ? p : T[p].pa), a);
            rot(p, b);
        }
    }
    pushup(p);
    return p;
}
// == rotate and splay finished ==

// == select kth, return (k+1)th ==
int select(const int rt, int k) {
    int u = rt;
    pushdown(u);

    while (u && T[T[u].cld[0]].sz != k) {
        if(k < T[T[u].cld[0]].sz) u = T[u].cld[0];
        else {
            k -= T[T[u].cld[0]].sz + 1;
            u = T[u].cld[1];
        }
        pushdown(u);
    }
    return u;
}
// == select finsihed ==

// == void change ==
void change(int l, int r, int val) {
    int x = select(root, l - 1);
    int y = select(root, r + 1);

    splay(x, NIL);
    splay(y, x);

    T[T[y].cld[0]].val += val;
    T[T[y].cld[0]].tag += val;
    T[T[y].cld[0]].big += val;
}
// == change finsihed ==

void turn(int l, int r) {
    int x = select(root, l - 1);
    int y = select(root, r + 1);

    splay(x, NIL);
    splay(y, x);
    T[T[y].cld[0]].rev ^= 1;
}

int query(int l, int r) {
    int x = select(root, l - 1);
    int y = select(root, r + 1);
    splay(x, NIL);
    splay(y, x);
    return T[T[y].cld[0]].big;
}

// == void debug ==
void dbg(const int rt) {
    int u = rt;
    if(T[u].cld[0]) dbg(T[u].cld[0]);

    puts("");
    debug(T[u].sz);
    debug(T[u].val);
    debug(T[u].cld[0]);
    debug(T[u].cld[1]);

    if(T[u].cld[1]) dbg(T[u].cld[1]);
}
// == dbg

int main() {
    freopen("input.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);

    buildTree(n);
    _for(i, 0, m) {
        int a, b, c, d;
        scanf("%d", &a);

        //dbg(NIL);
        //puts("\n\n\n");
        if(a == 1) {
            scanf("%d%d%d", &b, &c, &d);
            change(b, c, d);
        }
        else if(a == 2) {
            scanf("%d%d", &b, &c);
            turn(b, c);
        }
        else {
            scanf("%d%d", &b, &c);
            printf("%d\n", query(b, c));
        }
    }
}