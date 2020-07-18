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

const int maxn = 1e6 + 5;
const int NIL = -1;

// == Point definition ==
class Point {
public:
    int id, x, y;
    Point() {}
    Point(int _id, int _x, int _y) : id(_id), x(_x), y(_y) {}
    bool operator< (const Point& rhs) const {
        return id < rhs.id;
    }

    void print() {
        printf("%d\n", id);
    }
};

Point pt[maxn];

bool cmpx(const Point& p1, const Point& p2) {
    return p1.x < p2.x;
}

bool cmpy(const Point& p1, const Point& p2) {
    return p1.y < p2.y;
}
// == Point finished ==

// == KDTree structure ==
class Node {
public:
    int loc;
    int cld[2];
};

inline int sgn(int d) {
    return d % 2;
}

Node T[maxn];
int tot = 0, root;

void init() {
    tot = 0;
    _for(i, 0, maxn) T[i].cld[0] = T[i].cld[1] = NIL;
}

int buildKD(int l, int r, int d) {
    if(l >= r) return NIL;

    int mid = (l + r) >> 1;

    int t = ++tot;
    if(sgn(d) == 0) sort(pt + l, pt + r, cmpx);
    else sort(pt + l, pt + r, cmpy);

    T[t].loc = mid;
    T[t].cld[0] = buildKD(l, mid, d + 1);
    T[t].cld[1] = buildKD(mid + 1, r, d + 1);

    return t;
}
// == KDTree finished ==

// == query ==
void query(int u, int sx, int tx, int sy, int ty, int d, vector<Point>& ans) {
    int x = pt[T[u].loc].x;
    int y = pt[T[u].loc].y;

    if(sx <= x && x <= tx && sy <= y && y <= ty) ans.push_back(pt[T[u].loc]);

    if(sgn(d) == 0) {
        if(T[u].cld[0] != NIL) {
            if(sx <= x) query(T[u].cld[0], sx, tx, sy, ty, d + 1, ans);
        }
        if(T[u].cld[1] != NIL) {
            if(x <= tx) query(T[u].cld[1], sx, tx, sy, ty, d + 1, ans);
        }
    }
    else {
        if(T[u].cld[0] != NIL) {
            if(sy <= y) query(T[u].cld[0], sx, tx, sy, ty, d + 1, ans);
        }
        if(T[u].cld[1] != NIL) {
            if(y <= ty) query(T[u].cld[1], sx, tx, sy, ty, d + 1, ans);
        }
    }
}
// == query finsihed ==

int N = 0;
int main() {
    freopen("input.txt", "r", stdin);
    int x, y;
    scanf("%d", &N);
    _for(i, 0, N) {
        scanf("%d%d", &x, &y);
        pt[i] = Point(i, x, y);
    }

    init();

    root = buildKD(0, N, 0);

    int q;
    scanf("%d", &q);
    int sx, tx, sy, ty;
    vector<Point> ans;

    _for(i, 0, q) {
        scanf("%d%d%d%d", &sx, &tx, &sy, &ty);
        ans.clear();

        query(root, sx, tx, sy, ty, 0, ans);

        sort(ans.begin(), ans.end());

        _for(k, 0, ans.size()) ans[k].print();
        puts("");
    }
}