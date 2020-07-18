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

const int maxn = (5e4 + 10) * 2;
const int NIL = 0;
const int inf = 0x3f3f3f3f;

// == KDTree Node definition ==
int cd, K;

class Node {
public:
    int x[6], cld[2];
    ll _max[6], _min[6];

    bool operator< (const Node& rhs) const {
        if(x[cd] != rhs.x[cd]) return x[cd] < rhs.x[cd];
        _rep(i, cd + 1, K) if(x[i] != rhs.x[i]) return x[i] < rhs.x[i];
        _for(i, 1, cd) if(x[i] != rhs.x[i]) return x[i] < rhs.x[i];
        return x[cd] < rhs.x[cd];
    }
};

Node T[maxn];

inline void pushup(int x, int y) {
    _rep(i, 1, K) {
        T[x]._max[i] = max(T[x]._max[i], T[y]._max[i]);
        T[x]._min[i] = min(T[x]._min[i], T[y]._min[i]);
    }
}

int build(int l, int r, int dep) {
    if(l > r) return 0;

    int mid = (l + r) >> 1;
    cd = dep % K;
    nth_element(T + l, T + mid, T + r + 1);
    _rep(i, 1, K) T[mid]._min[i] = T[mid]._max[i] = T[mid].x[i];
    T[mid].cld[0] = T[mid].cld[1] = NIL;

    if(l < mid) {
        T[mid].cld[0] = build(l, mid - 1, dep + 1);
        pushup(mid, T[mid].cld[0]);
    }
    if(r > mid) {
        T[mid].cld[1] = build(mid + 1, r, dep + 1);
        pushup(mid, T[mid].cld[1]);
    }

    return mid;
}

int rt;
// == KDTree finished ==

int n, m, q;

// == temp node for update ==
typedef pair<ll, Node> PLN;
priority_queue<PLN> que;


ll euclid(const Node& a, const Node& b) {
    ll ans = 0;
    _rep(i, 1, K) ans += 1ll * (a.x[i] - b.x[i]) * (a.x[i] - b.x[i]);
    return ans;
}
// == temp node finsihed ==

// == k closest query ==
Node goal;

void query(int u, int dep) {
    if(!u) return;
    ll res = euclid(T[u], goal);

    if(res < que.top().first) {
        que.pop();
        PLN cur(res, T[u]);
        que.push(cur);
    }

    int cd = dep % K;
    ll cut = T[u].x[cd] - goal.x[cd];

    if(cut > 0) {
        query(T[u].cld[0], dep + 1);
        if(cut*cut < que.top().first) query(T[u].cld[1], dep + 1);
    }
    else {
        query(T[u].cld[1], dep + 1);
        if(cut*cut < que.top().first) query(T[u].cld[0], dep + 1);
    }
}
// == k closest query finsiehd ==

void init() {
    _rep(i, 1, K) T[0]._max[i] = -inf, T[0]._min[i] = inf;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (~scanf("%d%d", &n, &K)) {
        init();
        _rep(i, 1, n) _rep(j, 1, K) scanf("%d", &T[i].x[j]);

        // build KDTree and use KDTree
        rt = build(1, n, 1);
        // finished

        scanf("%d", &q);
        while (q--) {
            _rep(i, 1, K) scanf("%d", &goal.x[i]);

            scanf("%d", &m);
            PLN _NIL(inf, Node());
            _rep(i, 1, m) que.push(_NIL);

            // query closest m points
            query(rt, 1);
            stack<PLN> stk;
            while (!que.empty()) {
                stk.push(que.top());
                que.pop();
            }
            printf("the closest %d points are:\n", m);
            while (!stk.empty()) {
                PLN ans = stk.top();
                stk.pop();
                _rep(i, 1, K) {
                    printf("%d", ans.second.x[i]);
                    i != K ? printf(" ") : printf("\n");
                }
            }
        }
    }
}