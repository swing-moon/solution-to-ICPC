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

const double eps = 1e-6;
const double PI = acos(-1);

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

/***** solve circle problem *******/

class Circle {
public:
    Point c;
    double r;
    Circle(Point c, double r) : c(c), r(r) {}
    Point point(double rad) {
        return Point(c.x + r * cos(rad), c.y + r * sin(rad));
    }
};

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

int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point>& sol) {
    double d = Length(C1.c - C2.c);
    if(dcmp(d) == 0) {
        if(dcmp(C1.r - C2.r) == 0) return -1;
        return 0;
    }

    if(dcmp(C1.r + C2.r - d) < 0) return 0;
    if(dcmp(fabs(C1.r - C2.r) - d) > 0) return 0;

    double a = angle(C2.c - C1.c);
    double da = acos((C1.r * C1.r + d * d - C2.r * C2.r) / (2 * C1.r * d));

    Point p1 = C1.point(a - da), p2 = C1.point(a + da);

    sol.push_back(p1);
    if(p1 == p2) return 1;
    sol.push_back(p2);
    return 2;
}

// find circumscribedCircle
Circle circumscribedCircle(Point p1, Point p2, Point p3) {
    double Bx = p2.x - p1.x, By = p2.y - p1.y;
    double Cx = p3.x - p1.x, Cy = p3.y - p1.y;
    double D = 2 * (Bx * Cy - By * Cx);
    double cx = p1.x + (Cy * (Bx * Bx + By * By) - By * (Cx * Cx + Cy * Cy)) / D;
    double cy = p1.y + (Bx * (Cx * Cx + Cy * Cy) - Cx * (Bx * Bx + By * By)) / D;
    Point p = Point(cx, cy);
    return Circle(p, Length(p1 - p));
}

// find inscribedCircle
Circle inscribedCircle(Point p1, Point p2, Point p3) {
    double a = Length(p2 - p3);
    double b = Length(p3 - p1);
    double c = Length(p1 - p2);

    Point p = (p1 * a + p2 * b + p3 * c) / (a + b + c);
    return Circle(p, distanceToLine(p, p1, p2));
}

void format(const Circle& C) {
    printf("(%.6lf,%.6lf,%.6lf)\n", C.c.x, C.c.y, C.r);
}

// formatting rad
double lineAngleDegree(const Vector& v) {
    double ang = angle(v) * 180.0 / PI;
    while (dcmp(ang) < 0) ang += 360;
    while (dcmp(ang - 180) >= 0) ang -= 180;
    return ang;
}

// from one point p, get tangents
int getTangents(Point p, Circle C, Vector* v) {
    Vector u = C.c - p;
    double dist = Length(u);
    if(dist < C.r) return 0;
    else if(dcmp(dist - C.r) == 0) {
        v[0] = Rotate(u, PI / 2);
        return 1;
    }
    else {
        double ang = asin(C.r / dist);
        v[0] = Rotate(u, -ang);
        v[1] = Rotate(u, ang);
        return 2;
    }
}

void format(vector<double>& ans) {
    int n = ans.size();
    sort(ans.begin(), ans.end());

    printf("[");

    if(n) {
        printf("%.6lf", ans[0]);
        _for(i, 1, n) printf(",%.6lf", ans[i]);
    }

    printf("]\n");
}

// CircleThroughAPointAndTangentToALineWithRadius
// first we constructLine

Line getLine(double x1, double y1, double x2, double y2) {
    Point p1(x1, y1);
    Point p2(x2, y2);
    return Line(p1, p2 - p1);
}

vector<Point> CircleThroughAPointAndTangentToALineWithRadius(Point p, Line L, double r) {
    vector<Point> ans;
    double t1, t2;

    getLineCircleIntersection(L.move(-r), Circle(p, r), t1, t2, ans);
    getLineCircleIntersection(L.move(r), Circle(p, r), t1, t2, ans);

    //debug(ans.size());
    return ans;
}

void format(vector<Point> ans) {
    int n = ans.size();
    sort(ans.begin(), ans.end());
    printf("[");
    if(n) {
        printf("(%.6lf,%.6lf)", ans[0].x, ans[0].y);
        _for(i, 1, n) printf(",(%.6lf,%.6lf)", ans[i].x, ans[i].y);
    }

    printf("]\n");
}

// CircleTangentToTwoLinesWithRadius

Point getLineIntersection(Line a, Line b) {
    return getLineIntersection(a.p, a.v, b.p, b.v);
}

vector<Point> CircleTangentToTwoLinesWithRadius(Line a, Line b, double r) {
    vector<Point> ans;
    Line L1 = a.move(-r), L2 = a.move(r);
    Line L3 = b.move(-r), L4 = b.move(r);

    ans.push_back(getLineIntersection(L1, L3));
    ans.push_back(getLineIntersection(L1, L4));
    ans.push_back(getLineIntersection(L2, L3));
    ans.push_back(getLineIntersection(L2, L4));
    return ans;
}

// CircleTangentToTwoDisjointCirclesWithRadius
vector<Point> CircleTangentToTwoDisjointCirclesWithRadius(Circle c1, Circle c2, double r) {
    vector<Point> ans;
    Vector vtmp = c2.c - c1.c;
    double dist = Length(vtmp);

    int d = dcmp(dist - c1.r - c2.r - 2 * r);
    if(d > 0) return ans;
    getCircleCircleIntersection(Circle(c1.c, c1.r + r), Circle(c2.c, c2.r + r), ans);
    return ans;
}

int main() {
    freopen("input.txt", "r", stdin);
    string cmd;
    while (cin >> cmd) {
        double x1, y1, x2, y2, x3, y3, x4, y4, xp, yp, xc, yc, r1, r2, r;
        if(cmd == "CircumscribedCircle") {
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            format(circumscribedCircle(Point(x1, y1), Point(x2, y2), Point(x3, y3)));
        }
        if(cmd == "InscribedCircle") {
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
            format(inscribedCircle(Point(x1, y1), Point(x2, y2), Point(x3, y3)));
        }
        if(cmd == "TangentLineThroughPoint") {
            cin >> xc >> yc >> r >> xp >> yp;
            Vector vec[2];
            vector<double> ans;
            int cnt = getTangents(Point(xp, yp), Circle(Point(xc, yc), r), vec);
            _for(i, 0, cnt) ans.push_back(lineAngleDegree(vec[i]));
            format(ans);
        }
        if(cmd == "CircleThroughAPointAndTangentToALineWithRadius") {
            cin >> xp >> yp >> x1 >> y1 >> x2 >> y2 >> r;
            format(CircleThroughAPointAndTangentToALineWithRadius(Point(xp, yp), getLine(x1, y1, x2, y2), r));
        }
        if(cmd == "CircleTangentToTwoLinesWithRadius") {
            cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3 >> x4 >> y4 >> r;
            format(CircleTangentToTwoLinesWithRadius(getLine(x1, y1, x2, y2), getLine(x3, y3, x4, y4), r));
        }
        if(cmd == "CircleTangentToTwoDisjointCirclesWithRadius") {
            cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2 >> r;
            format(CircleTangentToTwoDisjointCirclesWithRadius(Circle(Point(x1, y1), r1), Circle(Point(x2, y2), r2), r));
        }
    }
}