//
//  main.cpp
//  POJ1011
//
//  Created by zhangmin chen on 2019/8/2.
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

const int maxn = 100;

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


int used[maxn], len = 0;
int a[maxn], n, cnt;

void init() {
    Set(a, 0);
    len = 0;
}

void initVis() {
    Set(used, 0);
}

bool cmp(int lhs, int rhs) {
    return lhs > rhs;
}

bool dfs(int d, int curlen, int last) {
    //
    if(d > cnt) return true;
    if(curlen == len) return dfs(d + 1, 0, 0);
    
    int fail = 0;
    _for(i, last, n) if(!used[i] && a[i] != fail && curlen + a[i] <= len) {
        used[i] = true;
        if(dfs(d, curlen + a[i], i + 1)) return true;
        fail = a[i];
        used[i] = 0;
        
        if(curlen == 0 || curlen + a[i] == len) return false;
    }
    return false;
}

int main() {
    freopen("input.txt", "r", stdin);
    while (scanf("%d", &n) == 1 && n) {
        init();
        
        int sum = 0, maxl = 0;
        _for(i, 0, n) {
            scanf("%d", &a[i]);
            sum += a[i];
            maxl = max(maxl, a[i]);
        }
        
        // scanf finished
        sort(a, a + n, cmp);
        
        for(len = maxl; len <= sum; len++) {
            //
            if(sum % len) continue;
            cnt = sum / len;
            
            initVis();
            if(dfs(1, 0, 0)) break;
        }
        cout << len << endl;
    }
}
