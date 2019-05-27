//
//  main.cpp
//  morning-halloween
//
//  Created by zhangmin chen on 2018/9/30.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <queue>

using namespace std;

const int maxs = 20;
const int maxn = 200;
const int dx[] = {-1, 1, 0, 0, 0};
const int dy[] = {0, 0, -1, 1, 0};

int beg[3], dest[3];
int deg[maxn], G[maxn][5];

inline int ID(int a, int b, int c) {
    return (a << 16) | (b << 8) | c;
}

inline bool confict(int a, int b, int a2, int b2) {
    return a2 == b2 || (a == b2 && b == a2);
}

int d[maxn][maxn][maxn];

int bfs() {
    queue<int> q;
    memset(d, -1, sizeof(d));
    q.push(ID(beg[0], beg[1], beg[2]));
    d[beg[0]][beg[1]][beg[2]] = 0;
    // (beg[0], beg[1], beg[2]) = (cnt1, cnt2, cnt3)
    // means position id
    
    while(!q.empty()) {
        int u = q.front(); q.pop();
        int p1 = (u >> 16) & 0xff, p2 = (u >> 8) & 0xff, p3 = u & 0xff;
        //decoding!
        
        if(p1 == dest[0] && p2 == dest[1] && p3 == dest[2]) return d[p1][p2][p3];
        
        for(int i = 0; i < deg[p1]; i++) {
            int p12 = G[p1][i];
            for(int j = 0; j < deg[p2]; j++) {
                int p22 = G[p2][j];
                if(confict(p1, p2, p12, p22)) continue;
                
                for(int k = 0; k < deg[p3]; k++) {
                    int p32 = G[p3][k];
                    if(confict(p1, p3, p12, p32))   continue;
                    if(confict(p2, p3, p22, p32))   continue;
                    if(d[p12][p22][p32] != -1)  continue;
                    
                    d[p12][p22][p32] = d[p1][p2][p3] + 1;
                    q.push(ID(p12, p22, p32));
                }
            }
        }
    }
    return -1;
}

int main() {
    int w, h, n;
    
    while(scanf("%d%d%d\n", &w, &h, &n) == 3 && n) {
        char maze[maxs][maxs];
        for(int i = 0; i < h; i++)
            fgets(maze[i], 20, stdin);
        
        //extract available hole
        int cnt, x[maxn], y[maxn], id[maxs][maxs];
        cnt = 0;
        for(int i = 0; i < h; i++) {
            for(int j = 0; j < w; j++) {
                if(maze[i][j] != '#') {
                    x[cnt] = i; y[cnt] = j; id[i][j] = cnt;
                    if(islower(maze[i][j])) beg[maze[i][j] - 'a'] = cnt;
                    else if(isupper(maze[i][j])) dest[maze[i][j] - 'A'] = cnt;
                    cnt++;
                }
            }
        }
        
        //build graph
        for(int i = 0; i < cnt; i++) {
            deg[i] = 0;
            for(int dir = 0; dir < 5; dir++) {
                int nx = x[i] + dx[dir], ny = y[i] + dy[dir];
                
                if(maze[nx][ny] != '#') G[i][deg[i]++] = id[nx][ny];
            }
        }
        
        // add fake nodes, there is a circle of a node
        if(n <= 2) {
            deg[cnt] = 1; G[cnt][0] = cnt; beg[2] = dest[2] = cnt++;
        }
        if(n <= 1) {
            deg[cnt] = 1; G[cnt][0] = cnt; beg[1] = dest[1] = cnt++;
        }
        
        printf("%d\n", bfs());
    }
    return 0;
}

