//
//  main.cpp
//  next_permutation
//
//  Created by zhangmin chen on 2018/8/24.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

int main() {
    int n, P[10];
    scanf("%d", &n);
    for(int i = 0; i < n; i++)  scanf("%d", &P[i]);
    
    sort(P, P+n);
    
    do {
        for(int i = 0; i < n; i++)  printf("%d ", P[i]);
        printf("\n");
    } while(next_permutation(P, P+n));
}
