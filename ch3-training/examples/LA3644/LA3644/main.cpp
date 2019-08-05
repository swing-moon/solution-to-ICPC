//
//  main.cpp
//  LA3644
//
//  Created by zhangmin chen on 2019/7/10.
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
typedef set<int>::iterator ssii;

const int maxn = 100000 + 10;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
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

int pa[maxn];
int findSet(int x) {
    return pa[x] == x ? x : pa[x] = findSet(pa[x]);
}
void initSet() {
    _for(i, 0, maxn) pa[i] = i;
}



int main() {
    freopen("input.txt", "r", stdin);
    int x, y;
    while (scanf("%d", &x) == 1) {
        initSet();
        int refuse = 0;
        
        while (x != -1) {
            scanf("%d", &y);
            
            x = findSet(x);
            y = findSet(y);
            if(x == y) refuse++;
            else pa[x] = y;
            
            scanf("%d", &x);
        }
        
        cout << refuse << endl;
    }
}
