//
//  main.cpp
//  UrbanElevations
//
//  Created by zhangmin chen on 2019/4/19.
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

using namespace std;
typedef long long llong;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)

const int maxn = 100 + 5;
int n;

class Building {
public:
    int id;
    double x, y, w, d, h;
    
    bool operator < (const Building& rhs) const {
        //
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

Building blds[maxn];
double xv[maxn*2+1];

bool buiding_exist(int i, double pos) {
    if(blds[i].x <= pos && blds[i].x + blds[i].w >= pos) return true;
    else return false;
}

bool visible(int i, double pos) {
    if(!buiding_exist(i, pos)) return false;
    
    for(int k = 0; k < n; k++) {
        // check other buidings
        if(!buiding_exist(k, pos)) continue;
        
        if(blds[k].y < blds[i].y && blds[k].h >= blds[i].h) return false;
        
    }
    return true;
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase = 0;
    while(scanf("%d", &n) == 1 && n) {
        for(int i = 0; i < n; i++) {
            scanf("%lf%lf%lf%lf%lf", &blds[i].x, &blds[i].y, &blds[i].w, &blds[i].d, &blds[i].h);
            xv[i*2] = blds[i].x;
            xv[i*2+1] = blds[i].x + blds[i].w;
            blds[i].id = i+1;
        }
        
        // finished all building data
        sort(blds, blds+n);
        sort(xv, xv+n*2);
        
        int mx = (int)(unique(xv, xv+n*2) - xv);
        // check xv[0...mx]
        
        if(kase++) printf("\n");
        printf("For map #%d, the visible buildings are numbered as follows:\n", kase);
        printf("%d", blds[0].id);
        
        for(int i = 1; i < n; i++) {
            bool ok = false;
            
            for(int k = 0; k < mx-1; k++) {
                // xv[k]
                int avg = (xv[k] + xv[k+1]) / 2;
                if(visible(i, avg)) {
                    ok = true;
                    break;
                }
            }
            
            if(ok) printf(" %d", blds[i].id);
        }
        
        printf("\n");
    }
}
