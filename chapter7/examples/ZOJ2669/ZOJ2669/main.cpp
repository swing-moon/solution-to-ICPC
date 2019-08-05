//
//  main.cpp
//  ZOJ2669
//
//  Created by zhangmin chen on 2019/7/7.
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

const int maxn = 10;
const int inf = 0x3f3f3f3f;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define _forDown(i, l, r) for(int i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }
#define _forPlus(i, l, d, r) for(int i = (l); i + d < (r); i++)


const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

class Grid {
public:
    int x, y;
    Grid(int _x = 0, int _y = 0) : x(_x), y(_y) {}
    
    bool operator< (const Grid& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

typedef set<Grid> Post;
set<Post> depth[maxn + 1];
// depth begin from [1, n]
int ans[maxn + 5][maxn + 5][maxn + 5];

int n, w, h;

void init() {
    Set(ans, 0);
    _for(i, 0, maxn) depth[i].clear();
}

void init2() {
    Post beg;
    beg.insert(Grid(0, 0));
    depth[1].insert(beg);
}

// from depth 1, then expand the solution tree

Post normalize(const Post& p) {
    Post p2;
    int minX = inf, minY = inf;
    
    for(auto& grid : p) {
        minX = min(minX, grid.x);
        minY = min(minY, grid.y);
    }
    
    for(auto& grid : p) {
        p2.insert(Grid(grid.x - minX, grid.y - minY));
    }
    return p2;
}

Post _rotate(const Post& p) {
    Post p2;
    for(auto& grid : p) {
        p2.insert(Grid(grid.y, -grid.x));
    }
    return normalize(p2);
}

Post _flip(const Post& p) {
    Post p2;
    for(auto& grid : p) {
        p2.insert(Grid(grid.x, -grid.y));
    }
    return normalize(p2);
}

// in dfs, if d == maxd, try to insert
// posture to depth[d]
bool tryInsert(Post p, int d) {
    _for(i, 0, 4) {
        p = _rotate(p);
        if(depth[d].count(p)) return false;
    }
    
    p = _flip(p);
    
    _for(i, 0, 4) {
        p = _rotate(p);
        if(depth[d].count(p)) return false;
    }
    
    depth[d].insert(p);
    return true;
}

//
void dfs(Post p, int d, int maxd) {
    if(d == maxd) {
        tryInsert(p, d);
        return;
    }
    
    for(auto grid : p) _for(dir, 0, 4) {
        Grid nxtG(grid.x + dx[dir], grid.y + dy[dir]);
        if(!p.count(nxtG)) {
            Post p2 = p;
            p2.insert(nxtG);
            dfs(p2, d+1, maxd);
        }
    }
}

void bfs(int d, int maxd) {
    queue<Post> que;
    for(auto p : depth[d]) que.push(p);
    
    while (!que.empty()) {
        Post f = que.front();
        que.pop();
        
        if(f.size() == maxd) {
            tryInsert(f, maxd);
            continue;
        }
        
        for(auto grid : f) _for(dir, 0, 4) {
            Grid nxtG(Grid(grid.x + dx[dir], grid.y + dy[dir]));
            if(!f.count(nxtG)) {
                Post p2 = f;
                p2.insert(nxtG);
                if(p2.size() <= maxd) que.push(p2);
            }
        }
    }
}


void printTable() {
    //
    init();
    init2();
    /*
    _rep(maxd, 2, maxn) for(auto p : depth[maxd - 1])
        dfs(p, maxd - 1, maxd);
     */
    _rep(maxd, 2, maxn) bfs(maxd - 1, maxd);
    
    _rep(n, 2, maxn) _rep(w, 1, maxn) _rep(h, 1, maxn) {
        int cnt = 0;
        
        for(auto p : depth[n]) {
            int maxX = 0, maxY = 0;
            for(auto grid : p) {
                maxX = max(maxX, grid.x);
                maxY = max(maxY, grid.y);
            }
            if(min(maxX, maxY) < min(w, h) && max(maxX, maxY) < max(w, h))
                cnt++;
        }
        
        ans[n][w][h] = cnt;
        //debug(ans[n][w][h]);
    }
    //for(auto g : depth[1]) for(auto p : g) cout << p.x << " " << p.y << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    printTable();
    
    while (scanf("%d%d%d", &n, &w, &h) == 3) {
        // solve()
        if(n == 1) {
            printf("1\n");
            continue;
        }
        
        printf("%d\n", ans[n][w][h]);
    }
    
}
