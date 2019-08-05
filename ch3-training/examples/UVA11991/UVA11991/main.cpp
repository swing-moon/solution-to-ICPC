//
//  main.cpp
//  UVA11991
//
//  Created by zhangmin chen on 2019/7/8.
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

const int maxn = 20 + 5;


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


map<int, vector<int> > mp;
int n, m, k, v;

void init() {
    mp.clear();
}

int main() {
    freopen("input.txt", "r", stdin);
    while(scanf("%d%d", &n, &m) == 2) {
        init();
        _for(i, 0, n) {
            scanf("%d", &v);
            if(!mp.count(v)) mp[v] = vector<int>();
            mp[v].push_back(i + 1);
        }
        
        while (m--) {
            int a, b;
            scanf("%d%d", &a, &b);
            if(!mp.count(b) || mp[b].size() < a) printf("0\n");
            else printf("%d\n", mp[b][a - 1]);
        }
    }
}
