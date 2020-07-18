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
const int mod = 1000000;
const int inf = 0x3f3f3f3f;
const int NIL = 0;
int n;

// == define tree ==
class Node {
public:
    int pa;
    int cld[2];
    int val, cnt;
} node[maxn];

inline int sgn(int x) {
    return node[node[x].pa].cld[1] == x;
}

int tot = 0;
int root;

int New(int val, int pa) {
    node[++tot].val = val;
    node[tot].pa = pa;
    node[tot].cnt = 1;
    return tot;
}

void build() {
    root = New(-inf, NIL);
    node[root].cld[1] = New(inf, root);
}

void dbg(int p) {
    if(node[p].cld[0]) dbg(node[p].cld[0]);

    printf("\n");
    debug(node[p].val);
    debug(node[node[p].pa].val);

    if(node[p].cld[1]) dbg(node[p].cld[1]);
}
// == tree finished ==

// == rotate ==
void setc(int q, int d, int p) {
    if(p) node[p].pa = q;
    if(q) node[q].cld[d] = p;
    if(q == NIL) root = p;
}

inline void rot(int x, int d) {
    int y = node[x].pa, z = node[y].pa;

    if(z) setc(z, sgn(y), x);
    if(y) setc(y, d, node[x].cld[d^1]);
    setc(x, d^1, y);
}

inline void rot(int x) {
    rot(x, sgn(x));
}
// == rotate finished ==

// == void splay ==
int splay(int p, const int to) {
    if(p == to) return p;

    while (node[p].pa != to) {
        if(node[p].pa == NIL) {
            root = p;
            break;
        }

        if(node[node[p].pa].pa == to) {
            rot(p);
            break;
        }
        else {
            int a = sgn(p), b = sgn(node[p].pa);
            rot((a^b ? p : node[p].pa), a);
            rot(p, b);
        }
    }
    return p;
}
// == splay finished ==

// == insert element ==
void insert(const int p, int x) {
    int u = p;
    int pa = NIL;

    while (u && node[u].val != x) {
        pa = u;
        u = node[u].cld[x > node[u].val];
    }

    if(u) node[u].cnt++;
    else {
        if(pa) {
            u = New(x, pa);
            node[pa].cld[x > node[pa].val] = u;
        }
        else {
            u = New(x, NIL);
            root = u;
        }
    }

    splay(u, root);
}
// == insert finished ==

// == delete element ==
int find(int x) {
    int u = root;
    while (true) {
        if(node[u].val == x) return u;
        if(node[u].cld[x > node[u].val] == 0) return NIL;
        u = node[u].cld[x > node[u].val];
    }
}

void _del(int x) {
    node[x].cld[0] = node[x].cld[1] = 0;
    node[x].pa = 0;
    node[x].val = node[x].cnt = 0;

    if(x == tot) tot--;
}

void del(int x) {
    int u = find(x);
    if(u == NIL) return;

    splay(u, root);

    if(node[u].cnt > 1) {
        node[u].cnt--;
        return;
    }

    if(node[u].cld[0] == 0) {
        int d = sgn(u);
        setc(node[u].pa, d, node[u].cld[1]);
        _del(u);
    }
    else {
        int d = sgn(u);
        int pre = node[u].cld[0];
        while (node[pre].cld[1]) pre = node[pre].cld[1];

        splay(pre, u);

        setc(pre, 1, node[u].cld[1]);
        setc(node[u].pa, d, pre);
        _del(u);
    }
}
// == delete finsihed ==

// == pre and next ==
int getPre(const int rt, int val) {
    int ans = -inf;
    int p = rt;

    while (p) {
        if(node[p].val == val) {
            if(node[p].cnt >= 1) {
                ans = node[p].val;
                return ans;
            }
            if(node[p].cld[0]) {
                p = node[p].cld[0];
                while (node[p].cld[1]) p = node[p].cld[1];
                ans = node[p].val;
            }
            break;
        }
        if(node[p].val < val && node[p].val > ans) ans = node[p].val;
        p = val < node[p].val ? node[p].cld[0] : node[p].cld[1];
    }
    return ans;
}

int getNxt(const int rt, int val) {
    int ans = inf;
    int p = rt;

    while (p) {
        if(node[p].val == val) {
            if(node[p].cnt >= 1) {
                ans = node[p].val;
                return ans;
            }
            if(node[p].cld[1]) {
                p = node[p].cld[1];
                while (node[p].cld[0]) p = node[p].cld[0];
                ans = node[p].val;
            }
            break;
        }
        if(node[p].val > val && node[p].val < ans) ans = node[p].val;
        p = val < node[p].val ? node[p].cld[0] : node[p].cld[1];
    }
    return ans;
}
// == pre and next finsihed ==

int main() {
    freopen("input.txt", "r", stdin);

    scanf("%d", &n);
    build();

    int ans;
    scanf("%d", &ans);
    insert(root, ans);
    n--;

    while (n--) {
        int x;
        scanf("%d", &x);

        int pre = getPre(root, x);
        int nxt = getNxt(root, x);

        ans += min(abs(pre - x), abs(nxt - x));

        insert(root, x);
    }

    printf("%d", ans);
}