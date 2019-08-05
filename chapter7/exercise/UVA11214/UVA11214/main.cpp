//
//  main.cpp
//  UVA11214
//
//  Created by zhangmin chen on 2019/7/24.
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

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;

const int maxn = 10 + 1;

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

bool vis[4][maxn * 2];
bool tar[maxn][maxn];

int N, M;

void init() {
    Set(tar, 0);
}

void initVis() {
    Set(vis, 0);
}

bool guard() {
    _for(i, 0, N) {
        _for(j, 0, M) if(tar[i][j] && !vis[0][i] && !vis[1][j] && !vis[2][i + j] && !vis[3][j + N - i])
            return false;
    }
    return true;
}

bool dfs(int cur, int d, int maxd) {
    if(d == maxd) {
        if(guard()) return true;
        else return false;
    }
    
    _for(i, cur, N * M) {
        int x = i / M, y = i % M;
        int v0 = vis[0][x], v1 = vis[1][y], v2 = vis[2][x + y], v3 = vis[3][y + N - x];
        vis[0][x] = vis[1][y] = vis[2][x + y] = vis[3][y + N - x] = true;
        
        if(dfs(i + 1, d + 1, maxd)) return true;
        
        vis[0][x] = v0; vis[1][y] = v1; vis[2][x + y] = v2; vis[3][y + N - x] = v3;
    }
    return false;
}


int main() {
    freopen("input.txt", "r", stdin);
    int kase = 1;
    while(scanf("%d%d", &N, &M) == 2 && N) {
        init();
        _for(i, 0, N) {
            char line[maxn];
            scanf("%s", line);
            
            // printf("%s\n", line);
            _for(j, 0, M) if(line[j] == 'X') tar[i][j] = true;
        }
        /*
        _for(i, 0, N) {
            _for(j, 0, M) printf("%d", tar[i][j]);
            printf("\n");
        }
        */
        // input finished, get marked place
        // then dfs and ida star
        
        int maxd;
        for(maxd = 0; ; maxd++) {
            initVis();
            if(dfs(0, 0, maxd)) break;
        }
        printf("Case %d: %d\n", kase++, maxd);
    }
}
