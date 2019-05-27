//
//  main.cpp
//  LA3670
//
//  Created by zhangmin chen on 2019/3/3.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

#define debug(x) cout << #x << ": " << x << endl
#define Set(x, v) memset(x, v, sizeof(x))
#define REP(i, l, r) for(int i = (l); i <= (r); i++)
#define FOR(i, l, r) for(int i = (l); i < (r); i++)

using namespace std;
const int maxn = 24;

int read() {
    int x;
    scanf("%d", &x);
    return x;
}

bool inRange(int x, int l, int r) {
    return l > r ? inRange(x, r, l) : (l <= x && x <= r);
}

int grid[maxn][maxn];
int dist[maxn][maxn][maxn];
// dist(x, y, ob) = dist_pre + 1;


// struct
int k, m, n;
struct POS {
    int x, y, ob;
    POS(int x, int y) : x(x), y(y) {}
};

bool operator== (const POS& a, const POS& b) {
    return a.x == b.x && a.y == b.y;
}


const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};


int bfs() {
    // x: m    y: n
    POS from(0, 0); POS to(m-1, n-1);
    from.ob = 0;
    Set(dist, -1);
    
    queue<POS> que;
    que.push(from);
    dist[from.x][from.y][from.ob] = 0;
    
    while(!que.empty()) {
        POS& f = que.front(); que.pop();
        //debug(dist[f.x][f.y][f.ob]);
        if(f == to) return dist[f.x][f.y][f.ob];
        int d = dist[f.x][f.y][f.ob];
        
        for(int i = 0; i < 4; i++) {
            int nx = f.x + dx[i];
            int ny = f.y + dy[i];
            
            if(!inRange(nx, 0, m-1) || !inRange(ny, 0, n-1)) continue;
            if(grid[nx][ny] == 1 && f.ob + 1 > k) continue;
            int nob = (grid[nx][ny] == 1) ? f.ob + 1 : 0;
            // i made a bug here
            //debug(nob);
            
            //POS nxt(nx, ny);
            //nxt.ob = nob;
            if(dist[nx][ny][nob] == -1) {
                dist[nx][ny][nob] = d+1;
                POS nxt(nx, ny);
                nxt.ob = nob;
                que.push(nxt);
            }
        }
    }
    return -1;
}

int main() {
    //
    freopen("input.txt", "r", stdin);
    int kase = read();
    while(kase--) {
        m = read();
        n = read();
        k = read();
        // m lines, n cols
        
        for(int i = 0; i < m; i++)
            for(int j = 0; j < n; j++)
                grid[i][j] = read();
        
        // then bfs()
        int ans = bfs();
        printf("%d\n", ans);
    }
}

