#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int maxr = 25 + 5;
const int maxc = 25 + 5;
const int inf = 1000000000;
int vis[maxr][maxc][4][5], dist[maxr][maxc][4][5];
int R, C;
char maze[maxr][maxc];

int ans;

const int dr[] = {-1, 0, 1, 0};
const int dc[] = {0, -1, 0, 1};

struct Node {
    int row, col, dir, color;
    Node(int row, int col, int dir, int color) : row(row), col(col), dir(dir), color(color) {}
};

//Node beg, fin;
int sr, sc, tr, tc;
queue<Node> Q;


void getNext(Node nu, int v) {
    if(nu.row < 0 || nu.row >= R || nu.col < 0 || nu.col >= C) return;

    if(maze[nu.row][nu.col] == '.' && !vis[nu.row][nu.col][nu.dir][nu.color]) {
        vis[nu.row][nu.col][nu.dir][nu.color] = 1;
        dist[nu.row][nu.col][nu.dir][nu.color] = v;
        Q.push(nu);

        if(nu.row == tr && nu.col == tc && nu.color == 0)
            ans = min(ans, v);
    }
}

void bfs(Node u) {
    vis[u.row][u.col][u.dir][u.color] = 1;
    dist[u.row][u.col][u.dir][u.color] = 0;
    Q.push(u);


    while(!Q.empty()) {
        //
        u = Q.front(); Q.pop();
        // get next Q;
        int v = dist[u.row][u.col][u.dir][u.color] + 1;

        Node fwd( u.row+dr[u.dir], u.col+dc[u.dir], u.dir, (u.color+1)%5 );
        Node left( u.row, u.col, (u.dir+1)%4, u.color );
        Node right( u.row, u.col, (u.dir+3)%4, u.color );


        // getNext(Node& nu)  -> Q.push(nu)
        // judgement finish?
        // remember push next
        // if is exit, update ans -> ans = min(ans, v);

        getNext(left, v); getNext(right, v); getNext(fwd, v);
    }
}


int main() {
    int kase = 0;
    while(scanf("%d%d", &R, &C) == 2 && R) {
        // get position of start and fin
        for(int i = 0; i < R; i++) {
            scanf("%s", maze[i]);
            for(int j = 0; j < C; j++) {
                //
                if(maze[i][j] == 'S') { sr = i; sc = j; }
                else if(maze[i][j] == 'T') { tr = i; tc = j; }
            }
        }
        maze[sr][sc] = maze[tr][tc] = '.';

        memset(vis, 0, sizeof(vis));
        memset(dist, 0, sizeof(dist));

        ans = inf;
        bfs(Node(sr, sc, 0, 0));
//        cout << ans << endl;
        if(kase > 0)
            printf("\n");
        printf("Case #%d\n", ++kase);
        if(ans == inf)
            cout << "destination not reachable" << endl;
        else
            printf("minimum time = %d sec\n", ans);
    }
}