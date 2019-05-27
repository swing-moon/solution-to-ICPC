#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
const int maxr = 1000 + 5;
const int maxc = 1000 + 5;
const int inf = 0x3f3f3f3f;

int r, c, ans;
char maze[maxr][maxc];
const int dr[4] = {-1, 1, 0, 0};
const int dc[4] = {0, 0, -1, 1};

int d[maxr][maxc][2], vis[maxr][maxc][2];

struct Cell {
    int r, c;
    Cell(int r, int c) : r(r), c(c) {}
};

queue<Cell> path;

bool valid(int ir, int ic) {
    return ir >= 0 && ir < r && ic >= 0 && ic < c;
}

// bfs notice: all cell in queue, we set a mark vis[nodes in cell] = 1, then queue.push()
void bfs(int kind) {
    while(!path.empty()) {
        Cell u = path.front(); path.pop();
        int ir = u.r, ic = u.c;

        for(int i = 0; i < 4; i++) {
            int nr = ir + dr[i], nc = ic + dc[i];
            if(valid(nr, nc) && !vis[nr][nc][kind] && maze[nr][nc] == '.') {
                vis[nr][nc][kind] = 1;
                d[nr][nc][kind] = d[ir][ic][kind] + 1;
                path.push(Cell(nr, nc));
            }
        }
        // push()
    }
}

void data(int r, int c) {
    if(maze[r][c] != '.' || !vis[r][c][0]) return;
    if(!vis[r][c][1] || d[r][c][1] > d[r][c][0]) ans = min(ans, d[r][c][0] + 1);
}

int main() {
    int T;
    scanf("%d", &T);

    while(T--) {
        memset(d, 0, sizeof(d));
        memset(vis, 0, sizeof(vis));


        scanf("%d%d", &r, &c);
        // get fire start and John start
        // maybe there are many firing cells

        vector<Cell> fires;

        int si, sj;
        for(int i = 0; i < r; i++) {
            scanf("%s", maze[i]);
            for(int j = 0; j < c; j++) {
                if(maze[i][j] == 'J') { si = i; sj = j; maze[i][j] = '.'; }
                else if(maze[i][j] == 'F') { fires.push_back(Cell(i, j)); maze[i][j] = '.'; }
                // fires[i].r   fires[i].c
            }
        }

        // init john
        vis[si][sj][0] = 1;
        d[si][sj][0] = 0;
        path.push(Cell(si, sj));
        bfs(0);

        // init fire
        for(int i = 0; i < fires.size(); i++) {
            vis[fires[i].r][fires[i].c][1] = 1;
            d[fires[i].r][fires[i].c][1] = 0;
            path.push(fires[i]);
        }
        bfs(1);

        ans = inf;
        for(int i = 0; i < r; i++) {
            data(i, 0); data(i, c-1);
        }

        for(int j = 0; j < c; j++) {
            data(0, j); data(r-1, j);
        }

        if(ans < inf) cout << ans << endl;
        else if(ans == inf) cout << "IMPOSSIBLE" << endl;
    }
}