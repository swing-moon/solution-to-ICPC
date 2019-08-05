//
//  main.cpp
//  POJ3523
//
//  Created by zhangmin chen on 2019/6/26.
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

const int maxn = 200;
const int maxs = 20;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }

const int dx[] = {-1, 0, 1, 0, 0};
const int dy[] = {0, -1, 0, 1, 0};

class Node{
public:
    int x, y;
    Node(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};

int from[3], to[3];
int deg[maxn], G[maxn][5];
Node nodes[maxn];
char grid[maxs][maxs];
int id[maxs][maxs];

int dist[maxn][maxn][maxn];
int color[maxn][maxn][maxn];

void init() {
    Set(from, 0);
    Set(to, 0);
    Set(deg, 0);
    Set(G, 0);
    Set(grid, 0);
    Set(id, 0);
    Set(dist, -1);
    Set(color, 0);
    
    _for(i, 0, maxn) {
        nodes[i].x = nodes[i].y = 0;
    }
}

int ID(int p1, int p2, int p3) {
    return (p1 << 16) | (p2 << 8) | p3;
}

void decode(int x, int& p1, int& p2, int& p3) {
    p1 = (x >> 16) & 0xff;
    p2 = (x >> 8) & 0xff;
    p3 = x & 0xff;
}

bool conflicit(int p1, int p2, int p12, int p22) {
    return p12 == p22 || (p1 == p22 && p2 == p12);
}

int bfs() {
    queue<int> queF;
    queue<int> queB;
    
    dist[from[0]][from[1]][from[2]] = 0;
    dist[to[0]][to[1]][to[2]] = 1;
    
    color[from[0]][from[1]][from[2]] = 1;
    color[to[0]][to[1]][to[2]] = 2;
    
    queF.push(ID(from[0], from[1], from[2]));
    queB.push(ID(to[0], to[1], to[2]));
    
    while (!queF.empty() || !queB.empty()) {
        int fSZ = (int)queF.size(), bSZ = (int)queB.size();
        
        while (fSZ--) {
            //
            int x = queF.front(); queF.pop();
            int p1, p2, p3;
            decode(x, p1, p2, p3);
            
            _for(i, 0, deg[p1]) {
                int p12 = G[p1][i];
                
                _for(j, 0, deg[p2]) {
                    int p22 = G[p2][j];
                    
                    if(conflicit(p1, p2, p12, p22)) continue;
                    
                    _for(k, 0, deg[p3]) {
                        int p32 = G[p3][k];
                        if(conflicit(p1, p3, p12, p32) || conflicit(p2, p3, p22, p32)) continue;
                        
                        if(color[p12][p22][p32] == 0) {
                            dist[p12][p22][p32] = dist[p1][p2][p3] + 1;
                            color[p12][p22][p32] = 1;
                            queF.push(ID(p12, p22, p32));
                        } else if(color[p12][p22][p32] == 2)
                            return dist[p12][p22][p32] + dist[p1][p2][p3];
                    }
                }
            }
        }
        
        while (bSZ--) {
            //
            int x = queB.front(); queB.pop();
            int p1, p2, p3;
            decode(x, p1, p2, p3);
            
            _for(i, 0, deg[p1]) {
                int p12 = G[p1][i];
                
                _for(j, 0, deg[p2]) {
                    int p22 = G[p2][j];
                    
                    if(conflicit(p1, p2, p12, p22)) continue;
                    
                    _for(k, 0, deg[p3]) {
                        int p32 = G[p3][k];
                        
                        if(conflicit(p1, p3, p12, p32) || conflicit(p2, p3, p22, p32)) continue;
                        
                        if(color[p12][p22][p32] == 0) {
                            dist[p12][p22][p32] = dist[p1][p2][p3] + 1;
                            color[p12][p22][p32] = 2;
                            queB.push(ID(p12, p22, p32));
                        } else if(color[p12][p22][p32] == 1)
                            return dist[p12][p22][p32] + dist[p1][p2][p3];
                    }
                }
            }
        }
    }
    
    return -1;
}

int main() {
    freopen("input.txt", "r", stdin);
    
    int w, h, n;
    while(scanf("%d%d%d\n", &w, &h, &n) == 3 && n) {
        init();
        _for(i, 0, h) fgets(grid[i], 20, stdin);
        
         // debugArr(grid, h, w);
        int cnt = 0;
        _for(i, 0, h) _for(j, 0, w) {
            if(grid[i][j] == '#') continue;
            
            nodes[cnt].x = i; nodes[cnt].y = j;
            id[i][j] = cnt;
            
            if(islower(grid[i][j])) from[grid[i][j] - 'a'] = cnt;
            else if(isupper(grid[i][j])) to[grid[i][j] - 'A'] = cnt;
            
            cnt++;
        }
        
        // build graph:
        _for(i, 0, cnt) {
            _for(d, 0, 5) {
                int nx = nodes[i].x + dx[d];
                int ny = nodes[i].y + dy[d];
                if(grid[nx][ny] == '#') continue;
                
                G[i][deg[i]++] = id[nx][ny];
            }
        }
        
        if(n <= 2) {
            deg[cnt] = 1; G[cnt][0] = cnt; from[2] = to[2] = cnt++;
        }
        if(n <= 1) {
            deg[cnt] = 1; G[cnt][0] = cnt; from[1] = to[1] = cnt++;
        }
        
        printf("%d\n", bfs());
    }
}
