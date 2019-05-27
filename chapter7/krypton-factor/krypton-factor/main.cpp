//
//  main.cpp
//  krypton-factor
//
//  Created by zhangmin chen on 2018/9/9.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

int n, L, cnt;
int S[100];

int check(int pos) {
    //check if satisfied when added a alpha
    for(int k = 1; k*2 <= pos+1; k++) {
        int equal = 1;
        for(int j = 0; j < k; j++) {
            if(S[pos-j] != S[pos-j-k]) {
                equal = 0;
                break;
            }
        }
        if(equal)   return 0;
    }
    return 1;
}

int dfs(int cur) {
    if(cnt++ == n) {
        for(int i = 0; i < cur; i++) {
            if(i % 64 == 0 && i > 0)    printf("\n");
            else if(i % 4 == 0 && i > 0)    printf(" ");
            printf("%c", 'A'+S[i]);
        }
        printf("\n%d\n", cur);
        return 0;
    } else {
        for(int i = 0; i < L; i++) {
            S[cur] = i;
            if(check(cur) && !dfs(cur+1)) {
//                cout << "cnt :" << cnt << endl;
                return 0;
            }
        }
    }
    return 1;
}


int main() {
    while(scanf("%d%d", &n, &L) == 2 && n > 0) {
        cnt = 0;
        dfs(0);
    }
    return 0;
}
