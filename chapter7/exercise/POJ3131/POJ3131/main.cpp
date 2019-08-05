//
//  main.cpp
//  POJ3131
//
//  Created by zhangmin chen on 2019/7/15.
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

const int N = 3;
const int maxstate = 5000000;
const int hashSZ = 5000003;

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

const string CH = "WRBE";
// const int BUFLEN = 4;
const int W = 0, R = 1, B = 2, E = 3;

const int DICE[3][3] = {
    {-1, B, R},
    {B, -1, W},
    {R, W, -1},
};

const int dx[] = {-1, 0, 1, 0};
const int dy[] = {0, -1, 0, 1};
const int UP = 0, LEFT = 1, DOWN = 2, RIGHT = 3;
// usage: dx[LEFT], dy[LEFT]

//const int revDir[] = {DOWN, RIGHT, UP, LEFT};
//const string DIR[] = {"UP", "LEFT", "DOWN", "RIGHT"};
// usage: revD = revDir[LEFT]

class CUBE {
public:
    int top, face, bottom, back, left, right;
    // set DICE[top][face] = LEFT;
    void clear() {
        top = face = bottom = back = left = right = 0;
    }
    
    bool operator!= (const CUBE& rhs) const {
        return top != rhs.top || face != rhs.face || left != rhs.left;
    }
};

typedef CUBE State[N][N];
int dist[maxstate];
State nodes[maxstate];
int head[hashSZ], nxth[maxstate];

void initHash() {
    Set(head, 0);
    Set(nxth, 0);
    Set(dist, 0);
    _for(k, 0, maxstate) {
        _for(i, 0, N) _for(j, 0, N) nodes[k][i][j].clear();
    }
}

void setPos(CUBE& cb, int _top, int _face) {
    //assert(cb.top != E);
    cb.top = _top;
    cb.face = _face;
    cb.left = DICE[_top][_face];
    
    cb.right = cb.left;
    cb.bottom = cb.top;
    cb.back = cb.face;
}

void setEmpty(CUBE& cb) {
    cb.top = cb.bottom = cb.left = cb.right = cb.face = cb.back = E;
}

CUBE Move(const CUBE& cb, int dir) {
    CUBE nxt;
    if(dir == UP) setPos(nxt, cb.face, cb.bottom);
    if(dir == DOWN) setPos(nxt, cb.back, cb.top);
    if(dir == LEFT) setPos(nxt, cb.right, cb.face);
    if(dir == RIGHT) setPos(nxt, cb.left, cb.face);
    
    return nxt;
}

int _hash(const State& st) {
    int val = 0;
    _for(i, 0, N) _for(j, 0, N) {
        val = val * 10 + st[i][j].top;
    }
    return val % hashSZ;
}

// h is hash value
void link(int id, int h) {
    nxth[id] = head[h];
    head[h] = id;
}

int cmpr(State& s1, State& s2) {
    _for(i, 0, N) _for(j, 0, N) {
        if(s1[i][j] != s2[i][j]) return 1;
    }
    return 0;
}

bool tryInsert(int id) {
    int h = _hash(nodes[id]);
    // debug(h);
    int u = head[h];
    
    while (u) {
        //
        if(cmpr(nodes[id], nodes[u]) == 0) return 0;
        u = nxth[u];
    }
    link(id, h);
    return true;
}

bool inRange(int x, int l, int r) {
    if(l > r) return inRange(x, r, l);
    return l <= x && x <= r;
}

bool valid(int x, int y) {
    return inRange(x, 0, 2) && inRange(y, 0, 2);
}

CUBE pan[N][N];

void initPan() {
    _for(i, 0, N) _for(j, 0, N) {
        CUBE cur;
        // cur.setPos(W, R);
        setPos(cur, W, R);
        pan[i][j] = cur;
    }
}

char target[N][N];
void initTar() {
    Set(target, 0);
}

void dbgPan(const CUBE pan[][N]) {
    _for(i, 0, N) {
        _for(j, 0, N) printf("%c ", CH[pan[i][j].top]);
        printf("\n");
    }
    printf("\n");
}

void dbgTar() {
    _for(i, 0, N) {
        _for(j, 0, N) printf("%c ", target[i][j]);
        printf("\n");
    }
    printf("\n");
}

void findEmpty(const CUBE pan[][N], int& ex, int& ey) {
    _for(i, 0, N) _for(j, 0, N) {
        const CUBE& cur = pan[i][j];
        if(CH[cur.top] == 'E') {
            ex = i;
            ey = j;
            return;
        }
    }
    return;
}

bool reach(const CUBE pan[][N], const char target[][N]) {
    //
    _for(i, 0, N) _for(j, 0, N) {
        //
        if(CH[pan[i][j].top] != target[i][j]) return 0;
    }
    return 1;
}

void assign(const CUBE pan[][N], State* nodes, int id) {
    _for(i, 0, N) _for(j, 0, N) {
        nodes[id][i][j] = pan[i][j];
    }
}


int bfs() {
    int front = 1, rear = 2;
    
    while (front < rear) {
        State& cur = nodes[front];
        if(reach(cur, target)) return front;
        
        int ex = -1, ey = -1;
        findEmpty(cur, ex, ey);
        assert(ex != -1 && ey != -1);
        
        _for(dir, 0, 4) {
            int nx = ex + dx[dir], ny = ey + dy[dir];
            if(!valid(nx, ny)) continue;
            
            State& to = nodes[rear];
            Cpy(to, cur);
            
            CUBE nxt = Move(cur[nx][ny], dir);
            to[nx][ny] = cur[ex][ey];
            to[ex][ey] = nxt;
            // dbgPan(to);
            
            dist[rear] = dist[front] + 1;
            if(tryInsert(rear)) rear++;
        }
        front++;
    }
    return 0;
}


// ans init as inf
// eCb is empty cube

// remember the parent of empty block



int main() {
    freopen("input.txt", "r", stdin);
    int ex, ey;
    int kase = 1;
    while (scanf("%d%d", &ex, &ey) == 2 && ex && ey) {
        initHash();
        initPan();
        initTar();
        
        setEmpty(pan[ey - 1][ex -1]);
        assign(pan, nodes, 1);
        
        _for(i, 0, N) _for(j, 0, N) {
            cin >> target[i][j];
        }
        
        printf("Case: %d\n", kase++);
        // input finished()
        
        //dbgPan(nodes[1]);
        // dbgTar();
        
        int ans = bfs();
        if(dist[ans] <= 30) printf("%d\n", dist[ans]);
        else printf("-1\n");
        // cout << "========" << endl;
        
    }
}
