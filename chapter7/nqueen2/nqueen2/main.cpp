//
//  main.cpp
//  nqueen2
//
//  Created by zhangmin chen on 2018/8/25.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>

int pos[50], vis[3][50], tot = 0, nc = 0, n = 8;

void search(int cur) {
    nc++;
    if(cur == n) {
        tot++;
    } else for(int i = 0; i < n; i++) {
        if(!vis[0][i] && !vis[1][cur+i] && !vis[2][cur-i+n]) {
            pos[cur] = i;
            vis[0][i] = vis[1][cur+i] = vis[2][cur-i+n] = 1;
            search(cur+1);
            vis[0][i] = vis[1][cur+i] = vis[2][cur-i+n] = 0;
        }
    }
}

int main() {
    scanf("%d", &n);
    memset(vis, 0, sizeof(vis));
    search(0);
    printf("%d\n", tot);
    printf("%d\n", nc);
    return 0;
}
