//
//  main.cpp
//  Fill
//
//  Created by zhangmin chen on 2019/6/26.
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

const int maxn = 200 + 5;
const int inf = 362880 + 5;

#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(b))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;

class Node {
public:
    int pour[3], dist;
    bool operator< (const Node& rhs) const {
        return dist > rhs.dist;
    }
    
    Node() {
        Set(pour, 0);
        dist = 0;
    }
    
    Node(const Node& rhs) {
        //
        Cpy(pour, rhs.pour);
        dist = rhs.dist;
    }
};

int vis[maxn][maxn], cap[3], ans[maxn];

void init() {
    Set(vis, 0);
    Set(cap, 0);
    Set(ans, -1);
}

void update(const Node& u) {
    _for(i, 0, 3) {
        int d = u.pour[i];
        if(ans[d] < 0 || u.dist < ans[d]) ans[d] = u.dist;
    }
}

void solve(int a, int b, int c, int d) {
    //
    cap[0] = a; cap[1] = b; cap[2] = c;
    priority_queue<Node> que;
    Node start;
    start.dist = 0;
    start.pour[0] = 0; start.pour[1] = 0; start.pour[2] = c;
    vis[0][0] = 1;
    que.push(start);
    
    while (!que.empty()) {
        Node x = que.top(); que.pop();
        update(x);
        if(ans[d] >= 0) break;
        
        // then bfs and spread the node
        // pour i to j
        _for(i, 0, 3) _for(j, 0, 3) if(i != j) {
            Node nxt(x);
            if(x.pour[i] == 0 || x.pour[j] == cap[j]) continue;
            
            int amount = min(cap[j], x.pour[i] + x.pour[j]) - x.pour[j];
            nxt.pour[i] -= amount;
            nxt.pour[j] += amount;
            nxt.dist = x.dist + amount;
            
            if(!vis[nxt.pour[0]][nxt.pour[1]]) {
                vis[nxt.pour[0]][nxt.pour[1]] = 1;
                que.push(nxt);
            }
        }
    }
    
    while (d >= 0) {
        if(ans[d] >= 0) {
            printf("%d %d\n", ans[d], d);
            return;
        }
        d--;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    
    int kase, a, b, c, d;
    scanf("%d", &kase);
    //debug(kase);
    
    while (kase--) {
        init();
        scanf("%d%d%d%d", &a, &b, &c, &d);
        solve(a, b, c, d);
    }
}
