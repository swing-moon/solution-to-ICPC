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

const int maxn = (1e5 + 5) * 2;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const int NIL = 0;
int n, q;
int ID[maxn];

// == KDTree definition ==
int cd, K = 2;

class Node {
public:
    ll x[2];
    int cld[2];
    ll xymax[2], xymin[2];
    int id;

    bool operator< (const Node& rhs) const {
        if(x[0] != rhs.x[0]) return x[0] < rhs.x[0];
        return x[1] < rhs.x[1];
    }

    void _init(int i) {
        ID[id] = i;
        _for(j, 0, K) xymin[j] = xymax[j] = x[j];
        cld[0] = cld[1] = NIL;
    }

    inline void update();

} Tree[maxn];

inline void Node::update() {
    _for(i, 0, K) if(cld[i]) _for(j, 0, K) {
        xymin[j] = min(xymin[j], Tree[cld[i]].xymin[j]);
        xymax[j] = max(xymax[j], Tree[cld[i]].xymax[j]);
    }
}

bool cmp(const Node& a, const Node& b) {
    return a.x[cd] < b.x[cd];
}
// Point cur = pt[Tree[u].id]

int root;
// == KDTree finished ==

// == build tree ==
int build(int l, int r, int dep) {
    if(l > r) return 0;

    int mid = (l + r) >> 1;

    cd = dep % K;
    nth_element(Tree + l, Tree + mid, Tree + r + 1, cmp);

    Tree[mid]._init(mid);
    if(l < mid) Tree[mid].cld[0] = build(l, mid - 1, dep + 1);
    if(mid < r) Tree[mid].cld[1] = build(mid + 1, r, dep + 1);

    Tree[mid].update();
    return mid;
}
// == build fisniehd ==

// == used to solve ==
struct A {
    ll dist;
    Node nd;
    A() {};
    A(ll d, Node nd) : dist(d), nd(nd) {}
} res;
// dist init to inf

inline ll euclid(const Node& a, const Node& b) {
    ll ans = 0;
    _for(i, 0, K) ans += 1ll * (a.x[i] - b.x[i]) * (a.x[i] - b.x[i]);
    return ans;
}

inline ll manhatten(int u, const Node& goal) {
    ll ans = 0;
    const Node& cur = Tree[u];

    _for(i, 0, K) {
        ans += (max(cur.xymin[i] - goal.x[i], 0LL) + max(goal.x[i] - cur.xymax[i], 0LL)) *
                (max(cur.xymin[i] - goal.x[i], 0LL) + max(goal.x[i] - cur.xymax[i], 0LL));
    }

    return ans;
}

void querymin(int u, const Node& goal) {
    if(!u) return;
    if(goal.id != Tree[u].id) {
        ll dist = euclid(goal, Tree[u]);

        if(dist == res.dist && Tree[u] < res.nd) {
            res.nd = Tree[u];
        }

        if(dist < res.dist) {
            res.dist = dist;
            res.nd = Tree[u];
        }
    }

    ll dl = Tree[u].cld[0] ? manhatten(Tree[u].cld[0], goal) : inf;
    ll dr = Tree[u].cld[1] ? manhatten(Tree[u].cld[1], goal) : inf;

    if(dl < dr) {
        if(dl <= res.dist) querymin(Tree[u].cld[0], goal);
        if(dr <= res.dist) querymin(Tree[u].cld[1], goal);
    }
    else {
        if(dr <= res.dist) querymin(Tree[u].cld[1], goal);
        if(dl <= res.dist) querymin(Tree[u].cld[0], goal);
    }
}
// == finsihed ==

// == findset definition ==
int pa[maxn];
int findset(int x) {
    return pa[x] == x ? x : pa[x] = findset(pa[x]);
}
// == findset finsihed ==

// == solve the problem ==
void fi(int i) {
    res = A(inf, Node());
    querymin(root, Tree[ID[i]]);
    int to = res.nd.id;

    int u = findset(i);
    int v = findset(to);

    //printf("#: %d, %d, %d, %d\n", i, to, u, v);
    if(u != v) pa[u] = v;
}
// == solve finished ==

void init() {
    //
    K = 2;
    res = A(inf, Node());
    Set(ID, 0);

    _for(i, 0, maxn) pa[i] = i;
}



int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);

    for(int _ = 1; _ <= kase; _++) {
        printf("Case #%d:\n", _);

        init();
        scanf("%d%d", &n, &q);
        _rep(i, 1, n) {
            scanf("%lld%lld", &Tree[i].x[0], &Tree[i].x[1]);
            Tree[i].id = i;
        }

        // build KDTree
        root = build(1, n, 0);
        //_rep(i, 1, n) debug(ID[i]);

        // query min dist
        _rep(i, 1, n) fi(i);

        // debug

        _rep(i, 1, q) {
            int x, y;
            scanf("%d%d", &x, &y);
            findset(x) == findset(y) ? puts("YES") : puts("NO");
        }
    }
}