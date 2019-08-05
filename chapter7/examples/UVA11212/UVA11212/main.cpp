//
//  main.cpp
//  UVA11212
//
//  Created by zhangmin chen on 2019/6/29.
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

const int maxn = 9;
const int MAXD = 10;

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

int v[maxn], n;

void init() {
    Set(v, 0);
}

bool sorted() {
    _for(i, 0, n-1) {
        if(v[i] >= v[i+1]) return false;
    }
    return true;
}

int h() {
    int cnt = 0;
    _for(i, 0, n-1) if(v[i] + 1 != v[i+1]) cnt++;
    
    if(v[n-1] != n) cnt++;
    return cnt;
}

int dfs(int d, int maxd) {
    //
    if( h() > 3 * (maxd - d) ) return false;
    if(sorted()) return true;
    
    // then: try to dfs(d+1, maxd)
    int buf[maxn], oldv[maxn];
    Cpy(oldv, v);
    
    _for(i, 0, n) _for(j, i, n) {
        int cnt = 0;
        _for(k, 0, n) if(k < i || k > j) buf[cnt++] = v[k];
        
        _for(p, 0, cnt) {
            int cnt2 = 0;
            _rep(k, 0, p) v[cnt2++] = buf[k];
            _rep(k, i, j) v[cnt2++] = oldv[k];
            _for(k, p+1, cnt) v[cnt2++] = buf[k];
            
            if(dfs(d+1, maxd)) return true;
            Cpy(v, oldv);
        }
    }
    
    return false;
}

int solve() {
    if(sorted()) return 0;
    int maxd;
    for(maxd = 1; maxd < MAXD; maxd++) {
        if(dfs(0, maxd)) return maxd;
    }
    return MAXD;
}

int main() {
    freopen("input.txt", "r", stdin);
    
    int kase = 0;
    
    while (scanf("%d", &n) == 1 && n) {
        _for(i, 0, n) scanf("%d", &v[i]);
        
        // dfs and solve()
        printf("Case %d: %d\n", ++kase, solve());
    }
}
