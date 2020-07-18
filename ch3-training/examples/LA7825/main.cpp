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

const int inf = 0x3f3f3f3f;
const int maxn = 1e5 + 5;
const int maxm = 100 + 5;
int n;

// == KDTree definition ==
int cd = 0;
const int K = 2;

struct Base {
    int x[2];
    int tp;
} sta[maxn];

class Node {
public:
    Node *cld[2];
    int xy[2];
    int tp;

    int tot;
    int sum[maxm];
    int x1, x2, y1, y2;

    void border(int L, int R, int& _x1, int& _x2, int& _y1, int& _y2) {
        _rep(i, L, R) {
            Base& cur = sta[i];
            _x1 = min(_x1, cur.x[0]);
            _x2 = max(_x2, cur.x[0]);
            _y1 = min(_y1, cur.x[1]);
            _y2 = max(_y2, cur.x[1]);
        }
    }

    inline void _init(int _tp = 0, int _x1 = 0, int _x2 = 0, int _y1 = 0, int _y2 = 0) {
        tot = 0;
        Set(sum, 0);
        cld[0] = cld[1] = NULL;

        x1 = _x1; x2 = _x2; y1 = _y1; y2 = _y2;
        tp = _tp;
    }

    inline void getData(int tid) {
        const Base& _cur = sta[tid];
        _for(i, 0, K) xy[i] = _cur.x[i];
        sum[_cur.tp]++;
        tot = 1;
    }
    void update();
} memory[maxn * 2];

typedef Node* T;
Node *mem = memory;
Node *root;

void Node::update() {
    _for(i, 0, K) if(cld[i]) {
            _for(j, 0, maxm) sum[j] += cld[i]->sum[j];
            tot += cld[i]->tot;
        }
}
// == KDTree finished ==

// == build KDTree ==
inline bool cmp(const Base& a, const Base& b) {
    return a.x[cd] < b.x[cd];
}


void build(T& cur, int l, int r, int dep) {
    if(l > r) return;
    cur = ++mem;

    int _x1, _x2, _y1, _y2;
    _x1 = _y1 = inf;
    _x2 = _y2 = 0;
    cur->border(l, r, _x1, _x2, _y1, _y2);

    //assert(dbg(cur) != 0);
    //debug(dbg(cur));

    cd = dep % K;
    int mid = (l + r) >> 1;
    nth_element(sta + l, sta + mid, sta + r + 1, cmp);

    cur->_init(sta[mid].tp, _x1, _x2, _y1, _y2);
    cur->getData(mid);
    build(cur->cld[0], l, mid - 1, dep + 1);
    build(cur->cld[1], mid + 1, r, dep + 1);

    cur->update();
}

// == build KDTree finished ==

// == used for calculate ==

inline int sqr(int x) {
    return x * x;
}
inline int maxdist(T cur, const Base& goal) {
    if(!cur) return 0;

    int ans = sqr(cur->x1 - goal.x[0]) + sqr(cur->y1 - goal.x[1]);
    ans = max(ans, sqr(cur->x1 - goal.x[0]) + sqr(cur->y2 - goal.x[1]));
    ans = max(ans, sqr(cur->x2 - goal.x[0]) + sqr(cur->y1 - goal.x[1]));
    ans = max(ans, sqr(cur->x2 - goal.x[0]) + sqr(cur->y2 - goal.x[1]));

    return ans;
}

inline int euclid(T cur, const Base& goal) {
    return sqr(cur->xy[0] - goal.x[0]) + sqr(cur->xy[1] - goal.x[1]);
}

void query(const T &cur, const Base& goal, int& res) {
    if(!cur) return;
    if(cur->tot == cur->sum[goal.tp]) return;
    if(maxdist(cur, goal) <= res) return;

    if(cur->tp != goal.tp) {
        res = max(res, euclid(cur, goal));
    }

    int d[2], flag = 1;
    d[0] = maxdist(cur->cld[0], goal);
    d[1] = maxdist(cur->cld[1], goal);

    if(d[0] > d[1]) flag ^= 1;

    if(d[flag] > res) query(cur->cld[flag], goal, res);
    if(d[flag^1] > res) query(cur->cld[flag^1], goal, res);
}

void solve() {
    int ans = 0;
    _rep(i, 1, n) query(root, sta[i], ans);
    printf("%d\n", ans);
}
// == calculate finsihed ==

void init() {
    _for(i, 0, maxn) (memory + i)->_init();
    mem = memory;
    root = NULL;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) == 1 && n) {
        // input sta data
        _rep(i, 1, n) {
            Base& cur = sta[i];
            scanf("%d%d%d", &cur.x[0], &cur.x[1], &cur.tp);
        }

        init();
        // build KDTree
        build(root, 1, n, 0);
        // solve
        solve();
    }
}