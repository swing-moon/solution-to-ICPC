//
//  main.cpp
//  Self-Assembly
//
//  Created by zhangmin chen on 2018/8/9.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>

using namespace std;

int G[52][52];
int vis[52];

int ID(char a1, char a2) {
    return (a1 - 'A') * 2 + (a2 == '+' ? 0 : 1);
}

void connect(char a1, char a2, char b1, char b2) {
    if(a1 == '0' || b1 == '0')  return;
    int u = ID(a1, a2) ^ 1, v = ID(b1, b2);
    G[u][v] = 1;
}

bool dfs(int u) {
    vis[u] = -1;
    for(int v = 0; v < 52; v++) if(G[u][v]) {
        if(vis[v] < 0)  return true;
        if(!vis[v] && dfs(v))   return true;
    }
    vis[u] = 1;
    return false;
}

bool find_cycle() {
    memset(vis, 0, sizeof(vis));
    for(int u = 0; u < 52; u++) {
        if(dfs(u))  return true;
    }
    return false;
}

int main() {
    int n;
    while(scanf("%d", &n) == 1 && n) {
        memset(G, 0, sizeof(G));
        while(n--) {
            char cube[10];
            scanf("%s", cube);
            for(int i = 0; i < 4; i++)
                for(int j = 0; j < 4; j++) if(i != j)
                    connect(cube[i*2], cube[i*2+1], cube[j*2], cube[j*2+1]);
        }
        
        if(find_cycle())    cout << "unbounded" << endl;
        else    cout << "bounded" << endl;
    }
    return 0;
}
