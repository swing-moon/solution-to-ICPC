//
//  main.cpp
//  UVA11846
//
//  Created by zhangmin chen on 2019/8/3.
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

const int maxn = 20 + 5;
const int inf = -1;

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

char grid[maxn][maxn];
char ans[maxn][maxn];
int N, K;


class DIR {
public:
    int w, h;
    DIR(int _w = 0, int _h = 0) : w(_w), h(_h) {}
};

void init() {
    Set(grid, '.');
    Set(ans, '.');
}

void dbg() {
    _for(i, 0, N) {
        _for(j, 0, N) printf("%c", grid[i][j]);
        printf("\n");
    }
    printf("\n");
}

void findSZ(const int u, vector<DIR>& dirs) {
    int x = u / N, y = u % N;
    int ey = N;
    // int tmp = 0;
    
    // [x, x + h] and [y, y + w]
    for(int h = 0; x + h < N; h++) for(int w = 0; y + w < ey; w++) {
        // find if valid through [x, x + h]  [y, y + w]
        int nx = x + h, ny = y + w;
        if(ans[nx][ny] != '.') {
            ey = ny;
            break;
        }
        
        int valid = 1, val = inf;
        // find digit in [x, x + h] [y, y + w]
        _rep(i, x, nx) {
            _rep(j, y, ny) {
                if(isdigit(grid[i][j])) {
                    if(val != inf) {
                        valid = false;
                        // tmp = j;
                        break;
                    }
                    else {
                        //
                        val = grid[i][j] - '0';
                        // tmp = j;
                    }
                }
            }
            if(!valid) break;
        }
        // [x, x + h] [y, y + w] find digit num
        
        int sz = (w + 1) * (h + 1);
        // debug(sz);
        // debug(val);
        if(valid && sz == val) {
            dirs.push_back(DIR(w, h));
            // debug(w);
            // debug(h);
            // cout << "====\n";
            // ey = tmp;
            // debug(tmp);
        }
        if(!valid) continue;
    }
}

bool dfs(int u, int id) {
    if(u == N * N) return true;
    if(ans[u / N][u % N] != '.') return dfs(u + 1, id);
    
    vector<DIR> dirs;
    findSZ(u, dirs);
    
    /*
    _for(i, 0, dirs.size()) {
        printf("(%d, %d) => (%d, %d)", u / N, u % N, dirs[i].h, dirs[i].w);
        printf("\n");
    }
    */
    
    int x = u / N, y = u % N;
    _for(k, 0, dirs.size()) {
        int w = dirs[k].w, h = dirs[k].h;
        
        _rep(i, x, x + h) _rep(j, y, y + w) {
            ans[i][j] = 'A' + id;
            // printf("%c", ans[i][j]);
        }
        // printf("finished\n");
        
        if(dfs(u + 1, id + 1)) return true;
        
        _rep(i, x, x + h) _rep(j, y, y + w) {
            ans[i][j] = '.';
        }
    }
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    while(scanf("%d%d", &N, &K) && (N || K)) {
        init();
        _for(i, 0, N) scanf("%s", grid[i]);
        
        //dbg();
        // input finished
        
        dfs(0, 0);
        _for(i, 0, N) {
            _for(j, 0, N) printf("%c", ans[i][j]);
            printf("\n");
        }
    }
}
