//
//  main.cpp
//  UVA10384
//
//  Created by zhangmin chen on 2019/8/4.
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
#include <bitset>
#include <assert.h>
#include <unordered_set>

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

const int R = 4, C = 6;
const string CH = "WNES";

const int dx[] = {0, -1, 0, 1};
const int dy[] = {-1, 0, 1, 0};
const int rev[] = {2, 3, 0, 1};

int sx = 0, sy = 0;

int vis[R][C];
int grid[R][C];

vector<char> paths;

void init() {
    Set(grid, 0);
}

void initVis() {
    paths.clear();
    Set(vis, 0);
}

void setbit(int& x, int b, bool flag) {
    if(flag) x |= (1 << b);
    else x &= ~(1 << b);
}
bool getbit(const int x, const int b) {
    return (x & (1 << b)) > 0;
}

bool valid(int x, int y) {
    return 0 <= x && x < R && 0 <= y && y < C;
}

bool isExit(const int x, const int y, vector<char>& paths) {
    int p = grid[x][y];
    if(x == 0 && !getbit(p, 1)) {
        paths.push_back(CH[1]);
        return true;
    }
    
    if(x == R - 1 && !getbit(p, 3)) {
        paths.push_back(CH[3]);
        return true;
    }
    
    if(y == 0 && !getbit(p, 0)) {
        paths.push_back(CH[0]);
        return true;
    }
    
    if(y == C - 1 && !getbit(p, 2)) {
        paths.push_back(CH[2]);
        return true;
    }
    return false;
}

bool dfs(int x, int y, vector<char>& paths, int d, const int maxd) {
    if(isExit(x, y, paths)) return true;
    if(d >= maxd) return false;
    
    int& p = grid[x][y];
    _for(dir, 0, 4) {
        int nx = x + dx[dir], ny = y + dy[dir];
        if(!valid(nx, ny) || vis[nx][ny]) continue;
        
        int& np = grid[nx][ny];
        
        paths.push_back(CH[dir]);
        vis[nx][ny] = 1;
        
        // dfs next position
        if(!getbit(p, dir)) {
            if(dfs(nx, ny, paths, d + 1, maxd)) return true;
        }
        else if(!getbit(np, dir)) {
            // push the wall
            setbit(p, dir, 0); setbit(np, dir, 1); setbit(np, rev[dir], 0);
            // next next position will change because of the pushment
            
            int nnx = nx + dx[dir], nny = ny + dy[dir];
            
            if(valid(nnx, nny)) setbit(grid[nnx][nny], rev[dir], 1);
            if(dfs(nx, ny, paths, d + 1, maxd)) return true;
            if(valid(nnx, nny)) setbit(grid[nnx][nny], rev[dir], 0);
            
            setbit(p, dir, 1); setbit(np, dir, 0); setbit(np, rev[dir], 1);
        }
        
        paths.pop_back();
        vis[nx][ny] = 0;
    }
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    
    while (scanf("%d%d", &sy, &sx) == 2 && (sx || sy)) {
        init();
        _for(i, 0, R) _for(j, 0, C) scanf("%d", &grid[i][j]);
        
        sx--; sy--;
        
        int maxd = 1;
        for(maxd = 1; ; maxd++) {
            initVis();
            vis[sx][sy] = 1;
            if(dfs(sx, sy, paths, 0, maxd)) break;
            vis[sx][sy] = 0;
        }
        
        _for(i, 0, paths.size()) cout << paths[i];
        cout << endl;
    }
}
