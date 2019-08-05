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
const int N = 3;

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;
const int revDir[] = {DOWN, RIGHT, UP, LEFT};

// WRB
const int W = 0, R = 1, B = 2;

int CUBE(const int top, const int face) {
    if(top == W && face == R) return 0;
    if(top == W && face == B) return 1;
    if(top == R && face == W) return 2;
    if(top == R && face == B) return 3;
    if(top == B && face == W) return 4;
    if(top == B && face == R) return 5;
    return -1;
}



int tar[N * N];
vector<int> tarST[3];

void init() {
    Set(tar, 0);
    _for(i, 0, 3) tarST[i].clear();
    
    tarST[W].push_back(R);
    tarST[W].push_back(B);
    
    tarST[R].push_back(W);
    tarST[R].push_back(B);
    
    tarST[B].push_back(W);
    tarST[B].push_back(R);
}
// first fill the blank

const string CH = "WRB";
void dbgTar() {
    _for(i, 0, N * N) {
        if(i != 0 && i % 3 == 0) printf("\n");
        if(tar[i] != -1) printf("%c ", CH[tar[i]]);
        else printf("E ");
    }
    printf("\n");
}

class Node {
public:
    int ep, val, dist;
    Node(int e = 0, int v = 0, int d = 0) : ep(e), val(v), dist(d) {}
};

const int maxstate = 1679616;

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

bool inRange(int x, int l, int r) {
    if(l > r) return inRange(x, r, l);
    return l <= x && x <= r;
}

bool valid(int x, int y) {
    return inRange(x, 0, N - 1) && inRange(y, 0, N - 1);
}


queue<Node> que1;
queue<Node> que2;

int vis1[9][maxstate];
int vis2[9][maxstate];

void initVis() {
    Set(vis1, 0);
    Set(vis2, 0);
    
    while(!que1.empty()) que1.pop();
    while(!que2.empty()) que2.pop();
}

void dfs(int d, int dta, int base, const int ep) {
    if(d > 8) {
        if(!vis2[ep][dta]) {
            vis2[ep][dta] = 1;
            // debug(dta);
            Node x(ep, dta, 0);
            que2.push(x);
        }
        return;
    }
    
    if(tar[d] == -1) dfs(d + 1, dta, base, ep);
    else {
        int sta = tar[d] * BASE[base];
        dfs(d + 1, dta + sta, base + 1, ep);
        
        sta = (tar[d] + 1) * BASE[base];
        dfs(d + 1, dta + sta, base + 1, ep);
    }
}



int getDig(const int dta, int k) {
    if(k == 0) return dta % 6;
    else {
        int base = 1;
        _for(i, 0, k) base *= 6;
        return (dta / base) % 6;
    }
}

// dig[9]



int update(const int& dta, const int& dir, const int& ep, const int& np, const int dig[]) {
    if(dir == LEFT || dir == RIGHT) {
        int k = min(ep, np);
        int v = dig[k];
        int nxtv = Move[v][revDir[dir]];
        
        int ndta = dta;
        ndta = ndta - v * BASE[k] + nxtv * BASE[k];
        return ndta;
    }
    else if(dir == UP) {
        int ndta = dta;
        int v = dig[np];
        int nxtv = Move[v][revDir[dir]];
        
        _for(i, np, ep) ndta -= (dig[i] * BASE[i]);
        ndta += nxtv * BASE[ep - 1];
        _for(i, np + 1, ep) ndta += (dig[i] * BASE[i - 1]);
        return ndta;
    }
    else if(dir == DOWN) {
        int ndta = dta;
        int v = dig[np - 1];
        int nxtv = Move[v][revDir[dir]];
        
        _for(i, ep, np) ndta -= (dig[i] * BASE[i]);
        ndta += nxtv * BASE[ep];
        _for(i, ep, np - 1) ndta += (dig[i] * BASE[i + 1]);
        return ndta;
    }
    return -1;
}

void initBfs(int ep) {
    assert(que1.empty());
    Node cur(ep, 0, 0);
    vis1[ep][0] = 1;
    que1.push(cur);
}

bool bfs(int& ans) {
    //
    const int DEP1 = 21, DEP2 = 9;
    int cnt1 = 0, cnt2 = 0;
    
    int flag = 0;
    while (true) {
        flag = 0;
        while (!que1.empty() && que1.front().dist <= cnt1) {
            flag = 1;
            //
            Node x = que1.front(); que1.pop();
            int _ep = x.ep;
            int _dist = x.dist;
            int _dta = x.val;
            
            
            if(vis2[_ep][_dta]) {
                ans = _dist + cnt2;
                return true;
            }
            
            if(_dist >= DEP1) continue;
            
            int dig[8];
            _for(i, 0, 8) dig[i] = getDig(_dta, i);
            
            _for(dir, 0, 4) {
                int ex = _ep / 3, ey = _ep % 3;
                int nx = ex + dx[dir], ny = ey + dy[dir];
                int np = nx * 3 + ny;
                
                if(!valid(nx, ny)) continue;
                
                
                int _ndta = update(_dta, dir, _ep, np, dig);
                
                if(!vis1[np][_ndta]) {
                    vis1[np][_ndta] = 1;
                    Node nxt(np, _ndta, _dist + 1);
                    que1.push(nxt);
                }
            }
        }
        if(cnt1 < DEP1) cnt1++;
        
        while (!que2.empty() && que2.front().dist <= cnt2) {
            flag = 1;
            //
            Node x = que2.front(); que2.pop();
            int _ep = x.ep;
            int _dist = x.dist;
            int _dta = x.val;
            
            if(vis1[_ep][_dta]) {
                ans = _dist + cnt1;
                return true;
            }
            
            if(_dist >= DEP2) continue;
            
            int dig[8];
            _for(i, 0, 8) dig[i] = getDig(_dta, i);
            
            _for(dir, 0, 4) {
                int ex = _ep / 3, ey = _ep % 3;
                int nx = ex + dx[dir], ny = ey + dy[dir];
                int np = nx * 3 + ny;
                
                if(!valid(nx, ny)) continue;
                
                
                int _ndta = update(_dta, dir, _ep, np, dig);
                //debug(_ndta);
                
                assert(np >= 0);
                assert(_ndta != -1);
                if(!vis2[np][_ndta]) {
                    vis2[np][_ndta] = 1;
                    Node nxt(np, _ndta, _dist + 1);
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
    
    // int kase = 1;
    while (scanf("%d%d", &ex, &ey) == 2 && ex && ey) {
        // printf("Case: %d\n", kase++);
        // printf("========\n");
        
        init();
        
        ex--; ey--;
        int ep = ey * 3 + ex;
        
        int tep = -1;
        
        char s[3];
        _for(i, 0, N) _for(j, 0, N) {
            scanf("%s", s);
            
            int k = i * 3 + j;
            if(s[0] == 'W') tar[k] = 0;
            else if(s[0] == 'R') tar[k] = 2;
            else if(s[0] == 'B') tar[k] = 4;
            else {
                tep = k;
                tar[k] = -1;
            }
        }
        // empty place is indicated as -1
        // input target finished
        
        // dbgTar();
        
        initVis();
        dfs(0, 0, 0, tep);
        
        
        
        initBfs(ep);
        int ans = 0;
        if(bfs(ans)) printf("%d\n", ans);
        else printf("-1\n");
    }
}
