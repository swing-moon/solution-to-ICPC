//
//  main.cpp
//  LA5197
//
//  Created by zhangmin chen on 2019/5/11.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

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

using namespace std;
typedef long long llong;
typedef set<string>::iterator ssii;

const double eps = 1e-7;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

class Point {
public:
    double x, y;
    Point(double x_ = 0.0, double y_ = 0.0) : x(x_), y(y_) {}
    
};

Point operator+ (const Point& lhs, const Point& rhs) {
    return Point(lhs.x + rhs.x, lhs.y + rhs.y);
}

Point operator- (const Point& lhs, const Point& rhs) {
    return Point(lhs.x - rhs.x, lhs.y - rhs.y);
}

Point operator* (const Point& lhs, double p) {
    return Point(lhs.x * p, lhs.y * p);
}

istream& operator>> (istream& is, Point& rhs) {
    return is >> rhs.x >> rhs.y;
}
double dist(const Point& lhs, const Point& rhs) {
    double tmp = (lhs.x - rhs.x) * (lhs.x - rhs.x) + (lhs.y - rhs.y) * (lhs.y - rhs.y);
    return sqrt(tmp);
}

int Minus_(double x) {
    //
    if(fabs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

int Minus(double x, double y) {
    return Minus_(x - y);
}

bool inRange(double x, double left, double right) {
    //
    if(Minus(left, right) > 0) return inRange(x, right, left);
    return Minus(left, x) <= 0 && Minus(x, right) <= 0;
}

bool inArea(const Point& p, const Point& lhs, const Point& rhs) {
    return inRange(p.x, lhs.x, rhs.x) && inRange(p.y, rhs.y, lhs.y);
    // made a bug here
}


class Map {
public:
    string name;
    Point p1, p2, center, corner;
    
    double width, height, area, ratio, minx;
    
    Map(string name_, Point p1_, Point p2_) {
        name = name_;
        p1 = p1_;
        p2 = p2_;
        
        center = (p1 + p2) * .5;
        width = fabs(p1.x - p2.x);
        height = fabs(p1.y - p2.y);
        ratio = fabs(height / width - 0.75);
        area = width * height;
        
        corner = Point(center.x + width / 2, center.y - height / 2);
        minx = center.x - width / 2;
    }
};

vector<Map> map_s;
map<string, Point> locats;

class Cmp {
public:
    Point loc;
    
    bool operator() (int lhs, int rhs) {
        //
        const Map& m1 = map_s[lhs];
        const Map& m2 = map_s[rhs];
        
        int d;
        
        d = Minus(m1.area, m2.area);
        if(d > 0) return true;
        if(d < 0) return false;
        
        d = Minus(dist(m1.center, loc), dist(m2.center, loc));
        if(d > 0) return true;
        if(d < 0) return false;
        
        d = Minus(m1.ratio, m2.ratio);
        if(d > 0) return true;
        if(d < 0) return false;
        
        d = Minus(dist(loc, m1.corner), dist(loc, m2.corner));
        if(d < 0) return true;
        if(d > 0) return false;
        
        d = Minus(m1.minx, m2.minx);
        if(d > 0) return true;
        if(d < 0) return false;
        
        return false;
    }
};

void getMapLevel(const Point pt, vector<int>& level, vector<int>& id) {
    //
    id.clear();
    
    Cmp cmp;
    cmp.loc = pt;
    
    _for(i, 0, map_s.size()) {
        const Map& mp = map_s[i];
        if(inArea(pt, mp.p1, mp.p2)) {
            id.push_back(i);
            // debug(inArea(pt, mp.p1, mp.p2));
        }
    }
    
    sort(id.begin(), id.end(), cmp);
    level.clear();
    level.assign(id.size(), 1);
    
    _for(i, 1, id.size()) {
        const Map& m1 = map_s[id[i-1]];
        const Map& m2 = map_s[id[i]];
        
        level[i] = level[i-1];
        int d = Minus(m2.area, m1.area);
        if(d < 0) level[i]++;
    }
}

void solve(const string& name, int lv) {
    //
    // vector<int> levels;
    
    cout << name << " at detail level " << lv;
    if(!locats.count(name)) {
        cout << " unknown location" << endl;
        return;
    }
    
    vector<int> ID, levels;
    getMapLevel(locats[name], levels, ID);
    
    if(ID.empty()) {
        cout << " no map contains that location" << endl;
        return;
    }
    
    int maxlv = levels.back();
    // debug(maxlv);
    if(maxlv < lv) {
        //
        cout << " no map at that detail level; using " << map_s[ID.back()].name << endl;
    } else {
        //
        int p = (int)(upper_bound(levels.begin(), levels.end(), lv) - levels.begin());
        cout << " using " << map_s[ID[p-1]].name << endl;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    string buf;
    getline(cin, buf);
    
    while (true) {
        string name;
        cin >> name;
        if(name == "LOCATIONS") break;
        
        Point p1_, p2_;
        cin >> p1_ >> p2_;
        // cout << p1_.x << " " << p1_.y << " " << p2_.x << " " << p2_.y << endl;
        Map mp(name, p1_, p2_);
        
        map_s.push_back(mp);
    }
    
    while(true) {
        string name;
        cin >> name;
        if(name == "REQUESTS") break;
        Point pt;
        cin >> pt;
        locats[name] = pt;
    }
    
    //_for(i, 0, map_s.size()) cout << map_s[i].name << " " << map_s[i].p1.x << endl;
    
    while (true) {
        string name;
        cin >> name;
        if(name == "END") break;
        int lv;
        cin >> lv;
        solve(name, lv);
    }
    return 0;
}
