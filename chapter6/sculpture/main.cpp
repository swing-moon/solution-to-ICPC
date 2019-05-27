#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 50 + 5;
const int maxw = 1000 + 1;

int n, x0[maxn], y0[maxn], z0[maxn], x1[maxn], y1[maxn], z1[maxn];

// discretization related
int nx, ny, nz;
int xv[maxn*2], yv[maxn*2], zv[maxn*2];

const int dx[] = {1,-1,0,0,0,0};
const int dy[] = {0,0,1,-1,0,0};
const int dz[] = {0,0,0,0,1,-1};
int color[maxn*2][maxn*2][maxn*2];

struct Cell {
    int x, y, z;
    Cell(int x = 0, int y = 0, int z = 0) : x(x), y(y), z(z) {}

    bool valid() const {
        return x >= 0 && x < nx-1 && y >= 0 && y < ny-1 && z >= 0 && z < nz-1;
    }
    bool solid() const {
        return color[x][y][z] == 1;
    }
    bool visited() const {
        return color[x][y][z] == 2;
    }
    void setvis() const {
        color[x][y][z] = 2;
    }

    Cell neighbor(int dir) const {
        return Cell(x+dx[dir], y+dy[dir], z+dz[dir]);
    }

    int volume() const {
        return (xv[x+1]-xv[x]) * (yv[y+1]-yv[y]) * (zv[z+1]-zv[z]);
    }

    int area(int dir) const {
        if(dx[dir] != 0)  return (yv[y+1]-yv[y]) * (zv[z+1]-zv[z]);
        else if(dy[dir] != 0)  return (xv[x+1]-xv[x]) * (zv[z+1]-zv[z]);
        return (xv[x+1]-xv[x]) * (yv[y+1]-yv[y]);
    }
};

void discretize(int* x, int& n) {
    sort(x, x+n);
    n = unique(x, x+n) - x;
}

int ID(int* x, int n, int v) {
    return lower_bound(x, x+n, v) - x;
}

void floodfill(int& vm, int& cm) {
    vm = 0;
    cm = 0;
    Cell beg;
    beg.setvis();
    queue<Cell> q;
    q.push(beg);

    while(!q.empty()) {
        Cell c = q.front(); q.pop();
        vm += c.volume();

        for(int i = 0; i < 6; i++) {
            Cell next = c.neighbor(i);
            if(!next.valid()) continue;

            if(next.solid())    cm += next.area(i);
            else if(!next.visited()) {
                next.setvis();
                q.push(next);
            }
        }
    }

    vm = maxw * maxw * maxw - vm;
}

int main() {
    int T;
    scanf("%d", &T);

    while(T--) {
        xv[0] = yv[0] = zv[0] = 0;
        xv[1] = yv[1] = zv[1] = maxw;
        nx = ny = nz = 2;

        scanf("%d", &n);
        for(int i = 0; i < n; i++) {
            scanf("%d%d%d%d%d%d", &x0[i], &y0[i], &z0[i], &x1[i], &y1[i], &z1[i]);
            x1[i] += x0[i];  y1[i] += y0[i];  z1[i] += z0[i];
            xv[nx++] = x0[i];  xv[nx++] = x1[i];
            yv[ny++] = y0[i];  yv[ny++] = y1[i];
            zv[nz++] = z0[i];  zv[nz++] = z1[i];
        }
        discretize(xv, nx);
        discretize(yv, ny);
        discretize(zv, nz);

        //paint
        memset(color, 0, sizeof(color));
        for(int i = 0; i < n; i++) {
            int X1 = ID(xv, nx, x0[i]),  X2 = ID(xv, nx, x1[i]);
            int Y1 = ID(yv, ny, y0[i]),  Y2 = ID(yv, ny, y1[i]);
            int Z1 = ID(zv, nz, z0[i]),  Z2 = ID(zv, nz, z1[i]);

            for(int X = X1; X < X2; X++)
                for(int Y = Y1; Y < Y2; Y++)
                    for(int Z = Z1; Z < Z2; Z++)
                        color[X][Y][Z] = 1;
        }

        int cm, vm;
        floodfill(vm, cm);
        printf("%d %d\n", cm, vm);
    }
    return 0;
}