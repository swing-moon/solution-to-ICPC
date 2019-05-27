//
//  main.cpp
//  ferguson
//
//  Created by zhangmin chen on 2019/2/26.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>

using namespace std;
const int maxn = 100;
const int M = 20;
int winning[maxn][maxn];

int main() {
    winning[1][1] = false;
    for(int k = 3; k < M; k++) {
        for(int n = 1; n < k; n++) {
            int m = k-n;
            winning[n][m] = false;
            
            for(int i = 1; i < n; i++) if(!winning[i][n-i])
                winning[n][m] = true;
            for(int i = 1; i < m; i++) if(!winning[i][m-i])
                winning[n][m] = true;
            
            if(n < m && !winning[n][m]) printf("%d %d\n", n, m);
        }
        
    }
    return 0;
}
