//
//  main.cpp
//  URAL1309
//
//  Created by zhangmin chen on 2019/7/11.
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


using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;

const int M = 9973;
const int maxn = 50000;

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


int _pow(int x, int k) {
    int ans = 1;
    _for(i, 0, k) ans = (ans * x) % M;
    return ans;
}

void _mod(int& x) {
    x %= M;
    if(x < 0) x += M;
}

int _A(int x) {
    int ans = 0;
    ans = (_pow(x, 5) - x + 7);
    _mod(ans);
    return ans;
}

int _B(int x) {
    int ans = 0;
    ans = -1 * _pow(x, 5) + _pow(x, 3) + 3 * x;
    _mod(ans);
    return ans;
}

int f[maxn];
void init() {
    Set(f, 0);
}

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);
    init();
    
    int b = n % M;
    
    // recursive: [1, b]
    _rep(i, 1, b) {
        int A0 = _A(i);
        int B0 = _B(i);
        f[i] = A0 * f[i - 1] + B0;
        _mod(f[i]);
    }
    
    // coefficent: [b+1, b+M], get A(b+M)f(x) + B(b+M)
    int A = 1, B = 0;
    _rep(i, b+1, b+M) {
        //
        int Ai = _A(i);
        int Bi = _B(i);
        f[i] = Ai * f[i - 1] + Bi;
        
        A *= Ai;
        B = B * Ai + Bi;
        _mod(A);
        _mod(B);
        _mod(f[i]);
    }
    
    int ans = f[b];
    while (b < n) {
        ans = ans * A + B;
        _mod(ans);
        b += M;
    }
    printf("%d\n", ans);
    
}
