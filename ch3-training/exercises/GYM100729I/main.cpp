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
typedef long long llong;
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
const int maxn = 15;
int ns, nw, np, r;

// == Point structure ==
class Point {
public:
    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    Point operator+ (const Point& rhs) const {
        return Point(x + rhs.x, y + rhs.y);
    }

    Point operator- (const Point& rhs) const {
        return Point(x - rhs.x, y - rhs.y);
    }

    bool operator== (const Point& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    bool operator< (const Point& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

typedef Point Vector;

llong Cross(const Vector& A, const Vector& B) {
    return (llong)A.x * B.y - (llong)A.y * B.x;
}
llong Length2(const Vector& A) {
    return (llong)A.x * A.x + (llong)A.y * A.y;
}

Point readPoint() {
    int x, y;
    scanf("%d%d", &x, &y);
    return Point(x, y);
}
// == Point structure finished ==

// == Segment Structure ==
class Line {
public:
    Point a, b;
};

Line walls[maxn];

bool segmentProperIntersection(const Point& a, const Point& b, const Point& c, const Point& d) {
    if(max(a.x, b.x) < min(c.x, d.x)
    || max(a.y, b.y) < min(c.y, d.y)
    || min(a.x, b.x) > max(c.x, d.x)
    || min(a.y, b.y) > max(c.y, d.y))
        return 0;

    llong v1 = Cross(b - a, c - a), v2 = Cross(b - a, d - a);
    llong v3 = Cross(d - c, a - c), v4 = Cross(d - c, b - c);

    return v1 * v2 <= 0 && v3 * v4 <= 0;
}
// == Segment Structure finished ==


set<Point> sen;
vector<Point> ANS;
// == solve the problem ==
int check(Point p, Vector v) {
    Point q = p + v;
    if(!sen.count(q)) return 0;

    int cnt = 0;
    _for(i, 0, nw) {
        if(segmentProperIntersection(walls[i].a, walls[i].b, p, q)) cnt++;
    }

    return cnt <= r && Length2(v) <= (llong)(r - cnt) * (r - cnt);
}

void solve(const Point& p) {
    _rep(dx, -r, r) _rep(dy, -r, r) {
        if(Length2(Vector(dx, dy)) > r * r) continue;
        if(check(p, Vector(dx, dy))) ANS.push_back(p + Vector(dx, dy));
    }
}
// == solve finsihed ==

void init() {
    sen.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d%d%d", &ns, &r, &nw, &np);
        init();

        _for(i, 0, ns) {
            sen.insert(readPoint());
        }

        _for(i, 0, nw) {
            walls[i].a = readPoint();
            walls[i].b = readPoint();
        }

        // == input finished ==

        // == then query for the products ==
        while (np--) {
            ANS.clear();
            Point p = readPoint();

            solve(p);

            printf("%d", (int)ANS.size());
            sort(ANS.begin(), ANS.end());
            for(auto e : ANS) printf(" (%d,%d)", e.x, e.y);
            printf("\n");
        }
    }
}