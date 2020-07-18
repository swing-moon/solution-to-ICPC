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

const double eps = 1e-10;

int dcmp(double x) {
    if(fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}

class Point {
public:
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

typedef Point Vector;

bool operator< (const Point& lhs, const Point& rhs) { return lhs.x < rhs.x || (lhs.x == rhs.x && lhs.y < rhs.y); }
bool operator== (const Point& lhs, const Point& rhs) { return dcmp(lhs.x - rhs.x) == 0 && dcmp(lhs.y - rhs.y) == 0; }

Vector operator+ (const Vector& lhs, const Vector& rhs) { return Vector(lhs.x + rhs.x, lhs.y + rhs.y); }
Vector operator- (const Vector& lhs, const Vector& rhs) { return Vector(lhs.x - rhs.x, lhs.y - rhs.y); }
Vector operator* (const Vector& lhs, double p) { return Vector(lhs.x * p, lhs.y * p); }
double Dot(const Vector& A, const Vector& B) { return A.x * B.x + A.y * B.y; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }
double Angle(const Vector& A, const Vector& B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
double Cross(const Vector& A, const Vector& B) { return A.x * B.y - A.y * B.x; }

Point readPoint() {
    double x, y;
    scanf("%lf%lf", &x, &y);
    return Point(x, y);
}

Point getLineIntersection(const Point& P, const Vector& v, const Point& Q, const Vector& w) {
    Vector u = P - Q;
    double t = Cross(w, u) / Cross(v, w);
    return P + v * t;
}

Vector Rotate(const Vector& A, double rad) {
    return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));
}

bool segmentProperIntersection(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
    double c1 = Cross(a2 - a1, b1 - a1), c2 = Cross(a2 - a1, b2 - a1);
    double c3 = Cross(b2 - b1, a1 - b1), c4 = Cross(b2 - b1, a2 - b1);
    return dcmp(c1) * dcmp(c2) < 0 && dcmp(c3) * dcmp(c4) < 0;
}

bool onSegment(Point p, Point a1, Point a2) {
    return dcmp(Cross(a1 - p, a2 - p)) == 0 && dcmp(Dot(a1 - p, a2 - p)) < 0;
}

const int maxn = 300 + 10;
Point p[maxn], v[maxn * maxn];
int N;

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while (scanf("%d", &N) == 1 && N) {
        printf("Case %d: ", ++kase);

        _for(i, 0, N) {
            scanf("%lf%lf", &p[i].x, &p[i].y);
            v[i] = p[i];
        }

        N--;
        int cnt = N, e = N;
        _for(i, 0, N) _for(j, i + 1, N) {
            if(segmentProperIntersection(p[i], p[i + 1], p[j], p[j + 1])) {
                v[cnt++] = getLineIntersection(p[i], p[i + 1] - p[i], p[j], p[j + 1] - p[j]);
            }
        }

        sort(v, v + cnt);
        cnt = unique(v, v + cnt) - v;
        //debug(cnt);


        _for(i, 0, cnt) _for(j, 0, N) {
            if(onSegment(v[i], p[j], p[j + 1])) e++;
        }

        printf("There are %d pieces.\n", e + 2 - cnt);
    }
}