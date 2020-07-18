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

const int maxn = 1e6 + 10;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;

// == tree structure ==
const int NIL = 0;
class Node {
public:
    int pa;
    int cld[2];
    int val, sz;

    bool rev;
    void create(int _val, int _pa) {
        pa = _pa;
        val = _val;
        sz = 1;
        cld[0] = cld[1] = 0;
        rev = 0;
    }
} T[maxn];
int root;

inline int sgn(int u) {
    return T[T[u].pa].cld[1] == u;
}

void pushup(int u) {
    T[u].sz = 1;
    if(T[u].cld[0]) {
        T[u].sz += T[T[u].cld[0]].sz;
    }
    if(T[u].cld[1]) {
        T[u].sz += T[T[u].cld[1]].sz;
    }
}

void pushdown(int u) {
    if(u == NIL) return;
    if(T[u].rev) {
        _for(k, 0, 2) if(T[u].cld[k]) {
            T[T[u].cld[k]].rev ^= 1;
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
    _rep(i, 2, n + 1) T[i].create(i - 1, NIL);

    root = build(1, n + 2);
    T[root].pa = NIL;

    T[NIL].cld[1] = root;
    T[NIL].pa = 0;
    T[NIL].sz = 0;
}
// == tree structure finished ==

// == rotate and splay ==
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
    rot(x, sgn(x));
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
// == rotate finished ==

// == select kth, return (k+1)th ==
int select(const int rt, int k) {
    int u = rt;
    while (u) {
        if(T[T[u].cld[0]].sz == k - 1) return u;
        if(T[T[u].cld[0]].sz >= k) u = T[u].cld[0];
        else {
            k -= T[T[u].cld[0]].sz + 1;
            u = T[u].cld[1];
        }
        pushdown(u);
    }
    return u;
}
// == select finished ==

// == void turn ==
void turn(int l, int r) {
    int x = select(root, l - 1);
    int y = select(root, r + 1);

    splay(x, NIL);
    splay(y, x);
    T[T[y].cld[0]].rev ^= 1;
}

void dfs(const int root) {
    int u = root;
    pushdown(u);

    if(T[u].cld[0]) dfs(T[u].cld[0]);
    if(T[u].val != -inf) printf("%d ", T[u].val);
    if(T[u].cld[1]) dfs(T[u].cld[1]);
}

// == turn finished ==

int main() {
    freopen("input.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);

    buildTree(n);
    while (m--) {
        int l, r;
        scanf("%d%d", &l, &r);
        l++, r++;
        turn(l, r);
    }
    dfs(root);
}