//
//  main.cpp
//  subset
//
//  Created by zhangmin chen on 2018/8/25.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

void print_permutation(int* A, int n, int cur) {
    for(int i = 0; i < cur; i++)    printf("%d ", A[i]);
    printf("\n");
    
    int s = cur ? A[cur-1]+1 : 0;
    for(int i = s; i < n; i++) {
        A[cur] = i;
        print_permutation(A, n, cur+1);
    }
}

int A[10];
int main() {
    int n;
    scanf("%d", &n);
    print_permutation(A, n, 0);
    return 0;
}
