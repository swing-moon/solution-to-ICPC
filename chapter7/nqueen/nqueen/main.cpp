//
//  main.cpp
//  nqueen
//
//  Created by zhangmin chen on 2018/8/25.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>

using namespace std;

int pos[50], tot = 0, n = 8, nc = 0;

void search(int cur) {
    nc++;
    if(cur == n)    tot++;
    else for(int i = 0; i < n; i++) {
        int ok = 1;
        pos[cur] = i;
        for(int j = 0; j < cur; j++) {
            if(pos[j] == pos[cur] || cur-j == pos[cur]-pos[j] || cur-j == pos[j]-pos[cur]) {
                ok = 0;
                break;
            }
        }
        
        if(ok)
            search(cur+1);
    }
}

int main() {
    scanf("%d", &n);
    search(0);
    printf("%d\n", tot);
    printf("%d\n", nc);
    return 0;
}
