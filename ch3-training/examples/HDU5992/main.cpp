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

const int maxn = (200000 + 5) * 2;
const ll inf = 0x3f3f3f3f3f3f3f3f;
const int NIL = 0;

// == KDTree definition ==
int cd, K = 2;

class Node {
public:
    int x[2], cld[2];
    int cost, id;

    bool operator< (const Node& rhs) const {
        return x[cd] < rhs.x[cd];
    }
} T[maxn];

int rt;

// usage, build(1, n, 0)
int build(int l, int r, int dep) {
    if(l > r) return 0;

    int mid = (l + r) >> 1;
    cd = dep % K;
    nth_element(T+l, T+mid, T+r+1);
    T[mid].cld[0] = T[mid].cld[1] = NIL;

    if(l < mid) T[mid].cld[0] = build(l, mid - 1, dep + 1);
    if(r > mid) T[mid].cld[1] = build(mid + 1, r, dep + 1);

    return mid;
}
// == KDTree definition finsished ==

// == ans used for update ==
ll euclid(const Node& a, const Node& b) {
    ll ans = 0;
    _for(i, 0, K) ans += 1ll * (a.x[i] - b.x[i]) * (a.x[i] - b.x[i]);
    return ans;
}

bool valid(const Node& cur, const Node& goal) {
    return cur.cost <= goal.cost;
}

typedef pair<ll, Node> PLN;
PLN ans;
// == ans finsihed ==

// == query ==
void query(int u, const Node& goal, int dep) {
    if(!u) return;
    ll res = euclid(T[u], goal);

    if(res == ans.first && T[u].id < ans.second.id && valid(T[u], goal)) {
        PLN cur(res, T[u]);
        ans = cur;
    }

    if(res < ans.first && valid(T[u], goal)) {
        PLN cur(res, T[u]);
        ans = cur;
    }

    int cd = dep % K;
    ll cut = T[u].x[cd] - goal.x[cd];

    if(cut > 0) {
        query(T[u].cld[0], goal, dep + 1);
        if(cut*cut < ans.first) query(T[u].cld[1], goal, dep + 1);
    }
    else {
        query(T[u].cld[1], goal, dep + 1);
        if(cut*cut < ans.first) query(T[u].cld[0], goal, dep + 1);
    }
}
// == query finsihed ==

int n, m;

void init() {
    K = 2;
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);

    while (kase--) {
        init();

        // == input data ==
        scanf("%d%d", &n, &m);
        _rep(i, 1, n) {
            _for(j, 0, 2) scanf("%d", &T[i].x[j]);
            scanf("%d", &T[i].cost);
            T[i].id = i;
        }
        // == input finsihed ==

        // == build kdtree ==
        rt = build(1, n, 0);
        // == build finsihed ==

        for(; m; m--) {
            Node goal;
            _for(j, 0, 2) scanf("%d", &goal.x[j]);
            scanf("%d", &goal.cost);

            PLN _NIL(inf, Node());
            ans = _NIL;
            // == query for closest point ==
            query(rt, goal, 0);
            // == query finsihed ==

            _for(i, 0, K) printf("%d ", ans.second.x[i]);
            printf("%d\n", ans.second.cost);
        }
    }
}