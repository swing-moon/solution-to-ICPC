//
//  main.cpp
//  POJ3131-2
//
//  Created by zhangmin chen on 2019/7/19.
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
#include <bitset>
#include <assert.h>

using namespace std;
typedef long long llong;
typedef set<int>::iterator ssii;


#define Cmp(a, b) memcmp(a, b, sizeof(b))
#define Cpy(a, b) memcpy(a, b, sizeof(a))
#define Set(a, v) memset(a, v, sizeof(a))
#define debug(x) cout << #x << ": " << x << endl
#define _forS(i, l, r) for(set<int>::iterator i = (l); i != (r); i++)
#define _rep(i, l, r) for(int i = (l); i <= (r); i++)
#define _for(i, l, r) for(int i = (l); i < (r); i++)
#define _forDown(i, l, r) for(int i = (l); i >= r; i--)
#define debug_(ch, i) printf(#ch"[%d]: %d\n", i, ch[i])
#define debug_m(mp, p) printf(#mp"[%d]: %d\n", p->first, p->second)
#define debugS(str) cout << "dbg: " << str << endl;
#define debugArr(arr, x, y) _for(i, 0, x) { _for(j, 0, y) printf("%c", arr[i][j]); printf("\n"); }
#define _forPlus(i, l, d, r) for(int i = (l); i + d < (r); i++)

const int BASE[] = {1, 6, 36, 216, 1296, 7776, 46656, 279936, 1679616};
const int maxn = 1679616 + 10;

class Node {
public:
    int st[9];
    int ep, dta, dist;
};

queue<Node> que1, que2;
Node s1, s2;

bool vis1[maxn][9];
bool vis2[maxn][9];
char tar[9];

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};

void initVis() {
    Set(vis1, 0);
    Set(vis2, 0);
}

void initQue() {
    while(!que1.empty()) que1.pop();
    while(!que2.empty()) que2.pop();
}

/*
 if(top == W && face == R) return 0;
 if(top == W && face == B) return 1;
 if(top == R && face == W) return 2;
 if(top == R && face == B) return 3;
 if(top == B && face == W) return 4;
 if(top == B && face == R) return 5;
 return -1;
 
 */

// const int Move[0][dir]
// const int Move[1][dir]
// UP LEFT DOWN RIGHT
// Move[0][UP] = (R, W)  Move[0][LEFT] = (B, R) Move[0][DOWN] = (R, W)  Move[0][RIGHT] = (B, R)
// Move[1][UP] = (B, W)  Move[1][LEFT] = (R, B)
// Move[2][UP] = (W, R)  Move[2][LEFT] = (B, W)
// Move[3][UP] = (B, R)  Move[3][LEFT] = (W, B)
// Move[4][UP] = (W, B)  Move[4][LEFT] = (R, W)
// Move[5][UP] = (R, B)  Move[5][LEFT] = (W, R)

const int Move[6][4] = {
    {2, 5, 2, 5},
    {4, 3, 4, 3},
    {0, 4, 0, 4},
    {5, 1, 5, 1},
    {1, 2, 1, 2},
    {3, 0, 3, 0}
};
// usage: int newCode = Move[oldCode][dir]

int cal(const Node x) {
    int k = 0, ans = 0;
    _for(i, 0, 9) {
        if(i != x.ep) ans = ans + x.st[i] * BASE[k++];
    }
    return ans;
}

bool valid(int x, int y) {
    if(0 <= x && x < 3 && 0 <= y && y < 3) return 1;
    return 0;
}

void dfs(Node& s2, int d) {
    if(d == 9) {
        s2.dist = 0;
        s2.dta = cal(s2);
        que2.push(s2);
        vis2[s2.dta][s2.ep] = true;
        return;
    }
    
    if(tar[d] == 'W') {
        s2.st[d] = 0;
        dfs(s2, d + 1);
        
        s2.st[d] = 1;
        dfs(s2, d + 1);
    }
    else if(tar[d] == 'R') {
        s2.st[d] = 2;
        dfs(s2, d + 1);
        
        s2.st[d] = 3;
        dfs(s2, d + 1);
    }
    else if(tar[d] == 'B') {
        s2.st[d] = 4;
        dfs(s2, d + 1);
        
        s2.st[d] = 5;
        dfs(s2, d + 1);
    }
    else {
        s2.st[d] = 6;
        dfs(s2, d + 1);
    }
}

bool bfs(int& ans) {
    const int DEP1 = 21, DEP2 = 9;
    int cnt1 = 0, cnt2 = 0, flag = 0;
    
    while (true) {
        flag = 0;
        
        while (!que1.empty() && que1.front().dist <= cnt1) {
            flag = 1;
            //
            Node x = que1.front(); que1.pop();
            if(vis2[x.dta][x.ep]) {
                ans = x.dist + cnt2;
                return true;
            }
            
            if(x.dist >= DEP1) continue;
            
            _for(dir, 0, 4) {
                Node nxt = x;
                int ex = x.ep / 3, ey = x.ep % 3;
                int nx = ex + dx[dir], ny = ey + dy[dir];
                
                if(!valid(nx, ny)) continue;
                
                int np = nx * 3 + ny;
                nxt.ep = np;
                
                nxt.st[x.ep] = Move[nxt.st[nxt.ep]][dir];
                nxt.st[nxt.ep] = 6;
                
                nxt.dist = x.dist + 1;
                nxt.dta = cal(nxt);
                
                if(!vis1[nxt.dta][nxt.ep]) {
                    vis1[nxt.dta][nxt.ep] = true;
                    que1.push(nxt);
                }
            }
        }
        if(cnt1 < DEP1) cnt1++;
        
        while (!que2.empty() && que2.front().dist <= cnt2) {
            flag = 1;
            //
            Node x = que2.front(); que2.pop();
            if(vis1[x.dta][x.ep]) {
                ans = x.dist + cnt1;
                return true;
            }
            
            if(x.dist >= DEP2) continue;
            
            _for(dir, 0, 4) {
                Node nxt = x;
                int ex = x.ep / 3, ey = x.ep % 3;
                int nx = ex + dx[dir], ny = ey + dy[dir];
                
                if(!valid(nx, ny)) continue;
                
                int np = nx * 3 + ny;
                nxt.ep = np;
                
                nxt.st[x.ep] = Move[nxt.st[nxt.ep]][dir];
                nxt.st[nxt.ep] = 6;
                
                nxt.dist = x.dist + 1;
                nxt.dta = cal(nxt);
                
                if(!vis2[nxt.dta][nxt.ep]) {
                    vis2[nxt.dta][nxt.ep] = true;
                    que2.push(nxt);
                }
            }
        }
        if(cnt2 < DEP2) cnt2++;
        if(!flag) return false;
    }
}


int main() {
    freopen("input.txt", "r", stdin);
    
    int ex, ey;
    while (scanf("%d%d", &ex, &ey) != EOF && ex && ey) {
        initVis();
        ex--; ey--;
        int ep = ey * 3 + ex;
        
        initQue();
        
        // get bfs s1
        _for(i, 0, 9) {
            if(i == ep) {
                //
                s1.st[i] = 6;
                s1.ep = i;
            }
            else s1.st[i] = 0;
        }
        
        s1.dist = 0;
        s1.dta = cal(s1);
        vis1[s1.dta][s1.ep] = true;
        que1.push(s1);
        // s1 finished
        
        _for(i, 0, 9) {
            char ch;
            cin >> ch;
            if(ch == 'E') s2.ep = i;
            tar[i] = ch;
        }
        
        dfs(s2, 0);
        
        //debug(que1.size());
        //debug(que2.size());
        //printf("====\n");
        
        int ans = 0;
        if(bfs(ans)) printf("%d\n", ans);
        else printf("-1\n");
    }
}
