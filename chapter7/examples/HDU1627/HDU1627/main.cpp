//
//  main.cpp
//  HDU1627
//
//  Created by zhangmin chen on 2019/6/20.
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

const int maxn = 100;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

int S[maxn], n, L;
int cnt = 0;

void init() {
    Set(S, 0);
    cnt = 0;
}

int OK(int cur) {
    for(int len = 1; len*2 <= cur+1; len++) {
        int equal = 1;
        _for(i, 0, len) {
            if(S[cur-i] != S[cur-i-len]) {
                equal = 0;
                break;
            }
        }
        if(equal) return 0;
    }
    return 1;
}

int dfs(int cur) {
    if(cnt++ == n) {
        _for(i, 0, cur) {
            if(i % 64 == 0 && i > 0) printf("\n");
            else if(i % 4 == 0 && i > 0) printf(" ");
            
            printf("%c", 'A' + S[i]);
        }
        printf("\n%d\n", cur);
        return 0;
    } else {
        _for(i, 0, L) {
            S[cur] = i;
            if(OK(cur) && !dfs(cur + 1)) return 0;
        }
    }
    return 1;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d%d", &n, &L) == 2 && n > 0) {
        //
        init();
        dfs(0);
    }
}
