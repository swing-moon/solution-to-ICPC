//
//  main.cpp
//  LA3403
//
//  Created by zhangmin chen on 2019/6/19.
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

const int maxn = 6;
const int MAXN = (1 << 6);

#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;


class Node {
public:
    double L, R;
    Node(double _L = 0, double _R = 0) : L(_L), R(_R) {}
};

int vis[MAXN];
double sum[MAXN], weight[maxn + 5];
vector<Node> nodes[MAXN];

int s;
double r;

void init1() {
    Set(vis, 0);
    Set(sum, 0);
    Set(weight, 0);
    _for(i, 0, MAXN) nodes[i].clear();
}

int init2() {
    int root = (1 << s) - 1;
    _rep(i, 0, root) _for(k, 0, s) {
        if( (1 << k) & i ) sum[i] += weight[k];
    }
    return root;
}

void dfs(int u) {
    if(vis[u]) return;
    vis[u] = true;
    
    bool haveChild = false;
    for(int left = (u - 1) & u; left; left = (left - 1) & u) {
        haveChild = true;
        
        int right = u ^ left;
        double dl = sum[right] / sum[u];
        double dr = sum[left] / sum[u];
        
        dfs(left);
        dfs(right);
        
        _for(i, 0, nodes[left].size()) _for(j, 0, nodes[right].size()) {
            Node cur;
            cur.L = max(nodes[left][i].L + dl, nodes[right][j].L - dr);
            cur.R = max(nodes[left][i].R - dl, nodes[right][j].R + dr);
            if(cur.L + cur.R < r) nodes[u].push_back(cur);
        }
    }
    
    if(!haveChild) nodes[u].push_back(Node());
}


int main() {
    freopen("input.txt", "r", stdin);
    
    int kase;
    scanf("%d", &kase);
    
    while (kase--) {
        scanf("%lf%d", &r, &s);
        init1();
        _for(i, 0, s) scanf("%lf", &weight[i]);
        int root = init2();
        
        dfs(root);
        double ans = -1;
        _for(i, 0, nodes[root].size()) {
            ans = max(ans, nodes[root][i].L + nodes[root][i].R);
        }
        
        printf("%.10lf\n", ans);
    }
}
