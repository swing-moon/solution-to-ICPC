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

    int big, val, tag;
    int sz;
    bool rev;

    inline void pushdown() {
        if(tag) {
            _for(k, 0, 2) if(cld[k]) {
                cld[k]->tag += tag;
                cld[k]->val += tag;
                cld[k]->big += tag;
            }
            tag = 0;
        }
        if(rev) {
            _for(k, 0, 2) if(cld[k]) cld[k]->rev ^= 1;
            rev = 0;
            swap(cld[0], cld[1]);
        }
    }

    inline void pushup() {
        big = val;
        sz = 1;
        if(cld[0] != null) {
            big = max(big, cld[0]->big);
            sz += cld[0]->sz;
        }
        if(cld[1] != null) {
            big = max(big, cld[1]->big);
            sz += cld[1]->sz;
        }
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

Node *null = new Node();
typedef Node* T;
T NIL = new Node();
T root = &A[0];

T build(int l, int r) {
    if(l > r) return null;
    int mid = (l + r) >> 1;

    T p = &A[mid];

    p->cld[0] = build(l, mid - 1);
    p->cld[1] = build(mid + 1, r);
    p->val = p->rev = 0;
    if(p->cld[0]) p->cld[0]->pa = p;
    if(p->cld[1]) p->cld[1]->pa = p;
    p->pushup();

    return p;
}

void buildTree(int n) {
    root = build(1, n + 2);
    root->pa = NIL;
    NIL->pa = NULL;
    NIL->cld[0] = NULL;
    NIL->cld[1] = root;

    null->sz = 0;
    null->pa = NULL;
    null->val = -inf;
}

void levedbg(T rt) {
    queue<T> que;
    que.push(rt);
    int cnt = 1, nxtcnt = 0;
    int level = 1;

    while (!que.empty()) {
        T x = que.front(); que.pop();
        if(x != null && x != NIL && x) printf("%d(%d) ", x->val, x->sgn());
        cnt--;
        if(x == NULL) continue;

        if(x->cld[0] != null) que.push(x->cld[0]), nxtcnt++;
        if(x->cld[1] != null) que.push(x->cld[1]), nxtcnt++;

        if(cnt == 0) {
            printf("\n");
            cnt = nxtcnt;
            nxtcnt = 0;
        }
    }
}
// == tree finished ==

// == void dbg ==
void dbg(const T rt) {
    T u = rt;
    //u->pushdown();
    if(u->cld[0] != null && u->cld[0]) dbg(u->cld[0]);
    if(u != NIL && u != null && u) {
        printf("%d ", u->val);
    }
    if(u->cld[1] != null && u->cld[1]) dbg(u->cld[1]);
}
// == dbg finished ==

// == select kth ==
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

void change(int l, int r, int val) {
    T x1 = select(root, l - 1);
    T x2 = select(root, r + 1);
    //debug(x1->sz), debug(x2->sz); puts("");

    x1->splay(NIL), root = x1;
    //dbg(x1); puts("");
    x2->splay(x1);

    x2->cld[0]->val += val;
    x2->cld[0]->tag += val;
    x2->cld[0]->big += val;

    //dbg(x2->cld[0]); puts("");
}

void turn(int l, int r) {
    T x1 = select(root, l - 1);
    T x2 = select(root, r + 1);

    x1->splay(NIL), root = x1;
    x2->splay(x1);

    x2->cld[0]->rev ^= 1;
}

int query(int l, int r) {
    T x1 = select(root, l - 1);
    T x2 = select(root, r + 1);
    x1->splay(NIL), root = x1;
    x2->splay(x1);

    return x2->cld[0]->big;
}
// == select finished ==



int main() {
    freopen("input.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);

    buildTree(n);
    //levedbg(root);

    _for(i, 0, m) {
        int a, b, c, d;
        scanf("%d", &a);

        if(a == 1) {
            scanf("%d%d%d", &b, &c, &d);
            b++, c++;
            change(b, c, d);
            // dbg(root); puts("");
        }
        else if(a == 2) {
            scanf("%d%d", &b, &c);
            b++, c++;
            turn(b, c);
        }
        else {
            scanf("%d%d", &b, &c);
            b++, c++;
            printf("%d\n", query(b, c));
        }
    }
}