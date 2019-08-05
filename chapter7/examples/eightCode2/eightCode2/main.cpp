//
//  main.cpp
//  eightCode2
//
//  Created by zhangmin chen on 2019/6/24.
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

const int maxstate = 1000000;
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

typedef int State[9];
int dist[maxstate];
State nodes[maxstate], goal;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

int vis[inf], fact[9];



bool valid(int x, int y) {
    if(x >= 0 && x < 3 && y >= 0 && y < 3) return true;
    return false;
}

const int hashSZ = 1000003;
int head[hashSZ], nxt[maxstate];


void init() {
    Set(vis, 0);
    Set(fact, 0);
    Set(head, 0);
    Set(nxt, 0);
    
    fact[0] = 1;
    _for(i, 1, 9) fact[i] = fact[i-1] * i;
}

int Hash(const State& s) {
    int val = 0;
    _for(i, 0, 9) val = val * 10 + s[i];
    return val % hashSZ;
}

void link(int id, int h) {
    nxt[id] = head[h];
    head[h] = id;
}

bool tryInsert(int id) {
    int h = Hash(nodes[id]);
    int u = head[h];
    
    while(u) {
        //
        if(Cmp(nodes[u], nodes[id]) == 0) return 0;
        u = nxt[u];
    }
    link(id, h);
    return true;
}

int bfs() {
    init();
    int front = 1, rear = 2;
    
    while (front < rear) {
        State& cur = nodes[front];
        if(Cmp(goal, cur) == 0) return front;
        
        int z;
        for(z = 0; z < 9; z++) if(!cur[z]) break;
        
        int x = z / 3, y = z % 3;
        
        _for(dir, 0, 4) {
            int nx = x + dx[dir];
            int ny = y + dy[dir];
            int nz = nx * 3 + ny;
            
            if(valid(nx, ny)) {
                State& to = nodes[rear];
                Cpy(to, cur);
                
                to[nz] = cur[z];
                to[z] = cur[nz];
                
                dist[rear] = dist[front] + 1;
                if(tryInsert(rear)) rear++;
            }
        }
        
        front++;
    }
    return 0;
}

int main() {
    freopen("input.txt", "r", stdin);
    
    _for(i, 0, 9) scanf("%d", &nodes[1][i]);
    _for(i, 0, 9) scanf("%d", &goal[i]);
    
    int ans = bfs();
    if(ans > 0) printf("%d\n", dist[ans]);
    else printf("-1\n");
    
    return 0;
}
