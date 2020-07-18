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
    Node* pa;
    Node* cld[2];

    int val, sz;
    bool rev;

    inline void pushdown() {
        if(rev)  {
            _for(k, 0, 2) if(cld[k]) cld[k]->rev ^= 1;
            swap(cld[0], cld[1]);
            rev = false;
        }
    }

    inline void pushup() {
        sz = 1;
        _for(k, 0, 2) if(cld[k] != null) sz += cld[k]->sz;
    }

    inline int sgn() {
        return pa->cld[1] == this;
    }

    void setc(int d, Node* x) {
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

    Node* splay(const Node* to) {
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
    p->val = mid;

    if(p->cld[0]) p->cld[0]->pa = p;
    if(p->cld[1]) p->cld[1]->pa = p;
    p->pushup();

    return p;
}

void buildTree(int n) {
    root = build(1, n + 2);
    root->pa = NIL;
    NIL->pa = NULL;
    NIL->cld[1] = root;
    NIL->cld[0] = NULL;

    null->sz = 0;
    null->pa = NULL;
}
// == tree structure finished ==

// == debug ==
void dbg(T rt) {
    T u = rt;
    if(u->cld[0]) dbg(u->cld[0]);
    if(u != null) printf("cur: %d\n", u->val);
    if(u->cld[1]) dbg(u->cld[1]);
}

void leveldbg(T rt) {
    queue<T> que;
    que.push(rt);
    int cnt = 1, nxtcnt = 0;
    int level = 1;
    while (!que.empty()) {
        T x = que.front();
        que.pop();
        if(x != null && x != NIL && x) printf("%d(%d) ", x->val, x->sgn());
        cnt--;
        if(x == NULL) continue;

        if(x->cld[0] != null) que.push(x->cld[0]), nxtcnt++;
        if(x->cld[1] != null) que.push(x->cld[1]), nxtcnt++;

        if(cnt == 0) {
            //printf("level: %d\n", level++);
            puts("");
            cnt = nxtcnt;
            nxtcnt = 0;
        }
    }
}
// == debug finished ==

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
// == select finsihed ==

void test() {
    cout << "====Test=====" << endl;
    int a, b;
    scanf("%d%d", &a, &b);
    T u = select(root, a);
    debug(u->val);
    if(u != null) u->splay(NIL);
    root = u;
    leveldbg(root);
}


// == reverse ==
inline void turn(int x1, int x2) {
    T L = select(root, x1 - 1), R = select(root, x2 + 1);
    L->splay(NIL), root = L;
    R->splay(root);

    T goal = R->cld[0];
    goal->rev ^= 1;
    R->cld[0] = null;
    R->pushup();
    root->pushup();

    T t1 = select(root, root->sz);
    T t2 = select(root, root->sz-1);
    t2->splay(NIL), root = t2;
    t1->splay(root);

    t1->cld[0] = goal;
    goal->pa = t1;

    t1->pushup();
    root->pushup();
}
// == reverse finsihed ==

vector<int> ans;
void dfs(T r, int n) {
    r->pushdown();
    if(r->cld[0] != null) dfs(r->cld[0], n);
    if(r->val != 1 && r->val != n + 2) printf("%d\n", r->val - 1);
    if(r->cld[1] != null) dfs(r->cld[1], n);
}

int main() {
    freopen("input.txt", "r", stdin);
    int n, m;
    scanf("%d%d", &n, &m);
    buildTree(n);
    //leveldbg(root);

    while (m--) {
        int x1, x2;
        scanf("%d%d", &x1, &x2);
        x1++, x2++;
        turn(x1, x2);
    }
    dfs(root, n);
}
