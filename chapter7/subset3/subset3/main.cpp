//
//  main.cpp
//  subset3
//
//  Created by zhangmin chen on 2018/8/25.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

void print_subset(int n, int s) {
    for(int i = 0; i < n; i++)
        if(s & (1<<i))  printf("%d ", i);
    printf("\n");
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < (1 << n); i++)
        print_subset(n, i);
    return 0;
}
