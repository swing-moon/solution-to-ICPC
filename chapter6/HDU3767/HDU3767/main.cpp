//
//  main.cpp
//  HDU3767
//
//  Created by zhangmin chen on 2019/5/24.
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

const int maxn = 1000 + 10;
const double width = 1000.0;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

class Circle {
public:
    double x, y, r;
    Circle(double x_ = 0.0, double y_ = 0.0, double r_ = 0.0) : x(x_), y(y_), r(r_) {}
};

Circle circles[maxn];
bool vis[maxn];

void init() {
    Set(vis, 0);
}

bool intersect(int id1, int id2) {
    double dist = sqrt( (circles[id1].x - circles[id2].x) * (circles[id1].x - circles[id2].x) + (circles[id1].y - circles[id2].y) * (circles[id1].y - circles[id2].y) );
    return dist < (circles[id1].r + circles[id2].r);
}

int n;
double l, r;

void border(int u) {
    if(circles[u].x - circles[u].r < 0) {
        double dist = sqrt( (circles[u].r * circles[u].r) - (circles[u].x * circles[u].x) );
        l = min(l, circles[u].y - dist);
    }
    
    if(circles[u].x + circles[u].r > width) {
        double dist = sqrt( (circles[u].r * circles[u].r) - (width - circles[u].x) * (width - circles[u].x) );
        r = min(r, circles[u].y - dist);
    }
}

bool dfs(int u) {
    //
    if(vis[u]) return false;
    vis[u] = true;
    
    if(circles[u].y - circles[u].r < 0) return true;
    
    _for(i, 0, n) {
        if(i == u) continue;
        if(intersect(u, i) && dfs(i)) return true;
    }
    border(u);
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    while(scanf("%d", &n) == 1) {
        init();
        bool ok = true;
        l = r = width;
        
        _for(i, 0, n) {
            scanf("%lf%lf%lf", &circles[i].x, &circles[i].y, &circles[i].r);
        }
        
        _for(i, 0, n) {
            if(circles[i].y + circles[i].r >= width && dfs(i)) {
                ok = false;
                break;
            }
        }
        
        if(ok) printf("0.00 %.2lf %.2lf %.2lf\n", l, width, r);
        else printf("IMPOSSIBLE\n");
    }
}
