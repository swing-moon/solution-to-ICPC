#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

struct Cell {
    int x, y;
    Cell(int x = 0, int y = 0) : x(x), y(y) {}

    bool operator < (const Cell& rhs) const {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }
};

typedef set<Cell> Polyomino;

#define FOR_CELL(c, p) for(Polyomino::const_iterator c = (p).begin(); c != (p).end(); c++)

inline Polyomino normalize(const Polyomino &p) {
    int minX = p.begin()->x, minY = p.begin()->y;

    FOR_CELL(c, p) {
        minX = min(minX, c->x);
        minY = min(minY, c->y);
    }

    Polyomino p2;
    FOR_CELL(c, p) {
        p2.insert(Cell(c->x - minX, c->y - minY));
    }
    return p2;
}

inline Polyomino rotate(const Polyomino &p) {
    Polyomino p2;
    FOR_CELL(c, p) {
        p2.insert(Cell(c->y, -c->x));
    }
    return normalize(p2);
}

inline Polyomino flip(const Polyomino &p) {
    Polyomino p2;
    FOR_CELL(c, p) {
        p2.insert(Cell(c->x, -c->y));
    }
    return normalize(p2);
}

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const int maxn = 10;

set<Polyomino> depth[maxn+1];
int ans[maxn+1][maxn+1][maxn+1];

void addPoly2Depth(const Polyomino &p0, const Cell& c) {
    Polyomino p = p0;
    p.insert(c);
    p = normalize(p);

    int n = p.size();
    // check if dupling
    for(int i = 0; i < 4; i++) {
        if(depth[n].count(p) != 0) return;
        p = rotate(p);
    }

    p = flip(p);
    for(int i = 0; i < 4; i++) {
        if(depth[n].count(p) != 0) return;
        p = rotate(p);
    }

    depth[n].insert(p);
}

void getData() {
    Polyomino s;
    s.insert(Cell(0, 0));
    depth[1].insert(s);

    // create depth search tree
    for(int n = 2; n <= maxn; n++) {
        for(set<Polyomino>::iterator p = depth[n-1].begin(); p != depth[n-1].end(); p++) {
            // FOR_CELL() (c->x, c->y) each cell
            FOR_CELL(c, *p) {
                for(int dir = 0; dir < 4; dir++) {
                    Cell newc(Cell(c->x + dx[dir], c->y + dy[dir]));
                    if(p->count(newc) == 0) addPoly2Depth(*p, newc);
                }
            }
        }
    }

    // calculate answer
    for(int n = 1; n <= maxn; n++)
        for(int w = 1; w <= maxn; w++)
            for(int h = 1; h <= maxn; h++) {
                int cnt = 0;

                for(set<Polyomino>::iterator p = depth[n].begin(); p != depth[n].end(); p++) {
                    int maxX = 0, maxY = 0;
                    //find the maxX and maxY in the poly, which block strech the furthest?
                    FOR_CELL(c, *p) {
                        // we have already normalized, check the max value
                        maxX = max(maxX, c->x);
                        maxY = max(maxY, c->y);
                    }

                    if(min(maxX, maxY) < min(h, w) && max(maxX, maxY) < max(h, w))
                        cnt++;
                }
                ans[n][w][h] = cnt;
            }

}

int main() {
    getData();

    int n, w, h;
    while(scanf("%d%d%d", &n, &w, &h) == 3) {
        printf("%d\n", ans[n][w][h]);
    }
    return 0;
}