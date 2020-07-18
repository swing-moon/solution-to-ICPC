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

const int maxn = 201000;

class Node {
public:
    Node* pa;
    Node* l;
    Node* r;
    int val, sz;
    int cnt;

    Node(int val = 0, Node* pa = NULL) : val(val), pa(pa) {
        l = r = NULL;
        sz = cnt = 1;
    }

    void update() {
        sz = cnt;
        if(l != NULL) sz += l->sz;
        if(r != NULL) sz += r->sz;

        l->pa = this;
        r->pa = this;
    }
} a[maxn];

typedef Node* T;
T root;

void init() {
    root = NULL;
}

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

void rotate(T& x) {
    if(x == x->pa->l) zig(x->pa);
    else zag(x->pa);
}

void splay(T& x, const T goal) {
    while (x->pa != goal) {
        T y = x->pa;
        T z = y->pa;

        if(z != goal) {
            (z->l == y) ^ (y->l == x) ? rotate(x) : rotate(y);
        }
        rotate(x);
    }
    if(goal == NULL) root = goal;
}

inline void Find(int x) {
    T u = root;
    if(u == NULL) return;
    while (u->val != x) {
        if(x > u->val) u = u->r;
        else u = u->l;
    }
    splay(u, root);
}

inline void insert(int x) {
    T u = root, fa = NULL;

    while (u && x != u->val) {
        fa = u;
        x > u->val ? u = u->r : u = u->l;
    }

    if(u != NULL) u->cnt++;
    else {
        u = new Node(x, fa);
        if(fa != NULL) {
            (x > fa->val) ? (fa->r = u) : (fa->l = u);
        }
    }

    splay(u, root);
}

int main() {
    //
}