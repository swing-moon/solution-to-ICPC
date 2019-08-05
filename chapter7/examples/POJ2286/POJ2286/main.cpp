//
//  main.cpp
//  POJ2286
//
//  Created by zhangmin chen on 2019/6/30.
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

const int maxn = 24;
const int maxl = 2000;
const int inf = 2400;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define _forDown(i, l, r) for(int i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }

/*
         00    01
         02    03
   04 05 06 07 08 09 10
         11    12
   13 14 15 16 17 18 19
         20    21
         22    23
 */


const int revID[8] = {5, 4, 7, 6, 1, 0, 3, 2};
const int center[8] = {6, 7, 8, 11, 12, 15, 16, 17};

int line[8][7] = {
    {0, 2, 6, 11, 15, 20, 22},
    {1, 3, 8, 12, 17, 21, 23},
    {10, 9, 8, 7, 6, 5, 4},
    {19, 18, 17, 16, 15, 14, 13}
};

int v[maxn];
char res[maxl];

void addLine() {
    _for(i, 4, 8) _for(j, 0, 7) {
        line[i][j] = line[revID[i]][6-j];
    }
}

void init() {
    Set(v, 0);
    Set(res, 0);
}

bool finish() {
    _for(i, 0, 8) if(v[center[i]] != v[center[0]]) return false;
    return true;
}

int diff(int t) {
    int cnt = 0;
    _for(i, 0, 8) if(v[center[i]] != t) cnt++;
    return cnt;
}

int h() {
    int ans = inf;
    _rep(i, 1, 3) ans = min(ans, diff(i));
    return ans;
}

void mv(int dir) {
    int tmp = v[line[dir][0]];
    _for(i, 0, 6) v[line[dir][i]] = v[line[dir][i+1]];
    v[line[dir][6]] = tmp;
}

int dfs(int d, int maxd) {
    if(finish()) {
        res[d] = '\0';
        printf("%s\n", res);
        return true;
    }
    if(h() + d > maxd) return false;
    
    // then recurse:
    _for(dir, 0, 8) {
        res[d] = 'A' + dir;
        mv(dir);
        if(dfs(d+1, maxd)) return true;
        mv(revID[dir]);
    }
    
    return false;
}


int main() {
    //
    freopen("input.txt", "r", stdin);
    addLine();
    init();
    
    while (scanf("%d", &v[0]) == 1 && v[0]) {
        //init();
        
        _for(i, 1, maxn) scanf("%d", &v[i]);
        _for(i, 0, maxn) if(!v[i]) return 0;
        
        if(finish()) {
            printf("No moves needed\n");
        } else {
            int maxd = 1;
            for(maxd = 1; ; maxd++) {
                if(dfs(0, maxd)) break;
            }
        }
        printf("%d\n", v[6]);
        init();
    }
}
