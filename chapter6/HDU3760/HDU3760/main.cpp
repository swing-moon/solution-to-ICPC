//
//  main.cpp
//  HDU3760
//
//  Created by zhangmin chen on 2019/5/23.
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
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;
typedef long long llong;
typedef set<string>::iterator ssii;

const int maxn = 100000 + 10;
const int inf = 1000000000;

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

class Edge {
public:
    int from, to, w;
    Edge(int f = 0, int t = 0, int w_ = 0) : from(f), to(t), w(w_) {}
};

vector<int> G[maxn];
int vis[maxn], d[maxn];
vector<Edge> edges;
int n;

void clearVis() {
    Set(vis, 0);
}

void init() {
    _for(i, 0, maxn) G[i].clear();
    clearVis();
    edges.clear();
    Set(d, 0);
}

void addEdge(int from, int to, int w) {
    edges.push_back((Edge){from, to, w});
    G[from].push_back((int)edges.size() - 1);
}


void revbfs() {
    d[n-1] = 0;
    vis[n-1] = true;
    
    queue<int> que;
    que.push(n-1);
    
    while(!que.empty()) {
        int u = que.front();
        que.pop();
        
        _for(i, 0, G[u].size()) {
            Edge& e = edges[G[u][i]];
            if(!vis[e.to]) {
                vis[e.to] = true;
                d[e.to] = d[u] + 1;
                que.push(e.to);
            }
        }
    }
}

void bfs() {
    clearVis();
    vector<int> ans;
    ans.clear();
    
    vis[0] = true;
    vector<int> nodes;
    nodes.push_back(0);
    
    _for(level, 0, d[0]) {
        int minColor = inf;
        _for(i, 0, nodes.size()) {
            int u = nodes[i];
            _for(v, 0, G[u].size()) {
                Edge& e = edges[G[u][v]];
                if(d[u] == d[e.to] + 1)
                    minColor = min(minColor, e.w);
            }
        }
        
        ans.push_back(minColor);
        
        vector<int> nodes2;
        _for(i, 0, nodes.size()) {
            int u = nodes[i];
            _for(v, 0, G[u].size()) {
                Edge& e = edges[G[u][v]];
                if(!vis[e.to] && d[u] == d[e.to] + 1 && minColor == e.w) {
                    vis[e.to] = true;
                    nodes2.push_back(e.to);
                }
            }
        }
        
        nodes = nodes2;
    }
    
    printf("%d\n", (int)ans.size());
    printf("%d", ans[0]);
    _for(i, 1, ans.size()) printf(" %d", ans[i]);
    printf("\n");
}

int main() {
    freopen("input.txt", "r", stdin);
    int kase;
    scanf("%d", &kase);
    
    while(kase--) {
        int from, to, w, m;
        init();
        
        scanf("%d%d", &n, &m);
        while (m--) {
            scanf("%d%d%d", &from, &to, &w);
            addEdge(from-1, to-1, w);
            addEdge(to-1, from-1, w);
        }
        
        //get all graph data
        revbfs();
        bfs();
    }
}
