//
//  main.cpp
//  print-permutation
//
//  Created by zhangmin chen on 2018/8/24.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>

int A[101];

using namespace std;

void print_permutation(int n, int* A, int cur) {
    if(cur == n) {
        for(int i = 0; i < n; i++)  printf("%d", A[i]);
        printf("\n");
    }
    else for(int v = 1; v <= n; v++) {
        //from small to large, ergodic all value of S
        int ok = 1;
        // if the data did not show up in A[0...cur-1]
        // put it to A[cur]
        
        for(int j = 0; j < cur; j++) {
            if(A[j] == v)   ok = 0;
        }
        
        if(ok) {
            A[cur] = v;
            print_permutation(n, A, cur+1);
        }
    }
}


int main() {
    int n;
    scanf("%d",&n);
    print_permutation(n, A, 0);
}
