//
//  main.cpp
//  mergeSort
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

const int maxn = 100000000;
int A[maxn];
int T[maxn];
int n;
int cnt = 0;

void init() {
    // static int cnt = 0;
    cnt = 0;
    memset(A, 0, sizeof(A));
    memset(T, 0, sizeof(T));
}

void mergeSort(int* A, int x, int y, int* T) {
    if(y - x > 1) {
        int mid = x + (y-x) / 2;
        int p = x, q = mid;
        
        int i = x;
        
        mergeSort(A, x, mid, T);
        mergeSort(A, mid, y, T);
        
        while(p < mid || q < y) {
            if( (q >= y) || (p < mid && A[p] <= A[q]) ) T[i++] = A[p++];
            else {
                T[i++] = A[q++];
                cnt += mid-p;
            }
        }
        
        for(int i = x; i < y; i++) A[i] = T[i];
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    // static int n;
    // init();
    cin >> n;
    init();
    
    for(int i = 0; i < n; i++) {
        cin >> A[i];
    }
    
    // mergeSort
    mergeSort(A, 0, n, T);
    for(int i = 0; i < n; i++) cout << A[i] << " ";
    cout << endl;
    
    cout << "cnt: " << cnt << endl;
}
