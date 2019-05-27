//
//  main.cpp
//  bandwidth
//
//  Created by zhangmin chen on 2018/9/9.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//


#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int maxn = 10;
int id[256], letter[maxn];

int main() {
    char alpha[1000];
    while(scanf("%s", alpha) == 1 && alpha[0] != '#') {
        
        //get data
        int n = 0;
        for(char ch = 'A'; ch <= 'Z'; ch++) {
            if(strchr(alpha, ch) != NULL) {
                id[ch] = n++;
                letter[id[ch]] = ch;
            }
        }
        
        // get id
        int len = (int)strlen(alpha), p = 0, q = 0;
        vector<int> u;
        map<int, vector<int> > v;
        for(;;) {
            while(p < len && alpha[p] != ':')   p++;
            if(p == len)    break;
            
            while(q < len && alpha[q] != ';')   q++;
            u.push_back(id[alpha[p-1]]);
            
            for(int i = p+1; i < q; i++) {
                v[id[alpha[p-1]]].push_back(id[alpha[i]]);
            }
            
            p++; q++;
        }
        
        //enumerate
        int P[maxn], bestP[maxn], ans = n, pos[maxn];
        for(int i = 0; i < n; i++)  P[i] = i;
        
        do {
            for(int i = 0; i < n; i++)  pos[P[i]] = i;
            int bandwidth = 0;
            for(int i = 0; i < u.size(); i++) {
                int cur = u[i];
                for(auto& k : v[cur]) {
                    bandwidth = max(bandwidth, abs(pos[cur] - pos[k]));
                }
            }
            if(bandwidth < ans) {
                ans = bandwidth;
                memcpy(bestP, P, sizeof(P));
            }
        }while(next_permutation(P, P+n));
        
        for(int i = 0; i < n; i++)
            printf("%c ", letter[bestP[i]]);
        printf("-> %d\n", ans);
    }
}
