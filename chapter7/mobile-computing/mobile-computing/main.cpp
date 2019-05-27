//
//  main.cpp
//  mobile-computing
//
//  Created by zhangmin chen on 2018/9/11.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstring>
#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

struct Tree {
    double L, R;
    Tree():L(0),R(0) {}
};

const int maxn = 6;
int n, vis[1<<maxn];
double weight[1<<maxn], sum[1<<maxn], r;
vector<Tree> trees[1<<maxn];

void dfs(int root) {
    if(vis[root])   return;
    vis[root] = true;
    
    bool have_child = false;
    for(int left = (root-1)&root; left; left = (left-1)&root) {
        have_child = true;
        
        int right = root ^ left;
        double dl = sum[right] / sum[root];
        double dr = sum[left] / sum[root];
        
        dfs(left);  dfs(right);
        
        //recall:
        for(int i = 0; i < trees[left].size(); i++)
            for(int j = 0; j < trees[right].size(); j++) {
                Tree t;
                t.L = max(trees[left][i].L + dl, trees[right][j].L - dr);
                t.R = max(trees[left][i].R - dl, trees[right][j].R + dr);
                if(t.L + t.R < r)   trees[root].push_back(t);
            }
    }
    
    if(!have_child) trees[root].push_back(Tree());
}

int main() {
    int kase;
    scanf("%d", &kase);
    
    while(kase--) {
        scanf("%lf%d", &r,&n);
        for(int i = 0; i < n; i++)  scanf("%lf", &weight[i]);
        
        //init:
        for(int i = 0; i < (1<<n); i++) {
            sum[i] = 0;
            trees[i].clear();
            for(int k = 0; k < n; k++) {
                if(i & (1<<k))  sum[i] += weight[k];
            }
        }
        
        //calculate:
        int root = (1<<n)-1;
        memset(vis, 0, sizeof(vis));
        dfs(root);
        
        double ans = -1;
        for(int i = 0; i < trees[root].size(); i++) {
            ans = max(ans, trees[root][i].L + trees[root][i].R);
        }
        printf("%.10lf\n", ans);
    }
}
