//
//  main.cpp
//  quicksort
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

const int maxn = 1000000;
int n;
int A[maxn];

void init() {
    memset(A, 0, sizeof(A));
}

void quicksort(int* A, int lo, int hi) {
    if(lo > hi) return;
    
    int pivot = A[lo];
    
    int i = lo, j = hi;
    
    while(i != j) {
        while(A[j] >= pivot && i < j) j--;
        while(A[i] <= pivot && i < j) i++;
        
        if(i < j) swap(A[i], A[j]);
    }
    
    A[lo] = A[i];
    A[i] = pivot;
    
    quicksort(A, lo, i-1);
    quicksort(A, i+1, hi);
}

int main() {
    freopen("input.txt", "r", stdin);
    cin >> n;
    init();
    
    for(int i = 0; i < n; i++) cin >> A[i];
    
    quicksort(A, 0, n-1);
    for(int i = 0; i < n; i++) cout << A[i] << " ";
    cout << endl;
}
