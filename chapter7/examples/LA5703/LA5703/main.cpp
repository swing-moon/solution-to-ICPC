//
//  main.cpp
//  LA5703
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

const int inf = 65536;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(llong i = (l); i <= (r); i++)
#define _for(i, l, r) for(llong i = (l); i < (r); i++)
#define _forDown(i, l, r) for(llong i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }

int main() {
    freopen("input.txt", "r", stdin);
    int T;
    scanf("%d", &T);
    
    for(int kase = 1; kase <= T; kase++) {
        // solve the problem
        llong ans = 0;
        int n, s1, v1, s2, v2;
        scanf("%d%d%d%d%d", &n, &s1, &v1, &s2, &v2);
        
        if(s1 > s2) {
            swap(s1, s2);
            swap(v1, v2);
        }
        
        if(n / s2 >= inf) {
            //
            _rep(i, 0, s1) ans = max(ans, v2 * i + (n - s2 * i) / s1 * v1);
            _rep(i, 0, s2) ans = max(ans, v1 * i + (n - s1 * i) / s2 * v2);
        }
        else {
            for(llong i = 0; s2 * i <= n; i++) {
                ans = max(ans, v2 * i + (n - s2 * i) / s1 * v1);
            }
        }
        
        printf("Case #%d: %lld\n", kase, ans);
    }
}
