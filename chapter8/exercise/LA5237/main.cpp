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

const int maxn = 13;

class Point {
public:
    int x, y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}

    bool operator< (const Point& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }

    bool operator== (const Point& rhs) const {
        return x == rhs.x && y == rhs.y;
    }
};

Point operator+ (const Point& lhs, const Point& rhs) {
    return Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

Point operator- (const Point& lhs, const Point& rhs) {
    return Point(lhs.x - rhs.x, lhs.y - rhs.y);
}

Point rotate(const Point& s, const Point& r) {
    Point dv = s - r;
    Point ans = r + Point(dv.y, -dv.x);
    return ans;
}

class Line {
public:
    Point from, to;
    bool vertical;

    Line rot(const Point& r) {
        Line ret;
        ret.from = ::rotate(from, r);
        ret.to = ::rotate(to, r);
        return ret;
    }

    void normalize() {
        vertical = (from.x == to.x);
        if(vertical) {
            if(from.y > to.y) swap(from.y, to.y);
        }
        else {
            if(from.x > to.x) swap(from.x, to.x);
        }
    }
};

int n;
vector<Line> lines;

void init() {
    lines.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    while(cin >> n && n) {
        init();

        Line l;
        l.to = Point(1, 0);
        l.vertical = false;

        lines.push_back(l);

        int minY = l.from.y, maxY = l.from.y;
        int minX = l.from.x, maxX = l.to.x;
        // debug(maxX);

        Point st = l.from, rt = l.to;
        // s rotate around r

        //debug(lines.size());
        _for(i, 0, n) {
            int sz = lines.size();
            _for(j, 0, sz) {
                Line nl = lines[j].rot(rt);
                nl.normalize();
                lines.push_back(nl);
                // debug(lines.size());
            }
            rt = rotate(st, rt);
        }

        // rotate finished

        map<Point, char> mp;
        _for(i, 0, lines.size()) {
            Point& lp = lines[i].from;
            lp.x *= 2;
            if(lines[i].vertical) lp.x--;

            minX = min(minX, lp.x);
            maxX = max(maxX, lp.x);
            minY = min(minY, lp.y);
            maxY = max(maxY, lp.y);

            //debug(maxY);
            //debug(maxX);

            mp[lp] = lines[i].vertical ? '|' : '_';
        }

        // output
        // debug(minX);
        string buf;
        _forDown(y, maxY, minY) {
            buf.clear();
            _rep(x, minX, maxX) {
                Point cur(x, y);
                if(mp.count(cur)) buf += mp[cur];
                else buf += ' ';
            }
            while(*(buf.rbegin()) == ' ') buf.erase(buf.size() - 1);
            cout << buf << endl;
        }
        cout << '^' << endl;
    }
}