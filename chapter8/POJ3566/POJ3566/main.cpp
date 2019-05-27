//
//  main.cpp
//  POJ3566
//
//  Created by zhangmin chen on 2019/5/19.
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

const int inf = 0x3f3f3f3f;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

char country(int i) {
    if(i < 26) return 'A' + i;
    else return i - 26 + 'a';
}

int main() {
    freopen("input.txt", "r", stdin);
    
    int n;
    while(scanf("%d", &n) == 1) {
        printf("2 %d %d\n", n, n);
        
        _for(i, 0, n) {
            _for(j, 0, n) printf("%c", country(i));
            printf("\n");
        }
        printf("\n");
        _for(i, 0, n) {
            _for(j, 0, n) printf("%c", country(j));
            printf("\n");
        }
    }
}
