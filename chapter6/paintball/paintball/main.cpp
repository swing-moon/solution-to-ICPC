//
//  main.cpp
//  paintball
//
//  Created by zhangmin chen on 2018/8/13.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>

using namespace std;
const int maxn = 1000 + 5;
const double width = 1000.0;
int n;
double Left, Right;
bool ok;
int vis[maxn];

struct point {
    double x, y, r;
    point(double x = 0.0, double y = 0.0, double r = 0.0):x(x),y(y),r(r) {}
}p[maxn];

bool intersect(int c1, int c2) {
    //intersect of two cycles
    return sqrt( (p[c1].x-p[c2].x) * (p[c1].x-p[c2].x) + (p[c1].y-p[c2].y) * (p[c1].y-p[c2].y) ) < (p[c1].r+p[c2].r);
}

void choose_cycle(int u) {
    //find the most North point!
    if(p[u].x - p[u].r < 0)
        Left = min(Left, p[u].y - sqrt( p[u].r*p[u].r - p[u].x*p[u].x ));
    if(p[u].x + p[u].r > width)
        Right = min(Right, p[u].y - sqrt( p[u].r*p[u].r - (width-p[u].x)*(width-p[u].x) ));
}

bool dfs(int u) {
    if(vis[u])  return false;
    // intersect cycles must not be previously visited!
    // No cycles!
    
    vis[u] = 1;
//    cout << u << "is being visited" << endl;
    if(p[u].y-p[u].r < 0)   return true;
    
    for(int i = 0; i < n; i++) {
        if(intersect(u, i) && dfs(i))   return true;
    }
    
    choose_cycle(u);
    return false;
}

int main() {
    while(scanf("%d", &n) == 1) {
        ok = true;  Left = Right = width;
        // North!
        memset(vis, 0, sizeof(vis));
        for(int i = 0; i < n; i++)
            scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].r);
        for(int i = 0; i < n; i++) {
            if(p[i].y+p[i].r >= width && dfs(i)) {  ok = false;  break;  }
        }
        
        if(ok)  printf("0.00 %.2lf %.2lf %.2lf\n", Left, width, Right);
        else  printf("IMPOSSIBLE\n");
    }
    return 0;
}
