//
//  main.cpp
//  nQueens01
//
//  Created by zhangmin chen on 2019/6/15.
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

const int maxn = 50;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

int col[maxn], tot = 0, n = 8;
int nc = 0;

void init() {
    Set(col, 0);
    tot = 0;
    nc = 0;
}

void search(int cur) {
    nc++;
    if(cur == n) tot++;
    else {
        _for(i, 0, n) {
            int ok = 1;
            col[cur] = i;
            
            _for(j, 0, cur) {
                if(col[j] == col[cur] || col[j] + j == col[cur] + cur || cur - col[cur] == j - col[j]) {
                    ok = 0;
                    break;
                }
            }
            
            if(ok) search(cur + 1);
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) && n) {
        init();
        search(0);
        printf("%d\n", tot);
        cout << endl;
    }
}
