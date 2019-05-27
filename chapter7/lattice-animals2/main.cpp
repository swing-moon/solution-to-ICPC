#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <set>
#include <map>
#include <algorithm>
#define inf 0x3f3f3f3f

using namespace std;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const int maxn = 10;
const int maxv = 150;

int n, w, h;

struct Cell {
    int x, y;
    Cell(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator < (const Cell &rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

typedef set<Cell> Poly;
set<Poly> depth[maxn+1];
int ans[maxn+5][maxn+5][maxn+5];
int res[maxn+5][maxv+5];

Poly normalize(const Poly &p) {
    Poly p2;
    int minX = inf, minY = inf;

    for(auto& c : p) {
        minX = min(minX, c.x);
        minY = min(minY, c.y);
    }

    for(auto& c : p) {
        p2.insert(Cell(c.x - minX, c.y - minY));
    }
    return p2;
}

Poly rotate(const Poly &p) {
    Poly p2;
    for(auto& c : p) {
        p2.insert(Cell(c.y, -c.x));
    }
    return normalize(p2);
}

Poly flip(const Poly &p) {
    Poly p2;
    for(auto& c : p) {
        p2.insert(Cell(c.x, -c.y));
    }
    return normalize(p2);
}

int getID(const Poly &p) {
    int ans = 0;
    for(auto& c : p) {
        ans += c.x * 10 + c.y;
    }
    return ans;
}

bool addPoly(Poly p) {
    // addPoly to depth[n]
    int pn = p.size();
    // if repeated, has visited! return
    // depth[pn].insert(p)


    for(int i = 0; i < 4; i++) {
        p = rotate(p);
        if(depth[pn].count(p)) return false;
    }

    p = flip(p);
    for(int i = 0; i < 4; i++) {
        p = rotate(p);
        if(depth[pn].count(p)) return false;
    }

    depth[pn].insert(p);
//    printf("%d depth data is %d \n", pn, getID(p));
    return true;
}

void dfs(const Poly& p) {
    if(p.size() == n) {
        addPoly(p);
        return;
    }

    for(auto& c : p) {
        for(int dir = 0; dir < 4; dir++) {
            Cell nextC(Cell(c.x + dx[dir], c.y + dy[dir]));
            if(!p.count(nextC)) {
                Poly p_next = p;
                p_next.insert(nextC);
                dfs(p_next);
            }
        }
    }
}

void print_table() {
    memset(ans, 0, sizeof(ans));
    Poly s;
    s.insert(Cell(0, 0));
    depth[1].insert(s);

    for(n = 2; n <= maxn; n++) {
        for(auto& p : depth[n-1]) {
            dfs(p);
        }
    }

    // enumerate
    for(n = 2; n <= maxn; n++) {
        for(int w = 1; w <= maxn; w++) {
            for(int h = 1; h <= maxn; h++) {
                int cnt = 0;

                for(auto& p : depth[n]) {
                    int maxX = 0, maxY = 0;
                    for(auto& c : p) {
                        maxX = max(maxX, c.x);
                        maxY = max(maxY, c.y);
                    }

                    if(min(maxX, maxY) < min(h, w) && max(maxX, maxY) < max(h, w))
                        cnt++;
                }

                ans[n][w][h] = cnt;
                res[n][w*10+h] = cnt;
            }
        }
    }
}

void print_res() {
    for(int i = 0; i <= 10; i++)
        for(int j = 0; j <= 150; j++)
            printf(",%d ", res[i][j]);
}

int main() {
    print_table();
    print_res();
    while(scanf("%d%d%d", &n, &w, &h) == 3) {
        if(n == 1) {
            printf("1\n");
            continue;
        }
        printf("%d\n", res[n][w*10+h]);
    }
}