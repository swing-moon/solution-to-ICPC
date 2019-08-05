//
//  main.cpp
//  LA3027
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

const int maxn = 20000 + 10;

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

int pa[maxn], d[maxn];
void initSet() {
    _for(i, 0, maxn) {
        pa[i] = i;
        d[i] = 0;
    }
}

int findSet(int x) {
    if(pa[x] == x) return x;
    else {
        int root = findSet(pa[x]);
        d[x] += d[pa[x]];
        return pa[x] = root;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);
    
    while (kase--) {
        initSet();
        int n, u, v;
        char cmd[9];
        scanf("%d", &n);
        
        while (scanf("%s", cmd) && cmd[0] != 'O') {
            if(cmd[0] == 'E') {
                scanf("%d", &u);
                findSet(u);
                cout << d[u] << endl;
            } else if(cmd[0] == 'I') {
                scanf("%d%d", &u, &v);
                pa[u] = v;
                d[u] = abs(u - v) % 1000;
            }
        }
    }
}
