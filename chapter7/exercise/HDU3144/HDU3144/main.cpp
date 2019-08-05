//
//  main.cpp
//  HDU3144
//
//  Created by zhangmin chen on 2019/7/28.
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

const int maxn = 7 + 5;

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

int tar[maxn][maxn];
int cur[maxn][maxn];
char sign[maxn][maxn];

int pa[maxn * maxn];
int n;

void initSet() {
    _for(i, 0, maxn * maxn) pa[i] = i;
}

int findSet(int x) {
    return x == pa[x] ? x : findSet(pa[x]);
}

void init() {
    Set(tar, -1);
    Set(cur, 0);
    Set(sign, 0);
}

bool ok(int p) {
    int x = p / n, y = p % n;
    //
    if(tar[x][y] != -1 && tar[x][y] != cur[x][y]) return false;
    if(x == n - 1 && tar[x + 1][y] != -1 && tar[x + 1][y] != cur[x + 1][y]) return false;
    if(y == n - 1 && tar[x][y + 1] != -1 && tar[x][y + 1] != cur[x][y + 1]) return false;
    if(x == n - 1 && y == n - 1 && tar[x + 1][y + 1] != -1 && tar[x + 1][y + 1] != cur[x + 1][y + 1]) return false;
    
    return true;
}

bool dfs(int p) {
    if(p == n * n) return true;
    
    int x = p / n, y = p % n;
    
    // code: (x + p)
    // try to put (x + p) with '/'
    sign[x][y] = '/';
    int pa1 = findSet(x + p + 1);
    int pa2 = findSet(x + p + 1 + n);
    
    if(pa1 != pa2) {
        int tmp = pa[pa1];
        pa[pa1] = pa2;
        cur[x][y + 1]++;
        cur[x + 1][y]++;
        
        if(ok(p) && dfs(p + 1)) return true;
        
        cur[x + 1][y]--;
        cur[x][y + 1]--;
        pa[pa1] = tmp;
    }
    
    sign[x][y] = '\\';
    pa1 = findSet(x + p);
    pa2 = findSet(x + p + n + 2);
    
    if(pa1 != pa2) {
        int tmp = pa[pa1];
        pa[pa1] = pa2;
        cur[x][y]++;
        cur[x + 1][y + 1]++;
        
        if(ok(p) && dfs(p + 1)) return true;
        
        cur[x + 1][y + 1]--;
        cur[x][y]--;
        pa[pa1] = tmp;
    }
    
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    // int kase;
    // scanf("%d", &kase);
    
    while (scanf("%d", &n) != EOF) {
        //
        init();
        initSet();
        // scanf("%d", &n);
        
        _for(i, 0, n + 1) _for(j, 0, n + 1) {
            char ch;
            cin >> ch;
            
            if(ch == '.') tar[i][j] = -1;
            else tar[i][j] = ch - '0';
        }
        
        /*
        _for(i, 0, n + 1) {
            _for(j, 0, n + 1) printf("% 2d", tar[i][j]);
            printf("\n");
        }
        */
        
        // input finished, then dfs
        
        dfs(0);
        _for(i, 0, n) {
            _for(j, 0, n) cout << sign[i][j];
            printf("\n");
        }
    }
}
