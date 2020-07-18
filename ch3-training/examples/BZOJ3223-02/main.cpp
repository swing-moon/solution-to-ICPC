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
const int inf = 0x3f3f3f3f;

// == tree structure ==
class Node {
public:
    static Node *null;
#define null Node::null
    Node *pa;
    Node *cld[2];

    int val, sz;
    bool rev;

    inline void pushdown() {
        if(rev) {
            _for(k, 0, 2) if(cld[k]) cld[k]->rev ^= 1;
            swap(cld[0], cld[1]);
            rev = 0;
        }
    }

    inline void pushup() {
        sz = 1;
        if(cld[0] != null) sz += cld[0]->sz;
        if(cld[1] != null) sz += cld[1]->sz;
    }

    inline int sgn() {
        return pa->cld[1] == this;
    }

    void setc(int d, Node *x) {
        cld[d] = x;
        x->pa = this;
    }

    void rot(int d) {
        Node *y = pa, *z = y->pa;
        z->setc(y->sgn(), this);
        y->setc(d, cld[d^1]);
        setc(d^1, y);

        y->pushup();
    }

    void rot() {
        rot(sgn());
    }

    Node *splay(const Node *to) {
        while (pa != to) {
            if(pa->pa == to) {
                rot();
                break;
            }
            else {
                int a = sgn(), b = pa->sgn();
                (a^b ? this : pa)->rot(a);
                rot(b);
            }
        }
        pushup();
        return this;
    }
} A[maxn];

typedef Node* T;
Node *null = new Node();
T NIL = new Node();
T root = &A[0];

T build(int l, int r) {
    if(l > r) return null;
    int mid = (l + r) >> 1;

    T p = &A[mid];
    p->val = mid;
    p->cld[0] = build(l, mid - 1);
    p->cld[1] = build(mid + 1, r);

    if(p->cld[0]) p->cld[0]->pa = p;
    if(p->cld[1]) p->cld[1]->pa = p;
    p->pushup();

    return p;
}

void buildTree(int n) {
    root = build(1, n + 2);
    root->pa = NIL;
    NIL->cld[0] = NULL;
    NIL->cld[1] = root;

    null->sz = 0;
    null->pa = NULL;

    A[1].val = -inf;
    A[n+2].val = -inf;
}
// == tree finished ==

// == select finished ==
T select(const T rt, int k) {
    T u = rt;
    while (u != null) {
        if(u->cld[0]->sz == k - 1) return u;
        if(u->cld[0]->sz >= k) u = u->cld[0];
        else {
            k -= u->cld[0]->sz + 1;
            u = u->cld[1];
        }
        u->pushdown();
    }
    return u;
}
// == select finished ==

// == change ==
void turn(int l, int r) {
    T x = select(root, l - 1);
    T y = select(root, r + 1);

    x->splay(NIL), root = x;
    y->splay(x);

    y->cld[0]->rev ^= 1;
}
// == change finished ==

// == dfs ==
void dfs(const T rt) {
    T u = rt;
    u->pushdown();

    if(u->cld[0]) dfs(u->cld[0]);
    if(u != null && u->val != -inf) printf("%d ", u->val - 1);
    if(u->cld[1]) dfs(u->cld[1]);
}
// == dfs finished ==

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