//
//  main.cpp
//  UVA10410
//
//  Created by zhangmin chen on 2019/3/31.
//  Copyright © 2019 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
#include <stack>
#include <map>
#include <set>

using namespace std;
typedef long long llong;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)


const int maxn = 1000 + 5;
int pa[maxn];
int n;

vector<int> bseq, dseq[maxn];
vector<int> G[maxn];

int read() {
    int x;
    scanf("%d", &x);
    return x;
}

void init() {
    bseq.clear();
    for(int i = 0; i < maxn; i++) dseq[i].clear();
    for(int i = 0; i < maxn; i++) G[i].clear();
    memset(pa, 0, sizeof(pa));
}

void dfs(int u, int& bi) {

    // find all sub_nodes
    // the we construct all sub-tree of node v
    // construct dseq[u] -> desq[v] -> dseq[vv]
    
    // i travel all sub node in dfs-seq
    //debug(dseq[u].size());
    
    // bseq[bi] is a direct-child of node u
    // find v == bseq[bi] in dseq[u][]
    // construct child nodes of dseq[v] at the same time!
    
    _for(i, 0, (int)dseq[u].size()) {
        int v = dseq[u][i];
        
        if(bi < n && v == bseq[bi]) {
            bi++;
            G[u].push_back(v);
            pa[v] = u;
            
            for(int j = i+1; j < dseq[u].size() && bi < n; j++) {
                int vv = dseq[u][j];
                if(vv == bseq[bi]) break;
                
                // dseq[v+1] -> vv, each node is sub-node of v
                // refresh dseq[v]
                dseq[v].push_back(vv);
                pa[vv] = v;
            }
        }
    }
    
    
    while(bi < n) dfs(pa[bseq[bi]], bi);
}

int main() {
    //
    freopen("input.txt", "r", stdin);
    while(cin >> n && n) {
        //
        init();
        for(int i = 0; i < n; i++) bseq.push_back(read());
        read();
        for(int i = 1; i < n; i++) dseq[bseq[0]].push_back(read());
        
        // the we deal the problem
        int bi = 1;
        dfs(bseq[0], bi);
        
        for(int i = 1; i <= n; i++) {
            sort(G[i].begin(), G[i].end());
            printf("%d:", i);
            for(int k = 0; k < G[i].size(); k++) {
                printf(" %d", G[i][k]);
            }
            printf("\n");
        }
    }
}
