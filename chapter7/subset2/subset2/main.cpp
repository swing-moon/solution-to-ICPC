//
//  main.cpp
//  subset2
//
//  Created by zhangmin chen on 2018/8/25.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>

using namespace std;

void print_subset(int n, int* B, int cur) {
    if(cur == n) {
        for(int i = 0; i < cur; i++)  if(B[i])
            printf("%d ", i);
        
        printf("\n");
        return;
    }
    
    B[cur] = 1;
    print_subset(n, B, cur+1);
    B[cur] = 0;
    print_subset(n, B, cur+1);
}


int B[10];
int main() {
    int n;
    scanf("%d", &n);
    print_subset(n, B, 0);
    return 0;
}
