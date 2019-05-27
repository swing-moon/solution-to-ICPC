//
//  main.cpp
//  uva10561
//
//  Created by zhangmin chen on 2019/2/27.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 200;
int g[maxn+10];

bool winning(const char* st) {
    // blue area -- green area -- red area
    int n = (int)strlen(st);
    for(int i = 0; i < n-2; i++)
        if(st[i] == 'X' && st[i+1] == 'X' && st[i+2] == 'X') return false;
    
    int isred[maxn+1];
    memset(isred, 0, sizeof(isred));
    isred[n] = 1;
    
    for(int i = 0; i < n; i++) if(st[i] == 'X') {
        for(int d = -2; d <= 2; d++) {
            if(i+d >= 0 && i+d < n) {
                //if(d == 0) continue;
                if(d != 0 && st[i+d] == 'X') return true;
                isred[i+d] = 1;
            }
        }
    }
    
    int sg = 0;
    //
    int beg = -1;
    for(int i = 0; i <= n; i++) {
        if(beg < 0 && !isred[i]) beg = i;
        if(beg >= 0 && isred[i]) sg ^= g[i-beg];
        if(isred[i]) beg = -1;
    }
    
    return sg != 0;
}

int mex(vector<int>& vec) {
    //
    if(vec.empty()) return 0;
    sort(vec.begin(), vec.end());
    if(vec[0] != 0) return 0;
    for(int i = 1; i < vec.size(); i++) {
        if(vec[i] > vec[i-1] + 1) return vec[i-1] + 1;
    }
    return vec[vec.size()-1] + 1;
}

void cal() {
    //
    g[0] = 0;
    g[1] = g[2] = g[3] = 1;
    for(int x = 4; x <= maxn; x++) {
        vector<int> vec;
        vec.push_back(g[x-3]);
        vec.push_back(g[x-4]);
        if(x >= 5) vec.push_back(g[x-5]);
        
        // green area: [k+1...x-3]
        // allowed!
        for(int k = 3; k < x-3; k++) {
            vec.push_back(g[k-2] ^ g[x-3-k]);
        }
        
        g[x] = mex(vec);
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    cal();
    //
    
    int T;
    scanf("%d", &T);
    while(T--) {
        char state[maxn + 10];
        scanf("%s", state);
        int n = (int)strlen(state);
        
        if(!winning(state)) printf("LOSING\n\n");
        else {
            printf("WINNING\n");
            
            // print path()
            vector<int> moves;
            for(int i = 0; i < n; i++) if(state[i] == '.') {
                state[i] = 'X';
                if(!winning(state)) moves.push_back(i+1);
                state[i] = '.';
            }
            
            printf("%d", moves[0]);
            for(int i = 1; i < moves.size(); i++) printf(" %d", moves[i]);
            printf("\n");
        }
    }
}
