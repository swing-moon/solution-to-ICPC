//
//  main.cpp
//  LA3506
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
const int maxn = 4000 + 5;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

int n;

int A[maxn], B[maxn], C[maxn], D[maxn];
int sum[maxn*maxn];

void init() {
    Set(A, 0);
    Set(B, 0);
    Set(C, 0);
    Set(D, 0);
    Set(sum, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    
    int kase;
    scanf("%d", &kase);
    
    while (kase--) {
        init();
        scanf("%d", &n);
        _for(i, 0, n) {
            cin >> A[i] >> B[i] >> C[i] >> D[i];
        }
        
        int k = 0;
        _for(i, 0, n) _for(j, 0, n) sum[k++] = A[i] + B[j];
        
        sort(sum, sum+k);
        
        llong cnt = 0;
        _for(i, 0, n) _for(j, 0, n) {
            cnt += upper_bound(sum, sum+k, -C[i]-D[j]) - lower_bound(sum, sum+k, -C[i]-D[j]);
        }
        printf("%lld\n", cnt);
        if(kase) printf("\n");
    }
}
