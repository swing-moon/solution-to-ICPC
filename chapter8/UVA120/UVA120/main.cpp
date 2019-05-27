//
//  main.cpp
//  UVA120
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

const int maxn = 100;
int A[maxn];
int n;

void init() {
    Set(A, 0);
}

void flip(int p) {
    for(int i = 0; i < p-i; i++) {
        swap(A[i], A[p-i]);
    }
    printf("%d ", n-p);
}

int main() {
    freopen("input.txt", "r", stdin);
    string line;
    while (getline(cin, line)) {
        init();
        stringstream ss(line);
        n = 0;
        while(ss >> A[n]) n++;
        _for(i, 0, n) printf("%d ", A[i]);
        printf("\n");
        
        for(int i = n-1; i > 0; i--) {
            // i is the position of top
            // [begin, end) max element
            long ith = max_element(A, A+i+1) - A;
            if((int)ith == i) continue;
            
            if(ith > 0) flip((int)ith);
            flip(i);
        }
        printf("0\n");
    }
}
