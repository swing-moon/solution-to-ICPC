//
//  main.cpp
//  HDU2771
//
//  Created by zhangmin chen on 2019/3/4.
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

const int maxw = 1000 + 1;
const int maxn = 50 + 10;

const int dx[] = {1, -1, 0, 0, 0, 0};
const int dy[] = {0, 0, 1, -1, 0, 0};
const int dz[] = {0, 0, 0, 0, 1, -1};

int read() {
    int x; scanf("%d", &x); return x;
}


// get sculpture
int x0[maxn], y0[maxn], z0[maxn], x1[maxn], y1[maxn], z1[maxn];
int xs[maxn*2], ys[maxn*2], zs[maxn*2];
int nx, ny, nz;
// nx++, ny++, nz++

int color[maxn*2][maxn*2][maxn*2];


// discretize:
// x[0] is the smallest, x[1] is the largest
// x_from = getID(x, nx, x[0])   x_to = getID(x, nx, x[1])

// vol: (xs[i+1]-xs[i]) * (ys[i+1]-ys[i]) * (zs[i+1]-zs[i])
void discretize(int* x, int& n) {
    sort(x, x+n);
    n = unique(x, x+n) - x;
}

int getID(int* x, int n, int v) {
    return lower_bound(x, x+n, v) - x;
}


void init() {
    xs[0] = ys[0] = zs[0] = 0;
    xs[1] = ys[1] = zs[1] = maxw;
    nx = ny = nz = 2;
}


struct POS {
    int x, y, z;
    POS(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}
    
    bool inRange() const {
        return x >= 0 && x < nx-1 && y >= 0 && y < ny-1 && z >= 0 && z < nz-1;
    }
    
    POS neighbor(int dir) {
        return POS(x+dx[dir], y+dy[dir], z+dz[dir]);
    }
    // POS np = pos.neighbor(), if(!np.inRange()) continue
    
    bool solid() const {
        return color[x][y][z] == 1;
    }
    void setVis() {
        color[x][y][z] = 2;
    }

    bool isVisted() const {
        return color[x][y][z] == 2;
    }
    
    // if (!np.isVisited()) que.push(np)
    
    int volume() const {
        return (xs[x+1]-xs[x]) * (ys[y+1]-ys[y]) * (zs[z+1]-zs[z]);
    }
    
    int area(int dir) const {
        if(dx[dir] != 0) return (ys[y+1] - ys[y]) * (zs[z+1] - zs[z]);
        else if(dy[dir] != 0) return (xs[x+1] - xs[x]) * (zs[z+1] - zs[z]);
        return (xs[x+1] - xs[x]) * (ys[y+1] - ys[y]);
    }
};

void bfs(int& vm, int& cm) {
    vm = cm = 0;
    POS start;
    
    queue<POS> que;
    start.setVis();
    que.push(start);
    
    while(!que.empty()) {
        POS fr = que.front(); que.pop();
        vm += fr.volume();
        
        for(int i = 0; i < 6; i++) {
            POS np = fr.neighbor(i);
            if(!np.inRange()) continue;
            
            if(np.solid()) cm += np.area(i);
            else if(!np.isVisted()) {
                np.setVis();
                que.push(np);
            }
        }
    }
    //debug(maxw*maxw*maxw);
    //debug(vm);
    vm = maxw * maxw * maxw - vm;
}

int m;
int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    kase = read();
    
    while(kase--) {
        init();
        
        m = read();
        for(int i = 0; i < m; i++) {
            scanf("%d%d%d%d%d%d", &x0[i], &y0[i], &z0[i], &x1[i], &y1[i], &z1[i]);
            // I made a bug here
            //debug(x0[i]); debug(y0[i]); debug(z0[i]);
            x1[i] += x0[i]; y1[i] += y0[i]; z1[i] += z0[i];
            xs[nx++] = x0[i]; xs[nx++] = x1[i];
            ys[ny++] = y0[i]; ys[ny++] = y1[i];
            zs[nz++] = z0[i]; zs[nz++] = z1[i];
        }
        
        discretize(xs, nx);
        discretize(ys, ny);
        discretize(zs, nz);
        //debug(nx), debug(ny), debug(nz);
        
        // build sculpture"
        Set(color, 0);
        for(int i = 0; i < m; i++) {
            int xbeg = getID(xs, nx, x0[i]), xend = getID(xs, nx, x1[i]);
            //debug(xbeg), debug(xend);
            int ybeg = getID(ys, ny, y0[i]), yend = getID(ys, ny, y1[i]);
            int zbeg = getID(zs, nz, z0[i]), zend = getID(zs, nz, z1[i]);
            
            FOR(px, xbeg, xend) FOR(py, ybeg, yend) FOR(pz, zbeg, zend)
                color[px][py][pz] = 1;
            
        }
        
        // bfs():
        int cm, vm;
        bfs(vm, cm);
        
        printf("%d %d\n", cm, vm);
    }
}
