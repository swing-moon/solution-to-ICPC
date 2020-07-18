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

const int maxn = 1e6 + 8;
const int mod = 1000000;
const int inf = 0x3f3f3f3f;
int n;

// == tree structure ==
class Node {
public:
    static Node *root;
#define root Node::root
    Node* pa;
    Node* cld[2];

    int val, cnt;
    Node() {}

    Node(int v, Node* pa) : val(v), pa(pa) {
        cld[0] = cld[1] = NULL;
        cnt = 1;
    }

    int sgn() {
        return pa->cld[1] == this;
    }

    void setc(int d, Node* x) {
        cld[d] = x;
        if(x) x->pa = this;
    }

    void rot(int d) {
        Node *y = pa, *z = y->pa;
        if(z) z->setc(y->sgn(), this);
        if(y) y->setc(d, cld[d^1]);
        setc(d^1, y);
    }

    void rot() {
        rot(sgn());
    }

    Node* splay(const Node* to) {
        if(this == to) return this;

        while (pa != to) {
            if(pa == NULL) {
                root = this;
                break;
            }

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

        return this;
    }
} *root;

typedef Node* T;

void build() {
    root = new Node(-inf, NULL);
    root->cld[1] = new Node(inf, root);
}
// == tree structure finished ==

// == debug ==
void dbg(const T& rt) {
    T p = rt;
    if(p->cld[0]) dbg(p->cld[0]);

    printf("\n");
    debug(p->val);
    if(p->pa) debug(p->pa->val);

    if(p->cld[1]) dbg(p->cld[1]);
}
// == debug finsihed ==



// == void insert operation ==
void insert(const T& p, int x) {
    T u = p;
    T pa = NULL;

    while (u && u->val != x) {
        pa = u;
        u = u->cld[x > u->val];
    }

    if(u != NULL) u->cnt++;
    else {
        if(pa != NULL) {
            u = new Node(x, pa);
            pa->cld[x > pa->val] = u;
        }
        else {
            u = new Node(x, NULL);
            root = u;
        }
    }

    u->splay(root);
}
// == insert finsihed ==

// == delete data ==
T find(int x) {
    T u = root;
    while (true) {
        if(x == u->val) return u;
        if(u->cld[x > u->val] == NULL) return NULL;
        u = u->cld[x > u->val];
    }
}

void del(int x) {
    T u = find(x);
    if(u == NULL) return;

    u->splay(root);

    if(u->cnt > 1) {
        u->cnt--;
        return;
    }

    if(u->cld[0] == NULL) {
        int d = u->sgn();
        u->pa->setc(d, u->cld[1]);
        delete u;
        u = NULL;
    }
    else {
        int d = u->sgn();
        T pre = u->cld[0];
        while (pre->cld[1]) pre = pre->cld[1];

        pre->splay(u);
        pre->setc(1, u->cld[1]);
        u->pa->setc(d, pre);
        delete u;
        u = NULL;
    }
}

void rmvTree(T& p) {
    if(p->cld[0]) rmvTree(p->cld[0]);
    if(p->cld[1]) rmvTree(p->cld[1]);
    delete p;
    p = NULL;
}
// == delete finsihed ==

// == precursor and successor ==
int getNxt(const T& rt, int val) {
    int ans = inf;
    T p = rt;

    while (p) {
        if(val == p->val) {
            if(p->cnt >= 1) {
                ans = p->val;
                return ans;
            }
            if(p->cld[1]) {
                p = p->cld[1];
                while (p->cld[0]) p = p->cld[0];
                ans = p->val;
            }
            break;
        }
        if(p->val > val && p->val < ans) ans = p->val;
        p = val < p->val ? p->cld[0] : p->cld[1];
    }
    return ans;
}

int getPre(const T& rt, int val) {
    int ans = -inf;
    T p = rt;

    while (p) {
        if(val == p->val) {
            if(p->cnt >= 1) {
                ans = p->val;
                return ans;
            }
            if(p->cld[0]) {
                p = p->cld[0];
                while (p->cld[1]) p = p->cld[1];
                ans = p->val;
            }
            break;
        }
        if(p->val < val && p->val > ans) ans = p->val;
        p = val < p->val ? p->cld[0] : p->cld[1];
    }
    return ans;
}
// == precursor finished ==

int ans = 0;
void init() {
    ans = 0;
}

int main() {
    freopen("input.txt", "r", stdin);

    build();
    init();

    scanf("%d", &n);
    scanf("%d", &ans);
    n--;

    insert(root, ans);
    while (n--) {
        int x;
        scanf("%d", &x);
        int pre = getPre(root, x);
        int nxt = getNxt(root, x);
        ans += min(abs(pre - x), abs(nxt - x));

        insert(root, x);
    }
    printf("%d", ans);
    rmvTree(root);
}