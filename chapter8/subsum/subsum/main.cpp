//
//  main.cpp
//  subsum
//
//  Created by zhangmin chen on 2019/5/3.
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

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

const int maxn = 100000;
int A[maxn];

void init() {
    memset(A, 0, sizeof(A));
}

int tot = 0;

int maxsum(int* A, int x, int y) {
    //
    // from [x, y)
    tot++;
    debug(tot);
    
    if(y-x == 1) return A[x];
    int mid = x + (y-x) / 2;
    
    // [x. mid)  [mid, y)
    int subs = max(maxsum(A, x, mid), maxsum(A, mid, y));
    
    int val = 0;
    int L = A[mid-1];
    for(int i = mid-1; i >= x; i--) L = max(L, val += A[i]);
    
    val = 0;
    int R = A[mid];
    for(int i = mid; i < y; i++) R = max(R, val += A[i]);
    
    
    return max(subs, L + R);
}

int main() {
    freopen("input.txt", "r", stdin);
    static int n;
    
    init();
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        cin >> A[i];
    }
    
    cout << maxsum(A, 0, n) << endl;
    
}
