//
//  main.cpp
//  Ideal-Path
//
//  Created by zhangmin chen on 2018/8/10.
//  Copyright © 2018年 zhangmin chen. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int maxn = 100010;
const int INF = 1000000000;

struct Edge {
    int u, v, c;
    Edge(int u = 0, int v = 0, int c = 0) : u(u), v(v), c(c) {}
};

int n;

vector<Edge> edges;
vector<int> G[maxn];

int d[maxn], vis[maxn];

void AddEdge(int u, int v, int c) {
    // get edge id!
    edges.push_back(Edge(u, v, c));
    int idx = (int)edges.size() - 1;
    G[u].push_back(idx);
}


void rev_bfs() {
    memset(vis, 0, sizeof(vis));
    memset(d, 0, sizeof(d));
    
    d[n-1] = 0;
    vis[n-1] = true;
    
    queue<int> q;
    q.push(n-1);
    
    while(!q.empty()) {
        int v = q.front();  q.pop();
        for(int i = 0; i < G[v].size(); i++) {
            int e = G[v][i];
            int next = edges[e].v;
            
            if(!vis[next]) {
                d[next] = d[v] + 1;
                vis[next] = true;
                q.push(next);
            }
        }
    }
}

vector<int> ans;

void bfs() {
    memset(vis, 0, sizeof(vis));
    vis[0] = true;
    ans.clear();
    
    vector<int> next;
    next.push_back(0);
    
    for(int i = 0; i < d[0]; i++) {
        int min_color = INF;
        for(int j = 0; j < next.size(); j++) {
            int u = next[j];
            for(int k = 0; k < G[u].size(); k++) {
                int e = G[u][k];
                int v = edges[e].v;
                if(d[u] == d[v]+1)
                    min_color = min(min_color, edges[e].c);
            }
        }
        
        ans.push_back(min_color);
        
        //find all vertice having the value of min_color
        vector<int> next2;
        for(int j = 0; j < next.size(); j++) {
            int u = next[j];
            for(int k = 0; k < G[u].size(); k++) {
                int e = G[u][k];
                int v = edges[e].v;
                
                if(d[u] == d[v]+1 && !vis[v] && edges[e].c == min_color) {
                    vis[v] = true;
                    next2.push_back(v);
                }
            }
        }
        
        next = next2;
    }
    
    printf("%d\n", ans.size());
    printf("%d", ans[0]);
    for(int i = 1; i < ans.size(); i++) printf(" %d", ans[i]);
    printf("\n");
}

int main() {
//    int u, v, c, m;
    int T;  scanf("%d", &T);
    while(T--) {
        int u, v, c, m;
        scanf("%d%d", &n, &m);
        edges.clear();
        for(int i = 0; i < n; i++)  G[i].clear();
        while(m--) {
            scanf("%d%d%d", &u, &v, &c);
            AddEdge(u-1, v-1, c);
            AddEdge(v-1, u-1, c);
        }
        
        rev_bfs();
        bfs();
    }
//    while(scanf("%d%d",&n, &m) == 2) {
//        edges.size();
//        for(int i = 0; i < n; i++)  G[i].clear();
//
//        while(m--) {
//            scanf("%d%d%d", &u, &v, &c);
//            AddEdge(u-1, v-1, c);
//            AddEdge(v-1, u-1, c);
//        }
//        rev_bfs();
//        bfs();
//    }
    return 0;
}

