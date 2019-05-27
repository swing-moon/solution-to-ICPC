//
//  main.cpp
//  prime-ring
//
//  Created by zhangmin chen on 2018/9/4.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 0x3f3f3f3f;

int isp[50], A[50], vis[50], n;

int is_prime(int x) {
    for(int i = 2; i * i <= x; i++) {
        if(x % i == 0)
            return 0;
    }
    return 1;
}

//pos from 1 to n, means we put number cur
// A[pos-1] means A[] sub number, {A[0],A[1],...A[n-1]}
void dfs(int pos) {
    if(pos == n && isp[ A[n-1]+A[0] ]) {
        for(int i = 0; i < n; i++) {
            if(i != 0)   printf(" ");
            printf("%d", A[i]);
        }
        printf("\n");
    }
    else {
        for(int v = 2; v <= n; v++) {
            if(!vis[v] && isp[ A[pos-1]+v ]) {
                A[pos] = v;
                vis[v] = 1;
                dfs(pos+1);
                vis[v] = 0;
            }
        }
    }
}

int main() {
    int kase = 0;
    while(scanf("%d", &n) == 1 && n > 0) {
        if(kase > 0)    printf("\n");
        printf("Case %d:\n", ++kase);
        
        for(int i = 2; i < n*2; i++)    isp[i] = is_prime(i);
        memset(vis, 0, sizeof(vis));
        A[0] = 1;
        dfs(1);
    }
    return 0;
}

/*
int main() {
    int kase = 0;
    int n;
    while(scanf("%d", &n) == 1 && n > 0) {
        if(kase > 0)    printf("\n");
        
        for(int i = 2; i <= 2*n; i++)   isp[i] = is_prime(i);
        
        //permutation
        for(int i = 0; i < n; i++)  A[i] = i+1;
        
        do {
            int ok = 1;
            for(int i = 0; i < n; i++)  if(!isp[ A[i]+A[(i+1)%n] ]) {
                ok = 0;     break;
            }
            
            if(ok) {
                for(int i = 0; i < n; i++)  printf("%d ", A[i]);
                printf("\n");
            }
            // position 1 is not changed!
        } while(next_permutation(A+1, A+n));
    }
}
*/

