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
Vector operator/ (const Vector& lhs, double p) { return Vector(lhs.x / p, lhs.y / p); }
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

double distanceToLine(const Point& P, const Point& A, const Point& B) {
    Vector v1 = B - A, v2 = P - A;
    return fabs(Cross(v1, v2)) / Length(v1);
}

double distanceToSegment(const Point& P, const Point& A, const Point& B) {
    if(A == B) return Length(P - A);
    Vector v1 = B - A, v2 = P - A, v3 = P - B;

    if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if(dcmp(Dot(v1, v3) > 0)) return Length(v3);
    else return fabs(Cross(v1, v2)) / Length(v1);
}

const int maxn = 50 + 10;
const double inf = 1e9;
int T, NA, NB;
Point A[maxn], B[maxn];
double Min, Max;

void update(Point P, Point A, Point B) {
    Min = min(Min, distanceToSegment(P, A, B));
    Max = max(Max, Length(P - A));
    Max = max(Max, Length(P - B));
}

int main() {
    freopen("input.txt", "r", stdin);
    scanf("%d", &T);
    _rep(kase, 1, T) {
        printf("Case %d: ", kase);

        scanf("%d%d", &NA, &NB);
        _for(i, 0, NA) A[i] = readPoint();
        _for(i, 0, NB) B[i] = readPoint();

        double lenA = 0, lenB = 0;
        _for(i, 0, NA - 1) lenA += Length(A[i + 1] - A[i]);
        _for(i, 0, NB - 1) lenB += Length(B[i + 1] - B[i]);

        int sa = 0, sb = 0;
        Point pa = A[0], pb = B[0];
        Min = inf;
        Max = -inf;

        while (sa < NA - 1 && sb < NB - 1) {
            double La = Length(A[sa + 1] - pa);
            double Lb = Length(B[sb + 1] - pb);
            double t = min(La / lenA, Lb / lenB);

            Vector va = (A[sa + 1] - pa) / La * lenA * t;
            Vector vb = (B[sb + 1] - pb) / Lb * lenB * t;

            update(pa, pb, pb + vb - va);

            // pa = pa + delta_a

            pa = pa + va;
            pb = pb + vb;

            if(pa == A[sa + 1]) sa++;
            if(pb == B[sb + 1]) sb++;
        }
        printf("%.0lf\n", Max - Min);
    }
}