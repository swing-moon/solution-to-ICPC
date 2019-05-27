//
//  main.cpp
//  BinarySearch
//
//  Created by zhangmin chen on 2019/5/19.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int binarySearch(int* A, int x, int y, int v) {
    // [x,y] to find v
    int mid;
    while(x < y) {
        mid = x + (y - x) / 2;
        if(A[mid] == v) return mid;
        else if(A[mid] > v) y = mid;
        else x = mid + 1;
    }
    return -1;
}

const int maxn = 100000;
int A[maxn];

void init() {
    memset(A, 0, sizeof(A));
}

int L_bound(int* A, int x, int y, int v) {
    int mid;
    while (x < y) {
        mid = x + (y - x) / 2;
        if(A[mid] >= v) y = mid;
        else x = mid + 1;
    }
    return x;
}

int U_bound(int* A, int x, int y, int v) {
    int mid;
    while(x < y) {
        mid = x + (y - x) / 2;
        if(A[mid] <= v) x = mid + 1;
        else y = mid;
    }
    return x;
}

int main() {
    freopen("input.txt", "r", stdin);
    init();
    int n;
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        cin >> A[i];
    }
    sort(A, A+n);
    
    int v;
    cin >> v;
    
    int id = binarySearch(A, 0, n-1, v);
    cout << id << endl;
}
