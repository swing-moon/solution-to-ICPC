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

// computation Geometry header
const double eps = 1e-10;
const double PI = acos(-1);
const double PI2 = 2 * PI;

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

Vector Normal(Vector A) {
    double L = Length(A);
    return Vector(-A.y / L, A.x / L);
}


class Circle {
public:
    Point c;
    double r;
    Circle(Point c = {0.0, 0.0}, double r = 0.0) : c(c), r(r) {}
    Point point(double rad) {
        return Point(c.x + r * cos(rad), c.y + r * sin(rad));
    }
};

typedef Circle Pan;

class Line {
public:
    Point p;
    Vector v;

    Line(Point p, Vector v) : p(p), v(v) {}

    Point point(double t) {
        return p + v *  t;
    }
    Line move(double d) {
        return Line(p + Normal(v) * d, v);
    }
};

double angle(Vector v) {
    return atan2(v.y, v.x);
}

int getLineCircleIntersection(Line L, Circle C, double& t1, double& t2, vector<Point>& sol) {
    double a = L.v.x, b = L.p.x - C.c.x, c = L.v.y, d = L.p.y - C.c.y;
    double e = a * a + c * c, f = 2 * (a * b + c * d), g = (b * b + d * d - C.r * C.r);
    double delta = f * f - 4 * e * g;

    if(dcmp(delta) < 0) return 0;
    if(dcmp(delta) == 0) {
        t1 = t2 = -f / (2 * e);
        sol.push_back(L.point(t1));
        return 1;
    }

    t1 = (-f - sqrt(delta)) / (2 * e);
    sol.push_back(L.point(t1));
    t2 = (-f + sqrt(delta)) / (2 * e);
    sol.push_back(L.point(t2));

    return 2;
}

double Normalize(double rad, double base = PI) {
    return rad - PI2 * floor((rad + PI - base) / PI2);
}

void getCircleCircleIntersection(Circle C1, Circle C2, vector<double>& rad) {
    double d = Length(C1.c - C2.c);
    if(dcmp(d) == 0) {
        return;
    }

    if(dcmp(C1.r + C2.r - d) < 0) return;
    if(dcmp(fabs(C1.r - C2.r) - d) > 0) return;

    double a = angle(C2.c - C1.c);
    double da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));

    rad.push_back(Normalize(a - da));
    rad.push_back(Normalize(a + da));
}

typedef vector<Point> Polygon;

int isPointInPolygon(const Point& p, const Polygon& poly) {
    int n = poly.size();
    int wn = 0;

    _for(i, 0, n) {
        const Point& p1 = poly[i];
        const Point& p2 = poly[(i+1) % n];

        if(p1 == p || p2 == p || onSegment(p, p1, p2)) return -1;
        int k = dcmp(Cross(p2 - p1, p - p1));
        int d1 = dcmp(p1.y - p.y);;
        int d2 = dcmp(p2.y - p.y);
        if(k > 0 && d1 <= 0 && d2 > 0) wn++;
        if(k < 0 && d2 <= 0 && d1 > 0) wn--;
    }

    if(wn != 0) return 1;
    return 0;
}

// poly[a], poly[b]
// (poly[a], poly[b]) is diagonal
bool isDiagonal(const Polygon& poly, int a, int b) {
    int n = poly.size();
    _for(i, 0, n) {
        if(i != a && i != b && onSegment(poly[i], poly[a], poly[b])) return false;
    }

    _for(i, 0, n) {
        if(segmentProperIntersection(poly[i], poly[(i+1) % n], poly[a], poly[b])) return false;
    }

    Point midp = (poly[a] + poly[b]) * 0.5;
    return isPointInPolygon(midp, poly) == 1;
}


// then solve the problem
const int maxn = 100 + 5;
const int inf = 1e9;
double f[maxn][maxn];


void initdp(const Polygon& poly) {
    int n = poly.size();
    _for(i, 0, n) _for(j, 0, n) f[i][j] = -1;
}

double dp(const Polygon& poly) {
    int n = poly.size();
    _forDown(i, n - 2, 0) _for(j, i + 1, n) {
        if(i + 1 == j) f[i][j] = 0;
        else if(!(i == 0 && j == n - 1) && !isDiagonal(poly, i, j)) f[i][j] = inf;
        else {
            f[i][j] = inf;
            _for(k, i + 1, j) {
                double m = max(f[i][k], f[k][j]);
                double area = fabs(Cross(poly[j] - poly[i], poly[k] - poly[i])) * 0.5;
                m = max(m, area);
                f[i][j] = min(f[i][j], m);
            }
        }
    }
    return f[0][n - 1];
}

int main() {
    freopen("input.txt", "r", stdin);
    int T, N;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &N);
        double x, y;
        Polygon poly;

        _for(i, 0, N) {
            scanf("%lf%lf", &x, &y);
            poly.push_back(Point(x, y));
        }

        assert(poly.size() > 0);
        initdp(poly);
        printf("%.1lf\n", dp(poly));
    }
}