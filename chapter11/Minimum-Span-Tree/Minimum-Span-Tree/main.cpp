//
//  main.cpp
//  Minimum-Span-Tree
//
//  Created by zhangmin chen on 2018/8/13.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

using namespace std;
const int INF = (1 << 21);
const int WHITE = 0;
const int BLACK = 2;
const int GRAY = 1;
const int maxn = 100;

int n, M[maxn][maxn], mincost;
int d[maxn], p[maxn], color[maxn];
int u;

int prim() {
    for(int i = 0; i < n; i++) {
        d[i] = INF; p[i] = -1; color[i] = WHITE;
    }
    // DO NOT USE MEMSET!
    
    d[0] = 0;
    
    while(true) {
        mincost = INF;
        u = -1;
        for(int i = 0; i < n; i++) {
            if(color[i] != BLACK && d[i] < mincost) {
                mincost = d[i];
                u = i;
            }
        }
        
        if(u == -1) break;
        color[u] = BLACK;
        
        for(int v = 0; v < n; v++) {
            if(color[v] != BLACK && M[u][v] != INF) {
                if(M[u][v] < d[v]) {
                    d[v] = M[u][v];
                    p[v] = u;
                    color[v] = GRAY;
                }
            }
        }
    }
    
    int sum = 0;
    for(int i = 0; i < n; i++) {
        if(p[i] != -1)  sum += M[p[i]][i];
    }
    return sum;
}


int main() {
    cin >> n;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int e;  cin >> e;
            M[i][j] = (e == -1) ? INF : e;
        }
    }
    
    /*for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++)
            cout << M[i][j] << " ";
        cout << endl;
    }*/
    
    cout << prim() << endl;
}
